#include <Windows.h>
#include <glut.h>
#include <iostream>


using namespace std;

#include "Tabuleiro.h"
#include "Jogador.h"

Tabuleiro::Tabuleiro()
{
	russo = new Jogador(false);
	sueco = new Jogador(true);
	jogadorDaVez = 0;
	pecaSelecionada = nullptr;
	fimDeJogo = -1; // se suecos ganharam, fimDeJogo = 0. Se russos ganharam, fim de jogo = 1
	// preenche o array de margem
	for (int i = 0; i < 9; i++) {
		margem.push_back(make_pair(0, i));
		margem.push_back(make_pair(i, 0));
		margem.push_back(make_pair(i, 8));
		margem.push_back(make_pair(8, i));
	}
}
void Tabuleiro::desenhaQuadrado(int i, int j, GLubyte red, GLubyte green, GLubyte blue)
{
	glColor3ub(red, green, blue);
	glBegin(GL_QUADS);
		glVertex2f(i * TAM_QUADRADO, j * TAM_QUADRADO);
		glVertex2f((i + 1) * TAM_QUADRADO, j * TAM_QUADRADO);
		glVertex2f((i + 1) * TAM_QUADRADO, (j + 1) * TAM_QUADRADO);
		glVertex2f(i * TAM_QUADRADO, (j + 1) * TAM_QUADRADO);
	glEnd();
}

void Tabuleiro::trocaJogadorDaVez() {
	if (jogadorDaVez == 0) {
		jogadorDaVez = 1;
	}
	else {
		jogadorDaVez = 0;
	}
}

void Tabuleiro::verificaSeGanhou() {
	
	bool ehRei = pecaSelecionada->getEhRei(); // verifica se a peça selecionada é o rei
	if (ehRei) {
		//se for o rei, tem que ver se chegou na margem.
		int i = pecaSelecionada->getPosI();
		int j = pecaSelecionada->getPosJ();
		for (pair<int, int> m : margem)
		{
			// rei sueco chegou na margem
			if (m.first == i && m.second == j) {
				fimDeJogo = 0;
				cout << "Jogador sueco ganhou" << endl;
				exit(1);
			}
		}
	}
	
	// está na vez dos russos
	if (jogadorDaVez == 1) {
		vector<Peca*> pecas = sueco->getPecas();
		// verifica se os suecos ainda possuem o rei
		bool temRei = false;
		for (int i = 0; i < pecas.size(); i++) {
			if (pecas[i]->getEhRei() == true) {
				temRei = true;
				break;
			}
		}
		if (temRei == false) {
			fimDeJogo = 1;
			cout << "Jogador russo ganhou" << endl;
			exit(1);
		}
	}
}

void Tabuleiro::setContraComputador() {
	contraComputador = true;
}


void Tabuleiro::verificaSeCapturou() {
	vector<Peca*> pecasRussas = russo->getPecas();
	vector<Peca*> pecasSuecas = sueco->getPecas();

	if (jogadorDaVez == 0) { //ver se os suecos cercaram algum russo
		for (Peca* p : pecasRussas) {
			int i = p->getPosI();
			int j = p->getPosJ();
			// verifica se esta na margem
			bool ehMargem = false;
			for (pair<int, int> m : margem)
			{
				if (m.first == i && m.second == j) {
					ehMargem = true;
				}
			}
			if (ehMargem == false) {
				if (((hasPeca(i - 1, j) + hasPeca(i + 1, j)) == 10) || (hasPeca(i, j - 1) + hasPeca(i, j + 1)) == 10) {
					russo->remove(i, j);
					pecasRussas = russo->getPecas();
				}
				//falta o caso da margem
			}
		}
	}
	else { // ver se os russos cercaram algum sueco

	}
}

void Tabuleiro::moveAleatoriamente() {
	// pega as peças russas
	vector<Peca*> pecasRussas = russo->getPecas();
	while (pospossible.size() == 0) { //enquanto nao encontrar uma peça livre para mover, continua procurando
		if (pecasRussas.size() != 0) {
			int index = std::rand() % (pecasRussas.size());
			pecaSelecionada = pecasRussas[index]; // escolhe a peça aleatoriamente
			pecaSelecionada->setSelecionado(true);
			pecaSelecionada->getPosPossible(pospossible); //preenche o vetor de possibilidades
			if (pospossible.size() > 0) { //se a peça tem casas livres para mover
				int index2 = std::rand() % (pospossible.size());
				int i = pospossible[index2].first;
				int j = pospossible[index2].second;
				pecaSelecionada->setPos(i, j);
			}
		}
		else { //nao tem mais peças russas
			break;
		}
	}
}

void Tabuleiro::Display()
{
	glLineWidth(5.0);
	glClearColor(217.0f / 255.0f, 199.0f / 255.0f, 159.0f / 255.0f, 0); //define qual cor vai pintar a tela
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, (9 * TAM_QUADRADO), 0, (9 * TAM_QUADRADO));
	glClear(GL_COLOR_BUFFER_BIT); //pinta com a cor do glClearColor(.....)
	

	// Desenha as casas russas
	for (int i = 3; i < 6; i++)
	{
		desenhaQuadrado(0, i, 120, 78, 47);
		desenhaQuadrado(8, i, 120, 78, 47);
		desenhaQuadrado(i, 0, 120, 78, 47);
		desenhaQuadrado(i, 8, 120, 78, 47);
	}
	desenhaQuadrado(1, 4, 120, 78, 47);
	desenhaQuadrado(7, 4, 120, 78, 47);
	desenhaQuadrado(4, 1, 120, 78, 47);
	desenhaQuadrado(4, 7, 120, 78, 47);
	desenhaQuadrado(4, 4, 120, 78, 47);

	// desenha as casas suecas
	for (int i = 2; i < 4; i++) {
		desenhaQuadrado(i, 4, 214, 135, 78);
		desenhaQuadrado(i + 3, 4, 214, 135, 78);
		desenhaQuadrado(4, i, 214, 135, 78);
		desenhaQuadrado(4, i + 3, 214, 135, 78);
	}
	// pinta os possiveis movimentos da peça selecionada
	for (std::pair<int, int> pos : pospossible)
	{
		desenhaQuadrado(pos.first, pos.second, 255, 0, 0);
	}

	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	for (int x = 0; x <= (9 * TAM_QUADRADO); x += TAM_QUADRADO)
	{
		glVertex2f(x, 0);
		glVertex2f(x, (9 * TAM_QUADRADO));
	}
	for (int y = 0; y <= (9 * TAM_QUADRADO); y += TAM_QUADRADO)
	{
		glVertex2f(0, y);
		glVertex2f((9 * TAM_QUADRADO), y);
	}
	glEnd();

	russo->Display();
	sueco->Display();
}

void Tabuleiro::MouseButton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{

		int i = x / TAM_QUADRADO;
		int j = (DIMX - y) / TAM_QUADRADO;
		Peca* sel;
		if (jogadorDaVez == 0) {
			sel = sueco->select(i, j);
		}
		else {
			sel = russo->select(i, j);
		}
		if (sel != nullptr)
		{
			pospossible.clear();
			if (sel->isSelecionado() && pecaSelecionada && pecaSelecionada != sel)
				pecaSelecionada->setSelecionado(false);

			pecaSelecionada = sel;

			if (pecaSelecionada->isSelecionado())
				pecaSelecionada->getPosPossible(pospossible);
		}
		else
		{
			// escolheu uma casa para mover e tem peça selecionada
			if (pecaSelecionada != nullptr)
			{
				bool moveu = pecaSelecionada->setPos(i, j); // move a peça, se possivel
				if (moveu != false) { // só passa a vez do jogador se fizer um movimento valido
					verificaSeCapturou();
					verificaSeGanhou();
					trocaJogadorDaVez(); // alterna entre os jogadores
					if (contraComputador == true) {
						pecaSelecionada->setSelecionado(false); // desfaz a seleçao da peça sueca
						pecaSelecionada = nullptr;
						pospossible.clear();
						moveAleatoriamente(); //move a peça russa aleatoriamente
						verificaSeCapturou();
						verificaSeGanhou();
						trocaJogadorDaVez(); // passa a vez de volta para os suecos
					}
				}
				pecaSelecionada->setSelecionado(false); // desfaz a seleçao
				pecaSelecionada = nullptr;
				pospossible.clear();
			}
		}
	}
}

int Tabuleiro::hasPeca(int i, int j)
{
	Peca* peca = russo->get(i, j);
	if (peca != nullptr)
		return 1;
	peca = nullptr;
	peca = sueco->get(i, j);
	if (peca != nullptr) {
		return 5;
	}
	return -1;
}
