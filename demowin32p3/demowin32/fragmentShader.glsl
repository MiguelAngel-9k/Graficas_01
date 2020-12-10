#version 330

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 vertex_color;
layout (location = 2) in vec3 vertex_texcoord;

out vec4 v_color;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main(){
	
	fs_color = texture(texture0, v_textcoord)*texture(texture1, v_textcoord) *vec4(v_color, 1f);

}