#include "chunkmeshcreator.h"

const Vector3 ChunkMeshCreator::normal_list[6] = {
    Vector3(0,1,0),
    Vector3(0,-1,0),
    Vector3(1,0,0),
    Vector3(-1,0,0),
    Vector3(0,0,1),
    Vector3(0,0,-1),
};

const Vector3 ChunkMeshCreator::vertex_list[8] = {
    Vector3(0,0,1),
    Vector3(1,0,1),
    Vector3(1,1,1),
    Vector3(0,1,1),
    Vector3(0,1,0),
    Vector3(0,0,0),
    Vector3(1,0,0),
    Vector3(1,1,0)
};

const Vector2 ChunkMeshCreator::uv_list[4] = {
    Vector2(0,0),
    Vector2(1,0),
    Vector2(1,1),
    Vector2(0,1)
};

const int ChunkMeshCreator::quad_list[6][6] = {
    {3,4,7,3,7,2}, //top
    {5,0,1,5,1,6}, //bottom
    {1,2,7,1,7,6}, //right
    {0,5,4,0,4,3}, //left
    {0,3,2,0,2,1}, //back
    {4,5,6,4,6,7}  //front
};

Ref<Mesh> ChunkMeshCreator::generate_mesh() {
    Ref<Mesh> mesh = memnew(Mesh);

    for (int x = 0; x < chunk->get_dimensions().x; x++) {
        for (int y = 0; y < chunk->get_dimensions().y; y++) {
            for (int z = 0; z < chunk->get_dimensions().z; z++) {
                Vector3 block_position = Vector3(x, y, z);
                Ref<Block> current_block = chunk->get_block(block_position);
                if (current_block == NULL) {
                    continue;
                }
                Ref<BlockData> current_block_data = current_block->block_data;
                if (current_block_data->is_opaque()) {
                    for (int side = BlockData::TOP; side <= BlockData::BACK; side++) {
                        Ref<Block> neighbour_block = safe_get_block(block_position + normal_list[side]);
                        CommonData::Side side_to_add = static_cast<CommonData::Side>(side);
                        if ( (neighbour_block == NULL || !neighbour_block->get_block_data()->is_opaque())) {
                            add_quad(block_position, current_block, side_to_add);
                        }
                    }
                }
            }
        }
    }

    Array d;
    d.resize(Mesh::ARRAY_MAX);
    d[Mesh::ARRAY_NORMAL] = normals;
    d[Mesh::ARRAY_TEX_UV] = uvs;
    d[Mesh::ARRAY_VERTEX] = vertices;

    DVector<int> indices;
    indices.resize(vertices.size());
    for(int i=0;i<vertices.size();i++)
        indices.set(i,i);

    d[Mesh::ARRAY_INDEX]=indices;
    mesh->add_surface(Mesh::PRIMITIVE_TRIANGLES, d);
    return mesh;
}

Ref<ConcavePolygonShape> ChunkMeshCreator::generate_collision_shape() {
    Ref<ConcavePolygonShape> new_shape = memnew(ConcavePolygonShape);
    new_shape->set_faces(vertices);
    return new_shape;
}

Ref<Block> ChunkMeshCreator::safe_get_block(Vector3 position) {
    CommonData::Side side = CommonData::NONE;
    if (position.x < 0) {
        position.set_axis(Vector3::AXIS_X, chunk->get_dimensions().x - 1);
        side = CommonData::LEFT;
    }
    if (position.y < 0) {
        position.set_axis(Vector3::AXIS_Y, chunk->get_dimensions().y - 1);
        side = CommonData::BOTTOM;
    }
    if (position.z < 0) {
        position.set_axis(Vector3::AXIS_Z, chunk->get_dimensions().z - 1);
        side = CommonData::BACK;
    }
    if (position.x >= chunk->get_dimensions().x) {
        position.set_axis(Vector3::AXIS_X, 0);
        side = CommonData::RIGHT;
    }
    if (position.y >= chunk->get_dimensions().y) {
        position.set_axis(Vector3::AXIS_Y, 0);
        side = CommonData::TOP;
    }
    if (position.z >= chunk->get_dimensions().z) {
        position.set_axis(Vector3::AXIS_Z, 0);
        side = CommonData::FRONT;
    }
    if (side != CommonData::NONE) {
        Chunk* neighbour_chunk = chunk->get_neighbour(side);
        if (!neighbour_chunk) {
            return NULL;
        }
        return neighbour_chunk->get_block(position);
    }
    return chunk->get_block(position);
}

void ChunkMeshCreator::add_quad(Vector3 position, Ref<Block> block, CommonData::Side side) {
    int start_index = vertices.size();
    vertices.resize(vertices.size() + 6);
    normals.resize(normals.size() + 6);
    for (int i=0; i<6; i++) {
        Vector3 new_vertex = vertex_list[quad_list[side][i]] + position;
        vertices.set(start_index+i, new_vertex);
        normals.set(start_index+i, normal_list[side]);
    }
    uvs.append_array(block_library->get_uvs(block->get_name(), side));
}

ChunkMeshCreator::ChunkMeshCreator(Chunk* chunk, Ref<BlockLibrary> block_lib, bool gen_collider)
{
    this->chunk = chunk;
    generate_collider = gen_collider;
    block_library = block_lib;
}

