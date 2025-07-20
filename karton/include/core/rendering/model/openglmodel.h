#ifndef OPENGLMODEL_H
#define OPENGLMODEL_H

#include <rendering/textureloader/opengltextureloader.h>
#include <rendering/model/model.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


class OpenGLModel : public Model
{
public:
    OpenGLModel(const std::string& path, bool gamma = false);

    void Draw(Shader& shader) override;

    void LoadModel(const std::string& path) override;

    const std::vector<std::shared_ptr<Mesh>>& GetMeshes() const override { return _meshes; }
    const std::vector<std::shared_ptr<Texture>>& GetTextures() const override { return _textures_loaded; }

private:
    void processNode(aiNode* node, const aiScene* scene);

    std::shared_ptr<Mesh> processMesh(aiMesh* mesh, const aiScene* scene);

    std::vector<std::shared_ptr<Texture>> loadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName);

private:
    std::string _directory;
    bool _gammaCorrection;
    std::vector<std::shared_ptr<Mesh>> _meshes;
    std::vector<std::shared_ptr<Texture>> _textures_loaded;
};

#endif // OPENGLMODEL_H
