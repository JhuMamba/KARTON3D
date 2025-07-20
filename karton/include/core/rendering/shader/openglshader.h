#ifndef OPENGLSHADER_H
#define OPENGLSHADER_H

#include <rendering/shader/shader.h>
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class OpenGLShader : public Shader
{
public:
    OpenGLShader(const char* vertexPath, const char* fragmentPath)
    {
        // (Same implementation as your current Shader constructor, just adapted)
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try
        {
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            vShaderFile.close();
            fShaderFile.close();
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
        }

        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();

        unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        CheckCompileErrors(vertex, "VERTEX");

        unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        CheckCompileErrors(fragment, "FRAGMENT");

        m_ID = glCreateProgram();
        glAttachShader(m_ID, vertex);
        glAttachShader(m_ID, fragment);
        glLinkProgram(m_ID);
        CheckCompileErrors(m_ID, "PROGRAM");

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    ~OpenGLShader()
    {
        glDeleteProgram(m_ID);
    }

    void Bind() const override
    {
        glUseProgram(m_ID);
    }

    void Unbind() const override
    {
        glUseProgram(0);
    }

    void SetBool(const std::string& name, bool value) const override
    {
        glUniform1i(glGetUniformLocation(m_ID, name.c_str()), (int)value);
    }

    void SetInt(const std::string& name, int value) const override
    {
        glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
    }

    void SetFloat(const std::string& name, float value) const override
    {
        glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
    }

    void SetVec2(const std::string& name, const glm::vec2& value) const override
    {
        glUniform2fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]);
    }

    void SetVec3(const std::string& name, const glm::vec3& value) const override
    {
        glUniform3fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]);
    }

    void SetVec4(const std::string& name, const glm::vec4& value) const override
    {
        glUniform4fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]);
    }

    void SetMat2(const std::string& name, const glm::mat2& mat) const override
    {
        glUniformMatrix2fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void SetMat3(const std::string& name, const glm::mat3& mat) const override
    {
        glUniformMatrix3fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void SetMat4(const std::string& name, const glm::mat4& mat) const override
    {
        glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

private:

    void CheckCompileErrors(unsigned int shader, const std::string& type)
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << std::endl;
            }
        }
    }
};

#endif // OPENGLSHADER_H