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
	desabilitaClick = false;
}

/*
desenhaQuadrado
Fun��o que desenha os quadrados do tabuleiro
A cor varia:
- Se for casa sueca
- Se for casa russa
- Se for demais casas
- Se a casa tiver selecionada
*/
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

/*********************************************************
trocaJogadorDaVez
Fun��o que passa a vez do jogador
**********************************************************/
void Tabuleiro::trocaJogadorDaVez() {
	if (jogadorDaVez == 0) {
		jogadorDaVez = 1;
	}
	else {
		jogadorDaVez = 0;
	}
}

/*********************************************************
verificaSeGanhou:
Fun��o que verifica se algum jogador venceu.
Ela deve ser chamada ao final de cada movimento. 
Caso o jogador sueco ganhe, a fun��o define fimDeJogo como 0
Caso o jogador russo ganhe, a fun��o define fimDeJogo como 1
Nos dois caso a fun��o finaliza o programa ao identificar a vit�ria.
*********************************************************/
void Tabuleiro::verificaSeGanhou() {
	vector<Peca*> suecos = sueco->getPecas();
	vector<Peca*> russos = russo->getPecas();
	if (jogadorDaVez == 0) {
		bool ehRei = pecaSelecionada->getEhRei(); // verifica se a pe�a selecionada � o rei
		if (ehRei) {
			//se for o rei, tem que ver se chegou na margem.
			int i = pecaSelecionada->getPosI();
			int j = pecaSelecionada->getPosJ();
			for (pair<int, int> m : margem)
			{
				// rei sueco chegou na margem
				if (m.first == i && m.second == j) {
					fimDeJogo = 0;
					cout << "**************************************************\n";
					cout << "Jogador sueco ganhou" << endl;
					cout << "**************************************************\n";
					desabilitaClick = true;
				}
			}
		}
		
		if (russos.size() == 0) {
			fimDeJogo = 0;
			cout << "**************************************************\n";
			cout << "Jogador sueco ganhou" << endl;
			cout << "**************************************************\n";
			desabilitaClick = true;
		}
	}
	// est� na vez dos russos
	if (jogadorDaVez == 1) {
		if (suecos.size() == 0) {
			fimDeJogo = 1;
			cout << "**************************************************\n";
			cout << "Jogador russo ganhou" << endl;
			cout << "**************************************************\n";
			desabilitaClick = true;
		}
		// verifica se os suecos ainda possuem o rei
		bool temRei = false;
		for (int i = 0; i < suecos.size(); i++) {
			if (suecos[i]->getEhRei() == true) {
				temRei = true;
				break;
			}
		}
		if (temRei == false) {
			fimDeJogo = 1;
			cout << "**************************************************\n";
			cout << "Jogador russo ganhou" << endl;
			cout << "**************************************************\n";
			desabilitaClick = true;
		}
	}
}

/*********************************************************
setContraComputador
Fun��o que deve ser chamada na main caso o jogo seja contra o computador
Ela define a vari�vel contraComputador como true
*********************************************************/
void Tabuleiro::setContraComputador() {
	contraComputador = true;
}

/*********************************************************
verificaSeCapturou
Fun��o que verifica se alguma pe�a foi capturada
Deve ser chamada ao final de cada movimento
Ela varre todo o tabuleiro e verifica:
- Se tem pe�as russas cercando pe�as suecas
- Se tem pe�as suecas cercando pe�as russas
Caso encontre alguma pe�a cercada, verifica se alguma
das pe�as que a cercam foi mexida naquela jogada. Pois a captura
n�o � valida quando a pe�a cercada se coloca entre duas pe�as inimigas

Ela faz uma verifica��o especial quando � o Rei, pois ele precisa que 
quatro pe�as russas o cerquem. 
*********************************************************/
void Tabuleiro::verificaSeCapturou() {
	vector<Peca*> pecasRussas = russo->getPecas();
	vector<Peca*> pecasSuecas = sueco->getPecas();

	int ii = pecaSelecionada->getPosI();
	int jj = pecaSelecionada->getPosJ();
	if (jogadorDaVez == 0) { //ve se os suecos cercaram algum russo
		int c = 0;
		while (c < pecasRussas.size()) { // percorre todas as pe�as russas pra ver se tem alguma cercada
			Peca* p = pecasRussas[c];
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
			// pe�a nao esta na margem
			if (ehMargem == false) {
				// tem pe�a russa cercada por pe�as suecas
				if (((hasPeca(i - 1, j) + hasPeca(i + 1, j)) == 10) || (hasPeca(i, j - 1) + hasPeca(i, j + 1)) == 10) {
					// alguma dessas pe�as foi a que moveu agora?
					if ((ii == (i - 1) && jj == j) || (ii == (i + 1) && jj == j) || (ii == (i) && jj == j - 1) || (ii == (i) && jj == j + 1)) {
						russo->remove(c);
						pecasRussas = russo->getPecas();
						c--;
					}
				}
			}
			// pe�a esta na margem
			else {
				if ((i == 8 || i == 0) && j < 8) {
					if ((hasPeca(i, j - 1) + hasPeca(i, j + 1)) == 10) {
						if ((ii == i && jj == j-1) || (ii == i && jj == j+1)) {
							russo->remove(c);
							pecasRussas = russo->getPecas();
							c--;
						}	
					}
				}else if ((j == 8 || j == 0) && i < 8) {
					if ((hasPeca(i-1, j) + hasPeca(i+1, j)) == 10) {
						if ((ii == i-1 && jj == j) || (ii == i+1 && jj == j)) {
							russo->remove(c);
							pecasRussas = russo->getPecas();
							c--;
						}
					}
				}
			}
			c++;
		}
	}
	else { // ver se os russos cercaram algum sueco
		int c = 0;
		while (c < pecasSuecas.size()) {
			Peca* p = pecasSuecas[c];
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
				if (pecasSuecas[c]->getEhRei() == false) {
					if (((hasPeca(i - 1, j) + hasPeca(i + 1, j)) == 2) || (hasPeca(i, j - 1) + hasPeca(i, j + 1)) == 2) {
						// alguma dessas pe�as foi a que moveu agora?
						if ((ii == (i - 1) && jj == j) || (ii == (i + 1) && jj == j) || (ii == (i) && jj == j - 1) || (ii == (i) && jj == j + 1)) {
							sueco->remove(c);
							pecasSuecas = sueco->getPecas();
							c--;
						}
					}
				}
				else { //a pe�a cercada eh o Rei
					// tem quatro pe�as cercando
					if (((hasPeca(i - 1, j) + hasPeca(i + 1, j)) == 2) && (hasPeca(i, j - 1) + hasPeca(i, j + 1)) == 2) {
						// alguma dessas pe�as foi a que moveu agora?
						if ((ii == (i - 1) && jj == j) || (ii == (i + 1) && jj == j) || (ii == (i) && jj == j - 1) || (ii == (i) && jj == j + 1)) {
							sueco->remove(c);
							pecasSuecas = sueco->getPecas();
							c--;
						}
					}
					// se tiver 3 pe�as e estiver perto do trono do rei
					/*
					else if () {

					}
					*/
				}
			}
			else {
				if ((i == 8 || i == 0) && j < 8) {

					if ((hasPeca(i, j - 1) + hasPeca(i, j + 1)) == 2) {
						if ((ii == i && jj == j - 1) || (ii == i && jj == j + 1)) {
							sueco->remove(c);
							pecasSuecas = sueco->getPecas();
							c--;
						}
						
					}
				}
				else if ((j == 8 || j == 0) && i < 8) {
					if ((hasPeca(i - 1, j) + hasPeca(i + 1, j)) == 2) {
						if ((ii == i-1 && jj == j) || (ii == i+1 && jj == j)) {
							sueco->remove(c);
							pecasSuecas = sueco->getPecas();
							c--;
						}
					}
				}
			}
			c++;
		}
	}
}

/*********************************************************
moveAleatoriamente
Fun��o que � chamada quando o jogo � contra o computador
Essa fun��o faz os movimentos aleat�rios na vez do computador
Definimos que o computador sempre vai ser russo

A fun��o pega as pe�as russas, gera um indice aleat�rio entre 0 e 
o tamanho das pe�as russas - 1. Assim, depois de escolher a pe�a, 
a fun��o verifica se essa pe�a tem movimentos v�lidos:
- caso tenha, gera outro indice aleatorio e escolhe um movimento para fazer
- caso n�o tenha, a fun��o escolhe outra pe�a. 

Ela fica em um loop at� encontrar uma pe�a com movimento v�lido
*********************************************************/
void Tabuleiro::moveAleatoriamente() {
	// pega as pe�as russas
	vector<Peca*> pecasRussas = russo->getPecas();
	pospossible.clear(); //apaga os dados do movimento sueco
	while (pospossible.size() == 0) {
		int index = std::rand() % (pecasRussas.size());
		pecaSelecionada = pecasRussas[index]; // escolhe a pe�a aleatoriamente
		pecaSelecionada->setSelecionado(true);
		pecaSelecionada->getPosPossible(pospossible); //preenche o vetor de possibilidades
		
		if (pospossible.size() == 0) { // se essa pe�a nao tem movimento possivel
			pospossible.clear();
			pecaSelecionada->setSelecionado(false); //desfaz a sele��o da pe�a
		}
		else {
			int index2 = std::rand() % (pospossible.size());
			int i = pospossible[index2].first;
			int j = pospossible[index2].second;
			pecaSelecionada->setPos(i, j);
		}
	}
}

/*********************************************************
Display

Fun��o que desenha o tabuleiro
Depois de desenhar o tabuleiro, chama as fun��es de display das pe�as russas e suecas
*********************************************************/
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
	// pinta os possiveis movimentos da pe�a selecionada
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

/*********************************************************
MouseButton
Fun��o que identifica o clique do mouse
Ao clicar em uma pe�a, a vari�vel pecaSelecionada guarda a pe�a selecionada
No segundo clique, caso a pe�a selecionada seja diferente de nullptr, isso significa que 
existe alguma pe�a selecionada antes e ent�o fazemos o movimento. 

A fun��o toma cuidado com o caso de clicar em uma casa inv�lida para mexer
E a cada movimento, chama as funcoes verificaSeGanhou e verificaSeCapturou
*********************************************************/
void Tabuleiro::MouseButton(int button, int state, int x, int y)
{
	if (desabilitaClick == false) {
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
				// escolheu uma casa para mover e tem pe�a selecionada
				if (pecaSelecionada != nullptr)
				{
					bool moveu = pecaSelecionada->setPos(i, j); // move a pe�a, se possivel
					if (moveu != false) { // s� passa a vez do jogador se fizer um movimento valido
						verificaSeCapturou();
						verificaSeGanhou();
						trocaJogadorDaVez(); // alterna entre os jogadores
						if (contraComputador == true) {
							// inicia a jogada do computador (russo)
							pecaSelecionada->setSelecionado(false); // desfaz a sele�ao da pe�a sueca
							pecaSelecionada = nullptr;
							pospossible.clear();
							moveAleatoriamente(); //move a pe�a russa aleatoriamente
							verificaSeCapturou();
							verificaSeGanhou();
							trocaJogadorDaVez(); // passa a vez de volta para os suecos
						}
					}
					pecaSelecionada->setSelecionado(false); // desfaz a sele�ao
					pecaSelecionada = nullptr;
					pospossible.clear();
				}
			}
		}
	}
	
}

/*********************************************************
hasPeca
Fun��o que verifica se tem pe�a na casa (i, j)
- Caso tenha pe�a e a pe�a seja russa, a fun��o retorna 1
- Caso tenha pe�a e a pe�a seja sueca, a fun��o retorna 5;
- Caso n�o tenha pe�a, a fun��o retorna -1.
*********************************************************/

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
