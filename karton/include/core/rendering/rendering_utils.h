#ifndef RENDERING_UTILS_H
#define RENDERING_UTILS_H

#include <glm/glm.hpp>
#include <string>

#define MAX_BONE_INFLUENCE 4

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
	int m_BoneIDs[MAX_BONE_INFLUENCE];
	float m_Weights[MAX_BONE_INFLUENCE];
};

struct Texture
{
private:
	unsigned int _id;
	std::string _type;
	std::string _path;

public:

	unsigned int id() const { return _id; }
	const std::string& type() const { return _type; }
	const std::string& path() const { return _path; }

	Texture(unsigned int id, std::string_view type, std::string_view path)
		: _id(id), _type(type), _path(path) {}

	bool operator==(const Texture& other) const {
		return _id == other.id() && _type == other.type() && _path == other.path();
	}

	bool operator!=(const Texture& other) const {
		return !(*this == other);
	}
};

#endif // !RENDERING_UTILS_H
