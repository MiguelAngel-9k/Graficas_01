#version 330

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 vertex_color;
layout (location = 2) in vec3 vertex_texcoord;


out vec3 v_position;
out vec3 v_color;
out vec2 v_textcoord;


void main(){

	v_position = vertex_position;
	v_color = vertex_color;
	v_textcoord = vec2(v_textcoord.x, v_textcoord.y);

	gl_position = vec4(vertex_position, 1.0f);
}