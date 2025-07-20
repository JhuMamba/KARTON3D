#include "openglmodel.h"
#include <rendering/mesh/openglmesh.h>

OpenGLModel::OpenGLModel(const std::string& path, bool gamma)
    : _gammaCorrection(gamma)
{
    LoadModel(path);
}

void OpenGLModel::Draw(Shader& shader)
{
    for (auto& mesh : _meshes)
        mesh->Draw(shader);
}

void OpenGLModel::LoadModel(const std::string& path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }
    _directory = path.substr(0, path.find_last_of('/'));
    processNode(scene->mRootNode, scene);
}

void OpenGLModel::processNode(aiNode* node, const aiScene* scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        _meshes.push_back(processMesh(mesh, scene));
    }
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

std::shared_ptr<Mesh> OpenGLModel::processMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<std::shared_ptr<Texture>> meshTextures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector;

        // positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;

        // normals
        if (mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;
        }

        // texture coordinates
        if (mesh->mTextureCoords[0])
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
            // tangent
            vector.x = mesh->mTangents[i].x;
            vector.y = mesh->mTangents[i].y;
            vector.z = mesh->mTangents[i].z;
            vertex.Tangent = vector;
            // bitangent
            vector.x = mesh->mBitangents[i].x;
            vector.y = mesh->mBitangents[i].y;
            vector.z = mesh->mBitangents[i].z;
            vertex.Bitangent = vector;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    // Process textures
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];


    auto diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    meshTextures.insert(meshTextures.end(), diffuseMaps.begin(), diffuseMaps.end());

    auto specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    meshTextures.insert(meshTextures.end(), specularMaps.begin(), specularMaps.end());

    auto normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    meshTextures.insert(meshTextures.end(), normalMaps.begin(), normalMaps.end());

    auto heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    meshTextures.insert(meshTextures.end(), heightMaps.begin(), heightMaps.end());


    return std::make_shared<OpenGLMesh>(vertices, indices, meshTextures);
}

std::vector<std::shared_ptr<Texture>> OpenGLModel::loadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName)
{
    std::vector<std::shared_ptr<Texture>> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);

        bool skip = false;
        for (auto& loadedTex : _textures_loaded)
        {
            if (std::strcmp(loadedTex->path().c_str(), str.C_Str()) == 0)
            {
                textures.push_back(loadedTex);
                skip = true;
                break;
            }
        }

        if (!skip)
        {
            unsigned int id = OpenGLTextureLoader::LoadTextureFromFile(str.C_Str(), this->_directory, false);
            auto texturePtr = std::make_shared<Texture>(id, typeName, str.C_Str());
            textures.push_back(texturePtr);
            _textures_loaded.push_back(texturePtr);
        }
    }
    return textures;
}