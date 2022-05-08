#include <Windows.h>
#include <gl/GL.h>

#define _USE_MATH_DEFINES
#include <cmath>

#include "Peca.h"
#include "Tabuleiro.h"

void Peca::Display() {
	glBegin(GL_POLYGON);
	for (int i = 0; i < 36; i++)
	{
		glVertex2d((TAM_QUADRADO/2.0 - 10) * sin(2 * i * M_PI / 36.0) + 0.5 * (pos_i + (pos_i + 1)) * 100, (TAM_QUADRADO / 2.0 - 10) * cos(2 * i * M_PI / 36.0) + 0.5 * (pos_j + (pos_j + 1)) * 100);
	}
	glEnd();
}