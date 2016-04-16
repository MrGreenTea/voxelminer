#include "math_funcs.h"
#include "chunkmeshcreator.h"
#include "voxelmap.h"

Vector3 VoxelMap::get_chunk_dimensions() const{
    return chunk_dimensions;
}

void VoxelMap::set_chunk_dimensions(Vector3 dimensions) {
    chunk_dimensions = dimensions.floor();
}

void VoxelMap::set_block_library(Ref<BlockLibrary> library) {
    block_library = library;
}

Ref<BlockLibrary> VoxelMap::get_block_library() const{
    return block_library;
}

void VoxelMap::set_update_automatically(bool update_auto) {
    update_automatically = update_auto;
    if (update_automatically) {
        set_process(true);
    }
}

bool VoxelMap::get_update_automatically() const{
    return update_automatically;
}

void VoxelMap::set_block(Vector3 position, String name) {
    Vector3 chunk_position = global_to_chunk_position(position);
    ERR_FAIL_COND(!loaded_chunks.has(chunk_position));
    Chunk* chunk = loaded_chunks[chunk_position];
    Ref<Block> new_block = block_library->get_new_block(name);
    chunk->set_block(global_to_chunk_local_positon(position), new_block);
    if (chunks_needing_update.find(chunk) == -1) {
            chunks_needing_update.push_back(chunk);
    }
}

void VoxelMap::remove_block(const Vector3 position) {
    Vector3 chunk_position = global_to_chunk_position(position);
    ERR_FAIL_COND(!loaded_chunks.has(chunk_position));
    Chunk* chunk = loaded_chunks[chunk_position];
    chunk->set_block(global_to_chunk_local_positon(position), NULL);
    if (chunks_needing_update.find(chunk) == -1) {
            chunks_needing_update.push_back(chunk);
    }
}

Ref<Block> VoxelMap::get_block(Vector3 position) const {
    Vector3 chunk_position = global_to_chunk_position(position);
    ERR_FAIL_COND_V(!loaded_chunks.has(chunk_position), NULL);
    Chunk* chunk = loaded_chunks[chunk_position];
    return chunk->get_block(global_to_chunk_local_positon(position));
}


Vector3 VoxelMap::global_to_chunk_position(Vector3 global_position) const {
    Vector3 return_vector = global_position / chunk_dimensions;
    return return_vector.floor();
}

Vector3 VoxelMap::global_to_chunk_local_positon(Vector3 position) const {
    position = position.floor();
    int x = int(position.x) % int(chunk_dimensions.x);
    int y = int(position.y) % int(chunk_dimensions.y);
    int z = int(position.z) % int(chunk_dimensions.z);
    return Vector3(x, y, z);
}

void VoxelMap::update_chunks() {
    int max_chunk_updates = 3;
    if (chunks_needing_update.size() < max_chunk_updates){
        max_chunk_updates = chunks_needing_update.size();
    }
    for (int i = 0; i < max_chunk_updates; i++) {
        chunks_needing_update[0]->build_mesh(get_block_library());
        chunks_needing_update.remove(0);
    }
}

Chunk* VoxelMap::create_new_chunk(Vector3 at_pos) {
    at_pos = at_pos.floor();
    if (loaded_chunks.has(at_pos)) {
        ERR_EXPLAIN("There is already a chunk at " + at_pos);
        return NULL;
    }
    Chunk* new_chunk = memnew(Chunk);
    new_chunk->set_dimensions(chunk_dimensions);
    Vector3 new_chunk_pos = Vector3(at_pos.x * chunk_dimensions.x, at_pos.y * chunk_dimensions.y, at_pos.z * chunk_dimensions.z);
    loaded_chunks[at_pos] = new_chunk;
    for (int i = 0; i != CommonData::NONE; i++) {
        Vector3 neighbour_pos = at_pos + ChunkMeshCreator::normal_list[i];
        if (loaded_chunks.has(neighbour_pos)) {
            Chunk* neighbour = loaded_chunks[neighbour_pos];
            CommonData::Side side = static_cast<CommonData::Side>(i);
            new_chunk->set_neighbour(side, neighbour);
            neighbour->set_neighbour(CommonData::opposite_sides[side], new_chunk);
        }
    }
    for (int x = 0; x<chunk_dimensions.x; x++) {
        for (int z = 0; z<chunk_dimensions.z; z++) {
            for (int y = 0; y<chunk_dimensions.y; y++) {
                Vector3 block_pos = Vector3(x, y, z);
                Vector3 global_block_pos = block_pos + new_chunk_pos;
                Ref<Block> new_block = generate_block_at(global_block_pos);
                if (new_block.is_valid()) {
                    new_chunk->set_block(block_pos, new_block);
                }
            }
        }
    }
    chunks_needing_update.push_back(new_chunk);
    new_chunk->set_material(block_library->get_chunk_material());
    add_child(new_chunk);
    new_chunk->set_translation(new_chunk_pos);
    return new_chunk;
}

Ref<Block> VoxelMap::generate_block_at(const Vector3 position) {
    double height = open_simplex_noise2(ctx, position.x/10, position.z/10);
    double mod = open_simplex_noise3(ctx, position.x/10, position.y/10, position.z/10);

    if (height - mod < 0) {
        List<String> blocks = block_library->get_all_block_names();
        int index = (open_simplex_noise3(ctx, position.x, position.y, position.z) + 1) * blocks.size();
        index = index%blocks.size();
        String block = blocks[index];
        return block_library->get_new_block(block);
    }
    return NULL;
}

void VoxelMap::_notification(int notification) {
    if (update_automatically && notification == NOTIFICATION_ENTER_TREE) {
        block_library->generate_texture_atlas();
        set_fixed_process(true);
    }
    if (update_automatically && notification == NOTIFICATION_FIXED_PROCESS) {
        update_chunks();
    }
}

void VoxelMap::_bind_methods(){
    ObjectTypeDB::bind_method(_MD("create_new_chunk:Chunk", "at_pos:Vector3"), &VoxelMap::create_new_chunk);
    ObjectTypeDB::bind_method(_MD("set_block", "position:Vector3", "name:String"), &VoxelMap::set_block);
    ObjectTypeDB::bind_method(_MD("remove_block", "position:Vector3"), &VoxelMap::remove_block);
    ObjectTypeDB::bind_method(_MD("get_block:Block", "position:Vector3"), &VoxelMap::get_block);
    ObjectTypeDB::bind_method(_MD("set_block_library", "block_library:BlockLibrary"), &VoxelMap::set_block_library);
    ObjectTypeDB::bind_method(_MD("get_block_library:BlockLibrary"), &VoxelMap::get_block_library);
    ObjectTypeDB::bind_method(_MD("set_chunk_dimensions", "dimensions"), &VoxelMap::set_chunk_dimensions);
    ObjectTypeDB::bind_method(_MD("get_chunk_dimensions"), &VoxelMap::get_chunk_dimensions);
    ObjectTypeDB::bind_method(_MD("set_update_automatically", "update_automatically:bool"), &VoxelMap::set_update_automatically);
    ObjectTypeDB::bind_method(_MD("get_update_automatically:bool"), &VoxelMap::get_update_automatically);

    ADD_PROPERTY( PropertyInfo(Variant::VECTOR3,"chunk_dimensions"), _SCS("set_chunk_dimensions"), _SCS("get_chunk_dimensions"));
    ADD_PROPERTY( PropertyInfo(Variant::OBJECT, "block_library", PROPERTY_HINT_RESOURCE_TYPE, "BlockLibrary"), _SCS("set_block_library"), _SCS("get_block_library"));
    ADD_PROPERTY( PropertyInfo(Variant::BOOL, "update_automatically"), _SCS("set_update_automatically"), _SCS("get_update_automatically"));
}

VoxelMap::VoxelMap()
{
    update_automatically = true;
    chunk_dimensions = CommonData::defaultChunkDimensions;
    open_simplex_noise(1, &ctx);
}

VoxelMap::~VoxelMap() {
    open_simplex_noise_free(ctx);
}

