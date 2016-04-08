#include "voxelmap.h"

int VoxelMap::get_chunk_dimensions() {
    return chunk_dimensions;
}

void VoxelMap::set_chunk_dimensions(int dimensions) {
    chunk_dimensions = dimensions;
}

void VoxelMap::_bind_methods(){
    ObjectTypeDB::bind_method(_MD("get_chunk_dimensions"),&VoxelMap::get_chunk_dimensions);
    ObjectTypeDB::bind_method(_MD("set_chunk_dimensions", "dimensions"),&VoxelMap::set_chunk_dimensions);

    ADD_PROPERTY( PropertyInfo(Variant::INT,"chunk_dimensions",PROPERTY_HINT_RANGE,"1,128,1"),_SCS("set_chunk_dimensions"),_SCS("get_chunk_dimensions"));
}

VoxelMap::VoxelMap()
{
    chunk_dimensions = 16;
}

