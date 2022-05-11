#pragma once

#include "Jogador.h"

#define TAM_QUADRADO 70
#define DIMX 630
#define DIMY 630

class Tabuleiro
{
private:
	Jogador *russo;
	Jogador *sueco;
	Peca* pecaSelecionada;
	std::vector<std::pair<int, int>> pospossible;
	int jogadorDaVez = 0;
	void desenhaQuadrado(int i, int j, GLubyte red, GLubyte green, GLubyte blue);
	void trocaJogadorDaVez();

public:
	static Tabuleiro* getInstance()
	{
		static Tabuleiro* tabuleiro = new Tabuleiro;
		return tabuleiro;
	}

	Tabuleiro();

	void Display();
	void MouseButton(int button, int state, int x, int y);
	bool hasPeca(int i, int j);
	std::vector<std::pair<int, int>>& getPospossible()
	{
		return pospossible;
	}
};

