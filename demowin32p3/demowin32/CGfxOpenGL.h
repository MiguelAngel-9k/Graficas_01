#pragma once
#include "Camera.h"

class CGfxOpenGL : public Camera
{
private:
	int m_windowWidth;
	int m_windowHeight;
	float m_angle;
public:
	float scale2;
	float scale1;
	float mov6;
	float mov5;
	float mov4;
	float mov3;
	float mov2;
	float mov1;
	float giro;
	float giroLateral;
	float R_bote;
	float R_boot;
	float R_beet;

	//float mov;
	float x;
	float y;
	float z;
	float xs;
	float ys;
	float zs;
	float Angulo;
	float Angulo2;
	float Angulo3;
	float movimientocamarax;
	float movimientocamaray;
	float movimientocamaraz;
	float rotacamarax;
	float rotacamaray;
	float rotacamaraz;
	float rotx;
	float rotz;
	float grad_rad;
	bool cambio;

	struct cam {
		float camx;
		float camy;
		float camz;
		float centerx;
		float centery;
		float centerz;
		float grados;
	}camera;
public:
	CGfxOpenGL();
	virtual ~CGfxOpenGL();
	bool Init();
	bool Shutdown();
	void SetupProjection(int width, int height);
	void Prepare(float dt);
	void Render();
};

//class cameraSettings {
//
//	cameraSettings() {};
//
//	glm::vec3 position;
//	glm::vec3 direction;
//	glm::vec3 upVector;
//
//	glm::mat4 projectionMatrix;
//	glm::mat4 viewMatrix;
//	glm::mat4 modelMatrix = glm::mat4(1.0f);
//
//	glm::mat4 MVP;
//
//	void initCamara(Camera*);
//	void setCamara(Camera*);
//
//};