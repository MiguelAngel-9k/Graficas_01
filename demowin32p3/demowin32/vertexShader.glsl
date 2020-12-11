#version 330

varying vec3 Normal;
out vec4 Color;


void main()
{
	//aqui definimos la textura activa con la que trabajaremos
	//por lo pronto es la 0, si hay mas pues entonces con su numero
    gl_TexCoord[0] = gl_MultiTexCoord0;

	//aqui pasamos la degradacion de la textura, no es color
	//para este caso
	Color = gl_Color;
}