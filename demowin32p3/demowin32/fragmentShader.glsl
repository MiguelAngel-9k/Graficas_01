#version 330

in float visibilidad;

uniform sampler2D text1;
uniform sampler2D text2;

varying vec3 Normal;
in vec4 Color;
vec3 color_temp1;
vec3 color_temp2;

void main() {

	//obtenemos el pixel con el sampler de la textura 1
	color_temp1 = vec3(texture2D( text1, gl_TexCoord[0].st));
	//obtenemos el pixel con el sampler de la textura 2
	color_temp2 = vec3(texture2D( text2, gl_TexCoord[0].st));
	//suma las dos texturas para dar el multitextura
	vec3 color_final = color_temp1 * Color.r + color_temp2 * Color.g + color.b;		

}