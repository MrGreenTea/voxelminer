#include "chunk.h"
#include "math/math_funcs.h"
#include "chunkmeshcreator.h"


void Chunk::build_mesh(Ref<BlockLibrary> block_lib) {
    ERR_FAIL_COND(block_lib.is_null());
    Ref<Mesh> new_mesh;
    ChunkMeshCreator builder = ChunkMeshCreator(this, block_lib);
    new_mesh = builder.generate_mesh();
    new_mesh->get_faces();
    mesh_instance->set_mesh(new_mesh);
    Ref<ConcavePolygonShape> collision_shape = builder.generate_collision_shape();
    if (get_shape_count() == 0) {
        add_shape(collision_shape);
    }
    else {
        set_shape(0, collision_shape);
    }
}

void Chunk::set_material(Ref<Material> material) {
    mesh_instance->set_material_override(material);
}

void Chunk::set_neighbour(const CommonData::Side side, Chunk *chunk) {
    ERR_FAIL_INDEX(side, 6)
    neighbour_chunks[side] = chunk;
}

Chunk* Chunk::get_neighbour(const CommonData::Side side) const {
    ERR_FAIL_INDEX_V(side, 6, NULL)
    return neighbour_chunks[side];
}

void Chunk::set_dimensions(Vector3 dims) {
    if (dims != dimensions) {
        dimensions = dims.floor();
        chunk_blocks.resize(dimensions.x*dimensions.y*dimensions.z);
        chunk_block_array_size = chunk_blocks.size();
    }
}

Vector3 Chunk::get_dimensions() const {
    return dimensions;
}

bool Chunk::is_uniform() const {
    return (dimensions.x == dimensions.y and dimensions.x == dimensions.z);
}

int Chunk::vector_to_index(const Vector3 vector) const {
    Vector3 floored_vector = vector.floor();
    return floored_vector.x + floored_vector.y * dimensions.y + floored_vector.z * dimensions.y * dimensions.z;
}

Ref<Block> Chunk::get_block(const Vector3 position) const {
    int index = vector_to_index(position);
    ERR_FAIL_INDEX_V(index, chunk_blocks.size(), NULL);
    return chunk_blocks.get(index);
}

void Chunk::set_block(const Vector3 position, Ref<Block> block) {
    int index = vector_to_index(position);
    ERR_FAIL_INDEX(index, chunk_blocks.size());
    chunk_blocks.set(index, block);
}

void Chunk::_bind_methods() {
    ObjectTypeDB::bind_method(_MD("set_block", "position:Vector3", "block:Block"), &Chunk::set_block);
    ObjectTypeDB::bind_method(_MD("get_block:Block", "position:Vector3"), &Chunk::get_block);
    ObjectTypeDB::bind_method(_MD("set_dimensions", "dimensions:Vector3"), &Chunk::set_dimensions);
    ObjectTypeDB::bind_method(_MD("get_dimensions:Vector3"), &Chunk::get_dimensions);
    ObjectTypeDB::bind_method(_MD("is_uniform"), &Chunk::is_uniform);
    ObjectTypeDB::bind_method(_MD("build_mesh"), &Chunk::build_mesh);

    ADD_PROPERTY( PropertyInfo(Variant::VECTOR3, "dimensions"), _SCS("set_dimensions"),_SCS("get_dimensions"));
}

Chunk::Chunk() : neighbour_chunks() {
    set_dimensions(CommonData::defaultChunkDimensions);
    mesh_instance = memnew(MeshInstance);
    mesh_instance->set_translation(Vector3());
    add_child(mesh_instance);
}
