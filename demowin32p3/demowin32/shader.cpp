#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;


#include <GL/glew.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "shader.h"

bool cargaShaders(GLuint program) {

	char infoLog[255];
	GLint success;

	std::string temp = "";
	std::string src = "";

	std::ifstream in_file;


	//vertex shader
	in_file.open("vertexShader.glsl");

	if (in_file.is_open()) {
		while (std::getline(in_file, temp))
			src += temp + "\n";
	}
	else {
		std::cout << "NO SE PUDO LEER EL VERTEX SHADER" << std::endl;
		return false;
	}

	in_file.close();

	//GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const GLchar* vertSrc = src.c_str();
	//glShaderSource(vertexShader, 1, &vertSrc, NULL);
	//glCompileShader(vertexShader);

	//glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		//glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "NO SE PUDO COMPILAR EL VERTEX SHADER" << std::endl;
		std::cout << infoLog << std::endl;
		return false;
	}

	//fragment shader
	in_file.open("fragmentShader.glsl");
	if (in_file.is_open()) {
		while (std::getline(in_file, temp))
			src += temp + "\n";
	}

	in_file.close();

	//GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);	
	const GLchar* fragSrc = src.c_str();
	//glShaderSource(fragmentShader, 1, &fragSrc, NULL);
	//glCompileShader(fragmentShader);

	//glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		//glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "NO SE PUDO COMPILAR EL FRAGMENT SHADER" << std::endl;
		std::cout << infoLog<<std::endl;
		return false;
	}
	//programa
	//program = glCreateProgram();

	//glAttachShader(program, vertexShader);
	//glAttachShader(program, fragmentShader);

	//glLinkProgram(program);

	//glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		//glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "NO SE PUDIERON ENLAZAR LOS SHADERS"<<std::endl;
		std::cout << infoLog << std::endl;
	}

	//terminar
	//glUseProgram(0);
	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);
}