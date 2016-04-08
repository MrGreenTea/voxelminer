#ifndef BLOCKLIBRARY_H
#define BLOCKLIBRARY_H

#include "math/math_2d.h"
#include "vector.h"
#include "blockdata.h"

class BlockLibrary
{
public:
    BlockLibrary();
    Vector<Vector2> get_uvs(String block_name, BlockData::Sides);
    BlockData* get_block_data(String block_name);
};

#endif // BLOCKLIBRARY_H
