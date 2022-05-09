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
	Peca* select(int i, int j);
};

