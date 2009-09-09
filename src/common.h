#ifndef COMMON_H
#define COMMON_H

#include "precompiled_headers.h"

#include "types.h"
#include "utils.h"

#define EMPTY_SHADER_PROGRAM 0
#define WINDOWED_MODE        TRUE


#define PI 3.14159f
#define DEG2RAD( a ) ( a / 180.0f ) * ( PI )
#define CLIP( a, min, max ) ( a < min ) ? min : ( ( a > max ) ? max : a )
#define MAX( a, max ) ( a < max ) ? ( max ) : ( a )
#define MIN( a, min ) ( a > min ) ? ( min ) : ( a )



#endif