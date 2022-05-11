#include <iostream>
#include <glut.h>
#include "Tabuleiro.h"

using namespace std;

#define DIMX 630
#define DIMY 630

int qt = 0; //quantidade de jogadores
bool contraComputador = false;
static void display()
{
	Tabuleiro::getInstance()->Display();
	if (contraComputador == true) {
		Tabuleiro::getInstance()->setContraComputador();
	}
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

	while (qt != 1 && qt != 2) {
		cout << "Digite a quantidade de jogadores" << endl;
		cout << "1 se for jogar contra o computador" << endl;
		cout << "2 se for jogar contra outra pessoa" << endl;
		cout << "3 se quiser encerrar o jogo" << endl;
		cin >> qt;
		if (qt == 3) {
			exit(1);
		}
	}


	if (qt == 1) {
		//Inicia com computador
		contraComputador = true;
	}
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(DIMX, DIMY);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Tablut");
	glutDisplayFunc(display); //precisa ser um metodo estatico
	glutMouseFunc(mouseButton); //le se um botao do mouse foi pressionado
	glutReshapeFunc(resize);
	glutMainLoop();
	
}