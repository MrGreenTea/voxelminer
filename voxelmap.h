#ifndef VOXELMAP_H
#define VOXELMAP_H

#include "core/map.h"
#include "scene/3d/spatial.h"
#include "scene/resources/material.h"
#include "block.h"
#include "blocklibrary.h"
#include "chunk.h"


class VoxelMap : public Spatial
{
    OBJ_TYPE(VoxelMap, Spatial)
    OBJ_CATEGORY("3D")
public:
    VoxelMap();
    void set_block(Vector3 position, String name);
    Ref<Block> get_block(Vector3 position);
    void set_chunk_dimensions(int dimensions);
    int get_chunk_dimensions();
private:
    Vector3 global_to_chunk_position(Vector3 global_position);
    Map<Vector3, Chunk*> loaded_chunks;
    int chunk_dimensions;
    Material chunk_material;

protected:
    static void _bind_methods();
};

#endif // VOXELMAP_H
