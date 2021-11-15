#version 330

// locaction = n, must coincide with glEnableVertexAttribArray(n) slot and with glVertexAttribPointer(n, ...)
// glVertexAttribPointer(n, 3, GL_FLOAT, ...) size = 3 and type = GL_FLOAT means vec3 type vertex attribute.
layout(location = 0) in vec3 my_vertex_position;
layout(location = 1) in vec2 vertex_uv0;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

out vec2 uv0;

void main()
{
	gl_Position = vec4(my_vertex_position, 1.0);
	// A vertex shaders always has to write special global variable gl_Position.
	// This variable must contain vertex position after model and view and projection transforms (clipping space).
	// gl_Position is used for clipping.

	uv0 = vertex_uv0;
}