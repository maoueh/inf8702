
void TextureUnit::setTextureMode(INT mode)
{
    addCombiner(GL_TEXTURE_ENV_MODE, mode);
}