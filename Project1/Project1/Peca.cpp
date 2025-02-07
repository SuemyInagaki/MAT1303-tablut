#include <Windows.h>
#include <gl/GL.h>

#define _USE_MATH_DEFINES
#include <cmath>

#include "Peca.h"
#include "Tabuleiro.h"
#include "Jogo.h"
#define DISCR 36


/*********************************************************
getPosPossible

preenche o vetor pospossible com as posi��es poss�veis da pe�a
*********************************************************/

void Peca::getPosPossible(std::vector<std::pair<int, int>>& pospossible)
{
	Tabuleiro *tabuleiro = Tabuleiro::getInstance();
	for (int i = d_pos_i + 1; i < 9; i++)
	{
		if (tabuleiro->hasPeca(i, d_pos_j) != -1)
			break;
		pospossible.push_back(std::make_pair(i, d_pos_j));
	}
	for (int i = d_pos_i - 1; i >= 0; i--)
	{
		if (tabuleiro->hasPeca(i, d_pos_j) != -1)
			break;
		pospossible.push_back(std::make_pair(i, d_pos_j));
	}
	for (int j = d_pos_j + 1; j < 9; j++)
	{
		if (tabuleiro->hasPeca(d_pos_i, j) != -1)
			break;
		pospossible.push_back(std::make_pair(d_pos_i, j));
	}
	for (int j = d_pos_j - 1; j >= 0; j--)
	{
		if (tabuleiro->hasPeca(d_pos_i, j) != -1)
			break;
		pospossible.push_back(std::make_pair(d_pos_i, j));
	}
}


/*********************************************************
setPos

Define a posi��o da pe�a
define d_pos_i com o i recebido 
define d_pos_j com o j recebido
*********************************************************/
bool Peca::setPos(int i, int j) {
	std::vector<std::pair<int, int>>& pospossible = Jogo::getInstance()->getPospossible();
	for (std::pair<int, int> pos : pospossible)
		if (i == pos.first && j == pos.second) {
			d_pos_i = i;
			d_pos_j = j;
			return true;
		}
	return false;
}

/*********************************************************
Display

ponta as pe�as
*********************************************************/

void Peca::Display()
{
	double radio = (TAM_QUADRADO / 2.0 - 10);
	glBegin(GL_POLYGON);
	for (int i = 0; i < DISCR; i++)
		glVertex2d(radio * sin(2 * i * M_PI / DISCR) + 0.5 * (d_pos_i + (d_pos_i + 1)) * TAM_QUADRADO,
			       radio * cos(2 * i * M_PI / DISCR) + 0.5 * (d_pos_j + (d_pos_j + 1)) * TAM_QUADRADO);
	glEnd();
	if (d_ehRei) {
		glBegin(GL_POLYGON);
		glColor3ub(255, 215, 0);
		for (int i = 0; i < DISCR; i++)
			glVertex2d((radio - 10) * sin(2 * i * M_PI / DISCR) + 0.5 * (d_pos_i + (d_pos_i + 1)) * TAM_QUADRADO,
				(radio - 10) * cos(2 * i * M_PI / DISCR) + 0.5 * (d_pos_j + (d_pos_j + 1)) * TAM_QUADRADO);
		glEnd();
	}
	if (d_selecionado) {
		glBegin(GL_POLYGON);
		glColor3ub(255, 0, 0);
		for (int i = 0; i < DISCR; i++)
			glVertex2d((radio - 20) * sin(2 * i * M_PI / DISCR) + 0.5 * (d_pos_i + (d_pos_i + 1)) * TAM_QUADRADO,
				       (radio - 20) * cos(2 * i * M_PI / DISCR) + 0.5 * (d_pos_j + (d_pos_j + 1)) * TAM_QUADRADO);
		glEnd();
	}
}


/*********************************************************
getEhRei

retorna o valor da variavel ehRei.
Se a pe�a for rei, retorna true.
Se a pe�a n�o for rei, retorna false.
*********************************************************/
bool Peca::getEhRei() {
	return d_ehRei;
}
