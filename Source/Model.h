#pragma once
#include "Mesh.h" 
#include "assimp/scene.h"
#include "MathGeoLib.h"
#include <vector>

class Model
{
public:
	Model();
	~Model();

	void Load(const char* image_name, const char* fbx_name, unsigned program);
	void LoadMaterials(const aiScene* scene, const char* image_name);
	void LoadTextures(const aiScene* scene, unsigned program);
	void LoadMeshes(const aiScene* scene, unsigned program);
	void Clear();
	void Draw(unsigned program);
	float3 GetPos();

private:
	float4x4 tranform = float4x4::identity;
	std::vector<unsigned> materials;
	std::vector<unsigned> textures;
	std::vector<Mesh> meshes;
};
