#ifndef VOXELMAP_H
#define VOXELMAP_H

#include "scene/3d/spatial.h"
#include "chunk.h"


class VoxelMap : public Spatial
{
    OBJ_TYPE(VoxelMap, Spatial)
    OBJ_CATEGORY("3D")
public:
    VoxelMap();
    void set_chunk_dimensions(int dimensions);
    int get_chunk_dimensions();
private:
    // Chunk chunks[];
    real_t chunk_dimensions;
    Dictionary chunks;
protected:
    static void _bind_methods();
};

#endif // VOXELMAP_H
