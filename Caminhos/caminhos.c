#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>    
#include "labirinto.h" 
#include "caminhos.h"

void inicializaCaminhos(ListaCaminhos *lista) {
    lista->inicio = (NoCaminho*) malloc(sizeof(NoCaminho));
    lista->final = lista->inicio;
    lista->inicio->prox = NULL;
    lista->qtdCaminhos = 0;
}

bool caminhosVazios(ListaCaminhos lista) {
    return (lista.inicio == lista.final);
}

void insereCaminho(ListaCaminhos *lista, Posicao caminho[], int tamanho) {
    lista->final->prox = (NoCaminho*) malloc(sizeof(NoCaminho));
    lista->final = lista->final->prox;
    lista->final->vetorCaminho = (Posicao*) malloc(tamanho * sizeof(Posicao));
    for( int i = 0; i < tamanho; i++) {
        lista->final->vetorCaminho[i] = caminho[i];
    }
    lista->final->tamanhoCaminho = tamanho;
    lista->final->prox = NULL;
    (lista->qtdCaminhos)++;
}

void imprimeCaminhos(ListaCaminhos lista) {
    NoCaminho* aux = lista.inicio->prox; 
    int contador = 1; 
    while(aux != NULL) {
        printf("Caminho %d (%d passos): ", contador, aux->tamanhoCaminho);
        for (int i = 0; i < aux->tamanhoCaminho; i++) {
            printf("(%d, %d)", aux->vetorCaminho[i].x, aux->vetorCaminho[i].y);
            if (i < aux->tamanhoCaminho - 1) {
                printf(" -> ");
            }
        }
        printf("\n"); 
        aux = aux->prox;
        contador++;
    }
}

int retornaQtdCaminhos(ListaCaminhos lista) {
    return lista.qtdCaminhos;
}

void liberaCaminhos(ListaCaminhos *lista) {
    NoCaminho *atual = lista->inicio->prox;
    NoCaminho *proximo;
    while (atual != NULL) {
        proximo = atual->prox;       
        free(atual->vetorCaminho);   
        free(atual);                 
        atual = proximo;
    }
    free(lista->inicio);
    lista->inicio = NULL;
    lista->final = NULL;
    lista->qtdCaminhos = 0;
}