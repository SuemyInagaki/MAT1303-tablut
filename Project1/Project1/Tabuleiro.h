#pragma once

#include "Jogador.h"
#include <glut.h>

#define TAM_QUADRADO 70
#define DIMX 630
#define DIMY 630

class Tabuleiro
{
public:
	static Tabuleiro* getInstance()
	{
		static Tabuleiro* tabuleiro = new Tabuleiro;
		return tabuleiro;
	}
	void desenhaQuadrado(int i, int j, GLubyte red, GLubyte green, GLubyte blue);
	Tabuleiro();

	void Display();
	int hasPeca(int i, int j);
	
};

