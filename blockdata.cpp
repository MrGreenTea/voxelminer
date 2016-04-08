#include "blockdata.h"
Ref<Texture> BlockData::get_default_texture() {
    return default_texture;
}

void BlockData::set_default_texture(Ref<Texture> texture) {
    default_texture = texture;
}

Ref<Texture> BlockData::get_texture(Sides side) {
    ERR_FAIL_INDEX_V(side, 6, NULL);
    return textures[side];
}

void BlockData::set_texture(Sides side, Ref<Texture> texture) {
    ERR_FAIL_INDEX(side, 6)
    textures[side] = texture;
}

bool BlockData::has_custom_mesh() {
    return custom_mesh != NULL;
}

Ref<Mesh> BlockData::get_custom_mesh() {
    return custom_mesh;
}

void BlockData::set_custom_mesh(Ref<Mesh> mesh) {
    custom_mesh = mesh;
}

bool BlockData::is_solid() {
    return solid;
}

void BlockData::set_solid(bool value) {
    solid = value;
}

bool BlockData::is_opaque() {
    return opaque;
}

void BlockData::set_opqaue(bool value) {
    opaque = value;
}


void BlockData::_bind_methods(){

    ObjectTypeDB::bind_method(_MD("set_default_texture", "texture:Texture"), &BlockData::set_default_texture);
    ObjectTypeDB::bind_method(_MD("get_default_texture:Texture"), &BlockData::get_default_texture);
    ObjectTypeDB::bind_method(_MD("set_texture", "side", "texture:Texture"), &BlockData::set_texture);
    ObjectTypeDB::bind_method(_MD("get_texture:Texture", "side"), &BlockData::get_texture);
    ObjectTypeDB::bind_method(_MD("has_custom_mesh"), &BlockData::has_custom_mesh);
    ObjectTypeDB::bind_method(_MD("set_custom_mesh", "mesh:Mesh"), &BlockData::set_custom_mesh);
    ObjectTypeDB::bind_method(_MD("get_custom_mesh"), &BlockData::get_custom_mesh);
    ObjectTypeDB::bind_method(_MD("set_solid","value"),&BlockData::set_solid);
    ObjectTypeDB::bind_method(_MD("is_solid"),&BlockData::is_solid);
    ObjectTypeDB::bind_method(_MD("set_opaque","value"),&BlockData::set_opqaue);
    ObjectTypeDB::bind_method(_MD("is_opaque"),&BlockData::is_opaque);

    ADD_PROPERTY( PropertyInfo(Variant::OBJECT, "default_texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture"), _SCS("set_default_texture"),_SCS("get_default_texture"));
    ADD_PROPERTYINO( PropertyInfo(Variant::OBJECT, "top_texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture"), _SCS("set_texture"), _SCS("get_texture"), TOP);
    ADD_PROPERTYINO( PropertyInfo(Variant::OBJECT, "bottom_texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture"), _SCS("set_texture"), _SCS("get_texture"), BOTTOM);
    ADD_PROPERTYINO( PropertyInfo(Variant::OBJECT, "right_texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture"), _SCS("set_texture"), _SCS("get_texture"), RIGHT);
    ADD_PROPERTYINO( PropertyInfo(Variant::OBJECT, "left_texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture"), _SCS("set_texture"), _SCS("get_texture"), LEFT);
    ADD_PROPERTYINO( PropertyInfo(Variant::OBJECT, "back_texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture"), _SCS("set_texture"), _SCS("get_texture"), BACK);
    ADD_PROPERTYINO( PropertyInfo(Variant::OBJECT, "front_texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture"), _SCS("set_texture"), _SCS("get_texture"), FRONT);
    ADD_PROPERTYNO( PropertyInfo(Variant::OBJECT, "custom_mesh", PROPERTY_HINT_RESOURCE_TYPE, "Mesh"), _SCS("set_custom_mesh"), _SCS("get_custom_mesh"));
    ADD_PROPERTY( PropertyInfo(Variant::BOOL,"solid"), _SCS("set_solid"),_SCS("is_solid") );
    ADD_PROPERTY( PropertyInfo(Variant::BOOL,"opaque"), _SCS("set_opaque"),_SCS("is_opaque") );

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

