#include "chunk.h"

Block* Chunk::get_block(const Vector3 position) {
    return data.get_block_at(position);
}

ChunkData* Chunk::get_data() {
    return &data;
}

Chunk::Chunk() : data(CommonData::defaultChunkDimensions)
{

}

Chunk::Chunk(int dimensions) : data(dimensions) {

}

Chunk::Chunk(int xDimensions, int yDimensions, int zDimensions) : data(xDimensions, yDimensions, zDimensions) {

}
