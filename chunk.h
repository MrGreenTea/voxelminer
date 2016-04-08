#ifndef CHUNK_H
#define CHUNK_H

#include "commondata.h"
#include "scene/3d/mesh_instance.h"
#include "core/math/vector3.h"
#include "chunkdata.h"
#include "block.h"

class Chunk : public MeshInstance
{
private:
    Vector3 worldPosition;
    Chunk* neighbour_chunks[6];
    ChunkData data;
public:
    Block* get_block(const Vector3 position);
    void set_block(const Vector3 position, Block* block);
    Chunk* get_neighbour(const CommonData::Side side);
    void set_neighbour(const CommonData::Side, Chunk* chunk);
    Vector3 global_to_voxel(const Vector3 position);
    Vector3 voxel_to_global(const Vector3 position);
    ChunkData* get_data();
    Chunk();
    Chunk(const int dimensions);
    Chunk(const int xDimensions, const int yDimensions, const int zDimensions);
};

#endif // CHUNK_H
