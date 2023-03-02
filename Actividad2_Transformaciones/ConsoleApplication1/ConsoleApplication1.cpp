//Actividad 2 Transformaciones
// Kevin Cabrera

#include <Windows.h>
#include <thread>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>


using namespace std;

//Variables  para contar el tiempo
int t = 1, old_t = 1;
float dt = 0;

float speed = 40;
float angle = 0;
// Scale variables
float triangleScale = 0;
float speedScale = 2;
bool scaling = true;
// Translate variables
float triangleTranslate = 0;
float speedTranslate = 2;
bool translating = true;

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

void drawSquare()
{
	glBegin(GL_QUADS);
	// Vertex
	glVertex3f(0.5f, -0.5f, 0.0f);
	glVertex3f(0.5f, 0.5f, 0.0f);
	glVertex3f(-0.5f, 0.5f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.0f);
	glEnd();
}

void drawTriangle()
{
	glBegin(GL_TRIANGLES);
	// Vertex
	glVertex3f(0.5f, -0.5f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.0f);
	glVertex3f(0.0f, 0.5f, 0.0f);
	glEnd();
}

void renderScene(void)
{
	// Limpia los buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reinicia las trasnformaciones
	glLoadIdentity();

	gluLookAt(
		0, 0.0f, 15.0f, //pos
		0.0f, 0.0f, 0, //target
		0.0f, 1.0f, 0.0f); //up Vector



	t = glutGet(GLUT_ELAPSED_TIME); //Obteniendo el tiempo y el delta
	dt = (t - old_t) / 1000.0f;
	old_t = t;
	/*
	glBegin(GL_QUADS); //unos Cuads chidos

	//glPushMatrix();

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);

	//glPopMatrix();
	glEnd();
	*/

	angle += dt * speed;

	// Conditionals for Scaling
	if (scaling)
	{
		triangleScale += dt * speedScale;
		if (triangleScale > 1)
		{
			scaling = false;
		}
	}

	else
	{
		triangleScale -= dt * speedScale;
		if (triangleScale <= 0)
		{
			scaling = true;
		}
	}

	// Conditionals for Translating
	if (translating)
	{
		triangleTranslate += dt * speedTranslate;
		if (triangleTranslate > 2)
		{
			translating = false;
		}
	}

	else
	{
		triangleTranslate -= dt * speedTranslate;
		if (triangleTranslate <= 0)
		{
			translating = true;
		}
	}

	// Color White
	glColor3f(1.0f, 1.0f, 1.0f);
	// Call to the function drawSquare
	drawSquare();
	glPushMatrix();
		glRotatef(angle, 0.0f, 0.0f, 1.0f);
		glPushMatrix();
			glRotatef(angle, 0.0f, 1.0f, 0.0f);
			// Transformation of the first Triangle
			glPushMatrix();
				glTranslatef(0.0f, 1.5f, 0.0f);
				// Call to the function drawTriangle with values for Green Colors
				glColor3f(0.0f, 1.0f, 0.0f);
				drawTriangle();
				// Transformation of the second Triangle
				glTranslatef(0.0, 1.5f, 0.0f);
				// Call to the function drawTriangle with values for Yellow Color
				glColor3f(1.0f, 1.0f, 0.0f);
				drawTriangle();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glColor3f(1.0f, 0.0f, 0.0f);
		glRotatef(angle, 0.0f, 0.0f, 1.0f);
		glPushMatrix();
			// Transformation of the second Triangle
			glTranslatef(0.0f, 4.5f, 0.0f);
			glPushMatrix();
				glScalef(triangleScale, triangleScale, triangleScale);
				glPushMatrix();
					glTranslatef(0.0f, triangleTranslate, 0.0f);
					drawTriangle();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();

	/*

	// Center Quad
	glBegin(GL_QUADS);
	glPushMatrix();
	// Color White
	glColor3f(1.0f, 1.0f, 1.0f);
	// Vertex
	glVertex3f(1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glPopMatrix();
	glEnd();

	// TRIANGLES

	// Triangle 1
	glBegin(GL_TRIANGLES);
	glPushMatrix();
	// Color Green
	glColor3f(0.0f, 1.0f, 0.0f);
	// Vertex
	glVertex3f(2.0f, 1.0f, 0.0f);
	glVertex3f(2.0f, -1.0f, 0.0f);
	glVertex3f(4.0f, 0.0f, 0.0f);
	glPopMatrix();
	glEnd();

	// Triangle 2
	glBegin(GL_TRIANGLES);
	glPushMatrix();
	// Color Yellow
	glColor3f(1.0f, 1.0f, 0.0f);
	// Vertex
	glVertex3f(5.0f, 1.0f, 0.0f);
	glVertex3f(5.0f, -1.0f, 0.0f);
	glVertex3f(7.0f, 0.0f, 0.0f);
	glPopMatrix();
	glEnd();

	// Triangle 3
	glBegin(GL_TRIANGLES);
	glPushMatrix();
	// Color Red
	glColor3f(1.0f, 0.0f, 0.0f);
	// Vertex
	glVertex3f(8.0f, 0.5f, 0.0f);
	glVertex3f(8.0f, -0.5f, 0.0f);
	glVertex3f(9.0f, 0.0f, 0.0f);
	glPopMatrix();
	glEnd();

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
	}
}

void InputUp(int key, int xx, int yy)
{

	switch (key) {
	case GLUT_KEY_UP:
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

