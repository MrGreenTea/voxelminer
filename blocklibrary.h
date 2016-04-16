#ifndef BLOCKLIBRARY_H
#define BLOCKLIBRARY_H

#include "scene/resources/material.h"
#include "block.h"
#include "blockdata.h"

class BlockLibrary : public Resource
{
    OBJ_TYPE(BlockLibrary, Resource)
private:
    String block_library_path;
    Map<String, Ref<BlockData> > block_map;
    Map<String, Rect2> uv_map;
    Ref<ImageTexture> atlas_texture;
    Ref<FixedMaterial> chunk_material;
    String get_texture_key(String name, int side) const;
protected:
    Ref<BlockData> get_added_block_data();
    static void _bind_methods();
    bool _set(const StringName& p_name, const Variant& p_value);
    bool _get(const StringName& p_name,Variant &r_ret) const;
    void _get_property_list( List<PropertyInfo> *p_list) const;
public:
    void generate_texture_atlas();
    DVector<Vector2> get_uvs(String block_name, CommonData::Side side) const;
    void set_block_data(Ref<BlockData> data);
    Ref<BlockData> get_block_data(String block_name) const;
    Ref<Block> get_new_block(String block_name);
    Ref<FixedMaterial> get_chunk_material();
    List<String> get_all_block_names();
    BlockLibrary();
};

#endif // BLOCKLIBRARY_H
