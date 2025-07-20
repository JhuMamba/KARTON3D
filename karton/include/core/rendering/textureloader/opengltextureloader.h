#ifndef OPENGLTEXTURELOADER_H
#define OPENGLTEXTURELOADER_H

#include <rendering/textureloader/textureloader.h>
#include <glad/glad.h>
#include <iostream>
#include <stb_image.h>

class OpenGLTextureLoader : public TextureLoader {
public:
    static unsigned int LoadTextureFromFile(const std::string& filename, const std::string& directory, bool gamma);
};

#endif
