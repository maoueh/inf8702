#include "texture_unit.h"

TextureUnit::TextureUnit(UINT unitId, const CHAR* filename) : Texture(filename),
    mUnitId(unitId), mCombiners(), mTextureMode(GL_MODULATE)
{
    
}

TextureUnit::~TextureUnit()
{

}

void TextureUnit::activate()
{
    glActiveTexture(mUnitId);
    glEnable(GL_TEXTURE_2D); // TODO Is it better to not call it and assume it is already enabled ?
    glBindTexture(GL_TEXTURE_2D, mHandle);

    vector<TextureUnitCombiner>::iterator it = mCombiners.begin();
    while( it != mCombiners.end() ) 
    {
        glTexEnvi(GL_TEXTURE_ENV, (*it).id, (*it).value);
        it++;
    }
}

TextureUnit& TextureUnit::addCombiner(UINT id, INT value)
{
    mCombiners.push_back(TextureUnitCombiner(id, value));
    return *this;
}

void TextureUnit::removeCombiner(UINT id, INT value)
{
    TextureUnitCombiner combiner(id, value);
    vector<TextureUnitCombiner>::iterator it = mCombiners.begin();
    while( it != mCombiners.end() ) {
        if ( *it == combiner )
            mCombiners.erase(it);
        it++;
    }
}