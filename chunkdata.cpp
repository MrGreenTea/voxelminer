#include "chunkdata.h"

bool ChunkData::is_vector_in_chunk(const Vector3 vector) {
    int index = vector_to_index(vector);
    return (index >= 0 && index < chunkBlocksArraySize);
}

int ChunkData::vector_to_index(const Vector3 vector) {
    return vector.x + vector.y * yDimensions + vector.z * yDimensions * zDimensions;
}

Block* ChunkData::get_block_at(const Vector3 position) {
    int index = vector_to_index(position);
    return &chunkBlocks[index];
}

void ChunkData::remove_block_at(const Vector3 position) {
    set_block_at(position, NULL);
}

void ChunkData::set_block_at(const Vector3 position, Block *block) {
    int index = vector_to_index(position);
    chunkBlocks[index] = *block;
}

ChunkData::ChunkData(const int dimensions)
{
    xDimensions = dimensions;
    yDimensions = dimensions;
    zDimensions = dimensions;
    chunkBlocks = memnew_arr(Block, dimensions*dimensions*dimensions);
    chunkBlocksArraySize = dimensions*dimensions*dimensions;
}

ChunkData::ChunkData(const int xDims, const int yDims, const int zDims) {
    xDimensions = xDims;
    yDimensions = yDims;
    zDimensions = zDims;
    chunkBlocks = memnew_arr(Block, xDims * yDims * zDims);
    chunkBlocksArraySize = xDims * yDims * zDims;
}

