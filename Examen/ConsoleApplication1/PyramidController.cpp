#include "PyramidController.h"
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>

// Constructor
PyramidController::PyramidController()
{

}

// Destroyer
PyramidController::~PyramidController()
{

}

// Method that varies the actual color 
float PyramidController::variationColor(float selectedColor)
{
	if (selectedColor == 0.0f)
	{
		return 0;
	}
	else
	{
		// Reduce the value of the color for the next face
		return selectedColor - 0.1f;
	}

}

// Method that generates the Pyramids, this method receives the actual color and varies the color of each face
void PyramidController::pyramidGenerator(float redColor, float greenColor, float blueColor)
{
	glPushMatrix();

	// First Triangle
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);
	// This variables takes the actual color and stores it in the RGB variable to return the same color
	// but with the variation (color degradation)
	redColor = variationColor(redColor);
	greenColor = variationColor(greenColor);
	blueColor = variationColor(blueColor);
	// Color First Triangle
	glColor3f(redColor, greenColor, blueColor);
	// Vertex
	glVertex3f(1.0f, -0.5f, 1.0f);
	glVertex3f(-1.0f, -0.5f, 1.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glEnd();

	// Second Triangle
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);
	// This variables takes the actual color and stores it in the RGB variable to return the same color
	// but with the variation (color degradation)
	redColor = variationColor(redColor);
	greenColor = variationColor(greenColor);
	blueColor = variationColor(blueColor);
	// Color Second Triangle
	glColor3f(redColor, greenColor, blueColor);
	// Vertex
	glVertex3f(-1.0f, -0.5f, -1.0f);
	glVertex3f(1.0f, -0.5f, -1.0);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glEnd();

	// Third Triangle
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);
	// This variables takes the actual color and stores it in the RGB variable to return the same color
	// but with the variation (color degradation)
	redColor = variationColor(redColor);
	greenColor = variationColor(greenColor);
	blueColor = variationColor(blueColor);
	// Color Third Triangle
	glColor3f(redColor, greenColor, blueColor);
	// Vertex
	glVertex3f(1.0f, -0.5f, -1.0f);
	glVertex3f(1.0f, -0.5f, 1.0f);
	glVertex3f(0.0, 1.0f, 0.0f);
	glEnd();

	// Fourth Triangle
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);
	// This variables takes the actual color and stores it in the RGB variable to return the same color
	// but with the variation (color degradation)
	redColor = variationColor(redColor);
	greenColor = variationColor(greenColor);
	blueColor = variationColor(blueColor);
	// Color Fourth Triangle
	glColor3f(redColor, greenColor, blueColor);
	// Vertex
	glVertex3f(-1.0f, -0.5f, 1.0f);
	glVertex3f(-1.0f, -0.5f, -1.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glEnd();

	// Base Triangle
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUADS);
	// This variables takes the actual color and stores it in the RGB variable to return the same color
	// but with the variation (color degradation)
	redColor = variationColor(redColor);
	greenColor = variationColor(greenColor);
	blueColor = variationColor(blueColor);
	// Base Color
	glColor3f(redColor, greenColor, blueColor);
	// Vertex
	glVertex3f(-1, -0.5, -1);
	glVertex3f(1, -0.5, -1);
	glVertex3f(1, -0.5, 1);
	glVertex3f(-1, -0.5, 1);
	glEnd();

	glPopMatrix();
}
