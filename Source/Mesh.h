#pragma once
#include "assimp/Mesh.h"
#include <vector>

class Mesh
{
public:
	Mesh();
	~Mesh();

	void LoadVBO(const aiMesh* mesh);
	void LoadEBO(const aiMesh* mesh);
	void CreateVAO();
	void Draw(const std::vector<unsigned>& model_textures);

private:
	unsigned vbo;
	unsigned num_vertices;
	unsigned ebo;
	unsigned num_indices;
	unsigned vao;
	unsigned material_index;
	unsigned program;
};
