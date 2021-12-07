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
	maxX = maxY = maxZ = minX = minY = minZ = 0.0f;

	const aiScene* scene = aiImportFile(fbx_name, aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_Triangulate);
	if (scene)
	{
		CONSOLELOG("File %s imported successfully.", fbx_name);
		//LoadMaterials(scene, image_name);
		LoadTextures(scene, program);
		LoadMeshes(scene, program);
	}
	else
	{
		CONSOLELOG("Error loading %s: %s.", fbx_name, aiGetErrorString());
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
	textures.reserve(materials.size());
	aiString file;
	for (unsigned i = 0; i < scene->mNumMaterials; ++i)
	{
		if (scene->mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, 0, &file) == AI_SUCCESS)
		{
			CONSOLELOG("Texture added.");
			textures.push_back(App->texture->LoadTextureFromImage(file.data, program));
			std::string s(file.data);
			imagesNames.push_back(s);
		}
	}
	/*
	for (unsigned i = 0; i < materials.size(); ++i)
	{
		textures.push_back(App->texture->LoadTextureFromMaterials(materials[i], program));
	}
	*/
}

void Model::LoadMeshes(const aiScene* scene, unsigned program)
{
	Mesh mesh;
	for (unsigned i = 0; i < scene->mNumMeshes; ++i)
	{
		const aiMesh* ai_mesh = scene->mMeshes[i];
		mesh.LoadVBO(ai_mesh, &maxX, &maxY, &maxZ, &minX, &minY, &minZ);
		CONSOLELOG("VBO loaded.");
		mesh.LoadEBO(ai_mesh);
		CONSOLELOG("EBO loaded.");
		mesh.CreateVAO();
		CONSOLELOG("VAO created.");
		int j = i;
		if (textures.size() <= i)
		{
			j = i - 1;
			imagesNames.push_back(imagesNames[j]);
		}
		mesh.Draw(textures, program, j);
		CONSOLELOG("Mesh drawn.");
		meshes.push_back(mesh);
		faces.push_back(ai_mesh->mNumFaces);
	}
}

void Model::Clear()
{
	materials.clear();
	textures.clear();
	meshes.clear();
	faces.clear();
	imagesNames.clear();
	CONSOLELOG("Model cleared.");
}

void Model::Draw(unsigned program)
{
	for (int i = 0; i < meshes.size(); ++i)
	{
		meshes[i].CreateVAO();		
		int j = i;
		if (textures.size() <= i)
			j = i - 1;
		meshes[i].Draw(textures, program, j);
	}
}

float3 Model::GetPosition()
{
	return tranform.TranslatePart();
}

float3x3 Model::GetRotation()
{
	return tranform.RotatePart();
}

float3 Model::GetScale()
{
	return tranform.GetScale();
}

std::vector<int> Model::GetFaces()
{
	return faces;
}

std::vector<std::string> Model::GetImagesNames()
{
	return imagesNames;
}

float3 Model::GetMax()
{
	return float3(maxX, maxY, maxZ);
}

float3 Model::GetMin()
{
	return float3(minX, minY, minZ);
}
