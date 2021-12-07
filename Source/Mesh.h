#pragma once
#include "assimp/Mesh.h"
#include <vector>

class Mesh
{
public:
	Mesh();
	~Mesh();

	void LoadVBO(const aiMesh* mesh, float* maxX, float* maxY, float* maxZ, float* minX, float* minY, float* minZ);
	void LoadEBO(const aiMesh* mesh);
	void CreateVAO();
	void Draw(const std::vector<unsigned>& model_textures, unsigned program, int index);

private:
	unsigned vbo;
	unsigned num_vertices;
	unsigned ebo;
	unsigned num_indices;
	unsigned vao;
	unsigned material_index;
	float maxX, maxY, maxZ, minX, minY, minZ;
};
