#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
/* coloque demais includes aqui */

/* ------------------- Nao altere estas structs ------------------------- */
struct nodo {
    int chave;
    struct nodo *prox;
};

struct lista {
    struct nodo *ini;
    struct nodo *ptr; /* ponteiro para algum nodo da lista (iterador) */
    int tamanho;

};
/* ---------------------------------------------------------------------- */

struct lista *lista_cria ()
{
	struct lista *l;
	if (!(l = malloc(sizeof(struct lista))))
		return NULL;

	l->ini = NULL;
	l->ptr = NULL;
	l->tamanho = 0;
	return l;
}

void lista_destroi (struct lista **lista)
{
	struct nodo * aux;

	(*lista)->ptr = (*lista)->ini;
	while (!((*lista)->ptr == NULL))
	{
		aux = (*lista)->ptr;
		(*lista)->ptr = (*lista)->ptr->prox;
		free(aux);

	}

	free(*lista);
	*lista = NULL;
	return;

}

int lista_insere_inicio (struct lista *lista, int chave)
{
	struct nodo *novo_nodo;
	if (!(novo_nodo = malloc(sizeof(struct nodo))))
		return 0;

	novo_nodo->prox = lista->ini;
	lista->ini = novo_nodo;
	novo_nodo->chave = chave;
	lista->tamanho =+ 1;
	return 1;
}

int lista_insere_fim (struct lista *lista, int chave)
{
	struct nodo *novo_nodo, *aux;
	if (!(novo_nodo = malloc(sizeof(struct nodo))))
    	return 0;

	aux = lista->ini;
    while (!(aux->prox == NULL))
	{
    	aux = aux->prox;
	}

	aux->prox = novo_nodo;
	novo_nodo->chave = aux->chave;
	novo_nodo->prox = NULL;
    lista->tamanho++;
    return 1;
}

int lista_vazia (struct lista *lista)
{
	if(lista->ini == NULL)
		return 1;
	return 0;
}

int lista_remove_inicio (struct lista *lista, int *chave)
{
	struct nodo *aux;
	if (lista_vazia(lista))
		return 0;

	*chave = lista->ini->chave;

	aux = lista->ini;
	lista->ini = lista->ini->prox;
	free(aux);

	lista->tamanho--;
	return 1;
}

int lista_remove_fim (struct lista *lista, int *chave)
{
	struct nodo *aux;
	if (lista_vazia(lista))
		return 0;

	aux = lista->ini;
	if (!(aux->prox = NULL))
   		 while (!(aux->prox->prox == NULL))
		{
        	aux = aux->prox;
		}

	free(aux);
	lista->tamanho--;
}


void lista_inicia_iterador (struct lista *lista)
{
	lista->ptr = lista->ini;
	return;
}

int lista_incrementa_iterador (struct lista *lista, int *chave)
{
	if (lista->ptr == NULL)
		return 0;

	*chave = lista->ptr->chave;
	lista->ptr = lista->ptr->prox;
	return 1;
}
void imprimir_lista (struct lista *l){
    int chave;

    if (lista_vazia (l)){
        printf ("lista vazia\n");
        return;
    }

    lista_inicia_iterador (l);
    lista_incrementa_iterador (l, &chave);
    printf ("%d", chave);
    while (lista_incrementa_iterador (l, &chave))
        printf (" %d", chave);
    printf ("\n");
}


void teste_insere_inicio (struct lista *l, int limite)
{
    int i;

    for (i=1; i <= limite; i++)
    {
        if (! lista_insere_inicio (l, i + 10)){
            printf ("Lista cheia, nao inseriu.\n");
            return;
        }
        imprimir_lista (l);
    }
}

int main()
{
	struct lista *l;
	int chave = 10;

	l = lista_cria();
	teste_insere_inicio(l,5);

	lista_destroi(&l);

}
