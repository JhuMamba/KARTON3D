#ifndef RENDERFACTORY_H
#define RENDERFACTORY_H

#include <memory>
#include <string>
#include <vector>

#include <rendering/mesh/mesh.h>
#include <rendering/model/model.h>
#include <rendering/rendering_utils.h>

class RenderFactory
{
public:
    virtual ~RenderFactory() = default;

    virtual std::shared_ptr<Mesh> CreateMesh(
        const std::vector<Vertex>& vertices,
        const std::vector<unsigned int>& indices,
        const std::vector<std::shared_ptr<Texture>>& textures) = 0;

    virtual std::shared_ptr<Texture> CreateTexture(
        const std::string& path,
        const std::string& directory,
        const std::string& typeName) = 0;

    virtual std::shared_ptr<Model> CreateModel(
        const std::string& path,
        bool gammaCorrection = false) = 0;
};

#endif // RENDERFACTORY_H
