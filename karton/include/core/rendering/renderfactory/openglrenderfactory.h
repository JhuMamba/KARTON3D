#ifndef OPENGLRENDERFACTORY_H
#define OPENGLRENDERFACTORY_H

#include <rendering/renderfactory/renderfactory.h>
#include <rendering/mesh/openglmesh.h>
#include <rendering/model/openglmodel.h>
#include <rendering/textureloader/opengltextureloader.h>
#include <rendering/rendering_utils.h>

class OpenGLRenderFactory : public RenderFactory, public std::enable_shared_from_this<OpenGLRenderFactory>
{
public:
    std::shared_ptr<Mesh> CreateMesh(
        const std::vector<Vertex>& vertices,
        const std::vector<unsigned int>& indices,
        const std::vector<std::shared_ptr<Texture>>& textures) override;

    std::shared_ptr<Texture> CreateTexture(
        const std::string& path,
        const std::string& directory,
        const std::string& typeName) override;

    std::shared_ptr<Model> CreateModel(
        const std::string& path,
        bool gammaCorrection = false) override;
};

#endif // !OPENGLRENDERFACTORY_H