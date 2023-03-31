// Actividad Asesorias 2
// Kevin Cabrera

#include <Windows.h>
#include <thread>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

//Variables  para contar el tiempo
int t = 1, old_t = 1;
float dt = 0;

bool _left, _right = false;

// Cuadro Paleta
float posicionX = 0;

// Pelota
float pelotaX = 5.0f;
float pelotaY = 5.0f;
bool dirX, dirY = false;

float productoP = 0.0f;

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

void Initialization() 
{
	cout << "Codigo inicial aqui" << endl;
	srand(time(NULL));
	// Rango de -1 a 1
	productoP = (float)(rand() % 201 - 100) / 100.0f;
	cout << productoP << endl;

	// Rango de 0 a 1
	productoP = (productoP + 1.0f) / 2.0f;
	cout << productoP << endl;
}

void DibujarCuadro()
{
	glBegin(GL_QUADS);
		glVertex3f(-0.5f, 0.5f, 0.0f);
		glVertex3f(0.5f, 0.5f, 0.0f);
		glVertex3f(0.5f, -0.5f, 0.0f);
		glVertex3f(-0.5f, -0.5f, 0.0f);
	glEnd();
}


void Pelota()
{
	// Colision con la paleta
	// Si choca con el borde izquierdo o derecho de la pelota
	/*if (pelotaY - dt <= 0.5f && pelotaX >= posicionX - 0.5f && pelotaX <= posicionX + 0.5f);
	{
		dirY = true;
	}
	*/
	
	// Limites X
	if (pelotaX + dt >= 6)
	{
		dirX = false;
	}
	if (pelotaX - dt <= -6)
	{
		dirX = true;
	}

	// Limites Y
	if (pelotaY + dt >= 8)
	{
		dirY = false;
	}
	if (pelotaY - dt <= -1)
	{
		dirY = true;
	}

	// Movimiento 
	if (dirX == true)
	{
		pelotaX += dt;
	}
	else
	{
		pelotaX -= dt;
	}

	if (dirY == true)
	{
		pelotaY += dt;
	}
	else
	{
		pelotaY -= dt;
	}

	glPushMatrix();
	glTranslatef(pelotaX, pelotaY, 0.0f);
		glBegin(GL_QUADS);
			glVertex3f(-0.2f, 0.2f, 0.0f);
			glVertex3f(0.2f, 0.2f, 0.0f);
			glVertex3f(0.2f, -0.2f, 0.0f);
			glVertex3f(-0.2f, -0.2f, 0.0f);
		glEnd();
	glPopMatrix();
}


void renderScene(void)
{
	// Limpia los buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reinicia las trasnformaciones
	glLoadIdentity();

	gluLookAt(
		0, 3.0f, 15.0f, //pos
		0.0f, 3.0f, 0, //target
		0.0f, 1.0f, 0.0f); //up Vector



	t = glutGet(GLUT_ELAPSED_TIME); //Obteniendo el tiempo y el delta
	dt = (t - old_t) / 1000.0f;
	old_t = t;

	
	/*
	if (_right == true)
	{
		posicionX += dt * 2;
	}
	if (_left == true)
	{
		posicionX -= dt * 2;
	}
	
	glPushMatrix();
		glTranslatef(posicionX, 0.0f, 0.0f);
		DibujarCuadro();
	glPopMatrix();

	Pelota();
	*/

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
	case GLUT_KEY_UP://GLUT_KEY_UP:		
		break;
	case GLUT_KEY_RIGHT:
		_right = true;
		break;
	case GLUT_KEY_LEFT:
		_left = true;
		break;
	}
}

void InputUp(int key, int xx, int yy)
{

	switch (key) {
	case GLUT_KEY_UP:
		break;
	case GLUT_KEY_RIGHT:
		_right = false;
		break;
	case GLUT_KEY_LEFT:
		_left = false;
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

