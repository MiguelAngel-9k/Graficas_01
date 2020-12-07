#ifdef _WINDOWS
#include <windows.h>
#endif
#include <GL/glew.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>
#include <GLFW/glfw3.h>
#include "Matrizes.h"
#include "CGfxOpenGL.h"
#include "Texture.h"
#include "glm.h"
#include "cargaOps.h"
#include <../../glm/glm.hpp>
#include <../../glm/gtc/matrix_transform.hpp>

SkyBox m_skybox;
MatrixOp operacion,operacion2;
float puntos[3][3],vector[3];
float tempang,tempang2,tempang3,xx,yy,zz,Puntoseparado[3];
bool unavez=true;
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

GLfloat density = 0.0075;
GLfloat fogColor[4] = {0.5, 0.5, 0.5, 1.0};
GLuint texture;
Texture treeTexture;
GLUquadricObj *quadratic;
float translacionesx,translacionesy,translacionesz,angulox,anguloy,anguloz;
float trasfera_X,trasfera_Y,trasfera_Z;
// disable implicit float-double casting
#pragma warning(disable:4305)

CGfxOpenGL::CGfxOpenGL()
{
	grad_rad = 3.141592/180;
	y=0;	x=0; z=-10;
	xs=0;ys=0;zs=0;
	Angulo2=0;	Angulo=0;	Angulo3=0;
	mov1=0;
	mov2=0;
	mov3=0;
	mov4=0;
	mov5=0;
	mov6=0;
	scale1=0;
	scale2=0;
	giro=0;
	giroLateral = 0;
	R_bote=0;
	R_boot=0;
	R_beet=0;

	trasfera_X=0;	trasfera_Y=0;	trasfera_Z=-5;
	/*quadratic=gluNewQuadric();			
	gluQuadricNormals(quadratic, GLU_SMOOTH);
	gluQuadricTexture(quadratic, GL_TRUE);	*/
	camera.camx = 0;
	camera.camy = 0;
	camera.camz = -10;
	camera.centerx = 0;
	camera.centery = 0;
	camera.centerz = 0;
	camera.grados = 0;
	rotx = 0; rotz = -10;
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
				L"Skybox/Left.bmp", L"Skybox/left.bmp", L"Skybox/right.bmp",L"mapaTerrenoOGR2.bmp",L"ground/pavimentoAlternativo.bmp",L"ground/pavimentoAlternativo.bmp");
	
	glEnable(GL_DEPTH_TEST);
	glEnable (GL_FOG);
	glFogi (GL_FOG_MODE, GL_EXP2);
	glFogfv (GL_FOG_COLOR, fogColor);
	glFogf (GL_FOG_DENSITY, density);
	glHint (GL_FOG_HINT, GL_NICEST); 

	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat mat_shininess[] = { 100.0 };

	//glMaterialfv(GL_FRONT, GL_SPECULAR , mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	/*glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);*/

	/*glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);*/

	/*glEnable(GL_NORMALIZE);
	glClearDepth(1.0f);						
	glDepthFunc(GL_LEQUAL);								
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);*/

	m_angle = 0.0f;
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



bool Carga_texturas()
{
	if(LoadTGA(&treeTexture,"blacksmith.tga"))
	{	
		glGenTextures(1,&treeTexture.texID);
		glBindTexture(GL_TEXTURE_2D, treeTexture.texID);
		glTexImage2D(GL_TEXTURE_2D, 0, treeTexture.bpp / 8, treeTexture.width, treeTexture.height, 0, treeTexture.type, GL_UNSIGNED_BYTE, treeTexture.imageData);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glEnable(GL_TEXTURE_2D);

		if (treeTexture.imageData) 
		{
			free(treeTexture.imageData);
		}
		return true; 
	}
	else return false;

	if(LoadTGA(&treeTexture,"blacksmith_texture.tga"))
	{	
		glGenTextures(1,&treeTexture.texID);
		glBindTexture(GL_TEXTURE_2D, treeTexture.texID);
		glTexImage2D(GL_TEXTURE_2D, 0, treeTexture.bpp / 8, treeTexture.width, treeTexture.height, 0, treeTexture.type, GL_UNSIGNED_BYTE, treeTexture.imageData);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glEnable(GL_TEXTURE_2D);

		if (treeTexture.imageData) 
		{
			free(treeTexture.imageData);
		}
		return true; 
	}
	else return false;
}



void Carga_Carro()
{
	if(!Modelo)
	{
		//Modelo=new GLMmodel;
		Modelo=glmReadOBJ("jeep2.obj");
		if(!Modelo)exit(0);
		glmUnitize(Modelo);
		glmFacetNormals(Modelo);
		glmVertexNormals(Modelo,90.0);
		respmodelo=glmReadOBJ("jeep2.obj");
		if(!respmodelo)exit(0);
		glmUnitize(respmodelo);
		glmFacetNormals(respmodelo);
		glmVertexNormals(respmodelo,90.0);
	}
	//glBindTexture(GL_TEXTURE_2D, treeTexture.texID);
	glmDraw(respmodelo,GLM_SMOOTH| GLM_MATERIAL);
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

	glmDraw(Faros, GLM_SMOOTH | GLM_MATERIAL);
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
	glmDraw(pmodel2, GLM_SMOOTH| GLM_MATERIAL);
}


void Carga_Casa() {
	if (!ModeloCSA) {		
		ModeloCSA = glmReadOBJ("CSA.obj");
		if (!ModeloCSA)
			exit(0);
		glmUnitize(ModeloCSA);		
        glmFacetNormals(ModeloCSA);        
		glmVertexNormals(ModeloCSA, 90.0);		
    }
	glmDraw(ModeloCSA, GLM_SMOOTH| GLM_TEXTURE);
}


void Carga_Llanta() {
	if (!ModeloLLNTA) {		
		ModeloLLNTA = glmReadOBJ("LLTA.obj");
		if (!ModeloLLNTA)
			exit(0);
		glmUnitize(ModeloLLNTA);		
        glmFacetNormals(ModeloLLNTA);        
		glmVertexNormals(ModeloLLNTA, 90.0);		
    }
	glmDraw(ModeloLLNTA, GLM_SMOOTH| GLM_TEXTURE);
}



void Carga_Hacha() {
	if (!ModeloHCHA) {		
		ModeloHCHA = glmReadOBJ("hachafinal.obj");
		if (!ModeloHCHA)
			exit(0);
		glmUnitize(ModeloHCHA);		
        glmFacetNormals(ModeloHCHA);        
		glmVertexNormals(ModeloHCHA, 90.0);		
    }
	glmDraw(ModeloHCHA, GLM_SMOOTH| GLM_TEXTURE);
}





void Carga_Barco() {
	if (!ModeloBRCO) {		
		ModeloBRCO = glmReadOBJ("barcofinal.obj");
		if (!ModeloBRCO)
			exit(0);
		glmUnitize(ModeloBRCO);		
        glmFacetNormals(ModeloBRCO);        
		glmVertexNormals(ModeloBRCO, 90.0);		
    }
	glmDraw(ModeloBRCO, GLM_SMOOTH| GLM_TEXTURE);
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


void Carga_Troncos() {
	if (!ModeloTRONK) {		
		ModeloTRONK = glmReadOBJ("Protagonista/protagonista_1.obj");
		if (!ModeloTRONK)
			exit(0);
		glmUnitize(ModeloTRONK);		
        glmFacetNormals(ModeloTRONK);        
		glmVertexNormals(ModeloTRONK, 45.0);		
    }
	glmDraw(ModeloTRONK, GLM_SMOOTH| GLM_TEXTURE);
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
	tempang=Angulo;
	tempang2=Angulo2;
	tempang3=Angulo3;
	translacionesx=x;
	translacionesy=y;
	translacionesz=z;
	angulox=Angulo;
	anguloy=Angulo2;
	anguloz=Angulo3;
	trasfera_X=xs;
	trasfera_Y=ys;
	trasfera_Z=zs;
	if(Angulo>=360)
	{
		Angulo=0;
	}
	else
	{
		if(Angulo2>=360)
		{
			Angulo=0;
		}
		else
		{
			if(Angulo3>=360)
			{
				Angulo=0;
			}
		}
	}
	glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GLfloat light_position[] = {0,-33,0.0,0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLoadIdentity();
	glClearColor(-1.7, 0.2, 0.4, 0.5f);	

	this->cameraUpdate();


	m_skybox.Traza(0,0,-10);


			glPushMatrix();
			operacion.lmadCargaIdentidad (operacion.raiz);
			operacion.lmadTranslacion (0,2,0);


	m_skybox.DibujaTerreno();
	m_skybox.DibujaAGUATerreno();
	glPopMatrix();


	glPushMatrix();		
		glTranslatef(-10, 40, -25);
		glScalef(20, 20, 20);
		glRotatef(180,0, 1, 0);
		Carga_casa_vieja();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(8, 27, -5);
		glScalef(4.5,4.5,4.5);
		Carga_Hombre();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(25, 64, -5);
		glScalef(40,40,40);		
		Carga_Edficio();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(56, 64, -5);
		glScalef(40, 40, 40);
		Carga_Edficio();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-60, 55, -5);
		glScalef(35, 35, 35);
		Carga_Edificio2();
	glPopMatrix();

	//acera de enfrente
	glPushMatrix();		
		glTranslatef(-10, 40, 130 );
		glScalef(20, 20, 20);		
		Carga_casa_vieja();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(25, 64, 130);
		glScalef(40,40,40);		
		glRotatef(180, 0, 1, 0);
		Carga_Edficio();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(56, 64, 130);
		glScalef(40, 40, 40);
		glRotatef(180, 0, 1, 0);
		Carga_Edficio();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-60, 55, 130);
		glScalef(35, 35, 35);
		glRotatef(180, 0, 1, 0);
		Carga_Edificio2();
	glPopMatrix();

	//Faro	
	int posicion = -100;

	glPushMatrix();
	glTranslatef(posicion, 40, 38);
	glScalef(20, 20, 20);
	glRotatef(-90, 0, 1, 0);
	Carga_Faros();
	glPopMatrix();

	for (int _faro = 1; _faro < 8; _faro++) {
		glPushMatrix();
			glTranslatef(posicion + 30, 40, 38);
			glScalef(20, 20, 20);
			glRotatef(-90, 0, 1, 0);
			Carga_Faros();
		glPopMatrix();
		posicion = posicion + 30;
	}

	posicion = -100;
	for (int _faro = 1; _faro < 8; _faro++) {
		glPushMatrix();
		glTranslatef(posicion + 30, 40, 80);
		glScalef(20, 20, 20);
		glRotatef(90, 0, 1, 0);
		Carga_Faros();
		glPopMatrix();
		posicion = posicion + 30;
	}

		glPushMatrix();
			operacion.lmadCargaIdentidad (operacion.raiz);
			operacion.lmadRotacion(0, 180, 0);
			operacion.lmadTranslacion (0,0,-3);
			//operacion.lmadRotacion (giroLateral,giro,0);
			operacion.lmadEscala(4, 4, 4);
			glLoadMatrixf(operacion.MC);

		Carga_Troncos();
		glPopMatrix();	


		/*glm::vec3 position(this->px, this->py, this->pz);
		glm::vec3 direction(this->dx, this->dy, this->dz);
		glm::vec3 upVector(this->ux, this->uy, this->uz);*/

		//Matriz de la vista
		glm::mat4 viewMatrix;
		viewMatrix[0] = glm::vec4(this->px, this->py, this->pz, 1);
		viewMatrix[1] = glm::vec4(this->dx, this->dy, this->dz,1);
		viewMatrix[2] = glm::vec4 (this->ux, this->uy, this->uz,1);
		viewMatrix[3] = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

		//matrix de la proyeccion (lo que se ve)
		glm::mat4 projectionMatrix = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

		//y la posicion o a donde se mira
		glm::mat4 modelMatrix(1.0f);

		//lo juntamos todo
		glm::mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;


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



