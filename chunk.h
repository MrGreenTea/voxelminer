#ifndef CHUNK_H
#define CHUNK_H

#include "commondata.h"
#include "scene/3d/mesh_instance.h"
#include "core/math/vector3.h"
#include "block.h"

class Chunk : public MeshInstance
{
    OBJ_TYPE( Chunk, MeshInstance )
    enum Sides {
        TOP = CommonData::TOP,
        BOTTOM = CommonData::BOTTOM,
        RIGHT = CommonData::RIGHT,
        LEFT = CommonData::LEFT,
        FRONT = CommonData::FRONT,
        BACK = CommonData::BACK
    };

    Chunk* neighbour_chunks[6];
    Vector3 dimensions;
    Ref<Block>* chunkBlocks;
    int chunkBlocksArraySize;
    int vector_to_index(const Vector3 vector);
protected:
    static void _bind_methods();
public:
    bool is_position_in_chunk(const Vector3 position);
    Ref<Block> get_block(const Vector3 position);
    void set_block(const Vector3 position, Ref<Block> block);
    Chunk* get_neighbour(const Sides side);
    void set_neighbour(const Sides, Chunk* chunk);
    Vector3 global_to_voxel(const Vector3 world_position);
    Vector3 voxel_to_global(const Vector3 local_position);
    void set_dimensions(Vector3 dims);
    Vector3 get_dimensions();
    bool is_uniform();
    Chunk();
};

#endif // CHUNK_H
