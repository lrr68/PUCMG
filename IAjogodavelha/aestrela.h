
/* G(x,y) = 3-MAX(num op linha, num op coluna, num op diagonal) */
int
g(int x, int y, int oponente, int tabuleiro[3][3])
{
	int num_op_l = 0;
	int num_op_c = 0;
	int num_op_d = 0;

	/* oponentes na linha */
	for (int i=0; i<TAM_TBL; ++i)
		if (tabuleiro[x][i] == oponente)
			num_op_l++;

	/* oponentes na coluna */
	for (int i=0; i<TAM_TBL; ++i)
		if (tabuleiro[i][y] == oponente)
			num_op_c++;

	/* tem diagonal */
	if (x == y) {
		if (tabuleiro[0][0] == oponente)
			num_op_d++;
		if (tabuleiro[1][1] == oponente)
			num_op_d++;
		if (tabuleiro[2][2] == oponente)
			num_op_d++;
	} else if ((x == 0 && y == 2) || (x == 2 && y == 0)) {
		if (tabuleiro[0][2] == oponente)
			num_op_d++;
		if (tabuleiro[1][1] == oponente)
			num_op_d++;
		if (tabuleiro[2][0] == oponente)
			num_op_d++;
	}

	return 3-(MAX((MAX(num_op_l,num_op_c)),num_op_d));
}

/* numero de linhas/colunas/diagonais que possui um oponente */
int
h(int x, int y, int jogador, int tabuleiro[3][3])
{
	int c = 0;
	int oponente = -jogador;

	/* so oponentes na linha ? */
	int i;
	for (i=0; i<TAM_TBL; ++i)
		if (tabuleiro[x][i] == jogador)
			break;
	if (i == TAM_TBL) ++c;

	/* so oponentes na coluna ? */
	for (i=0; i<TAM_TBL; ++i)
		if (tabuleiro[i][y] == jogador)
			break;
	if (i == TAM_TBL) ++c;

	/* pelo menos um e somente oponentes na diagonal ? */
	if (x == y) {
		if (tabuleiro[0][0] == -jogador || tabuleiro[1][1] == -jogador ||
				tabuleiro[2][2] == -jogador)
		{
			if (tabuleiro[0][0] != jogador && tabuleiro[1][1] != jogador &&
					tabuleiro[2][2] != jogador)
				++c;
		}
	} else if ((x == 0 && y == 2) || (x == 1 && y == 1) || (x == 2 && y == 0)) {
		if (tabuleiro[0][0] == -jogador || tabuleiro[1][1] == -jogador ||
				tabuleiro[2][2] == -jogador)
		{
			if (tabuleiro[0][2] != jogador && tabuleiro[1][1] != jogador &&
				tabuleiro[2][0] != oponente)
			++c;
		}
	}
		
	return c;
}

struct Celula
a_estrela(int tabuleiro[3][3], int jogador)
{
	int vg;
	int vh;
	int f;
	struct Celula melhor;
	melhor.f = melhor.g = melhor.h = INFINITO;


	for (int i=0; i<TAM_TBL; ++i) {
		for (int j=0; j<TAM_TBL; ++j) {
			/* pula posicoes ja computadas */
			if (tabuleiro[i][j] != 0)
				continue;

			vg = g(i, j, -jogador,tabuleiro);
			vh = h(i, j, -jogador,tabuleiro);
			f = vg - vh;
	
			if (f < melhor.f) {
				melhor.f = f;
				melhor.h = vh;
				melhor.g = vg;
				melhor.i = i;
				melhor.j = j;
			}
		}
	}

	tabuleiro[melhor.i][melhor.j] = jogador;
	if (jogador == X) printf("\nX ");
	else printf("\nO ");

	printf("jogou em %d %d\n",melhor.i,melhor.j);
	mostra_tabuleiro(tabuleiro);
	return melhor;
}
