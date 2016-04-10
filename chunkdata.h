#ifndef CHUNKDATA_H
#define CHUNKDATA_H

#include "block.h"
#include "core/dvector.h"
#include "core/math/vector3.h"

class ChunkData
{
private:
    bool uniform;
    Ref<Block>* chunkBlocks;
    int chunkBlocksArraySize;
    bool is_vector_in_chunk(const Vector3 vector);
    int vector_to_index(const Vector3 vector);
public:
    int xDimensions;
    int yDimensions;
    int zDimensions;
    Ref<Block> get_block_at(const Vector3 position);
    void set_block_at(const Vector3 position, Ref<Block> block);
    void remove_block_at(const Vector3 position);
    bool is_uniform();
    void delete_data();
    ChunkData(const int dimensions);
    ChunkData(const int xDimensions, const int yDimensions, const int zDimensions);
};

#endif // CHUNKDATA_H
