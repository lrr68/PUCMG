/* int[3][3] DO JOGO DA VELHA */


/* MACROS */
#define MAX(x,y) (x > y) ? x : y
#define MIN(x,y) (x < y) ? x : y
#define TAM_TBL 3
#define ZERA_TABULEIRO(s) for (int i=0; i<TAM_TBL; ++i) \
                          for (int j=0; j<TAM_TBL; ++j) \
                          s[i][j] = 0;

#define JOG_ALEATORIA(s,j,r) srand(time(NULL));\
						   r= rand() % 8;\
						   if (s[r/3][r%3] == 0) s[r/3][r%3] = j;\

#define INFINITO 0x7fff

/* TIPOS */
#define O -1 /* Min */
#define X 1  /* Max */

struct Jogada {
	int i;
	int j;
};

/* DEFINICOES DE FUNCOES */
int
tem_posicoes(int tabuleiro[3][3])
{
	for (int i=0; i<TAM_TBL; ++i) {
		for (int j=0; j<TAM_TBL; ++j) {
			if (tabuleiro[i][j] == 0)
				return 1;
		}
	}
	return 0;
}

int
valor(int tabuleiro[3][3])
{
	/* confere linhas */
	for (int i=0; i<TAM_TBL; ++i) { 
		/* ganhou em alguma linha */
		if (tabuleiro[i][0]==tabuleiro[i][1] && tabuleiro[i][1]==tabuleiro[i][2]) { 
			if (tabuleiro[i][0]==X) 
				return +10; 
			else if (tabuleiro[i][0]==O) 
				return -10; 
		} 
	} 

	/* confere colunas */
	for (int j=0; j<3; ++j) { 
		/* ganhou em alguma coluna */
		if (tabuleiro[0][j]==tabuleiro[1][j] && tabuleiro[1][j]==tabuleiro[2][j]) { 
			if (tabuleiro[0][j]==X) 
				return +10; 
			else if (tabuleiro[0][j]==O) 
				return -10; 
		} 
	} 

	/* diagonais */
	if (tabuleiro[0][0]==tabuleiro[1][1] && tabuleiro[1][1]==tabuleiro[2][2]) { 
		if (tabuleiro[0][0]==X) 
			return +10; 
		else if (tabuleiro[0][0]==O) 
			return -10; 
	} 

	if (tabuleiro[0][2]==tabuleiro[1][1] && tabuleiro[1][1]==tabuleiro[2][0]) { 
		if (tabuleiro[0][2]==X) 
			return +10; 
		else if (tabuleiro[0][2]==O) 
			return -10; 
	} 

	/* empate */
	return 0; 
}

void
mostra_tabuleiro(int tabuleiro[3][3])
{
	for (int i=0; i<TAM_TBL; ++i) {
		for (int j=0; j<TAM_TBL; ++j) {
			if (tabuleiro[i][j] == X)
				printf(" X");
			else if (tabuleiro[i][j] == O)
				printf(" O");
			else 
				printf(" -");
		}
		printf("\n");
	}
	printf("------------------\n");
}

int
acabou(int tabuleiro[3][3])
{
	return !(valor(tabuleiro) != 10 && 
			valor(tabuleiro) != -10 && 
			tem_posicoes(tabuleiro));
}
