#include <Windows.h>
#include <glut.h>
#include <iostream>


using namespace std;

#include "Tabuleiro.h"
#include "Jogador.h"

Tabuleiro::Tabuleiro()
{
	russo = new Jogador(false);
	sueco = new Jogador(true);
	pecaSelecionada = nullptr;
}
void Tabuleiro::desenhaQuadrado(int i, int j, GLubyte red, GLubyte green, GLubyte blue)
{
	glColor3ub(red, green, blue);
	glBegin(GL_QUADS);
		glVertex2f(i * TAM_QUADRADO, j * TAM_QUADRADO);
		glVertex2f((i + 1) * TAM_QUADRADO, j * TAM_QUADRADO);
		glVertex2f((i + 1) * TAM_QUADRADO, (j + 1) * TAM_QUADRADO);
		glVertex2f(i * TAM_QUADRADO, (j + 1) * TAM_QUADRADO);
	glEnd();
}

void Tabuleiro::trocaJogadorDaVez() {
	if (jogadorDaVez == 0) {
		jogadorDaVez = 1;
	}
	else {
		jogadorDaVez = 0;
	}
}

void Tabuleiro::Display()
{
	glLineWidth(5.0);
	glClearColor(217.0f / 255.0f, 199.0f / 255.0f, 159.0f / 255.0f, 0); //define qual cor vai pintar a tela
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, (9 * TAM_QUADRADO), 0, (9 * TAM_QUADRADO));
	glClear(GL_COLOR_BUFFER_BIT); //pinta com a cor do glClearColor(.....)
	
	// Desenha as casas russas
	for (int i = 3; i < 6; i++)
	{
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

	// desenha as casas suecas
	for (int i = 2; i < 4; i++) {
		desenhaQuadrado(i, 4, 214, 135, 78);
		desenhaQuadrado(i + 3, 4, 214, 135, 78);
		desenhaQuadrado(4, i, 214, 135, 78);
		desenhaQuadrado(4, i + 3, 214, 135, 78);
	}
	// pinta os possiveis movimentos da peça selecionada
	for (std::pair<int, int> pos : pospossible)
	{
		desenhaQuadrado(pos.first, pos.second, 255, 0, 0);
	}

	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	for (int x = 0; x <= (9 * TAM_QUADRADO); x += TAM_QUADRADO)
	{
		glVertex2f(x, 0);
		glVertex2f(x, (9 * TAM_QUADRADO));
	}
	for (int y = 0; y <= (9 * TAM_QUADRADO); y += TAM_QUADRADO)
	{
		glVertex2f(0, y);
		glVertex2f((9 * TAM_QUADRADO), y);
	}
	glEnd();

	russo->Display();
	sueco->Display();
}

void Tabuleiro::MouseButton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{

		int i = x / TAM_QUADRADO;
		int j = (DIMX - y) / TAM_QUADRADO;
		Peca* sel;
		if (jogadorDaVez == 0) {
			sel = sueco->select(i, j);
		}
		else {
			sel = russo->select(i, j);
		}
		if (sel != nullptr)
		{
			pospossible.clear();
			if (sel->isSelecionado() && pecaSelecionada && pecaSelecionada != sel)
				pecaSelecionada->setSelecionado(false);

			pecaSelecionada = sel;

			if (pecaSelecionada->isSelecionado())
				pecaSelecionada->getPosPossible(pospossible);
		}
		else
		{
			// selecionou uma peça
			if (pecaSelecionada != nullptr)
			{
				pecaSelecionada->setPos(i, j); // move a peça
				pecaSelecionada->setSelecionado(false); // desfaz a seleçao
				pecaSelecionada = nullptr;
				pospossible.clear();
				trocaJogadorDaVez(); // alterna entre os jogadores 

			}
		}
	}
}

bool Tabuleiro::hasPeca(int i, int j)
{
	Peca* peca = russo->get(i, j);
	if (peca != nullptr)
		return true;
	peca = sueco->get(i, j);
	return (peca != nullptr);
}