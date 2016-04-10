#include "chunkdata.h"

bool ChunkData::is_vector_in_chunk(const Vector3 vector) {
    int index = vector_to_index(vector);
    return (index >= 0 && index < chunkBlocksArraySize);
}

int ChunkData::vector_to_index(const Vector3 vector) {
    return vector.x + vector.y * yDimensions + vector.z * yDimensions * zDimensions;
}

Ref<Block> ChunkData::get_block_at(const Vector3 position) {
    int index = vector_to_index(position);
    ERR_FAIL_INDEX_V(index, chunkBlocksArraySize, NULL);
    return chunkBlocks[index];
}

void ChunkData::remove_block_at(const Vector3 position) {
    set_block_at(position, NULL);
}

void ChunkData::set_block_at(const Vector3 position, Ref<Block> block) {
    int index = vector_to_index(position);
    ERR_FAIL_INDEX(index, chunkBlocksArraySize);
    chunkBlocks[index] = block;
}

bool ChunkData::is_uniform() {
    return (xDimensions == yDimensions) and (xDimensions == zDimensions);
}

void ChunkData::delete_data() {
    memdelete_arr(chunkBlocks);
}

ChunkData::ChunkData(const int dimensions)
{
    xDimensions = dimensions;
    yDimensions = dimensions;
    zDimensions = dimensions;
    chunkBlocks = memnew_arr(Ref<Block>, dimensions*dimensions*dimensions);
    chunkBlocksArraySize = dimensions*dimensions*dimensions;
}

ChunkData::ChunkData(const int xDims, const int yDims, const int zDims) {
    xDimensions = xDims;
    yDimensions = yDims;
    zDimensions = zDims;
    chunkBlocks = memnew_arr(Ref<Block>, xDims * yDims * zDims);
    chunkBlocksArraySize = xDims * yDims * zDims;
}

