#include "chunk.h"
#include "math/math_funcs.h"

void Chunk::set_dimensions(Vector3 dims) {
    if (dims != dimensions) {
        dimensions = dims.floor();
        chunkBlocks = memnew_arr(Ref<Block>, dimensions.x*dimensions.y*dimensions.z);
        chunkBlocksArraySize = dimensions.x*dimensions.y*dimensions.z;
    }
}

Vector3 Chunk::get_dimensions() {
    return dimensions;
}

bool Chunk::is_uniform() {
    return (dimensions.x == dimensions.y and dimensions.x == dimensions.z);
}

int Chunk::vector_to_index(const Vector3 vector) {
    return vector.x + vector.y * dimensions.y + vector.z * dimensions.y * dimensions.z;
}

Ref<Block> Chunk::get_block(const Vector3 position) {
    int index = vector_to_index(position);
    ERR_FAIL_INDEX_V(index, chunkBlocksArraySize, NULL);
    return chunkBlocks[index];
}

void Chunk::set_block(const Vector3 position, Ref<Block> block) {
    int index = vector_to_index(position);
    ERR_FAIL_INDEX(index, chunkBlocksArraySize);
    chunkBlocks[index] = block;
}

void Chunk::_bind_methods() {
    ObjectTypeDB::bind_method(_MD("set_block", "position:Vector3", "block:Block"), &Chunk::set_block);
    ObjectTypeDB::bind_method(_MD("get_block:Block", "position:Vector3"), &Chunk::get_block);
    ObjectTypeDB::bind_method(_MD("set_dimensions", "dimensions:Vector3"), &Chunk::set_dimensions);
    ObjectTypeDB::bind_method(_MD("get_dimensions:Vector3"), &Chunk::get_dimensions);
    ObjectTypeDB::bind_method(_MD("is_uniform"), &Chunk::is_uniform);

    ADD_PROPERTY( PropertyInfo(Variant::VECTOR3, "dimensions"), _SCS("set_dimensions"),_SCS("get_dimensions"));
}

Chunk::Chunk(){
    set_dimensions(CommonData::defaultChunkDimensions);
}
