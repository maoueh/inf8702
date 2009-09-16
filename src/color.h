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

    inline FLOAT& operator[] (const int index);
    inline Color& operator= (const Color& rightSide);

    inline bool operator== (const Color& rightSide) const;
    inline bool operator!= (const Color& rightSide) const;

    inline Color& operator += (const Color& rightSide);
    inline Color& operator -= (const Color& rightSide);
    inline Color& operator *= (const Color& rightSide);
    inline Color& operator *= (const FLOAT scalar);

    inline FLOAT red()   { return components[RED_COMPONENT]; }
    inline FLOAT green() { return components[GREEN_COMPONENT]; }
    inline FLOAT blue()  { return components[BLUE_COMPONENT]; }
    inline FLOAT alpha() { return components[ALPHA_COMPONENT]; }

    FLOAT components[4];
};

#include "color.inl"

#endif