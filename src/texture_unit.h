#ifndef TEXTURE_UNIT_H
#define TEXTURE_UNIT_H

#include <vector>

#include "texture.h"

class TextureUnitCombiner
{
public:
    TextureUnitCombiner() : id(0), value(0) { };
    TextureUnitCombiner(UINT theId, INT theValue) : id(theId), value(theValue) { }; 

    BOOL operator==(const TextureUnitCombiner& rightSide)
    {
        return id == rightSide.id && value == rightSide.value;
    }

    UINT id;
    INT value;
};

class TextureUnit : public Texture
{
public:
    TextureUnit(UINT unitId, const CHAR* filename);
    virtual ~TextureUnit();

    virtual void activate();

    TextureUnit& addCombiner(UINT id, INT value);
    void removeCombiner(UINT id, INT value);

    inline void setTextureMode(INT mode);

private:
    UINT mUnitId;
    INT mTextureMode;
    
    // TODO Use a set structure instead to avoid duplicate combiner
    vector<TextureUnitCombiner> mCombiners;
};

#include "texture_unit.inl"

#endif