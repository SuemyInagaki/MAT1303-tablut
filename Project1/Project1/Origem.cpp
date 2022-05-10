#include <iostream>
#include <glut.h>
#include "Tabuleiro.h"

using namespace std;

#define DIMX 630
#define DIMY 630

static void display()
{
	Tabuleiro::getInstance()->Display();

	glFlush(); //transfere o colorBuffer para a visualizacao
	glutSwapBuffers();
}

static void mouseButton(int button, int state, int x, int y)
{
	Tabuleiro::getInstance()->MouseButton(button, state, x, y);
	display();
}

static void resize(int width, int height)
{
	// we ignore the params and do:
	glutReshapeWindow(DIMX, DIMY);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(DIMX, DIMY);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Tablut");
	glutDisplayFunc(display); //precisa ser um metodo estatico
	glutMouseFunc(mouseButton); //le se um botao do mouse foi pressionado
	glutReshapeFunc(resize);

	glutMainLoop();
}