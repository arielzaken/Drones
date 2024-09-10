#include "stdint.h"

typedef struct vec2D{
    int32_t x, y;
    // TODO: add support for different operations 
} vec2D;

typedef struct vec3D{
    int32_t x, y, z;
    // TODO: add support for different operations 
} vec3D;

typedef struct Twist{
    vec3D v; // linear velocity
    vec3D w; // angular velocity
} Twist;