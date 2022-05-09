#include <Windows.h>
#include <gl/GL.h>

#define _USE_MATH_DEFINES
#include <cmath>

#include "Peca.h"
#include "Tabuleiro.h"

#define DISCR 36

void Peca::Display()
{
	double radio = (TAM_QUADRADO / 2.0 - 10);
	glBegin(GL_POLYGON);
	for (int i = 0; i < DISCR; i++)
		glVertex2d(radio * sin(2 * i * M_PI / DISCR) + 0.5 * (d_pos_i + (d_pos_i + 1)) * TAM_QUADRADO,
			       radio * cos(2 * i * M_PI / DISCR) + 0.5 * (d_pos_j + (d_pos_j + 1)) * TAM_QUADRADO);
	glEnd();
	if (d_ehRei) {
		glBegin(GL_POLYGON);
		glColor3ub(255, 215, 0);
		for (int i = 0; i < DISCR; i++)
			glVertex2d((radio - 10) * sin(2 * i * M_PI / DISCR) + 0.5 * (d_pos_i + (d_pos_i + 1)) * TAM_QUADRADO,
				(radio - 10) * cos(2 * i * M_PI / DISCR) + 0.5 * (d_pos_j + (d_pos_j + 1)) * TAM_QUADRADO);
		glEnd();
	}
	if (d_selecionado) {
		glBegin(GL_POLYGON);
		glColor3ub(255, 0, 0);
		for (int i = 0; i < DISCR; i++)
			glVertex2d((radio - 20) * sin(2 * i * M_PI / DISCR) + 0.5 * (d_pos_i + (d_pos_i + 1)) * TAM_QUADRADO,
				       (radio - 20) * cos(2 * i * M_PI / DISCR) + 0.5 * (d_pos_j + (d_pos_j + 1)) * TAM_QUADRADO);
		glEnd();
	}
}