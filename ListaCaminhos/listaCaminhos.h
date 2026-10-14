#ifndef LISTACAMINHOS_H
#define LISTACAMINHOS_H

typedef struct NoCaminho {
    Posicao *vetorCaminho;
    int tamanhoCaminho;
    struct NoCaminho *prox;
} NoCaminho;

typedef struct {
    NoCaminho *inicio, *final;
    int qtdCaminhos;
} ListaCaminhos;

void inicializaCaminhos(ListaCaminhos *lista);
bool caminhosVazios(ListaCaminhos lista);
void insereCaminho(ListaCaminhos *lista, Posicao caminho[], int tamanho);
void imprimeCaminhos(ListaCaminhos lista);
int retornaQtdCaminhos(ListaCaminhos lista);
void liberaCaminhos(ListaCaminhos *lista);


#endif