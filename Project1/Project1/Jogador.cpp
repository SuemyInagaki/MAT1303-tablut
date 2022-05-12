#include <Windows.h>
#include <gl/GL.h>
#include <iostream>
#include "Jogador.h"
using namespace std;
Jogador::Jogador(bool temRei) {
	d_temRei = temRei;
	if (temRei) {
		Peca* rei = new Peca(4, 4, true);
		d_pecas.push_back(rei); //coloca a peca rei no vetor pecas
		for (int i = 2; i < 4; i++) {
			Peca* peca = new Peca(i, 4, false);
			d_pecas.push_back(peca); //coloca a peca no vetor pecas
			peca = new Peca(i + 3, 4, false);
			d_pecas.push_back(peca);
			peca = new Peca(4, i, false);
			d_pecas.push_back(peca);
			peca = new Peca(4, i + 3, false);
			d_pecas.push_back(peca);
		}
	}
	else {
		for (int i = 3; i < 6; i++) {
			Peca* peca = new Peca(0, i, false);
			d_pecas.push_back(peca);
			peca = new Peca(8, i, false);
			d_pecas.push_back(peca);
			peca = new Peca(i, 0, false);
			d_pecas.push_back(peca);
			peca = new Peca(i, 8, false);
			d_pecas.push_back(peca);
		}
		Peca* peca = new Peca(1, 4, false);
		d_pecas.push_back(peca);
		peca = new Peca(7, 4, false);
		d_pecas.push_back(peca);
		peca = new Peca(4, 1, false);
		d_pecas.push_back(peca);
		peca = new Peca(4, 7, false);
		d_pecas.push_back(peca);
	}
}
/*********************************************************
Display

Define a cor dependendo se é sueco ou russo
Chama a display do módulo Peca
*********************************************************/
void Jogador::Display()
{
	for (Peca *peca : d_pecas) {
		if (d_temRei)
			glColor3f(1, 1, 1);
		else
			glColor3f(0, 0, 0);
		peca->Display();
	}
}
/*********************************************************
get

Retorna o ponteiro para a peça do jogador na posição (i, j), caso exista
*********************************************************/
Peca* Jogador::get(int i, int j)
{
	for (Peca* peca : d_pecas) {
		if (peca->getPosI() == i && peca->getPosJ() == j) {
			return peca;
		}
	}
	return nullptr;
}

/*********************************************************
select

Seleciona ou deseleciona a peça na posicao (i, j)
*********************************************************/
Peca* Jogador::select(int i, int j) {
	Peca* peca = get(i, j);
	if (peca != nullptr)
		peca->invertSelecionado();

	return peca;
}

/*********************************************************
getPecas

retorna o vetor de peças do jogador
*********************************************************/
std::vector<Peca*> Jogador::getPecas() {
	return d_pecas;
}

/*********************************************************
remove

remove a peça do vetor de peças na posicao recebida como parâmetro
*********************************************************/
void Jogador::remove(int posicao) {
	d_pecas.erase(d_pecas.begin()+posicao);
}