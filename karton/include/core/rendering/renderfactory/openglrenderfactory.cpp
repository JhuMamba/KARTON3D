#include "openglrenderfactory.h"

std::shared_ptr<Mesh> OpenGLRenderFactory::CreateMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<std::shared_ptr<Texture>>& textures)
{
    return std::make_shared<OpenGLMesh>(vertices, indices, textures);
}

std::shared_ptr<Texture> OpenGLRenderFactory::CreateTexture(const std::string& path, const std::string& directory, const std::string& typeName)
{
    auto id = OpenGLTextureLoader::LoadTextureFromFile(path, directory, false);
    return std::make_shared<Texture>(id, typeName, path);
}

std::shared_ptr<Model> OpenGLRenderFactory::CreateModel(const std::string& path, bool gammaCorrection)
{
    return std::make_shared<OpenGLModel>(path, gammaCorrection);
}
