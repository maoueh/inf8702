#include "color.h"

const Color Color::BLACK(0.0, 0.0, 0.0);
const Color Color::BLUE(0.0, 0.0, 1.0);
const Color Color::GREEN(0.0, 1.0, 0.0);
const Color Color::RED(1.0, 0.0, 0.0);
const Color Color::WHITE(1.0, 1.0, 1.0);

Color::Color()
{
    components[0] = 0.0; components[1] = 0.0; 
    components[2] = 0.0; components[3] = 1.0;
}

Color::Color(FLOAT red, FLOAT green, FLOAT blue)
{
    components[0] = red;  components[1] = green; 
    components[2] = blue; components[3] = 1.0;
}

Color::Color(FLOAT red, FLOAT green, FLOAT blue, FLOAT alpha)
{
    components[0] = red;  components[1] = green; 
    components[2] = blue; components[3] = alpha;
}