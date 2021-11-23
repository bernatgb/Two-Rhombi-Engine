#pragma once
#include "assimp/scene.h"
#include <vector>

class Model
{
public:
	Model();
	~Model();

	void Load(const char* file_name); 
	void LoadMaterials(const aiScene* scene);
	void LoadTextures();
	void LoadMeshes();

private:
	std::vector<unsigned> materials;
};
