#pragma once
class Peca
{
private:
	int pos_i, pos_j;
	bool ehRei;
public:
	Peca(int x, int y, bool ehRei) {
		pos_i = x;
		pos_j = y;
		ehRei = ehRei;
	}
	void Display();
};

