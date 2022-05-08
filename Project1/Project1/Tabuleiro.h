#pragma once
#define TAM_QUADRADO 100
class Tabuleiro
{
private:
	static void desenhaQuadrado(int i, int j, GLubyte red, GLubyte green, GLubyte blue);
public:
	Tabuleiro() {}
	static void Display();
};

