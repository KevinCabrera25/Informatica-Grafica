#include <Windows.h>
#include <thread>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include <ctime>
#include <random>



using namespace std;

//Variables  para contar el tiempo
int t = 1, old_t = 1;
float dt = 0;
float velocidadAngulo = 60.0f;
float angulo;
float slider = 0;
float amplitud = 20;
bool goingLeft = false, goingRight = false;
float ftejem;

void randomNum(float ft)
{
	random_device rd;
	mt19937 gen(rd());

	uniform_real_distribution<double> dist(0.0, 1.0);

	ft = dist(gen);
}
int num = (rand() % 11) - 5; //0 a 10; //-5 a 5

Piramide Piramide1 = Piramide();

Piramide* arrayPiramides = new Piramide[9];


float colores[10][3]
{



};
void drawBigSquare()
{
	// frente
	glColor3f(0, 0, 1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
	glVertex3f(6, 6, 0);
	glVertex3f(6, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 6, 0);
	glEnd();


	// detras
	glColor3f(0, 1, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
	glVertex3f(6, 6, -6);
	glVertex3f(6, 0, -6);
	glVertex3f(0, 0, -6);
	glVertex3f(0, 6, -6);
	glEnd();


	// cara izquierda
	glColor3f(0.5, 0, 0.5);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
	glVertex3f(6, 6, 0);
	glVertex3f(6, 0, 0);
	glVertex3f(6, 0, -6);
	glVertex3f(6, 6, -6);
	glEnd();


	// cara derecha
	glColor3f(1, 1, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 6, 0);
	glVertex3f(0, 6, -6);
	glVertex3f(0, 0, -6);
	glEnd();


	// base

	glColor3f(0, 0.5, 0.5);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUADS);
	glVertex3f(6, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, -6);
	glVertex3f(6, 0, -6);
	glEnd();


	// tapa
	glColor3f(1, 0, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
	glVertex3f(6, 6, 0);
	glVertex3f(0, 6, 0);
	glVertex3f(0, 6, -6);
	glVertex3f(6, 6, -6);
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
	randomNum(ftejem);
	cout << ftejem << endl;
	cout << num << endl;
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



	t = glutGet(GLUT_ELAPSED_TIME); //Obteniendo el tiempo y el delta
	dt = (t - old_t) / 1000.0f;
	old_t = t;

	if (goingLeft) slider -= dt * 5;
	if (goingRight) slider += dt * 5;
	angulo += velocidadAngulo * dt;
	// Actualiza la variable de escala
	glPushMatrix();

	glTranslatef(-3, -3, 3);

	drawBigSquare();

	glPopMatrix();

	//drawpiramide()

	for (int i = 0; i < 10; i++)
	{
		arrayPiramides[i].dibujarPiramide(1, 0, 1, dt);
	}


	//Piramide1.dibujarPiramide(0,0,1);

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
	}
}

void InputUp(int key, int xx, int yy)
{

	switch (key) {
	case GLUT_KEY_RIGHT:
		goingRight = false;
		break;
	case GLUT_KEY_LEFT:
		goingLeft = false;
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