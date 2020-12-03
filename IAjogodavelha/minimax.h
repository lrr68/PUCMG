/* MINIMAX NO JOGO DA VELHA */

int
minimax(int tabuleiro[3][3], int profundidade, int ehMax)
{
	int val = valor(tabuleiro);
	int melhor_val;
	int atual;

	/* max ganhou */
	if (val == 10)
		return val;

	/* min ganhou */
	if (val == -10)
		return val;

	/* empate */
	if (!tem_posicoes(tabuleiro))
		return 0;

	if (ehMax) {
		atual = X;
		melhor_val = -INFINITO;
	} else {
		atual = O;
		melhor_val = INFINITO;
	}

	/* percorre todas as posicoes */
	for (int i = 0; i<TAM_TBL; ++i) { 
		for (int j = 0; j<TAM_TBL; ++j) { 
			/* se for possivel, joga nessa posicao */
			if (tabuleiro[i][j] == 0) { 

				tabuleiro[i][j] = atual;
				val = minimax(tabuleiro, profundidade+1, !ehMax);

				melhor_val = ehMax ?
					MAX(melhor_val, val) :
					MIN(melhor_val, val); 

				/* desjoga */
				tabuleiro[i][j] = 0;
			} 
		} 
	} 

	return melhor_val;
}

/* retorna a posicao de 0 a 9 para a melhor jogada para o jogador j */
struct Jogada *
melhor_jogada(int tabuleiro[3][3], int jogador)
{
	int melhor_val = (jogador == X) ?
		-INFINITO :
		+INFINITO ;
	struct Jogada *melhor_jog = (struct Jogada *)malloc(sizeof(struct Jogada));
	melhor_jog->i = -1;
	melhor_jog->j = -1;
	/* jogador max faz a primeira jogada nessa funcao
	 * portanto ehMax inicia como min
	 * */
	int ehMax = !(jogador == X);

	/* percorre todas as posicoes e calcula minimax de todas as vazias */
	for (int i=0; i<TAM_TBL; ++i) {
		for (int j=0; j<TAM_TBL; ++j) {
			 
			if (tabuleiro[i][j] == 0) {
				
				tabuleiro[i][j] = jogador;

				int val = minimax(tabuleiro, 0, ehMax);
				/* desjoga */
				tabuleiro[i][j] = 0;

				if (jogador == X && val > melhor_val) {
					melhor_jog->i = i;
					melhor_jog->j = j;
				} else if (jogador == O && val < melhor_val) {
					melhor_jog->i = i;
					melhor_jog->j = j;
				}
				melhor_val = val;

			}
		}
	}

	return melhor_jog;
}

int rodar_minimax(int tabuleiro[3][3], int atual)
{
	/* X-MAX
	 * O-Min
	 * */

	struct Jogada *jogada = (struct Jogada *)malloc(sizeof (struct Jogada));
	jogada->i = -1;
	jogada->j = -1;

	while (! acabou(tabuleiro)) {

		jogada = melhor_jogada(tabuleiro,atual);

		if (atual == X) printf("\nX ");
		else printf("\nO ");
		printf("Jogou em %d %d:\n", jogada->i, jogada->j);

		tabuleiro[jogada->i][jogada->j] = atual;
		mostra_tabuleiro(tabuleiro);

		/* toogle no jogador */
		atual = -atual;
	}

	if (valor(tabuleiro) == 10)
		printf("MAX GANHOU\n");
	else if (valor(tabuleiro) == -10)
		printf("MIN GANHOU\n");
	else
		printf("EMPATE\n");

	return 0;
}
