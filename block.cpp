#include "block.h"

String Block::get_name() {
    return block_data->get_name();
}

void Block::set_block_data(Ref<BlockData> data) {
    block_data = data;
}

Ref<BlockData> Block::get_block_data() {
    return block_data;
}

void Block::set_custom_data(String key, Variant value) {
    custom_data[key] = value;
}

Variant Block::get_custom_data(String key) {
    if (custom_data.has(key)) {
        return custom_data[key];
    }
    if (block_data->custom_data.has(key)) {
        return block_data->custom_data[key];
    }
    return Variant();
}

void Block::set_custom_data_dict(Dictionary dict) {
    custom_data = dict;
}

Dictionary Block::get_custom_data_dict() {
    return custom_data;
}

void Block::_bind_methods() {
    ObjectTypeDB::bind_method(_MD("set_block_data", "block_data:BlockData"), &Block::set_block_data);
    ObjectTypeDB::bind_method(_MD("get_block_data:BlockData"), &Block::get_block_data);
    ObjectTypeDB::bind_method(_MD("set_custom_data", "key:String", "value:Variant"), &Block::set_custom_data);
    ObjectTypeDB::bind_method(_MD("get_custom_data:Variant", "key:String"), &Block::get_custom_data);
    ObjectTypeDB::bind_method(_MD("set_custom_data_dict", "dict:Dictionary"), &Block::set_custom_data_dict);
    ObjectTypeDB::bind_method(_MD("get_custom_data_dict:Dictionary"), &Block::get_custom_data_dict);

    ADD_PROPERTY( PropertyInfo(Variant::DICTIONARY, "custom_data"), _SCS("set_custom_data_dict"),_SCS("get_custom_data_dict"));
}

Block::Block()
{

}

