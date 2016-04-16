#ifndef COMMONDATA
#define COMMONDATA

#include "math/vector3.h"
//lookup tables, enums etc. needed everwhere

namespace CommonData {
    const Vector3 defaultChunkDimensions = Vector3(16, 16, 16);

    enum Side{
        TOP,
        BOTTOM,
        RIGHT,
        LEFT,
        FRONT,
        BACK,
        NONE
    };

    const Side opposite_sides[7] = {
        BOTTOM,
        TOP,
        LEFT,
        RIGHT,
        BACK,
        FRONT,
        NONE
    };
}

#endif // COMMONDATA
