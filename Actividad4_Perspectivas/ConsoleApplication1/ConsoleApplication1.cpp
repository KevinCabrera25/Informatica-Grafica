// Actividad 3 Piramide	
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
short patron = 0xABAB;
float angle = 0;
float speed = 40;


void DrawLine()
{
	glEnable(GL_LINE_STIPPLE); ///habilitar patrones
	glColor3f(1.0f, .6f, 0.3f);
	glLineWidth(1.0f);
	glLineStipple(8, patron);
	glBegin(GL_LINES);
	glVertex3f(-2.0f, 1.5f, 2.0f);
	glVertex3f(0.0f, 2.0f, 2.0f);
	glVertex3f(0.0f, 2.0f, 2.0f);
	glVertex3f(2.0f, 1.5f, 2.0f);
	glEnd();
	glDisable(GL_LINE_STIPPLE);///apagamos patron
}

void DrawQuads()
{
	glBegin(GL_QUADS);
	// Vertex
	glVertex3f(1.0f, -0.5f, 0.0f);
	glVertex3f(1.0f, 0.5f, 0.0f);
	glVertex3f(-1.0f, 0.5f, 0.0f);
	glVertex3f(-1.0f, -0.5f, 0.0f);
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
		glRotatef(angle, 0.0f, 1.0f, 0.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		DrawQuads();
		glPushMatrix();
			glTranslatef(0.0f, 0.0f, 5.0f);
			glColor3f(0.0f, 0.0f, 1.0f);
			DrawQuads();
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glPushMatrix();
			glRotatef(angle, 0.0f, 1.0f, 0.0f);
			glTranslatef(-1.0f, 0.0f, 1.0f);
			glPushMatrix();
				glScalef(2.0f, 1.0f, 0.0f);
				glTranslatef(0.0f, 0.0f, 2.0f);
				glColor3f(0.98f, 0.76f, 0.0f);
				DrawQuads();
			glPopMatrix();
		glPopMatrix();		
	glPopMatrix();

	/*
	glPushMatrix();
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.6f, 1.0f);
	glVertex3f(0.0f, 0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, -1.0f);
	glVertex3f(0.5f, -0.5f, -1.0f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glPolygonMode(GL_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, -1.0f);
	glVertex3f(-0.5f, -0.5f, 0.0f);
	glEnd();
	glDisable(GL_CULL_FACE);
	glPopMatrix();

	glPushMatrix();
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	glPolygonMode(GL_FRONT, GL_FILL);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-0.5f, -0.5f, -1.0f);
	glVertex3f(-0.5f, -0.5f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glVertex3f(0.5f, -0.5f, -1.0f);
	glEnd();
	glPopMatrix();
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

