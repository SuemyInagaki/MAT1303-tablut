#include <Windows.h>
//#include <glut.h>
#include <iostream>


using namespace std;

#include "Tabuleiro.h"
#include "Jogador.h"
#include "Jogo.h"
Tabuleiro::Tabuleiro(){}

/*
desenhaQuadrado
Função que desenha os quadrados do tabuleiro
A cor varia:
- Se for casa sueca
- Se for casa russa
- Se for demais casas
- Se a casa tiver selecionada
*/
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


/*********************************************************
Display

Função que desenha o tabuleiro
Depois de desenhar o tabuleiro, chama as funções de display das peças russas e suecas
*********************************************************/
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

	std::vector<std::pair<int, int>> pospossible = Jogo::getInstance()->getPospossible();
	for (std::pair<int, int> pos : pospossible)
	{
		Tabuleiro::getInstance()->desenhaQuadrado(pos.first, pos.second, 255, 0, 0);
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

}



/*********************************************************
hasPeca
Função que verifica se tem peça na casa (i, j)
- Caso tenha peça e a peça seja russa, a função retorna 1
- Caso tenha peça e a peça seja sueca, a função retorna 5;
- Caso não tenha peça, a função retorna -1.
*********************************************************/

int Tabuleiro::hasPeca(int i, int j)
{
	Jogador* russo = Jogo::getInstance()->getRusso();
	Jogador* sueco = Jogo::getInstance()->getSueco();
	Peca* peca = russo->get(i, j);
	if (peca != nullptr)
		return 1;
	peca = nullptr;
	peca = sueco->get(i, j);
	if (peca != nullptr) {
		return 5;
	}
	return -1;
}
