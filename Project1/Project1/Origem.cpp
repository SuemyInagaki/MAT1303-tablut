#include <iostream>
using namespace std;
#include <glut.h>

#include "Tabuleiro.h"

int main(int argc, char** argv)
{
	Tabuleiro tabuleiro;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(900, 900);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Tablut");
	glutDisplayFunc(Tabuleiro::Display); //precisa ser um metodo estatico
	glutMainLoop();
}