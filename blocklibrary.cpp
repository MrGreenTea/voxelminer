#include "core/bind/core_bind.h"
#include "tools/editor/io_plugins/editor_atlas.h"

#include "blocklibrary.h"

String BlockLibrary::get_texture_key(String name, int side) const{
    return name + ":" + itos(side);
}

DVector<Vector2> BlockLibrary::get_uvs(String block_name, CommonData::Side side) const {
    const int right_order[6] = {0,3,2,0,2,1};
    const int flipped_order[6] = {2,1,0,2,0,3};
    const int* order = (side%2==0) ? flipped_order : right_order;
    Rect2 uv_rect;
    if (uv_map.has(get_texture_key(block_name, side))) {
        uv_rect = uv_map[get_texture_key(block_name, side)];
    }
    else {
        uv_rect = uv_map[block_name];
    }

    Vector2 bottom_left = uv_rect.get_pos();
    Vector2 top_right = uv_rect.get_pos() + uv_rect.get_size();
    Vector2 bottom_right = Vector2(top_right.x, bottom_left.y);
    Vector2 top_left = Vector2(bottom_left.x, top_right.y);
    // const Vector2 uv_list[4] = {Vector2(0,0), Vector2(1,0), Vector2(1,1), Vector2(0,1)};
    const Vector2 uv_list[4] = {bottom_left, bottom_right, top_right, top_left};
    DVector<Vector2> new_uvs;
    new_uvs.resize(6);
    new_uvs.set(0, uv_list[order[0]]);
    new_uvs.set(1, uv_list[order[1]]);
    new_uvs.set(2, uv_list[order[2]]);
    new_uvs.set(3, uv_list[order[3]]);
    new_uvs.set(4, uv_list[order[4]]);
    new_uvs.set(5, uv_list[order[5]]);
    return new_uvs;
}

void BlockLibrary::generate_texture_atlas() {
    Map<int, String > texture_map;
    Vector<Ref<ImageTexture> > textures;
    Vector<Size2i> texture_sizes;
    // gather all textures and side textures
    for (Map<String, Ref<BlockData> >::Element* e = block_map.front(); e; e=e->next()) {
        String name = e->key();
        Ref<BlockData> block_data = e->get();
        int index = textures.size();
        texture_map[index] = name;
        Ref<ImageTexture> texture = block_data->get_default_texture();
        textures.push_back(texture);
        texture_sizes.push_back(Size2i(texture->get_width(), texture->get_height()));
        for (int i = 0; i < 6; i++) {
            BlockData::Sides side = static_cast<BlockData::Sides>(i);
            Ref<ImageTexture> side_texture = block_data->_get_side_texture_in_editor(side);
            if (side_texture.is_valid()) {
                texture_map[textures.size()] = get_texture_key(name, side);
                textures.push_back(side_texture);
                texture_sizes.push_back(Size2i(side_texture->get_width(), side_texture->get_height()));
            }
        }
    }

    Vector<Point2i> texture_positions;
    Size2i atlas_size;
    EditorAtlas::fit(texture_sizes, texture_positions, atlas_size);
    Image atlas;
    atlas.create(atlas_size.width, atlas_size.height, 0, Image::FORMAT_RGBA);
    for (int i = 0; i < textures.size(); i++) {
        Image texture = textures[i]->get_data();
        Point2i base = texture_positions[i];
        Size2i texture_size = texture_sizes[i];
        Rect2 src_rect = Rect2(Point2(0, 0), texture_size);
        Point2 uv_base = Point2(base.x / (float)atlas_size.width, base.y / (float)atlas_size.height);
        Size2 uv_size = Size2(texture_size.x / (float)atlas_size.width, texture_size.y / (float)atlas_size.height);
        Rect2 uv_rect = Rect2(uv_base, uv_size);
        uv_map[texture_map[i]] = uv_rect;
        atlas.blit_rect(texture, src_rect, base);
    }
    atlas.save_png("res://atlas.png");
    Ref<ImageTexture> new_atlas = memnew(ImageTexture);
    new_atlas->create_from_image(atlas, 0);
    atlas_texture = new_atlas;
}

List<String> BlockLibrary::get_all_block_names() {
    List<String> block_names;
    for (Map<String, Ref<BlockData> >::Element* e=block_map.front(); e; e=e->next()) {
        block_names.push_back(e->key());
    }
    return block_names;
}

Ref<BlockData> BlockLibrary::get_added_block_data() {
    return NULL;
}

void BlockLibrary::set_block_data(Ref<BlockData> data) {
    StringName block_name = data->get_name();
    block_map[block_name] = data;
}

Ref<BlockData> BlockLibrary::get_block_data(String block_name) const {
    ERR_FAIL_COND_V(!block_map.has(block_name), NULL)
    return block_map[block_name];
}

Ref<Block> BlockLibrary::get_new_block(const String block_name) {
    Ref<BlockData> block_data = get_block_data(block_name);
    ERR_FAIL_COND_V(block_data.is_null(), NULL)
    Ref<Block> new_block =  memnew(Block);
    new_block->set_block_data(block_data);
    return new_block;

}

Ref<FixedMaterial> BlockLibrary::get_chunk_material() {
    if (!chunk_material.is_valid()) {
        Ref<FixedMaterial> new_material = memnew(FixedMaterial);
        // Ref<ImageTexture> texture = atlas_texture;
        new_material->set_texture(FixedMaterial::PARAM_DIFFUSE, atlas_texture);
        chunk_material = new_material;
    }
    return chunk_material;
}

bool BlockLibrary::_set(const StringName &p_name, const Variant &p_value) {
    set_block_data(p_value);
    return true;
}

bool BlockLibrary::_get(const StringName &p_name, Variant &r_ret) const {
    if (p_name == "add_block") {
        r_ret = Variant();
        return true;
    }
    else {
        if (!block_map.has(p_name)) {
            ERR_EXPLAIN("BlockLibrary has no entry for block with name " + p_name);
            return false;
        }
        r_ret = get_block_data(p_name);
        return true;
    }
}

void BlockLibrary::_get_property_list( List<PropertyInfo> *p_list) const {
    for(Map<String, Ref<BlockData> >::Element *E=block_map.front();E;E=E->next()) {
        p_list->push_back(PropertyInfo(Variant::OBJECT, E->key(), PROPERTY_HINT_RESOURCE_TYPE, "BlockData"));
    }
}

void BlockLibrary::_bind_methods() {
    ObjectTypeDB::bind_method(_MD("add_block_data", "data:BlockData"), &BlockLibrary::set_block_data);
    ObjectTypeDB::set_method_flags("BlockLibrary", "add_block_data", METHOD_FLAG_EDITOR);
    ObjectTypeDB::bind_method(_MD("get_added_block_data:BlockData"), &BlockLibrary::get_added_block_data);
    ObjectTypeDB::set_method_flags("BlockLibrary", "get_added_block_data", METHOD_FLAG_EDITOR);

    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "add_block", PROPERTY_HINT_RESOURCE_TYPE, "BlockData"), "add_block_data", "get_added_block_data");
}

BlockLibrary::BlockLibrary()
{

}

