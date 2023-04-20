// Actividad 4 Producto Punto
// Kevin Cabrera

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

float PI = 3.1416;

float a = 0;
float b = 0;

float producto = 0.0f;

float opacidad = 0.0f;

// Vector 1
float xPos = 0.0f;
float yPos = 0.0f;

// Vector Movement
bool goingLeft = false, goingRight = false;
float posX = 0.0f;
float posY = 0.0f;

// Declaracion del arreglo de vectores
float vector1[2] = { xPos, yPos };
float vector2[2] = { posX, posY };

// Arreglo de colores para una figura de 3 vertices
float color[3][3] = {
	{1, 0, 0},
	{0, 1, 0},
	{0, 0, 1}
};

void Poligono() 
{
	int segmentos = 3;
	float step = (1.0f / segmentos) * PI * 2; //0 a 2Pi
	float _x = 0;
	glColor3f(1, 1, 1);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glBegin(GL_POLYGON);
	//glColor3f(0, 0, 1,0);

	for (int i = 0; i < segmentos; i++)
	{
		glColor4f(color[i][0], color[i][1], color[i][2], 0.5f);
		glVertex2f(sin(_x), cos(_x));//0
		_x = _x + step;
	}

	glEnd();
}

float ProductoPunto(float vector1[], float vector2[])
{
	producto = (vector1[0] * vector2[0]) + (vector1[1] * vector2[1]);
	return producto;
	cout << producto << endl;
}

void DibujarVector1(float f, float amp)
{
	// Para usar el framerate para las mismas velocidades
	a += dt * 2;

	float frecuencia = f;
	float amplitud = amp;
	float offset = -2.0f;

	// sin(a*frecuencia) modifica la velocidad a la que va cada ciclo
	// sin(x) * amplitud modifica la amplitud, la distancia en x del centro, y en Y es menor la distancia
	float xPos = (sin(a * frecuencia) * amplitud);
	float yPos = (cos(a * frecuencia) * amplitud);

	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_LINES);
			glVertex2f(0.0f, 0.0f);
			glVertex2f(xPos, yPos);
		glEnd();
	glPopMatrix();
}

void DibujarVector2(float f, float amp)
{
	// Para usar el framerate para las mismas velocidades
	if (goingLeft)
	{
		// Movimiento Izquierda
		b -= dt * 2;
	}
	if (goingRight)
	{
		// Movimiento Derecha
		b += dt * 2;
	}
	
	float frecuencia = f;
	float amplitud = amp;
	float offset = -2.0f;
	
	// sin(a*frecuencia) modifica la velocidad a la que va cada ciclo
	// sin(x) * amplitud modifica la amplitud, la distancia en x del centro, y en Y es menor la distancia
	float posX = (sin(b * frecuencia) * amplitud);
	float posY = (cos(b * frecuencia) * amplitud);
	
	glBegin(GL_LINES);
		// Color Blanco
		glColor3f(1.0f, 1.0f, 1.0f);
			// Centro
			glVertex2f(0.0f, 0.0f);
			glVertex2f(posX, posY);
	glEnd();
}

void IngresarVectores(float vector[3])
{
	cout << "Ingrese los componentes x, y, z del vector: " << endl;
	cin >> vector[0] >> vector[1] >> vector[2];
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
		(sin(slider) * amplitud), 1, (cos(slider) * amplitud), //pos
		0.0f, 0.0f, 0, //target
		0.0f, 1.0f, 0.0f); //up Vector


	t = glutGet(GLUT_ELAPSED_TIME); //Obteniendo el tiempo y el delta
	dt = (t - old_t) / 1000.0f;
	old_t = t;

	angle += angleVelocity * dt;
	// Actualiza la variable de escala

	// Se llama al metodo para generar el poligono
	Poligono();

	// Metodo que dibuja el vector que siempre se mueve
	DibujarVector1(0.5f, 3.0f);

	// Metodo que dibuja el vector que controla el usuario
	DibujarVector2(0.6f, 4.0f);

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
	float producto = ProductoPunto(vector1, vector2);
	cout << producto << endl;

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
