#ifndef BLOCK_H
#define BLOCK_H

#include "reference.h"
#include "blockdata.h"


class Block : public Reference
{
    OBJ_TYPE(Block, Reference)
    Dictionary custom_data;
protected:
    static void _bind_methods();
public:
    Ref<BlockData> block_data;
    Ref<BlockData> get_block_data();
    void set_block_data(Ref<BlockData> data);
    void set_custom_data(String key, Variant value);
    void set_custom_data_dict(Dictionary dict);
    Dictionary get_custom_data_dict();
    Variant get_custom_data(String key);
    Block();
};

#endif // BLOCK_H
