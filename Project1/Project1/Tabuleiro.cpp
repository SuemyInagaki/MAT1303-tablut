#include <Windows.h>
#include <glut.h>
#include <iostream>

using namespace std;

#include "Tabuleiro.h"
#include "Jogador.h"

Tabuleiro::Tabuleiro() {
	russo = new Jogador(false);
	sueco = new Jogador(true);
	pecaSelecionada = nullptr;
}
void Tabuleiro::desenhaQuadrado(int i, int j, GLubyte red, GLubyte green, GLubyte blue) {
	glColor3ub(red, green, blue);
	glBegin(GL_QUADS);
		glVertex2f(i * TAM_QUADRADO, j * TAM_QUADRADO);
		glVertex2f((i + 1) * TAM_QUADRADO, j * TAM_QUADRADO);
		glVertex2f((i + 1) * TAM_QUADRADO, (j + 1) * TAM_QUADRADO);
		glVertex2f(i * TAM_QUADRADO, (j + 1) * TAM_QUADRADO);
	glEnd();
}

void Tabuleiro::SDisplay() {
	getInstance()->Display();

	glFlush(); //transfere o colorBuffer para a visualizacao
	glutSwapBuffers();
}

void Tabuleiro::SMouseButton(int button, int state, int x, int y) {
	getInstance()->MouseButton(button, state, x, y);
}

void Tabuleiro::Display() {
	glLineWidth(5.0);
	glClearColor(217.0f/255.0f, 199.0f / 255.0f, 159.0f / 255.0f, 0); //define qual cor vai pintar a tela
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, (9 * TAM_QUADRADO), 0, (9 * TAM_QUADRADO));
	glClear(GL_COLOR_BUFFER_BIT); //pinta com a cor do glClearColor(.....)
	for (int i = 3; i < 6; i++) {
		desenhaQuadrado(0, i, 120, 78, 47);
		desenhaQuadrado(8, i, 120, 78, 47);
		desenhaQuadrado(i, 0, 120, 78, 47);
		desenhaQuadrado(i, 8, 120, 78, 47);
	}
	desenhaQuadrado(1, 4, 120, 78, 47);
	desenhaQuadrado(7, 4, 120, 78, 47);
	desenhaQuadrado(4, 1, 120, 78, 47);
	desenhaQuadrado(4, 7, 120, 78, 47);
	desenhaQuadrado(4, 4, 120, 78, 47);

	for (int i = 2; i < 4; i++) {
		desenhaQuadrado(i, 4, 214, 135, 78);
		desenhaQuadrado(i + 3, 4, 214, 135, 78);
		desenhaQuadrado(4, i, 214, 135, 78);
		desenhaQuadrado(4, i + 3, 214, 135, 78);
	}

	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	for (int x = 0; x <= (9 * TAM_QUADRADO); x += TAM_QUADRADO) {
		glVertex2f(x, 0);
		glVertex2f(x, (9 * TAM_QUADRADO));
	}
	for (int y = 0; y <= (9 * TAM_QUADRADO); y += TAM_QUADRADO) {
		glVertex2f(0, y);
		glVertex2f((9 * TAM_QUADRADO), y);
	}
	glEnd();

	russo->Display();
	sueco->Display();
}

void Tabuleiro::MouseButton(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		int i = x / 100;
		int j = (900 - y) / 100;
		Peca * sel = russo->select(i, j);
		if (sel != nullptr) {
			if (sel->isSelecionado() && pecaSelecionada)
				pecaSelecionada->setSelecionado(false);

			pecaSelecionada = sel;
		}
		else {
			if (pecaSelecionada != nullptr) {
				pecaSelecionada->setPosI(i);
				pecaSelecionada->setPosJ(j);
				pecaSelecionada->setSelecionado(false);
				pecaSelecionada = nullptr;
			}
		}
		Tabuleiro::SDisplay();
		
	}
}

