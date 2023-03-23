#include <Windows.h>
#include <thread>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>


using namespace std;

// Variables to measure time
int t = 1, old_t = 1;
float dt = 0;
float angleVelocity = 60.0f;
float angle;
float slider = 0;
float sliderY = 0;
float amplitud = 10;
float amplitudB = 5;
bool goingLeft = false, goingRight = false;

// Declaracion del arreglo de vectores
float vector1[3];
float vector2[3];

// Declaracion del arreglo que almacena los valores del vector del Producto Cruz
float productoCruz[3];


void IngresarVectores(float vector[3])
{
	cout << "Ingrese los componentes x, y, z del vector: " << endl;
	cin >> vector[0] >> vector[1] >> vector[2];
}

void ProductoCruz(float vector1[3], float vector2[3], float productoCruz[3])
{
	productoCruz[0] = vector1[1] * vector2[2] - vector1[2] * vector2[1];
	productoCruz[1] = vector1[2] * vector2[0] - vector1[0] * vector2[2];
	productoCruz[2] = vector1[0] * vector2[1] - vector1[1] * vector2[0];
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

void GenerarVectores(float vector1[3], float vector2[3], float productoCruz[3])
{
	glColor3f(1.0f, 0.0f, 0.0f);//rojo
	glLineWidth(1.0f);
	glBegin(GL_LINES);
		// Vector1
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(vector1[0], vector1[1], vector1[2]);

		// Vector2 Azul
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(vector2[0], vector2[1], vector2[2]);

		// Producto Cruz
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(productoCruz[0], productoCruz[1], productoCruz[2]);

		// Suma de Vectores Turquesa
		glColor3f(0.42f, 0.85f, 1.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(vector1[0] + vector2[0], vector1[1] + vector2[1], vector1[2] + vector2[2]);
	glEnd();
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
		(sin(slider) * amplitud), 1, (cos(slider) * amplitud), //pos
		0.0f, 0.0f, 0, //target
		0.0f, 1.0f, 0.0f); //up Vector


	t = glutGet(GLUT_ELAPSED_TIME); //Obteniendo el tiempo y el delta
	dt = (t - old_t) / 1000.0f;
	old_t = t;

	if (goingLeft) slider -= dt * 5;
	if (goingRight) slider += dt * 5;

	
	angle += angleVelocity * dt;
	// Actualiza la variable de escala

	// Se llama al metodo GenerarVectores
	GenerarVectores(vector1, vector2, productoCruz);


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
	switch (key)
	{
	case GLUT_KEY_RIGHT:
		goingRight = false;
		break;
	case GLUT_KEY_LEFT:
		goingLeft = false;
		break;
	}
}

#pragma endregion

int main(int argc, char* argv[])
{

	// Se llama al metodo para llenar el arreglo de Vectores
	IngresarVectores(vector1);
	IngresarVectores(vector2);

	// Se llama al metodo para realizar el Producto Cruz de los 2 vectores
	ProductoCruz(vector1, vector2, productoCruz);
	// Se imprime el resultado del Producto Cruz 
	cout << productoCruz[0] << ", " << productoCruz[1] << ", " << productoCruz[2] << endl;

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
