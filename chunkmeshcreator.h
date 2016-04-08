#ifndef CHUNKMESHCREATOR_H
#define CHUNKMESHCREATOR_H

#include "chunk.h"
#include "scene/resources/mesh.h"

struct bitset {
    char data;

    bitset() {
        data = 0;
    }

    void set(size_t pos, bool val = true) {
        data ^= (-val ^ data) & (1 << pos);
    }

    void flip(size_t pos) {
        data ^= 1 << pos;
    }

    bool get(size_t pos) {
        return (data >> pos) & 1;
    }

    size_t count() {
        char v = data; // count the number of bits set in v
        size_t c; // c accumulates the total bits set in v

        for (c = 0; v; c++) {
            v &= v - 1; // clear the least significant bit set
        }

        return c;
    }

    void reset() {
        data = 0;
    }

    bool operator[](size_t pos)       { return (data >> pos) & 1; }
    const bool operator[](size_t pos) const { return (data >> pos) & 1; }

};

class ChunkMeshCreator
{
    const static Vector3 normal_list[6];
    const static Vector3 vertex_list[8];
    const static Vector2 uv_list[4];
    const static int     quad_list[6][6];

private:
    bool generateCollider;
    DVector<Vector3> vertices;
    DVector<Vector3> normals;
    DVector<Vector2> uvs;
    void add_quad(CommonData::Side side);
public:
    ChunkMeshCreator(bool generateCollider = true);
    Mesh* generate_mesh(Chunk* chunk);
};

#endif // CHUNKMESHCREATOR_H
