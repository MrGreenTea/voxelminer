#ifndef VOXELMAP_H
#define VOXELMAP_H

#include "scene/3d/spatial.h"
#include "scene/resources/material.h"
#include "block.h"
#include "blocklibrary.h"
#include "chunk.h"
#include "open-simplex-noise.h"


class VoxelMap : public Spatial
{
    OBJ_TYPE(VoxelMap, Spatial)
    OBJ_CATEGORY("3D")
public:
    VoxelMap();
    ~VoxelMap();
    void set_chunk_dimensions(Vector3 dimensions);
    Vector3 get_chunk_dimensions() const;
    void set_block_library(Ref<BlockLibrary> library);
    Ref<BlockLibrary> get_block_library() const;
    void set_update_automatically(bool update_automatically);
    bool get_update_automatically() const;
    void set_block(const Vector3 position, String name);
    void remove_block(const Vector3 position);
    Ref<Block> get_block(const Vector3 position) const;
    Chunk *create_new_chunk(const Vector3 at_pos);
private:
    bool update_automatically;
    Ref<BlockLibrary> block_library;
    Vector3 chunk_dimensions;
    Material chunk_material;
    Map<Vector3, Chunk*> loaded_chunks;
    Vector<Chunk*> chunks_needing_update;
    void update_chunks();
    Vector3 global_to_chunk_position(const Vector3 global_position) const;
    Vector3 global_to_chunk_local_positon(const Vector3 position) const;
    Ref<Block> generate_block_at(const Vector3 position);
    osn_context* ctx;

protected:
    static void _bind_methods();
    void _notification(int notification);

};

#endif // VOXELMAP_H
