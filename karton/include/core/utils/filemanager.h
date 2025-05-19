#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <iostream>
#include <unordered_map>
#include <mutex>

// constants
const std::string ASSETS_DIR = "assets/";
const std::string SHADERS_DIR = ASSETS_DIR + "shaders/";
const std::string SPRITES_DIR = ASSETS_DIR + "sprites/";
const std::string MODELS_DIR = ASSETS_DIR + "models/";

class FileManager
{
public:
    static std::string GetShaderPath(const std::string& filename) {
        return SHADERS_DIR + filename;
    }

    static const char* GetShaderPathCStr(const std::string& filename) {
        static std::unordered_map<std::string, std::string>& cache = GetShaderCache();
        static std::mutex cacheMutex;

        std::lock_guard<std::mutex> lock(cacheMutex);

        auto it = cache.find(filename);
        if (it == cache.end()) {
            cache[filename] = SHADERS_DIR + filename;
        }
        return cache[filename].c_str();
    }

    static std::string GetSpritePath(const std::string& filename) {
        return SPRITES_DIR + filename;
    }

    static std::string GetModelPath(const std::string& filename) {
        return MODELS_DIR + filename;
    }

    static const char* GetSpritePathCStr(const std::string& filename) {
        static std::unordered_map<std::string, std::string>& cache = GetShaderCache();
        static std::mutex cacheMutex;

        std::lock_guard<std::mutex> lock(cacheMutex);

        auto it = cache.find(filename);
        if (it == cache.end()) {
            cache[filename] = SPRITES_DIR + filename;
        }
        return cache[filename].c_str();
    }

    static unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma)
    {
        std::string filename = std::string(path);
        filename = directory + '/' + filename;

        unsigned int textureID;
        glGenTextures(1, &textureID);

        int width, height, nrComponents;
        unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
        if (data)
        {
            GLenum format;
            if (nrComponents == 1)
                format = GL_RED;
            else if (nrComponents == 3)
                format = GL_RGB;
            else if (nrComponents == 4)
                format = GL_RGBA;

            glBindTexture(GL_TEXTURE_2D, textureID);
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            stbi_image_free(data);
        }
        else
        {
            std::cout << "Texture failed to load at path: " << path << std::endl;
            stbi_image_free(data);
        }

        return textureID;
    }
private:
    static std::unordered_map<std::string, std::string>& GetShaderCache() {
        static std::unordered_map<std::string, std::string> cache;
        return cache;
    }
};

#endif
