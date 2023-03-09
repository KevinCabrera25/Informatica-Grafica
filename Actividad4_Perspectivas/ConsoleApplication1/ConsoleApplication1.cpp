// Actividad 4 Perspectivas	
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
float angle = 0;
float speed = 40;

void DrawQuads()
{
	glBegin(GL_QUADS);
	// Vertex
	glVertex3f(0.5f, -0.5f, 0.0f);
	glVertex3f(0.5f, 0.5f, 0.0f);
	glVertex3f(-0.5f, 0.5f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.0f);
	glEnd();
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

// Change to Orthographic View
void changeWindowSizeOrtho()
{
	// Matriz de proyección
	glMatrixMode(GL_PROJECTION);

	// Reinicia Matriz
	glLoadIdentity();

	glOrtho(-1.0f, 1.0f, -1.0f, 1.0f,//left,right,bottom,top
		1.0f, 1000.0f);

	// Matriz de modelos del Modelview
	glMatrixMode(GL_MODELVIEW);
}

// Change to Frustum View
void changeWindowSizeFrustum()
{
	// Matriz de proyección
	glMatrixMode(GL_PROJECTION);

	// Reinicia Matriz
	glLoadIdentity();

	glFrustum(-1.0f, 1.0f, -1.0f, 1.0f, //left,right,bottom,top
		1.0f, 1000.0f);

	// Matriz de modelos del Modelview
	glMatrixMode(GL_MODELVIEW);
}

// Change to Perspective View
void changeWindowSizePerspective()
{
	// Matriz de proyección
	glMatrixMode(GL_PROJECTION);

	// Reinicia Matriz
	glLoadIdentity();

	gluPerspective(45.0f, 1600 * 1.0 / 900, 0.1f, 100.0f);
	//fov, aspectRatio, nearclip,farclip

	// Matriz de modelos del Modelview
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
		0, 0.0f, 10.0f, //pos
		0.0f, 0.0f, 0, //target
		0.0f, 1.0f, 0.0f); //up Vector

	t = glutGet(GLUT_ELAPSED_TIME); //Obteniendo el tiempo y el delta
	dt = (t - old_t) / 1000.0f;
	old_t = t;

	angle += dt * speed;


	glPushMatrix();

		glRotatef(angle, 0.5f, 1.0f, 0.0f);

		glPushMatrix(); // Green Quad

			glColor3f(0.0f, 1.0f, 0.0f);
			glTranslatef(0.0f, 0.0f, 2.5f);
			DrawQuads();

		glPopMatrix();

		glPushMatrix(); // Blue Quad

			glColor3f(0.0f, 0.0f, 1.0f);
			glTranslatef(0.0f, 0.0f, -2.5f);
			DrawQuads();

		glPopMatrix();

		glPushMatrix(); // Red Quad

			glColor3f(1.0f, 0.0f, 0.0f);
			glRotatef(90, 1, 0, 0);
			glTranslatef(0.0f, 0.0f, 0.5f);
			glScalef(1, 5, 1);
			DrawQuads();

		glPopMatrix();

		glPushMatrix(); // Orange Quad

			glColor3f(1.0f, 0.5f, 0.0f);
			glRotatef(90, 1, 0, 0);
			glTranslatef(0.0f, 0.0f, -0.5f);
			glScalef(1, 5, 1);
			DrawQuads();

		glPopMatrix();

		glPushMatrix(); // Yellow Quad

			glColor3f(1.0f, 1.0f, 0.0f);
			glRotatef(90, 0, 1, 0);
			glTranslatef(0.0f, 0.0f, 0.5f);
			glScalef(5, 1, 1);
			DrawQuads();

		glPopMatrix();

		glPushMatrix(); // Purple Quad

			glColor3f(1.0f, 0.0f, 1.0f);
			glRotatef(90, 0, 1, 0);
			glTranslatef(0.0f, 0.0f, -0.5f);
			glScalef(5, 1, 1);
			DrawQuads();

		glPopMatrix();


	glPopMatrix();

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
	case GLUT_KEY_LEFT://Vista Ortho
		changeWindowSizeOrtho();
		break;
	case GLUT_KEY_RIGHT://Vista Perspective
		changeWindowSizePerspective();
		break;
	case GLUT_KEY_UP://Vista Frustum
		changeWindowSizeFrustum();
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