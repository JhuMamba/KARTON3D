#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

#include <rendering/renderer/renderer.h>
#include <rendering/shader/openglshader.h>

#include <glad/glad.h>

class OpenGLRenderer : public Renderer {
public:
    void Init() override {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);
        stbi_set_flip_vertically_on_load(true);
    }

    void SetClearColor(float r, float g, float b, float a) override {
        glClearColor(r, g, b, a);
    }

    void Clear() override {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void SetViewProjection(const glm::mat4& view, const glm::mat4& projection) override {
        m_view = view;
        m_projection = projection;
    }

    void RenderModel(const glm::mat4& modelMatrix, Model& model, Shader& shader) override {
        shader.Bind();
        shader.SetMat4("view", m_view);
        shader.SetMat4("projection", m_projection);
        shader.SetMat4("model", modelMatrix);
        model.Draw(shader);
    }

    void BeginFrame() override {}
    void EndFrame() override {}

private:
    glm::mat4 m_view;
    glm::mat4 m_projection;
};

#endif OPENGLRENDERER_H