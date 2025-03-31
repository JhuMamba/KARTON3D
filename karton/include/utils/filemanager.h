#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <iostream>
#include <unordered_map>
#include <mutex>

// constants
const std::string ASSETS_DIR = "assets/";
const std::string SHADERS_DIR = ASSETS_DIR + "shaders/";
const std::string SPRITES_DIR = ASSETS_DIR + "sprites/";

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
private:
    static std::unordered_map<std::string, std::string>& GetShaderCache() {
        static std::unordered_map<std::string, std::string> cache;
        return cache;
    }
};

#endif
