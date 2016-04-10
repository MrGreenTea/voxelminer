#include "register_types.h"
#include "object_type_db.h"
#include "block.h"
#include "block_material.h"
#include "blockdata.h"
#include "chunk.h"
#include "chunkdata.h"
#include "chunkmeshcreator.h"
#include "voxelmap.h"

// #define TOOLS_ENABLED 1

void register_voxelmap_types() {
  ObjectTypeDB::register_type<Block>();
  ObjectTypeDB::register_type<BlockMaterial>();
  ObjectTypeDB::register_type<BlockData>();
  ObjectTypeDB::register_type<Chunk>();
  // ObjectTypeDB::register_type<ChunkData>();
  ObjectTypeDB::register_type<VoxelMap>();
}



void unregister_voxelmap_types() {


}
