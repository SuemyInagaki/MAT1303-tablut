#pragma once
#include <vector>
#include "Peca.h"

class Jogador
{
private:
	bool d_temRei;
	std::vector<Peca*> pecas;
public:
	Jogador(bool temRei);
	void Display();
};

