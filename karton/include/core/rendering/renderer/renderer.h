#ifndef RENDERER_H
#define RENDERER_H

#include <glm/glm.hpp>

class Shader;
class Model;

class Renderer {
public:
    virtual ~Renderer() = default;

    virtual void Init() = 0;
    virtual void SetClearColor(float r, float g, float b, float a) = 0;
    virtual void Clear() = 0;

    virtual void SetViewProjection(const glm::mat4& view, const glm::mat4& projection) = 0;
    virtual void RenderModel(const glm::mat4& modelMatrix, Model& model, Shader& shader) = 0;

    virtual void BeginFrame() = 0;
    virtual void EndFrame() = 0;
};
#endif // IRENDERER_H