#include "Piramide.h"
#include <stdlib.h>
#include <time.h>
#include <GL\glew.h>
#include <GL\freeglut.h>

Piramide::Piramide()
{
	static bool iniciado = false;
	if (!iniciado)
	{
		srand(time(NULL));
		iniciado = true;
	}
	// -5 a 5
	_x =( rand() % 9) - 4;
	_y = (rand() % 9) - 4;
	_z = (rand() % 9) - 4;

	_r = ((rand() % 51) + 25) / 100.0f;
	_g = ((rand() % 51) + 25) / 100.0f;
	_b = ((rand() % 51) + 25) / 100.0f;

	_rotX = (rand() % 2) == 0 ? -1 : 1;
	_rotY = (rand() % 2) == 0 ? -1 : 1;
	_rotZ = (rand() % 2) == 0 ? -1 : 1;

	_direcX = (rand() % 2);
	_direcY = (rand() % 2);
	_direcZ = (rand() % 2);

	_speed = (rand());

	size = ((rand() % 14) + 2) / 10.0f;
}

Piramide::~Piramide()
{

}

void Piramide::moverPiramide(float _dt)
{
	// incrementa el angulo
	_angle += _dt * 25.0f;

	// Next Move
	float nextM = _dt * _speed;

	// Logica de choque, limites
	if (_x + nextM > 5)
	{
		_direcX = false;
	}
	else if (_x - nextM < -5)
	{
		_direcX = true;
	}

	if (_y + nextM > 5)
	{
		_direcY = false;
	}
	else if (_y - nextM < -5)
	{
		_direcY = true;
	}
	
	if (_z + nextM > 5)
	{
		_direcX = false;
	}
	else if (_z - nextM < -5)
	{
		_direcZ = true;
	}

	// Logica de Movimiento
	if (_direcX == true) _x += _dt * _speed;
	else _x -= _dt * _speed;

	// Logica de Movimiento
	if (_direcY == true) _x += _dt * _speed;
	else _y -= _dt * _speed;

	// Logica de Movimiento
	if (_direcZ == true) _x += _dt * _speed;
	else _z -= _dt * _speed;


	glPushMatrix();
		glTranslatef(_x, _y, _z);
		glRotatef(_angle, _rotX, _rotY, _rotZ);
		dibujarPiramide();
	glPopMatrix();

}