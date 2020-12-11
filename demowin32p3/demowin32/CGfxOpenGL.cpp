#ifdef _WINDOWS
#include <windows.h>
#endif
#include "glew.h"
//#include "GL/glew.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>
#include <glfw3.h>
#include "Matrizes.h"
#include "CGfxOpenGL.h"
#include "Texture.h"
#include "glm.h"
#include "cargaOps.h"
#include <iostream>
//#include "shader.cpp"
#include <../../../glm/glm.hpp>
#include <../../../glm/gtc/matrix_transform.hpp>

SkyBox m_skybox;
MatrixOp operacion,operacion2;
GLMmodel *Modelo=NULL;
GLMmodel *pmodel2=NULL;
GLMmodel *Edificio2=NULL;
GLMmodel *respmodelo=NULL;
GLMmodel *ModeloCSA=NULL;
GLMmodel *ModeloLLNTA=NULL;
GLMmodel *ModeloHCHA=NULL;
GLMmodel *ModeloBRCO=NULL;
GLMmodel *ModeloTRONK=NULL;
GLMmodel *casaVieja = NULL;
GLMmodel *Hombre = NULL;
GLMmodel *Edificio = NULL;
GLMmodel *Faros = NULL;


GLfloat lightPos[] = { 0,100,0 };
GLfloat lightColor[] = {0.9,0.9,1};
GLfloat ambColor[] = { 0.0,0.0,0.0 };

void setMaterials(GLfloat ambientR, GLfloat ambientG, GLfloat ambientB, GLfloat diffueR, GLfloat diffueG, GLfloat diffueB, GLfloat specularR, GLfloat specularG, GLfloat specularB, GLfloat shinines) {

	GLfloat ambient[] = { ambientR, ambientG, ambientB };
	GLfloat diffuse[] = { diffueR, diffueG, diffueB };
	GLfloat specular[] = { specularR, specularG, specularB };

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shinines);

}

GLuint texture;
Texture treeTexture;
GLUquadricObj *quadratic;


#pragma warning(disable:4305)

CGfxOpenGL::CGfxOpenGL()
{
	
	this->cameraInitialize();

}


CGfxOpenGL::~CGfxOpenGL()
{
}


bool CGfxOpenGL::Init()
{
	// clear to black background
	m_skybox.Tamaño(190.0);
	m_skybox.CargaTextura(L"Skybox/arriba.bmp", L"Skybox/abajo.bmp", L"Skybox/Front2.bmp",
				L"Skybox/Left.bmp", L"Skybox/left.bmp", L"Skybox/right.bmp",L"mapaTerrenoOGR3.bmp",L"ground/pavimentoAlternativo.bmp", L"segudoTerreno",L"bottom.bmp");
	
	glEnable(GL_LIGHTING);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambColor);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightColor);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightColor);

	setMaterials(1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0);

	return true;
}


bool CGfxOpenGL::Shutdown()
{
	m_skybox.Libera();
	return true;
}

void CGfxOpenGL::SetupProjection(int width, int height)
{
	if (height == 0) // don’t want a divide by zero
	{
		height = 1;
	}

	glViewport(0, 0, width, height); // reset the viewport to new dimensions
	glMatrixMode(GL_PROJECTION); // set projection matrix current matrix
	glLoadIdentity(); // reset projection matrix

	// calculate aspect ratio of window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,1.0f,1000.0f);
	glMatrixMode(GL_MODELVIEW); // set modelview matrix
	glLoadIdentity(); // reset modelview matrix
	m_windowWidth = width;
	m_windowHeight = height;
}
//estableces modo matriz

void CGfxOpenGL::Prepare(float dt)
{
	m_angle += 0.1f;
}


void Carga_casa_vieja()
{	
	if (!casaVieja)
	{
		casaVieja = glmReadOBJ("old_house_obj/casa_vieja_5.obj");
		if (!casaVieja)
			exit(0);
		glmUnitize(casaVieja);
		glmFacetNormals(casaVieja);
		glmVertexNormals(casaVieja, 90.0);
	}

	glmDraw(casaVieja, GLM_SMOOTH | GLM_TEXTURE);
}

void Carga_Faros()
{	
	if (!Faros)
	{
		Faros = glmReadOBJ("calle/Faro.obj");
		if (!Faros)
			exit(0);
		glmUnitize(Faros);
		glmFacetNormals(Faros);
		glmVertexNormals(Faros, 90.0);
	}

	glmDraw(Faros, GLM_SMOOTH | GLM_TEXTURE);
}




void Carga_Nave() {
	if (!pmodel2) {		
		pmodel2 = glmReadOBJ("Hombre.obj");
		if (!pmodel2)
			exit(0);
		glmUnitize(pmodel2);		
        glmFacetNormals(pmodel2);        
		glmVertexNormals(pmodel2, 90.0);		
    }
	glmDraw(pmodel2, GLM_SMOOTH| GLM_TEXTURE);
}


void Carga_Hombre() {
	if (!Hombre) {
		Hombre = glmReadOBJ("Hombre/Hombre.obj");
		if (!Hombre)
			exit(0);
		glmUnitize(Hombre);
		glmFacetNormals(Hombre);
		glmVertexNormals(Hombre, 90.0);
	}
	glmDraw(Hombre, GLM_SMOOTH | GLM_TEXTURE);
}


void Carga_Edficio() {
	if (!Edificio) {
		Edificio = glmReadOBJ("Edificio/Building.obj");
		if (!Edificio)
			exit(0);
		glmUnitize(Edificio);
		glmFacetNormals(Edificio);
		glmVertexNormals(Edificio, 90.0);
	}
	glmDraw(Edificio, GLM_SMOOTH | GLM_TEXTURE);
}

void Carga_Edificio2() {
	if (!Edificio2) {		
		Edificio2 = glmReadOBJ("Edificio2/Edificio2.obj");
		if (!Edificio2)
			exit(0);
		glmUnitize(Edificio2);
        glmFacetNormals(Edificio2);
		glmVertexNormals(Edificio2, 90.0);
    }
	//glBindTexture(GL_TEXTURE_2D, treeTexture.texID);
	glmDraw(Edificio2, GLM_SMOOTH| GLM_TEXTURE);
}


void CGfxOpenGL::Render()
{
	glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glClearColor(-1.7, 0.2, 0.4, 0.5f);	

	this->cameraUpdate();


	m_skybox.Traza(0,0,-10);


			glPushMatrix();
			operacion.lmadCargaIdentidad (operacion.raiz);
			operacion.lmadTranslacion (0,2,0);


	m_skybox.DibujaTerreno();
	//m_skybox.DibujaAGUATerreno();
	glPopMatrix();


	glPushMatrix();		
		glTranslatef(-10, 40, -100);
		glScalef(20, 20, 20);
		glRotatef(180,0, 1, 0);
		Carga_casa_vieja();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(8, 27, -55);
		glScalef(4.5,4.5,4.5);
		Carga_Hombre();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(25, 64, -80);
		glScalef(40,40,40);		
		Carga_Edficio();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(56, 64, -80);
		glScalef(40, 40, 40);
		Carga_Edficio();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-60, 55, -80);
		glScalef(35, 35, 35);
		Carga_Edificio2();
	glPopMatrix();

	//acera de enfrente
	glPushMatrix();		
		glTranslatef(-10, 40, 90 );
		glScalef(20, 20, 20);		
		Carga_casa_vieja();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(25, 64, 90);
		glScalef(40,40,40);		
		glRotatef(180, 0, 1, 0);
		Carga_Edficio();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(56, 64, 90);
		glScalef(40, 40, 40);
		glRotatef(180, 0, 1, 0);
		Carga_Edficio();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-60, 55, 90);
		glScalef(35, 35, 35);
		glRotatef(180, 0, 1, 0);
		Carga_Edificio2();
	glPopMatrix();

	//Faro	
	int posicion = -100;

	glPushMatrix();
	glTranslatef(posicion, 40, -30);
	glScalef(20, 20, 20);
	glRotatef(-90, 0, 1, 0);
	Carga_Faros();
	glPopMatrix();

	for (int _faro = 1; _faro < 8; _faro++) {
		glPushMatrix();
			glTranslatef(posicion + 30, 40, -30);
			glScalef(20, 20, 20);
			glRotatef(-90, 0, 1, 0);
			Carga_Faros();
		glPopMatrix();
		posicion = posicion + 30;
	}

	posicion = -100;
	for (int _faro = 1; _faro < 8; _faro++) {
		glPushMatrix();
		glTranslatef(posicion + 30, 40, 40);
		glScalef(20, 20, 20);
		glRotatef(90, 0, 1, 0);
		Carga_Faros();
		glPopMatrix();
		posicion = posicion + 30;
	}

		//glPushMatrix();
		//	operacion.lmadCargaIdentidad (operacion.raiz);
		//	operacion.lmadRotacion(0, 180, 0);
		//	operacion.lmadTranslacion (0,0,-3);
		//	//operacion.lmadRotacion (giroLateral,giro,0);
		//	operacion.lmadEscala(4, 4, 4);
		//	glLoadMatrixf(operacion.MC);

		//Carga_Troncos();
		//glPopMatrix();	


		/*glm::vec3 position(this->px, this->py, this->pz);
		glm::vec3 direction(this->dx, this->dy, this->dz);
		glm::vec3 upVector(this->ux, this->uy, this->uz);*/

		//Matriz de la vista



}


	//void cameraSettings::initCamara(Camera* newCamera) {
	//	newCamera->px = 0, newCamera->py = 30, newCamera->pz = 0, newCamera->dx = 0, newCamera->dy = 23, newCamera->dz = -25;
	//	newCamera->ux = 0, newCamera->uy = 1, newCamera->uz = 0;
	//	/*gluLookAt(newCamera.px, newCamera.py, newCamera.pz, newCamera.dx, newCamera.dy, newCamera.dz, newCamera.ux, newCamera.uy, newCamera.uz);
	//	newCamera.viewVectorMag = sqrt(pow(newCamera.dx - newCamera.px, 2) + pow(newCamera.dz - newCamera.pz, 2));*/
	//	newCamera->ableToMove = true;
	//}

	//void cameraSettings::setCamara(Camera* camaraValues) {

	//	position = glm::vec3(camaraValues->px, camaraValues->py, camaraValues->pz);
	//	direction = glm::vec3(camaraValues->dx, camaraValues->dy, camaraValues->dz);
	//	upVector = glm::vec3(camaraValues->ux, camaraValues->uy, camaraValues->uz);

	//	projectionMatrix = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	//	//viewMatrix = glm::lookAt(position, (direction + position), upVector);

	//	MVP = projectionMatrix * viewMatrix * modelMatrix;
	//}



