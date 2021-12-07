#include "Mesh.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleCamera.h"
#include "GL/glew.h"
#include "MathGeoLib.h"

Mesh::Mesh()
{
	//maxX = maxY = maxZ = minX = minY = minZ = 0.0f;
}

Mesh::~Mesh()
{
	//glDeleteBuffers(1, &vbo);
	//glDeleteBuffers(1 ,&ebo);
	glDeleteVertexArrays(1, &vao);
}

void Mesh::LoadVBO(const aiMesh* mesh, float* maxX, float* maxY, float* maxZ, float* minX, float* minY, float* minZ)
{
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	unsigned vertex_size = (sizeof(float) * 3 + sizeof(float) * 2);
	unsigned buffer_size = vertex_size * mesh->mNumVertices;
	glBufferData(GL_ARRAY_BUFFER, buffer_size, nullptr, GL_STATIC_DRAW);
	// function to initialize VBO, passing a custom buffer with whole data:
	// positions followed by texture coordinates.

	unsigned position_size = sizeof(float) * 3 * mesh->mNumVertices;
	glBufferSubData(GL_ARRAY_BUFFER, 0, position_size, mesh->mVertices);
	// updates a range of VBO data with given buffer.
	
	unsigned uv_offset = position_size;
	unsigned uv_size = sizeof(float) * 2 * mesh->mNumVertices;
	float2* uvs = (float2*)(glMapBufferRange(GL_ARRAY_BUFFER, uv_offset, uv_size, GL_MAP_WRITE_BIT));
	// returns a pointer to VBO range of data so you can write/read from it.
	
	for (unsigned i = 0; i < mesh->mNumVertices; ++i)
	{
		uvs[i] = float2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
		aiVector3D vertex = mesh->mVertices[i];
		if (*maxX < vertex.x)
			*maxX = vertex.x;
		if (*maxY < vertex.y)
			*maxY = vertex.y;
		if (*maxZ < vertex.z)
			*maxZ = vertex.z;
		if (*minX > vertex.x)
			*minX = vertex.x;
		if (*minY > vertex.y)
			*minY = vertex.y;
		if (*minZ > vertex.z)
			*minZ = vertex.z;
	}

	glUnmapBuffer(GL_ARRAY_BUFFER); // must be called when you are done with glMapBufferRange pointer.
	num_vertices = mesh->mNumVertices;
}

void Mesh::LoadEBO(const aiMesh* mesh)
{
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	unsigned index_size = sizeof(unsigned) * mesh->mNumFaces * 3;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_size, nullptr, GL_STATIC_DRAW);

	unsigned* indices = (unsigned*)(glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, 0, index_size, GL_MAP_WRITE_BIT));
	// returns a pointer to VBO data so you can write/read from it.
	
	for (unsigned i = 0; i < mesh->mNumFaces; ++i)
	{
		assert(mesh->mFaces[i].mNumIndices == 3); // note: assume triangles = 3 indices per face
		*(indices++) = mesh->mFaces[i].mIndices[0];
		*(indices++) = mesh->mFaces[i].mIndices[1];
		*(indices++) = mesh->mFaces[i].mIndices[2];
	}

	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER); // must be called when you are done with glMapBuffer pointer.
	num_indices = mesh->mNumFaces * 3;
}

void Mesh::CreateVAO()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao); // VAO stores all of this calls so that can be replaced with this call

	// calls for VBO and EBO.
	glBindBuffer(GL_ARRAY_BUFFER, vbo); 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	// (for separated array attributes)
	// call for each attribute.
	glEnableVertexAttribArray(0); 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1); 
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(float) * 3 * num_vertices));
}

void Mesh::Draw(const std::vector<unsigned>& model_textures, unsigned program, int material_index)
{
	const float4x4& view = App->camera->GetViewMatrix();
	const float4x4& proj = App->camera->GetProjectionMatrix();
	float4x4 model = float4x4::identity;
	glUseProgram(program);
	glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_TRUE, (const float*)&model);
	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_TRUE, (const float*)&view);
	glUniformMatrix4fv(glGetUniformLocation(program, "proj"), 1, GL_TRUE, (const float*)&proj);
	glActiveTexture(GL_TEXTURE0);

	glBindTexture(GL_TEXTURE_2D, model_textures[material_index]);
	glUniform1i(glGetUniformLocation(program, "diffuse"), 0);
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, nullptr);
}
