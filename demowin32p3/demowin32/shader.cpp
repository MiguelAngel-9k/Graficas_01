#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;


#include <GL/glew.h>
#include "shader.h"

bool cargaShaders(const char * vertex_file_path, const char * fragment_file_path) {

	char infoLog[255];
	GLint success;

	std::string temp = "";
	std::string src = "";

	std::ifstream in_file;


	//vertex shader
	in_file.open("vertec");

	if (in_file.is_open()) {
		while (std::getline(in_file, temp))
			src += temp + "\n";
	}
	else {
		std::cout << "NO SE PUDO LEER EL SHADER" << std::endl;
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
	}
}