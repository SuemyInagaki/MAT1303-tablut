#pragma once
#include <vector>
#include "Peca.h"

class Jogador
{
private:
	bool d_temRei;
	std::vector<Peca*> d_pecas;
public:
	Jogador(bool temRei);
	void Display();
	Peca* get(int i, int j);
	Peca* select(int i, int j);
	void remove(int posicao);
	std::vector<Peca*> getPecas();
};

