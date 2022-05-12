#pragma once
#include "Peca.h"
#include "Jogador.h"
#include "Tabuleiro.h"
#include "Jogo.h"

#include <Windows.h>
#include <glut.h>
#include <iostream>
#include<vector>
class Jogo
{
private:
	Jogador *russo;
	Jogador *sueco;
	Peca* pecaSelecionada;
	int jogadorDaVez;
	int fimDeJogo;
	bool contraComputador;
	std::vector<std::pair<int, int>> margem;
	std::vector<std::pair<int, int>> pospossible;
	void verificaSeCapturou();
	void trocaJogadorDaVez();
	void verificaSeGanhou();
	bool desabilitaClick;
	Tabuleiro tab;
public:
	Jogo();
	void moveAleatoriamente();
	void Display();
	void setContraComputador();
	void MouseButton(int button, int state, int x, int y);
	
	Jogador* getRusso() {
		return russo;
	}
	Jogador* getSueco() {
		return sueco;
	}
	static Jogo* getInstance()
	{
		static Jogo* jogo = new Jogo;
		return jogo;
	}
	std::vector<std::pair<int, int>>& getPospossible()
	{
		return pospossible;
	}

};

