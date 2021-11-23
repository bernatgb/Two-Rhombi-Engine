#pragma once
#include "assimp/scene.h"
#include <vector>

class Model
{
public:
	Model();
	~Model();

	void Load(const char* image_name, const char* fbx_name, unsigned program);
	void LoadMaterials(const aiScene* scene, const char* image_name);
	void LoadTextures(const aiScene* scene, unsigned program);
	void LoadMeshes(const aiScene* scene);

private:
	std::vector<unsigned> materials;
	std::vector<unsigned> textures;
};
