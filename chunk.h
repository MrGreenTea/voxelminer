#ifndef CHUNK_H
#define CHUNK_H

#include "core/math/vector3.h"
#include "scene/3d/mesh_instance.h"
#include "scene/3d/physics_body.h"
#include "block.h"
#include "blocklibrary.h"
#include "commondata.h"

class Chunk : public StaticBody
{
    OBJ_TYPE( Chunk, StaticBody )

    Chunk* neighbour_chunks[6];
    Vector3 dimensions;
    DVector<Ref<Block> > chunk_blocks;
    int chunk_block_array_size;
    int vector_to_index(const Vector3 vector) const;
    MeshInstance* mesh_instance;
protected:
    static void _bind_methods();
public:
    void build_mesh(Ref<BlockLibrary> block_lib);
    bool is_position_in_chunk(const Vector3 position) const;
    Ref<Block> get_block(const Vector3 position) const;
    void set_block(const Vector3 position, Ref<Block> block);
    Chunk* get_neighbour(const CommonData::Side side) const;
    void set_neighbour(const CommonData::Side side, Chunk* chunk);
    Vector3 global_to_voxel(const Vector3 world_position) const;
    Vector3 voxel_to_global(const Vector3 local_position) const;
    void set_dimensions(Vector3 dims);
    Vector3 get_dimensions() const;
    bool is_uniform() const;
    void set_material(Ref<Material> material);

    Chunk();
};

#endif // CHUNK_H
