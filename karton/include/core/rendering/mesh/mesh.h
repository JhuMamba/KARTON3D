// IMesh.h
#ifndef MESH_H
#define MESH_H

#include <rendering/shader/shader.h>

class Mesh {
public:
    virtual ~Mesh() = default;

    virtual void Draw(Shader& shader) = 0;
};

#endif // MESH_H
