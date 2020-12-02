#pragma once

// Include GLFW
#include <GLFW/glfw3.h>
//#include <gl/glu.h>

// Include GLM
#include <../../glm/glm.hpp>
#include <../../glm/gtc/matrix_transform.hpp>
using namespace glm;

class Camara {
private:

	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;
	glm::vec3 position;
	// Initial horizontal angle : toward -Z
	const float horizontalAngle = 3.14f;
	// Initial vertical angle : none
	const float verticalAngle = 0.0f;
	// Initial Field of View
	const float initialFoV = 45.0f;

	const float speed = 3.0f; // 3 units / second
	const float mouseSpeed = 0.005f;

	double xpos = 0, ypos = 0;

public:

	Camara() {}	
	Camara(vec3 Posicion);
	mat4 getViewMatrix();
	mat4 getProjectionMatrix();
	vec3 getPosicion();
	void computeMatrix(char);


};