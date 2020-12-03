/* Lista para o A* */

struct Celula {
	int i;
	int j;
	int f; /* f=g+h */
	int g;
	int h;
};

struct Lista {
	struct Celula cel;
	struct Lista *prox;
	int feito;
};

struct Lista *
inserir(struct Celula *cel, struct Lista *lista)
{
	struct Lista *i;
	struct Lista *novo = (struct Lista *)malloc(sizeof(struct Lista));
	novo->cel = *cel;
	novo->feito = 0;

	/* caminha ate o fim da lista */
	for (i=lista; i->prox != NULL; i=i->prox);

	/* insere */
	i->prox = novo;
	return novo;
}

void
deletar(struct Celula *cel, struct Lista *lista)
{
	struct Lista *i;
	for (i=lista; (i->prox != NULL) && (&i->prox->cel != cel); i=i->prox);

	if (i->prox != NULL) {
		struct Lista *aux = i->prox;
		i->prox = i->prox->prox;
		aux->prox = NULL;
		free(aux);
	}
}
