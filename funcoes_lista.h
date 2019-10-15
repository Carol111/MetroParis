
// Funções da lista de adjacências

//-------------------------------------------------------------------------------------------------

//Cria lista vazia

void vazia(TipoLista *lista)
{
    lista->head = (LINK)malloc(sizeof(celula));
    lista->tail = lista->head;
    lista->head->prox = NULL;
}

//Insere nova celula depois do ultimo vertice adjacente

void insere(int *e,char *l,float *d, TipoLista *lista)
{
    lista->tail->prox = (LINK)malloc(sizeof(celula));
    lista->tail = lista->tail->prox;
    lista->tail->estacao = *e;
    lista->tail->linha = *l;
    lista->tail->d_real = *d;
    lista->tail->prox = NULL;
}
