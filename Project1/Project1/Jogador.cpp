#include <Windows.h>
#include <gl/GL.h>

#include "Jogador.h"

Jogador::Jogador(bool temRei) {
	d_temRei = temRei;
	if (temRei) {
		Peca* rei = new Peca(4, 4, true);
		pecas.push_back(rei); //coloca a peca rei no vetor pecas
		for (int i = 2; i < 4; i++) {
			Peca* peca = new Peca(i, 4, false);
			pecas.push_back(peca); //coloca a peca no vetor pecas
			peca = new Peca(i + 3, 4, false);
			pecas.push_back(peca);
			peca = new Peca(4, i, false);
			pecas.push_back(peca);
			peca = new Peca(4, i + 3, false);
			pecas.push_back(peca);
		}
	}
	else {
		for (int i = 3; i < 6; i++) {
			Peca* peca = new Peca(0, i, false);
			pecas.push_back(peca);
			peca = new Peca(8, i, false);
			pecas.push_back(peca);
			peca = new Peca(i, 0, false);
			pecas.push_back(peca);
			peca = new Peca(i, 8, false);
			pecas.push_back(peca);
		}
		Peca* peca = new Peca(1, 4, false);
		pecas.push_back(peca);
		peca = new Peca(7, 4, false);
		pecas.push_back(peca);
		peca = new Peca(4, 1, false);
		pecas.push_back(peca);
		peca = new Peca(4, 7, false);
		pecas.push_back(peca);
	}
}

void Jogador::Display()
{
	if (d_temRei)
		glColor3f(1, 1, 1);
	else
		glColor3f(0, 0, 0);
	for (Peca *peca : pecas)
	{
		peca->Display();
	}
}