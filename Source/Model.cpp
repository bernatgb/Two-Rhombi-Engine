#include "Model.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "Mesh.h"
#include "assimp/cimport.h"
#include "assimp/postprocess.h"

Model::Model()
{}

Model::~Model()
{
	Clear();
}

void Model::Load(const char* image_name, const char* fbx_name, unsigned program)
{
	const aiScene* scene = aiImportFile(fbx_name, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene)
	{
		LoadMaterials(scene, image_name);
		LoadTextures(scene, program);
		LoadMeshes(scene, program);
	}
	else
	{
		CONSOLELOG("Error loading %s: %s", fbx_name, aiGetErrorString());
	}
}

void Model::LoadMaterials(const aiScene* scene, const char* image_name)
{
	aiString file;
	materials.reserve(scene->mNumMaterials);
	for (unsigned i = 0; i < scene->mNumMaterials; ++i)
	{
		if (scene->mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, 0, &file) == AI_SUCCESS)
		{
			materials.push_back(App->texture->LoadImage(file.data));
			//materials.push_back(App->texture->LoadImage(image_name));
		}
	}
}

void Model::LoadTextures(const aiScene* scene, unsigned program)
{
	for (unsigned i = 0; i < scene->mNumMaterials; ++i)
	{
		textures.push_back(App->texture->LoadTextureFromImage(materials[i], program));
	}
}

void Model::LoadMeshes(const aiScene* scene, unsigned program)
{
	Mesh mesh;
	for (unsigned i = 0; i < scene->mNumMeshes; ++i)
	{
		const aiMesh* ai_mesh = scene->mMeshes[i];
		mesh.LoadVBO(ai_mesh);
		mesh.LoadEBO(ai_mesh);
		mesh.CreateVAO();
		mesh.Draw(textures, program);
		meshes.push_back(mesh);
	}
}

void Model::Clear()
{
	materials.clear();
	textures.clear();
	meshes.clear();
}

void Model::Draw(unsigned program)
{
	for (int i = 0; i < meshes.size(); ++i)
	{
		meshes[i].CreateVAO();
		meshes[i].Draw(textures, program);
	}
}

float3 Model::GetPos()
{
	return tranform.TranslatePart();
}

const char* Model::GetImageName(const char* fbx_name)
{
	const aiScene* scene = aiImportFile(fbx_name, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene)
	{
		aiString file;
		// assuming only one material
		if (scene->mMaterials[0]->GetTexture(aiTextureType_DIFFUSE, 0, &file) == AI_SUCCESS)
		{
			return file.data;
		}
	}
	return "(null)";
}
