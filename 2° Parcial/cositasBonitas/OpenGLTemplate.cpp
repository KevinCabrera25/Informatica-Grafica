
#include <Windows.h>
#include <thread>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include "CTargaImage.h"
#include "OpenGLTemplate.h"

using namespace std;

//Variables  para contar el tiempo
int t = 1, old_t = 1;
float _dt = 0;

bool goRight = false, goLeft = false,
UP = false, DOWN=false, LEFT=false, RIGHT=false, shifted = false;
float _xRotator;

// ====================== Nuevo
CTargaImage* m_textura;
unsigned int m_texTarget;
// ====================== Nuevo

float _left = 0.0, _right = 0.5, _top = 1.0, _bottom = 0.75;//cat

float frames = 0.0f;

#pragma region OpenGLSetupInputAndStuff

void changeWindowSize(int w, int h)
{

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
	//Borramos de color negro
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);


	//Activamos Uso de texturas
	glEnable(GL_TEXTURE_2D);
	///============================================================================================================================
	m_textura = new CTargaImage;
	if (!m_textura->Load("runningcat.tga")) //si falla en cargar la textura cortamos ejecucion
	//if (!m_textura->Load("run.tga")) //si falla en cargar la textura cortamos ejecucion
		return;


	//generamos textura para OpenGL
	glGenTextures(1, &m_texTarget);
	//Convertimos la imagen en textura para OpenGL y vinculamos
	glBindTexture(GL_TEXTURE_2D, m_texTarget);
	//los filtros minimos requeridos para una texturizado MIN y MAG
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //prepara los algoritmos de minificación usa 4 funciones y/o mapas mip
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //genera los algoritmos de maxificacion
	//Una vez creado el objeto lo cargaremos
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_textura->GetWidth(), m_textura->GetHeight(),
		0, GL_RGB, GL_UNSIGNED_BYTE, m_textura->GetImage());
	///============================================================================================================================
}


void MoveRunningCat() {
	frames += _dt;

	float xAmount = 1.0f / 2.0f;
	float yAmount = 1.0f / 4.0f;
	if (frames >= 0.1f)
	{
		if (_right >= 1.0f)
		{
			_right = xAmount;
			_top -= yAmount;
			_bottom -= yAmount;
			_left = 0.0f;
		}
		else
		{
			_right += xAmount;
			_left += xAmount;
		}
		frames = 0.0f;
	}
}

void moveUVs() {
	float uvSpeed = 0.2f;
	if (UP && !shifted) _top -= _dt * uvSpeed;
	if (DOWN && !shifted) _top += _dt * uvSpeed;

	if (UP && shifted) _bottom -= _dt * uvSpeed;
	if (DOWN && shifted) _bottom += _dt * uvSpeed;

	if (LEFT && !shifted) _left += _dt * uvSpeed;
	if (RIGHT && !shifted) _left -= _dt * uvSpeed;

	if (LEFT && shifted) _right += _dt * uvSpeed;
	if (RIGHT && shifted) _right -= _dt * uvSpeed;
}

void renderScene(void)
{
	// Limpia los buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reinicia las trasnformaciones
	glLoadIdentity();

	gluLookAt(
		(sin(_xRotator) * 7.0f), 0.0f, (cos(_xRotator) * 7.0f), //pos
		0, 0, 0.0f, //target
		0.0f, 1.0f, 0.0f); //up Vector

	t = glutGet(GLUT_ELAPSED_TIME); //Obteniendo el tiempo y el delta
	_dt = (t - old_t) / 1000.0f;
	old_t = t;

	if (goLeft)  _xRotator -= _dt * 3.0f;
	if (goRight) _xRotator += _dt * 3.0f;

	glPushMatrix();
		glScalef(1.0f, 1.0f, 1.0f);
		//Indicamos que usaremos textura 1
		glBindTexture(GL_TEXTURE_2D, m_texTarget);
		glBegin(GL_QUADS);

			glTexCoord2f(_left, _top);     glVertex3f(-1.0f, 1.0f, 0);    //izqarriba
			glTexCoord2f(_right, _top);    glVertex3f(1.0f, 1.0f, 0);	 //derecharriba
			glTexCoord2f(_right, _bottom); glVertex3f(1.0f, -1.0f, 0);  //derechabajo
			glTexCoord2f(_left, _bottom);  glVertex3f(-1.0f, -1.0f, 0);//izqabajo

		glEnd();
	glPopMatrix();

	
	//MoveRunningCat();
	moveUVs();

	glutSwapBuffers(); //intercambia los búferes de la ventana actual si tiene doble búfer.
}

void processNormalKeys(unsigned char key, int x, int y)
{

	if (key == 97)
		goLeft = true;

	if (key == 100)
		goRight = true;
	 
	if (key == 32)
		shifted = true;

	if (key == 27) {
		cout << " <==================================> LiberarMemoria <==================================> " << endl;
		glDeleteTextures(1, &m_texTarget);
		m_textura->Release();
		delete m_textura;
		exit(0);
	}
}

void processNormalKeysUP(unsigned char key, int x, int y)
{
	if (key == 97)
		goLeft = false;

	if (key == 100)
		goRight = false;

	if (key == 32)
		shifted = false;

}

void InputDown(int key, int xx, int yy)
{
	switch (key)
	{
		case GLUT_KEY_UP:
			UP = true;
			break;
		case GLUT_KEY_DOWN:
			DOWN = true;
			break;
		case GLUT_KEY_LEFT:
			LEFT = true;
			break;
		case GLUT_KEY_RIGHT:
			RIGHT = true;
			break;

	}
}

void InputUp(int key, int xx, int yy)
{
	switch (key) {
	case GLUT_KEY_UP:
		UP = false;
		break;
	case GLUT_KEY_DOWN:
		DOWN = false;
		break;
	case GLUT_KEY_LEFT:
		LEFT = false;
		break;
	case GLUT_KEY_RIGHT:
		RIGHT = false;
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
	glutKeyboardUpFunc(processNormalKeysUP);
	glutSpecialFunc(InputDown); //teclas especiales
	glutSpecialUpFunc(InputUp); //teclas especiales al soltarse	

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	// =================================== NUEVO ===================================
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

	// entrar GLUT al ciclo de procesamiento de eventos
	glutMainLoop();

	cout << " <==================================> LiberarMemoria <==================================> " << endl;
		glDeleteTextures(1, &m_texTarget);
		m_textura->Release();
		delete m_textura;
	return 1;
}

