#pragma once

#include "Jogador.h"

#define TAM_QUADRADO 100

class Tabuleiro
{
private:
	Jogador *russo;
	Jogador *sueco;
	Peca* pecaSelecionada;
	void desenhaQuadrado(int i, int j, GLubyte red, GLubyte green, GLubyte blue);
public:
	static void SDisplay();
	static void SMouseButton(int button, int state, int x, int y);
	static Tabuleiro* getInstance()
	{
		static Tabuleiro* tabuleiro = new Tabuleiro;
		return tabuleiro;
	}
	Tabuleiro();
	void Display();
	void MouseButton(int button, int state, int x, int y);
};

