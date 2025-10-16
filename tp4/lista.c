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
	lista->tamanho++;
	return 1;
}
/*botar comentarios */
int lista_insere_fim (struct lista *lista, int chave)
{
	struct nodo *novo_nodo, *aux;
	if (!(novo_nodo = malloc(sizeof(struct nodo))))
	{
		return 0;
	}

	if(!lista_vazia(lista)) /*tem jeito mais elegante de se implementar? */
	{
		aux = lista->ini;
		while (!(aux->prox == NULL))
		{ /*ver se resolve o problema do {} */
			aux = aux->prox;
		}
		aux->prox = novo_nodo;
	}
	else
		lista->ini = novo_nodo;

	novo_nodo->chave = chave;
	novo_nodo->prox = NULL;
	lista->tamanho++;
	return 1;
}

int lista_insere_ordenado (struct lista *lista, int chave) /*decrescente ou crescente ou ambos? */
{
 	struct nodo *novo_nodo;
	struct nodo *aux;
	if (!(novo_nodo = malloc(sizeof(struct nodo))))
		return 0;

	if (lista_vazia(lista)) /* jeito mais elegante? */
	{
		lista->ini = novo_nodo;
		novo_nodo->prox = NULL;
	}

	else if (lista->ini->chave > chave) /* o que é mais elegante, else if ou double return + definir aux no inicio
ou usar lista->ini?*/
	{
		novo_nodo->prox = lista->ini;
		lista->ini = novo_nodo;
	}
	else
	{
		aux = lista->ini;
		while ((aux->prox != NULL) && (aux->prox->chave < chave))
		{
			aux = aux->prox;
		}
		novo_nodo->prox = aux->prox;
		aux->prox = novo_nodo;
	}
	novo_nodo->chave = chave;
	lista->tamanho++;

	return 1;
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
		{
	return 0;
		}

	aux = lista->ini;
	if ((aux->prox == NULL))
		{
			*chave = aux->chave;
			free(lista->ini);
			lista->ini = NULL;
		}
	else
	{
		while (!(aux->prox->prox == NULL))
		{
		aux = aux->prox;
		}
		*chave = aux->prox->chave;
		free(aux->prox);
		aux->prox = NULL;
	}
	lista->tamanho--;
	return 1;
}

int lista_remove_ordenado (struct lista *lista, int chave)
{
	struct nodo *aux;
	struct nodo *deleta_nodo;
	if (lista_vazia(lista))
	{
		return 0;
	}

	aux = lista->ini;
	if (aux->prox == NULL) /* maneira mais eficiente?*/
	{
		free(aux);
		lista->ini = NULL;
		lista->tamanho--;
		return 1;
	}
	if (aux->chave == chave)
	{
 		lista->ini = lista->ini->prox;
		free(aux); /* unificar os free? deleta_nodo = aux; */
	}

	else
	{
		while (aux->prox->chave != chave)
		{
			aux = aux->prox;
		}
		deleta_nodo = aux->prox;
		aux->prox = aux->prox->prox;
		free(deleta_nodo);
	}

	lista->tamanho--;
	return 1;
}

int lista_vazia (struct lista *lista)
{
	if(lista->ini == NULL)
		return 1;
	return 0;
}

int lista_tamanho (struct lista *lista)
{
	return lista->tamanho;
}

int lista_pertence (struct lista *lista, int chave)
{
	struct nodo *aux = lista->ini;

	while ((aux != NULL) && (aux->chave != chave))
	{
		aux = aux->prox;
	}
	if (aux == NULL)
		return 0;
	return 1;
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
