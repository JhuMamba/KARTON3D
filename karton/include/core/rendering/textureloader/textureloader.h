#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <string>
#include <memory>

#include <rendering/rendering_utils.h>

class TextureLoader {
public:
    virtual ~TextureLoader() = default;

    // Load texture from file with given path and directory.
    virtual std::unique_ptr<Texture> LoadTextureFromFile(const std::string& filename, const std::string& directory, bool gamma) = 0;
};

#endif
