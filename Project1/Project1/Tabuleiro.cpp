#include <Windows.h>
#include <glut.h>

#include "Tabuleiro.h"

void Tabuleiro::Display() {
	glLineWidth(5.0);
	glClearColor(1, 1, 1, 0); //define qual cor vai pintar a tela
	glMatrixMode(GL_PROJECTION);
	// for setting the transformation which here is 2D
	gluOrtho2D(0, 900, 0, 900);
	glClear(GL_COLOR_BUFFER_BIT); //pinta com a dor do glClearColor(.....)
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	for (int x = 0; x <= 900; x += 100)
	{
		glVertex2f(x, 0);
		glVertex2f(x, 900);
	}
	for (int y = 0; y <= 900; y += 100)
	{
		glVertex2f(0, y);
		glVertex2f(900, y);
	}
	glEnd();

	glFlush(); //transfere o colorBuffer para a visualizacao
	glutSwapBuffers();
}

