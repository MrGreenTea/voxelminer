#include "chunkmeshcreator.h"

const Vector3 ChunkMeshCreator::normal_list[6] = {
    Vector3(0,1,0),
    Vector3(0,-1,0),
    Vector3(1,0,0),
    Vector3(-1,0,0),
    Vector3(0,0,1),
    Vector3(0,0,-1)
};

const Vector3 ChunkMeshCreator::vertex_list[8] = {
    Vector3(0,0,0),
    Vector3(1,0,0),
    Vector3(1,1,0),
    Vector3(0,1,0),
    Vector3(0,0,1),
    Vector3(1,0,1),
    Vector3(1,1,1),
    Vector3(0,1,1)
};

const Vector2 ChunkMeshCreator::uv_list[4] = {
    Vector2(0,0),
    Vector2(1,0),
    Vector2(1,1),
    Vector2(0,1)
};

const int ChunkMeshCreator::quad_list[6][6] = {
    {1,2,7,1,7,6}, //right
    {0,5,4,0,4,3}, //left
    {3,4,7,3,7,2}, //top
    {5,0,1,5,1,6}, //bottom
    {0,3,2,0,2,1}, //back
    {4,5,6,4,6,7}  //front
};

Mesh* ChunkMeshCreator::generate_mesh(Chunk* chunk) {
    Mesh* mesh = memnew(Mesh);

    for (int x = 0; x < chunk->get_dimensions().x; x++) {
        for (int y = 0; y < chunk->get_dimensions().y; y++) {
            for (int z = 0; z < chunk->get_dimensions().z; z++) {
                Vector3 blockPosition = Vector3(x, y, z);
                Ref<Block> currentBlock = chunk->get_block(blockPosition);
                if (currentBlock->block_data->is_opaque()) {
                    if (chunk->get_block(blockPosition+normal_list[CommonData::RIGHT])->block_data->is_opaque()) {

                    }
                }
            }
        }
    }

    return mesh;
}

ChunkMeshCreator::ChunkMeshCreator(bool generate_collider)
{
    generateCollider = generate_collider;
}

