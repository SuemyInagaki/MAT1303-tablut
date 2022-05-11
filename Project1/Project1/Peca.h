#pragma once

#include <vector>
#include <utility>

class Peca
{
private:
	int d_pos_i, d_pos_j;
	bool d_ehRei;
	bool d_selecionado;
public:
	Peca(int x, int y, bool ehRei) {
		d_pos_i = x;
		d_pos_j = y;
		d_ehRei = ehRei;
		d_selecionado = false;
	}

	void invertSelecionado() {
		d_selecionado = !d_selecionado;
	}

	void setSelecionado(bool sel) {
		d_selecionado = sel;
	}

	bool isSelecionado() {
		return d_selecionado;
	}

	void setPosI(int i) {
		d_pos_i = i;
	}

	int getPosI() {
		return d_pos_i;
	}

	void setPosJ(int j) {
		d_pos_j = j;
	}

	int getPosJ() {
		return d_pos_j;
	}

	bool setPos(int i, int j);

	void getPosPossible(std::vector<std::pair<int, int>>& pospossible);

	void Display();

	bool getEhRei();

	void remove();
};

