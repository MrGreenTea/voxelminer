#ifndef BLOCK_H
#define BLOCK_H

#include "blockdata.h"

class Block
{
public:
    Block();
    bool is_solid();
    bool is_opaque();
    BlockData* blockData;

private:

};

#endif // BLOCK_H
