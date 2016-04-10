#include "blockdata.h"
#include "core/bind/core_bind.h"


Ref<Texture> BlockData::get_default_texture() {
    return default_texture;
}

void BlockData::set_default_texture(Ref<Texture> texture) {
    default_texture = texture;
}

Ref<Texture> BlockData::_get_side_texture_in_editor(Sides side) {
    // in-editor only getter for side texture properties
    ERR_FAIL_INDEX_V(side, 6, NULL);
    return textures[side];
}

Ref<Texture> BlockData::get_texture(Sides side) {
    ERR_FAIL_INDEX_V(side, 6, NULL);
    if (textures[side] != NULL) {
        return textures[side];
    }
    else {
        return default_texture;
    }
}

void BlockData::set_texture(Sides side, Ref<Texture> texture) {
    ERR_FAIL_INDEX(side, 6)
    textures[side] = texture;
}

bool BlockData::has_custom_mesh() {
    return custom_mesh != NULL;
}

String BlockData::get_custom_mesh_path() {
    return custom_mesh_path;
}

void BlockData::set_custom_mesh_path(String path) {
    set_opqaue(false);
    set_solid(false);
    custom_mesh_path = path;
}

Spatial* BlockData::get_custom_mesh() {
    return custom_mesh;
}

bool BlockData::is_solid() {
    if (has_custom_mesh()) {
        return false;
    }
    return solid;
}

void BlockData::set_solid(bool value) {
    if (!has_custom_mesh()) {
        solid = value;
    }
}

bool BlockData::is_opaque() {
    if (has_custom_mesh()) {
        return false;
    }
    return opaque;
}

void BlockData::set_opqaue(bool value) {
    if (!has_custom_mesh()) {
        opaque = value;
    }
}

void BlockData::set_custom_data_dict(Dictionary dict) {
    custom_data = dict;
}

Dictionary BlockData::get_custom_data_dict() {
    return custom_data;
}

void BlockData::set_custom_data_path(String path) {
    custom_data_file_path = path;
    _File json_file = _File();
    Error err = json_file.open(path, _File::READ);
    custom_data.clear();
    if (err == OK) {
        custom_data.parse_json(json_file.get_as_text());
    }
    json_file.close();
}

String BlockData::get_custom_data_path() {
    return custom_data_file_path;
}

void BlockData::_bind_methods(){

    ObjectTypeDB::bind_method(_MD("set_default_texture", "texture:Texture"), &BlockData::set_default_texture);
    ObjectTypeDB::bind_method(_MD("get_default_texture:Texture"), &BlockData::get_default_texture);
    ObjectTypeDB::bind_method(_MD("set_texture", "side", "texture:Texture"), &BlockData::set_texture);
    ObjectTypeDB::bind_method(_MD("get_texture:Texture", "side"), &BlockData::get_texture);
    ObjectTypeDB::bind_method(_MD("_get_side_texture_in_editor", "side"), &BlockData::_get_side_texture_in_editor);
    ObjectTypeDB::set_method_flags("BlockData", "_get_side_texture_in_editor", METHOD_FLAG_EDITOR);
    ObjectTypeDB::bind_method(_MD("set_custom_mesh_path", "path"), &BlockData::set_custom_mesh_path);
    ObjectTypeDB::bind_method(_MD("get_custom_mesh_path"), &BlockData::get_custom_mesh_path);
    ObjectTypeDB::bind_method(_MD("has_custom_mesh"), &BlockData::has_custom_mesh);
    //ObjectTypeDB::bind_method(_MD("set_custom_mesh", "mesh"), &BlockData::set_custom_mesh);
    ObjectTypeDB::bind_method(_MD("get_custom_mesh:Spatial"), &BlockData::get_custom_mesh);
    ObjectTypeDB::bind_method(_MD("set_solid","value"),&BlockData::set_solid);
    ObjectTypeDB::bind_method(_MD("is_solid"),&BlockData::is_solid);
    ObjectTypeDB::bind_method(_MD("set_opaque","value"),&BlockData::set_opqaue);
    ObjectTypeDB::bind_method(_MD("is_opaque"),&BlockData::is_opaque);
    ObjectTypeDB::bind_method(_MD("set_custom_data_dict", "path:String"), &BlockData::set_custom_data_dict);
    ObjectTypeDB::bind_method(_MD("get_custom_data_dict:Dictionary"), &BlockData::get_custom_data_dict);
    ObjectTypeDB::bind_method(_MD("set_custom_data_path", "path:String"), &BlockData::set_custom_data_path);
    ObjectTypeDB::bind_method(_MD("get_custom_data_path:String"), &BlockData::get_custom_data_path);

    ADD_PROPERTY( PropertyInfo(Variant::OBJECT, "default_texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture"), _SCS("set_default_texture"),_SCS("get_default_texture"));
    ADD_PROPERTYINZ( PropertyInfo(Variant::OBJECT, "top_texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture"), _SCS("set_texture"), _SCS("_get_side_texture_in_editor"), TOP);
    ADD_PROPERTYINZ( PropertyInfo(Variant::OBJECT, "bottom_texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture"), _SCS("set_texture"), _SCS("_get_side_texture_in_editor"), BOTTOM);
    ADD_PROPERTYINZ( PropertyInfo(Variant::OBJECT, "right_texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture"), _SCS("set_texture"), _SCS("_get_side_texture_in_editor"), RIGHT);
    ADD_PROPERTYINZ( PropertyInfo(Variant::OBJECT, "left_texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture"), _SCS("set_texture"), _SCS("_get_side_texture_in_editor"), LEFT);
    ADD_PROPERTYINZ( PropertyInfo(Variant::OBJECT, "back_texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture"), _SCS("set_texture"), _SCS("_get_side_texture_in_editor"), BACK);
    ADD_PROPERTYINZ( PropertyInfo(Variant::OBJECT, "front_texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture"), _SCS("set_texture"), _SCS("_get_side_texture_in_editor"), FRONT);
    ADD_PROPERTYNZ( PropertyInfo(Variant::STRING, "custom_mesh", PROPERTY_HINT_FILE, "scn,res,xscn,xml,tscn"), _SCS("set_custom_mesh_path"), _SCS("get_custom_mesh_path"));
    ADD_PROPERTYNO( PropertyInfo(Variant::BOOL,"solid"), _SCS("set_solid"),_SCS("is_solid") );
    ADD_PROPERTYNO( PropertyInfo(Variant::BOOL,"opaque"), _SCS("set_opaque"),_SCS("is_opaque") );
    ADD_PROPERTYNZ( PropertyInfo(Variant::STRING, "custom_data", PROPERTY_HINT_FILE, "json"), _SCS("set_custom_data_path"),_SCS("get_custom_data_path"));

    BIND_CONSTANT(TOP);
    BIND_CONSTANT(BOTTOM);
    BIND_CONSTANT(RIGHT);
    BIND_CONSTANT(LEFT);
    BIND_CONSTANT(BACK);
    BIND_CONSTANT(FRONT);


}

BlockData::BlockData()
{
    solid = true;
    opaque = true;
}

