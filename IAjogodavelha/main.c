/* HEADERS */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "lista.h"
#include "tabuleiro.h"
#include "minimax.h"
#include "aestrela.h"

int
main()
{
	/* MINIMAX */
	/*int tabuleiro_mm[3][3];
	ZERA_TABULEIRO(tabuleiro_mm);
	* primeira jogada do max *
	int aux;
	JOG_ALEATORIA(tabuleiro_mm,X,aux);
	JOG_ALEATORIA(tabuleiro_ae,X,aux);
	*/

	int c = 0;
	int atual = O;
	int tabuleiro_ae[3][3];
	ZERA_TABULEIRO(tabuleiro_ae);
	struct Celula jogadaO;

	/* tabuleiro aleatorio */
	int tabuleiro_mm[3][3] = {
		{ 0, 0, 0},
		{ 0, X, O},
		{ 0, 0 ,X}
	};

	/*
	int tabuleiro_ae[3][3] = {
		{ 0, 0, 0},
		{ 0, X, O},
		{ 0, 0 ,X}
	};
	*/

	printf("RESOLVENDO COM MINIMAX\nTabuleiro:\n");
	mostra_tabuleiro(tabuleiro_mm);
	rodar_minimax(tabuleiro_mm, atual);

	printf("\nRESOLVENDO COM A*\n");
	
	while (!acabou(tabuleiro_ae)) {
		printf(" Faca sua jogada:    |0 1 2|\n (numero de 0 a 8    |3 4 5|\n correspondente à    |6 7 8|\n posição desejada na matriz acima)\n");
		c = getchar(); getchar(); /* le o \n que sobrou no buffer */
		c-=48; /* conver para inteiro */

		while (c < 0 || 8 < c || tabuleiro_ae[c/3][c%3] != 0) {
			printf("Numero invalido, digite novamente\n");
			c = getchar(); getchar();
		}

		tabuleiro_ae[c/3][c%3] = X;
		mostra_tabuleiro(tabuleiro_ae);

		if (!acabou(tabuleiro_ae)) {
			jogadaO = a_estrela(tabuleiro_ae, atual);
			tabuleiro_ae[jogadaO.i][jogadaO.j] = O;
		}
	}

	if (valor(tabuleiro_ae) == 10)
		printf("Você ganhou.\n");
	else if (valor(tabuleiro_ae) == -10)
		printf("Você perdeu.\n");
	else
		printf("EMPATE\n");

	return 0;
}
