#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

//tamanhos dos navios
//esse numero tambem indica o tipo de navio
#define porta_aviao 5
#define navio_tanque 4
#define contratorpedeiro 3
#define submarino 2

//numero de navios
#define num_pa 1
#define num_nt 2
#define num_ct 3
#define num_su 4

//Codigo que comunica que perdi o jogo
#define PERDI "perdi"

//insere um navio no tabuleiroA
//sempre insere para baixo e para direita,
//portanto o primeiro ponto do navio deve 
//ser sempre o mais de cima e mais da esquerda
void inserir_navio(char linha[10],int** tabuleiro)
{
	//linha no formato nn x y (h/v)
	//nn = tipo do navio
	//x y = coordenadas da primeira posicao do navio
	//v = vertical
	//h = horizontal
	
	int x=0, y=0;
	int tipo_navio = submarino;
	if (linha[0] == 'p')
		tipo_navio = porta_aviao;
	else if (linha[0] == 'n')
		tipo_navio = navio_tanque;
	else if (linha[0] == 'c')
		tipo_navio = contratorpedeiro;


	x = letra2num(linha[3]) % 10;
	y = letra2num(linha[5]) % 10;


	//ou insere na horizontal ou na vertical
	if (linha[7] == 'h') {

		for (int i=0; i< tipo_navio; i++) {
			tabuleiro[x][y+i] = tipo_navio;
		}
	}else{
		for (int i=0; i< tipo_navio; i++) {
			tabuleiro[x+i][y] = tipo_navio;
		}
	}

}

//cria um tabuleiro aleatoriamente
void init_rand(int** tabuleiro)
{
	//coloca os navios individualmente no tabuleiro
	//sempre sorteia numeros de forma que os navios nao
	//ultrapassem o limite do tabuleiro
	//limites do sorteio diferentes para cada tipo de navio
	srand(time(NULL));
	int x=0,
		y=0,
		o=0; //orientacao 0->vertical 1->horizontal
	
	//submarinos -> tamanho 2 portanto podem ir 
	//so ate a posicao 8 do tabuleiro
	for(int i=0; i<num_su; i++) {
		o = rand() % 2;
		if(o) { //horizontal
			x= rand() % 9;
			y= rand() % 10;
			while ((tabuleiro[x][y] != 0) && (tabuleiro[x+1][y] != 0)) {
				x= rand() % 9;
				y= rand() % 10;
			}
			tabuleiro[x][y] = submarino;
			tabuleiro[x+1][y] = submarino;
		}else{ //vertical
			x= rand() % 10;
			y= rand() % 9;
			while ((tabuleiro[x][y] != 0) && (tabuleiro[x][y+1] != 0)) {
				x= rand() % 10;
				y= rand() % 9;
			}
			tabuleiro[x][y] = submarino;
			tabuleiro[x][y+1] = submarino;
		}
	}
	
	//contratorpedeiro -> tamanho 3 portanto podem ir 
	//so ate a posicao 7 do tabuleiro
	for(int i=0; i<num_ct; i++) {
		o = rand() % 2;
		if(o) { //horizontal
			x= rand() % 8;
			y= rand() % 10;
			while ((tabuleiro[x][y] != 0) && (tabuleiro[x+1][y] != 0) && (tabuleiro[x+2][y] != 0)) {
				x= rand() % 8;
				y= rand() % 10;
			}
			tabuleiro[x][y] = contratorpedeiro;
			tabuleiro[x+1][y] = contratorpedeiro;
			tabuleiro[x+2][y] = contratorpedeiro;
		}else{ //vertical
			x= rand() % 10;
			y= rand() % 8;
			while ((tabuleiro[x][y] != 0) && (tabuleiro[x][y+1] != 0) && (tabuleiro[x][y+2] != 0)) {
				x= rand() % 10;
				y= rand() % 8;
			}
			tabuleiro[x][y] = contratorpedeiro;
			tabuleiro[x][y+1] = contratorpedeiro;
			tabuleiro[x+2][y] = contratorpedeiro;
		}
	}

	//navio_tanque -> tamanho 4 portanto podem ir 
	//so ate a posicao 6 do tabuleiro
	for(int i=0; i<num_nt; i++) {
		o = rand() % 2;
		if(o) { //horizontal
			x= rand() % 7;
			y= rand() % 10;
			while ((tabuleiro[x][y] != 0) && (tabuleiro[x+1][y] != 0) && (tabuleiro[x+2][y] != 0) && (tabuleiro[x+3][y] != 0)) {
				x= rand() % 7;
				y= rand() % 10;
			}
			tabuleiro[x][y] = navio_tanque;
			tabuleiro[x+1][y] = navio_tanque;
			tabuleiro[x+2][y] = navio_tanque;
			tabuleiro[x+3][y] = navio_tanque;
		}else{ //vertical
			x= rand() % 10;
			y= rand() % 7;
			while ((tabuleiro[x][y] != 0) && (tabuleiro[x][y+1] != 0) && (tabuleiro[x][y+2] != 0) && (tabuleiro[x][y+3] != 0)) {
				x= rand() % 10;
				y= rand() % 7;
			}
			tabuleiro[x][y] = navio_tanque;
			tabuleiro[x][y+1] = navio_tanque;
			tabuleiro[x][y+2] = navio_tanque;
			tabuleiro[x][y+3] = navio_tanque;
		}
	}

	//porta_aviao -> tamanho 5 portanto podem ir 
	//so ate a posicao 5 do tabuleiro
	for(int i=0; i<num_pa; i++) {
		o = rand() % 2;
		if(o) { //horizontal
			x= rand() % 6;
			y= rand() % 10;
			while ((tabuleiro[x][y] != 0) && (tabuleiro[x+1][y] != 0) && (tabuleiro[x+2][y] != 0) && (tabuleiro[x+3][y] != 0) && (tabuleiro[x+4][y] != 0)) {
				x= rand() % 6;
				y= rand() % 10;
			}
			tabuleiro[x][y] = porta_aviao;
			tabuleiro[x+1][y] = porta_aviao;
			tabuleiro[x+2][y] = porta_aviao;
			tabuleiro[x+3][y] = porta_aviao;
			tabuleiro[x+4][y] = porta_aviao;
		}else{ //vertical
			x= rand() % 10;
			y= rand() % 6;
			while ((tabuleiro[x][y] != 0) && (tabuleiro[x][y+1] != 0) && (tabuleiro[x][y+2] != 0) && (tabuleiro[x][y+3] != 0) && (tabuleiro[x][y+4] != 0)) {
				x= rand() % 10;
				y= rand() % 6;
			}
			tabuleiro[x][y] = porta_aviao;
			tabuleiro[x][y+1] = porta_aviao;
			tabuleiro[x][y+2] = porta_aviao;
			tabuleiro[x][y+3] = porta_aviao;
			tabuleiro[x][y+4] = porta_aviao;
		}
	}
}

void init(int** tabuleiro,char *arq)
{
	int c;
	int i=0;
	char linha[10] ;
	//zera o tabuleiro
	for(int i=0; i< 10; i++)
		for(int j=0; j<10;j++)
			tabuleiro[i][j]='~';

	FILE *file = fopen(arq,"r");
	if (file) {
		//Le o arquivo caractere por caractere
		while((c=getc(file)) != EOF) {
			//le a linha toda, insere no tabuleiroA, zera a linha
			if (c != '\n') {
				linha[i] = c;
				i++;
			} else {
				inserir_navio(linha,tabuleiro);
				i=0;
			}
		}
	} else {
		perror("Nenhum arquivo de entrada encontrado\n");
		exit(EXIT_FAILURE);
	}
}

int terminou(int** tabuleiro)
{
	int fim = 0;
	for(int i=0; i< 10; i++) {
		for(int j=0; j< 10; j++) {
			//se ainda houver algum navio pula fora e retorna falso
			if (tabuleiro[i][j] != 0)
				goto fora;
		}
	}
	fim = 1;
fora: 
	return fim;
}

char* tipo2nome(int tipo)
{
	char* retorno;
	switch (tipo) {
		case 2: retorno="submarino";
				break;
		case 3: retorno="contratorpedeiro";
				break;
		case 4: retorno="navio tanque";
				break;
		case 5: retorno="porta aviões";
				break;
	}
	return retorno;
}

void mostraTabuleiros(int** tabuleiro,int** tiros)
{
	printf("Meu tabuleiro:\n");
	printf("   A B C D E F G H I J\n");
	for(int i=0;i<10;i++) {
		printf("%d- ",i);
		for(int j=0;j<10;j++) {
			//mostra os numeros
			if (tabuleiro[i][j] < 6)
				printf("%d ",tabuleiro[i][j]);
			else //mostra o X que acertou
				printf("%c ",tabuleiro[i][j]);
		}
		printf("\n");
	}

	printf("Meus tiros:\n");
	printf("   A B C D E F G H I J\n");
	for(int i=0;i<10;i++) {
		printf("%d- ",i);
		for(int j=0;j<10;j++) {
			if (tiros[i][j] == 'X')
				printf("X ");
			else if (tiros[i][j] == 'A')
				printf("A ");
			else
				printf("~ ");
		}
		printf("\n");
	}
}

int jogada(int x, int y, int** tabuleiro)
{
	int acertou = 0;
	int tipo_n = tabuleiro[x][y];
	if (tipo_n != '~') {
		acertou = 1;
		tabuleiro[x][y]='X';
		//se afundou o navio, printa qual foi e que derrubou
		if ( 	(tabuleiro[x][y-1] != tipo_n) && 
				(tabuleiro[x][y+1] != tipo_n) && 
				(tabuleiro[x-1][y] != tipo_n) && 
				(tabuleiro[x+1][y] != tipo_n)
		   )
			printf("Afundou um %s\n",tipo2nome(tipo_n));
	}
	return acertou;
}
