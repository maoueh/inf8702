#ifndef COLOR_H
#define COLOR_H

#include "common.h"

#define RED_COMPONENT   0
#define GREEN_COMPONENT 1
#define BLUE_COMPONENT  2
#define ALPHA_COMPONENT 3

class Color
{
public:
    static const Color BLACK;
    static const Color BLUE;
    static const Color GREEN;
    static const Color WHITE;
    static const Color RED;

    Color();
    Color(FLOAT red, FLOAT green, FLOAT blue);
    Color(FLOAT red, FLOAT green, FLOAT blue, FLOAT alpha);

    inline FLOAT red()   { return components[0]; }
    inline FLOAT green() { return components[1]; }
    inline FLOAT blue()  { return components[2]; }
    inline FLOAT alpha() { return components[3]; }

    FLOAT components[4];
};

#endif