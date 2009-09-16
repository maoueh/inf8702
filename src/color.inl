
inline FLOAT& Color::operator[] (const int index)
{
    assert(index >= 0 && index <= 3 && "Color: index out of range");
    return components[index];
}

inline Color& Color::operator= (const Color& rightSide)
{
    components[0] = rightSide.components[0];
    components[1] = rightSide.components[1];
    components[2] = rightSide.components[2];
    components[3] = rightSide.components[3];
    return *this;
}

inline bool Color::operator== (const Color& rightSide) const
{
    return components[0] == rightSide.components[0] && 
           components[1] == rightSide.components[1] &&
           components[2] == rightSide.components[2] &&
           components[3] == rightSide.components[3];
}

inline bool Color::operator!= (const Color& rightSide) const
{
    return components[0] != rightSide.components[0] || 
           components[1] != rightSide.components[1] ||
           components[2] != rightSide.components[2] ||
           components[3] != rightSide.components[3];
}

inline Color& Color::operator+= (const Color& rightSide)
{
    components[0] += rightSide.components[0];
    components[1] += rightSide.components[1];
    components[2] += rightSide.components[2];
    components[3] += rightSide.components[3];
    return *this;
}

inline Color& Color::operator-= (const Color& rightSide)
{
    components[0] -= rightSide.components[0];
    components[1] -= rightSide.components[1];
    components[2] -= rightSide.components[2];
    components[3] -= rightSide.components[3];
    return *this;
}

inline Color& Color::operator*= (const Color& rightSide)
{
    components[0] *= rightSide.components[0];
    components[1] *= rightSide.components[1];
    components[2] *= rightSide.components[2];
    components[3] *= rightSide.components[3];
    return *this;
}

inline Color& Color::operator*= (const FLOAT scalar)
{
    components[0] *= scalar;
    components[1] *= scalar;
    components[2] *= scalar;
    components[3] *= scalar;
    return *this;
}
