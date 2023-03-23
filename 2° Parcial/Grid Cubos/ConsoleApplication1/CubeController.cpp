#include "CubeController.h"
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>

CubeController::CubeController()
{

}

CubeController::~CubeController()
{

}

// Metodo de Variacion del Color
float CubeController::variationColor(float selectedColor)
{
	if (selectedColor == 0.0f)
	{
		return 0;
	}
	else
	{
		return selectedColor - 0.1;
	}
}

// Metodo para la generacion de Cubos
void CubeController::cubeGenerator(float r, float g, float b)
{
	glBegin(GL_QUADS);

	// FRONT
	// Color variation
	r = variationColor(r);
	g = variationColor(g);
	b = variationColor(b);
	glColor3f(r, g, b);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	// BACK
	// Color variation
	r = variationColor(r);
	g = variationColor(g);
	b = variationColor(b);
	glColor3f(r, g, b);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	// RIGHT
	// Color variation
	r = variationColor(r);
	g = variationColor(g);
	b = variationColor(b);
	glColor3f(r, g, b);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f); 

	// LEFT
	// Color variation
	r = variationColor(r);
	g = variationColor(g);
	b = variationColor(b);
	glColor3f(r, g, b);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f); 

	// TOP
	// Color variation
	r = variationColor(r);
	g = variationColor(g);
	b = variationColor(b);
	glColor3f(r, g, b);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f); 

	// BOTTOM
	// Color variation
	r = variationColor(r);
	g = variationColor(g);
	b = variationColor(b);
	glColor3f(r, g, b);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f); 


	glEnd();
}
