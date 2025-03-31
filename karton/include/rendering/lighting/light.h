#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>
#include <rendering/shader.h>

class Light {
public:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    Light(Shader& shader, glm::vec3 a, glm::vec3 d, glm::vec3 s)
        : mShader(shader), ambient(a), diffuse(d), specular(s) {
    }

    virtual void applyLight() = 0;

protected:
    Shader& mShader;
};

class DirectionalLight : public Light {
public:
    glm::vec3 direction;

    DirectionalLight(Shader& shader, glm::vec3 dir,
        glm::vec3 a = glm::vec3(0.05f),
        glm::vec3 d = glm::vec3(0.4f),
        glm::vec3 s = glm::vec3(0.5f))
        : Light(shader, a, d, s), direction(dir) {
    }

    void applyLight() override {
        mShader.use();
        mShader.setVec3("dirLight.direction", direction);
        mShader.setVec3("dirLight.ambient", ambient);
        mShader.setVec3("dirLight.diffuse", diffuse);
        mShader.setVec3("dirLight.specular", specular);
    }
};

class PointLight : public Light {
public:
    glm::vec3 position;
    float constant, linear, quadratic;
    int index;

    PointLight(Shader& shader, int idx, glm::vec3 pos,
        glm::vec3 a = glm::vec3(0.05f),
        glm::vec3 d = glm::vec3(0.8f),
        glm::vec3 s = glm::vec3(1.0f),
        float c = 1.0f, float l = 0.09f, float q = 0.032f)
        : Light(shader, a, d, s), index(idx), position(pos),
        constant(c), linear(l), quadratic(q) {
    }

    void applyLight() override {
        mShader.use();
        std::string base = "pointLights[" + std::to_string(index) + "]";
        mShader.setVec3(base + ".position", position);
        mShader.setVec3(base + ".ambient", ambient);
        mShader.setVec3(base + ".diffuse", diffuse);
        mShader.setVec3(base + ".specular", specular);
        mShader.setFloat(base + ".constant", constant);
        mShader.setFloat(base + ".linear", linear);
        mShader.setFloat(base + ".quadratic", quadratic);
    }
};

class SpotLight : public Light {
public:
    glm::vec3 position;
    glm::vec3 direction;
    float cutOff, outerCutOff;
    float constant, linear, quadratic;

    SpotLight(Shader& shader, glm::vec3 pos, glm::vec3 dir,
        glm::vec3 a = glm::vec3(0.0f),
        glm::vec3 d = glm::vec3(1.0f),
        glm::vec3 s = glm::vec3(1.0f),
        float c = 1.0f, float l = 0.09f, float q = 0.032f,
        float cut = glm::cos(glm::radians(12.5f)),
        float outerCut = glm::cos(glm::radians(15.0f)))
        : Light(shader, a, d, s), position(pos), direction(dir),
        constant(c), linear(l), quadratic(q), cutOff(cut), outerCutOff(outerCut) {
    }

    void applyLight() override {
        mShader.use();
        mShader.setVec3("spotLight.position", position);
        mShader.setVec3("spotLight.direction", direction);
        mShader.setVec3("spotLight.ambient", ambient);
        mShader.setVec3("spotLight.diffuse", diffuse);
        mShader.setVec3("spotLight.specular", specular);
        mShader.setFloat("spotLight.constant", constant);
        mShader.setFloat("spotLight.linear", linear);
        mShader.setFloat("spotLight.quadratic", quadratic);
        mShader.setFloat("spotLight.cutOff", cutOff);
        mShader.setFloat("spotLight.outerCutOff", outerCutOff);
    }
};

#endif // LIGHT_H
