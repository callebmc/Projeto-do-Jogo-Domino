#ifndef DOMINO_H_INCLUDED
#define DOMINO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node
{
    int ladoA;
    int ladoB;
    struct node* next;
    struct node* prev;
} Lista;

Lista* criar (void);

Lista* inserir (Lista* lista, int elemA, int elemB);

Lista* inserir_fim(Lista* lista, int elemA, int elemB);

void imprimir_para_frente (Lista *lista);

void liberar (Lista *lista);

Lista* procurar(Lista* lista, int elemA, int elemB);

Lista* remover (Lista *lista, int elemA, int elemB);

int jogo_jogado(Lista* jogo, Lista* player1, Lista* player2, Lista* domino, int vez);

int tamanho(Lista* l);

int comprar(Lista** l, Lista** p);

int verifica(Lista* domino, Lista* peca);

void imprimir_pecas(Lista* l);

int jogada_pc(Lista** j, Lista** d, Lista** p);

int soma_pecas(Lista* p);

#endif // DOMINO_H_INCLUDED
