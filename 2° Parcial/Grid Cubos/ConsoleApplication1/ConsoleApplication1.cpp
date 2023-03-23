#include <Windows.h>
#include <thread>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include "CubeController.h"

using namespace std;

// Variables to measure time
int t = 1, old_t = 1;
float dt = 0;
float angleVelocity = 60.0f;
float angle;
float slider = 0;
float sliderY = 0;
float amplitud = 10;
float amplitudB = 25;
bool goingLeft = false, goingRight = false;
bool goingUp = false, goingDown = false;

// Matriz
const int rows = 2, col = 2;

float colores[rows * col][3];
float size[rows * col];
float _direc[rows * col];
float _posZ[rows * col];
float _speedZ[rows * col];

 
 // Cube Size
float cubeSize = 1.0f;

/*
class MATRIZ
{
public:
	void Matriz()
	{
		for (int f = 0; f < rows; f++)
		{
			for (int c = 0; c < col; c++)
			{
				_Matriz[f][c] = 0;
			}
		}
	}

	void LlenarMatriz()
	{
		for (int f = 0; f < rows; f++)
		{
			for()
		}
	}

private:
	int _Matriz[rows][col];
};

*/

CubeController* CubeArray = new CubeController[5];

// Cube Start position
float cubeTranslation[5] =
{
	-1.5f,
	-1.0f,
	-0.5f,
	0.0f,
	1.0f,
};

bool cubeDirection[5] = { true, true, true, true, true };

float cubeColor[5][3] =
{
	{0.0f, 0.0f, 1.0f},
	{0.0f, 1.0f, 1.0f},
	{1.0f, 0.0f, 1.0f},
	{1.0f, 0.0f, 0.0f},
	{0.0f, 1.0f, 0.0f},
};

void CubeControl(int cubeI)
{
	if (cubeDirection[cubeI])
	{
		if (cubeTranslation[cubeI] < -1.5f)
		{
			cubeTranslation[cubeI] += 0.03f;
		}
		else
		{
			cubeDirection[cubeI] = false;
		}
	}
	else
	{
		if (cubeTranslation[cubeI] > 1.5)
		{
			cubeTranslation[cubeI] -= 0.03f;
		}
		else
		{
			cubeDirection[cubeI] = true;
		}
	}
}

void CubeMovement(int cubeI)
{
	switch (cubeI)
	{
	case 0:
		glTranslatef(0.0f, 0.0f, cubeTranslation[cubeI] - 1.5f);
		break;
	case 1:
		glTranslatef(0.0f, 0.0f, cubeTranslation[cubeI] - 1.5f);
		break;
	case 2:
		glTranslatef(0.0f, 0.0f, cubeTranslation[cubeI] - 1.5f);
		break;
	case 3:
		glTranslatef(0.0f, 0.0f, cubeTranslation[cubeI] - 1.5f);
		break;
	case 4:
		glTranslatef(0.0f, 0.0f, cubeTranslation[cubeI] - 1.5f);
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



void Initialization()
{
	cout << "Codigo inicial aqui" << endl;

	for (int i = 0; i < rows * col; i++)
	{
		colores[i][0] = (rand());
	}

	int indexCube = 0;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < col; j++)
		{
			float moveV = _dt * _speedZ[indexCube];

			if (_direc[indexCube]) +);
			glPushMatrix(); 
			glTranslatef(i * 2.5f, j * 2.5f, 0);
			CuboExamen(colores[indexCube][0], colores[indexCube][1]], colores[indexCube][2]);
		}
	}

}

void CuboExamen(float r, float g, float b)
{
	glBegin(GL_QUADS);

	// FRONT
	// Color variation
	glColor3f(r, g, b);
	glColor3f(0.6f, 0.6f, 0.6f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	// BACK
	// Color variation

	glColor3f(r - 0.1f, g - 0.1f, b - 0.1f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	// RIGHT
	// Color variation

	glColor3f(r, g, b);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);

	// LEFT
	// Color variation
	
	glColor3f(r, g, b);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);

	// TOP
	// Color variation

	glColor3f(r, g, b);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);

	// BOTTOM
	// Color variation

	glColor3f(r, g, b);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);


	glEnd();
}

void renderScene(void)
{
	// Limpia los buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reinicia las trasnformaciones
	glLoadIdentity();

	gluLookAt(
		(sin(slider) * amplitud), + col, rows, (cos(slider) * amplitud), //pos
		col, rows, 0, //target
		0.0f, 1.0f, 0.0f); //up Vector
	
	t = glutGet(GLUT_ELAPSED_TIME); //Obteniendo el tiempo y el delta
	dt = (t - old_t) / 1000.0f;
	old_t = t;

	if (goingLeft) slider -= dt * 5;
	if (goingRight) slider += dt * 5;
	if (goingUp) sliderY -= dt * 5;
	if (goingDown) sliderY += dt * 5;
	
	angle += angleVelocity * dt;
	// Actualiza la variable de escala


	for (int i = 0; i < 5; i++)
	{
		glPushMatrix();
			CubeMovement(i);
			CubeControl(i);
			glPushMatrix();
				glScalef(cubeSize, cubeSize, cubeSize);
				CubeArray[i].cubeGenerator(cubeColor[i][0], cubeColor[i][1], cubeColor[i][2]);
			glPopMatrix();
		glPopMatrix();
		cubeSize -= 1.0f;
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
