#include <Windows.h>
#include <thread>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include "PyramidController.h"
#include "Piramide.h"

using namespace std;

// Variables to measure time
int t = 1, old_t = 1;
float dt = 0;
float angleVelocity = 60.0f;
float angle;
float slider = 0;
float sliderY = 0;
float amplitud = 15;
float amplitudB = 5;
bool goingLeft = false, goingRight = false;
bool goingUp = false, goingDown = false;

const int numPiramides = 1;

// Declaration Pyramid Array
PyramidController* pyramidArray = new PyramidController[9];

Piramide piramide[numPiramides];

// Variable to control the Pyramid size
float pyramidSize = 1.0f;

// Variables to control the Pyramid's Translation (Where the Pyramids Start)
// Z Axe Cube Boundaries -6(back) to 0(front)
float pyramidTranslation[10] =
{
	-4.0f,
	-2.0f,
	-3.0f,
	-1.0f,
	-4.0f,
	-1.0f,
	-5.0f,
	-4.0f,
	0.0f,
	-3.0f
};
bool pyramidDirection[10] = { true, true, true, true, true, true, true, true, true, true };

//Variables to control RGB
float pyramidColor[10][3] =
{
	{0.0f, 0.0f, 1.0f},
	{0.0f, 1.0f, 1.0f},
	{1.0f, 0.0f, 1.0f},
	{1.0f, 0.0f, 0.0f},
	{0.0f, 1.0f, 0.0f},
	{1.0f, 1.0f, 1.0f},
	{1.0f, 1.0f, 0.0f},
	{0.35f, 0.0f, 0.64f},
	{0.0f, 0.74f, 0.32f},
	{0.67f, 0.45f, 0.27f}
};

// *** Methods to Draw each face of the CUBE ***

void dibujarEjes()
{
	//ejes
	glEnable(GL_LINE_STIPPLE);
	short patron = 0xF0F0;
	glLineStipple(8, patron);
	glBegin(GL_LINES);

	//ejeX
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-20.0f, 0.0f, 0.0f);
	glVertex3f(20.0f, 0.0f, 0.0f);

	//ejeY
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, -20.0f, 0.0f);
	glVertex3f(0.0f, 20.0f, 0.0f);

	//ejeZ
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, -20.0f);
	glVertex3f(0.0f, 0.0f, 20.0f);

	glEnd();
	glDisable(GL_LINE_STIPPLE);

}

void dibujarCubo
{
	glPolygonMode(gl)
		//cubo
	glBegin(GL_QUADS);

	glColor3f(0.6f, 0.6f, 0.6f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);//FRONT

	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);//back


	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f); //right

	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f); //left


	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f); //top


	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f); //bottom

	glEnd();

}

void dibujarPiramide()
{
	float _r = 0.5f, _g = 0.5f, _b = 0.5f;

	glBegin(GL_QUADS);
			glColor3f(_r, _g, _b); //blanco

			glVertex3f(-1.0f, -0.5f, 1.0f);
			glVertex3f(-1.0f, -0.5f, -1.0f);
			glVertex3f(1.0f, -0.5f, -1.0f);
			glVertex3f(1.0f, -0.5f, 1.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
			glColor3f(_r + 0.15f, _g + 0.15f, _b + 0.15f); //red

			glVertex3f(0.0f, 1, 0.0f);
			glVertex3f(-1.0f, -0.5f, 1.0f);
			glVertex3f(-1.0f, -0.5f, -1.0f);


			glColor3f(_r + 0.25f, _g + 0.25f, _b + 0.25f); //green

			glVertex3f(0.0f, 1, 0.0f);
			glVertex3f(-1.0f, -0.5f, -1.0f);
			glVertex3f(1.0f, -0.5f, -1.0f);

			glColor3f(_r - 0.1f, _g - 0.1f, _b - 0.1f); //blue

			glVertex3f(0.0f, 1, 0.0f);
			glVertex3f(1.0f, -0.5f, 1.0f);
			glVertex3f(-1.0f, -0.5f, 1.0f);

			glColor3f(_r - 0.25f, _g - 0.25f, _b - 0.25f); //magenta

			glVertex3f(0.0f, 1, 0.0f);
			glVertex3f(1.0f, -0.5f, 1.0f);
			glVertex3f(1.0f, -0.5f, -1.0f);
	glEnd();
}

// Front
void drawFrontQuad()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
	glVertex3f(6, 6, 0);
	glVertex3f(6, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 6, 0);
	glEnd();
}

// Back
void drawBackQuad()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
	glVertex3f(6, 6, -6);
	glVertex3f(6, 0, -6);
	glVertex3f(0, 0, -6);
	glVertex3f(0, 6, -6);
	glEnd();
}

// Left Quad
void drawLeftQuad()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
	glVertex3f(6, 6, 0);
	glVertex3f(6, 0, 0);
	glVertex3f(6, 0, -6);
	glVertex3f(6, 6, -6);
	glEnd();
}

// Right Quad
void drawRightQuad()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 6, 0);
	glVertex3f(0, 6, -6);
	glVertex3f(0, 0, -6);
	glEnd();
}

// Base Quad
void drawBaseQuad()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUADS);
	glVertex3f(6, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, -6);
	glVertex3f(6, 0, -6);
	glEnd();
}

// Top Quad
void drawTopQuad()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
	glVertex3f(6, 6, 0);
	glVertex3f(0, 6, 0);
	glVertex3f(0, 6, -6);
	glVertex3f(6, 6, -6);
	glEnd();
}

// Method to control the Pyramids recives the number Pyramid iteration
void pyramidControl(int pyramidIteration)
{

	if (pyramidDirection[pyramidIteration])
	{
		// If the pyramid has not reached the boundaries
		if (pyramidTranslation[pyramidIteration] < -0.5f)
		{
			// Move constantly in 0.03
			pyramidTranslation[pyramidIteration] += 0.03f;
		}
		else
		{
			// Moving Backwards
			pyramidDirection[pyramidIteration] = false;
		}
	}
	else
	{
		// If the pyramid has reached the boundaries
		if (pyramidTranslation[pyramidIteration] > -4.0f)
		{
			// Move constantly in - 0.03
			pyramidTranslation[pyramidIteration] -= 0.03f;
		}
		else
		{
			// Keep Moving
			pyramidDirection[pyramidIteration] = true;
		}
	}
}

// Method that describes the Pyramid Movement for each Pyramid
void pyramidMovement(int pyramidIteration)
{
	switch (pyramidIteration)
	{
	case 0:	//Translate(x,y,z)
		glTranslatef(pyramidTranslation[pyramidIteration] + 4.0f, 1.0f, pyramidTranslation[pyramidIteration]);
		break;
	case 1: //Translate(x,y,z)
		glTranslatef(pyramidTranslation[pyramidIteration] + 4.0f, pyramidTranslation[pyramidIteration] + 3.0f, -3.0f);
		break;
	case 2: //Translate(x,y,z)
		glTranslatef(0.0f, pyramidTranslation[pyramidIteration] + 3.0f, pyramidTranslation[pyramidIteration]);
		break;
	case 3: //Translate(x,y,z)
		glTranslatef(pyramidTranslation[pyramidIteration] + 4.0f, pyramidTranslation[pyramidIteration] + 3.0f, -2.0f);
		break;
	case 4: //Translate(x,y,z)
		glTranslatef(pyramidTranslation[pyramidIteration] + 4.0f, -2.0f, pyramidTranslation[pyramidIteration]);
		break;
	case 5: //Translate(x,y,z)
		glTranslatef(3.0f, pyramidTranslation[pyramidIteration] + 3.0f, pyramidTranslation[pyramidIteration]);
		break;
	case 6: //Translate(x,y,z)
		glTranslatef(pyramidTranslation[pyramidIteration] + 4.0f, 0.0f, -2.0f);
		break;
	case 7: //Translate(x,y,z)
		glTranslatef(4.0f, pyramidTranslation[pyramidIteration] + 3.0f, pyramidTranslation[pyramidIteration]);
		break;
	case 8: //Translate(x,y,z)
		glTranslatef(pyramidTranslation[pyramidIteration] + 4.0f, pyramidTranslation[pyramidIteration] + 3.0f, -6.0f);
		break;
	case 9: //Translate(x,y,z)
		glTranslatef(pyramidTranslation[pyramidIteration] + 4.0f, pyramidTranslation[pyramidIteration] + 3.0f, pyramidTranslation[pyramidIteration]);
		break;
	}
}

// Method to Rotate the Pyramids 
// Each Rotate rotates the Pyramid on its axis
void PyramidRotation(int pyramidIteration) {
	switch (pyramidIteration)
	{
	case 0:
		glRotatef(t / 6.0f, 0.0f, 1.0f, 0.0f);
		break;
	case 1:
		glRotatef(t / 6.0f, 1.0f, 0.0f, 0.0f);
		break;
	case 2:
		glRotatef(t / 6.0f, 1.0f, 0.0f, 1.0f);
		break;
	case 3:
		glRotatef(t / 6.0f, 0.0f, 0.0f, 1.0f);
		break;
	case 4:
		glRotatef(t / 6.0f, 0.0f, 1.0f, 1.0f);
		break;
	case 5:
		glRotatef(t / 6.0f, 1.0f, 1.0f, 0.0f);
	case 6:
		glRotatef(t / 6.0f, 1.0f, 1.0f, 1.0f);
		break;
	case 7:
		glRotatef(t / 6.0f, 0.0f, 0.0f, 1.0f);
		break;
	case 8:
		glRotatef(t / 6.0f, 0.0f, 1.0f, 0.0f);
		break;
	case 9:
		glRotatef(t / 6.0f, 1.0f, 0.0f, 0.0f);
		break;
	}
}

#pragma region OpenGLSetupInputAndStuff

void changeWindowSize(int w, int h)
{
	cout << "redim" << endl;
	// Previene una división por cero, cuando la ventana es demasiado corta
	// (no puede haber ventana con 0 de ancho).
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;

	// Usa la matriz de proyección
	glMatrixMode(GL_PROJECTION);

	// Reinicia Matriz
	glLoadIdentity();

	// Hace que el Viewport use toda la pantalla
	glViewport(0, 0, w, h);

	// da la perspectiva correcta, fov, ratio, nearClip, farClip
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// usa la matriz de modelos the Modelview
	glMatrixMode(GL_MODELVIEW);
}



void Initialization() {
	cout << "Codigo inicial aqui" << endl;
}

void renderScene(void)
{
	// Limpia los buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reinicia las trasnformaciones
	glLoadIdentity();

	gluLookAt(
		(sin(slider) * amplitud), 0, (cos(slider) * amplitud), //pos
		0.0f, 0.0f, 0, //target
		0.0f, 1.0f, 0.0f); //up Vector
	
	gluLookAt(
		(cos(sliderY) * amplitudB), 0, (sin(sliderY) * amplitudB),
			0.0f, 0.0f, 0, //target
			1.0f, 1.0f, .0f); //up Vector
	

	t = glutGet(GLUT_ELAPSED_TIME); //Obteniendo el tiempo y el delta
	dt = (t - old_t) / 1000.0f;
	old_t = t;

	if (goingLeft) slider -= dt * 5;
	if (goingRight) slider += dt * 5;
	if (goingUp) sliderY -= dt * 5;
	if (goingDown) sliderY += dt * 5;
	
	angle += angleVelocity * dt;
	// Actualiza la variable de escala

	dibujarEjes();
	dibujarPiramide();

	for (int i = 0; i < length; i++)
	{

	}


	glutSwapBuffers(); //intercambia los búferes de la ventana actual si tiene doble búfer.
}

void processNormalKeys(unsigned char key, int x, int y)
{
	//cout << (int)key << endl;
	if (key == 27)
		exit(0);
}

void InputDown(int key, int xx, int yy)
{
	switch (key)
	{
	case GLUT_KEY_RIGHT:
		goingRight = true;
		break;
	case GLUT_KEY_LEFT:
		goingLeft = true;
		break;
	case GLUT_KEY_UP:
		goingUp = true;
		break;
	case GLUT_KEY_DOWN:
		goingDown = true;
		break;
	}
}

void InputUp(int key, int xx, int yy)
{

	switch (key) 
	{
	case GLUT_KEY_RIGHT:
		goingRight = false;
		break;
	case GLUT_KEY_LEFT:
		goingLeft = false;
		break;
	case GLUT_KEY_UP:
		goingUp = false;
		break;
	case GLUT_KEY_DOWN:
		goingDown = false;
		break;
	}
}
#pragma endregion

int main(int argc, char* argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1600, 900); //dimensiones
	glutCreateWindow("TemplateWindow");
	Initialization();

	// register callbacks
	glutDisplayFunc(renderScene); //establece el callback de visualización para la ventana actual. 
	glutReshapeFunc(changeWindowSize); //establece el callback de redimensionado para la ventana actual
	glutIdleFunc(renderScene); //establece el callback global de inactividad.(si no recibe eventos, resize, etc)
	glutKeyboardFunc(processNormalKeys);//las teclas ASCII
	//glutKeyboardUpFunc(processNormalKeys); 
	glutSpecialFunc(InputDown); //teclas especiales
	glutSpecialUpFunc(InputUp); //teclas especiales al soltarse	

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	// entrar GLUT al ciclo de procesamiento de eventos
	glutMainLoop();

	return 1;
}
