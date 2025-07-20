#ifndef MODEL_H
#define MODEL_H

#include <memory>
#include <string>
#include <vector>

#include <rendering/mesh/mesh.h>
#include <rendering/shader/shader.h>
#include <rendering/rendering_utils.h>


class Model
{
public:
    virtual ~Model() = default;

    // Draw with given shader
    virtual void Draw(Shader& shader) = 0;

    // Load model from file (or constructor can take path)
    virtual void LoadModel(const std::string& path) = 0;

    // Get Meshes (optional, depends on your design)
    virtual const std::vector<std::shared_ptr<Mesh>>& GetMeshes() const = 0;

    // Get Textures (optional)
    virtual const std::vector<std::shared_ptr<Texture>>& GetTextures() const = 0;
};

#endif // MODEL_H
