#ifndef LABIRINTO_H
#define LABIRINTO_H

typedef struct {
    char conteudo;
    bool visitado;
} Sala;

typedef struct{
    int x;
    int y;
} Posicao;

bool escolheCaminho(int x, int y, int m, int n, Sala matriz[m][n], int qtChaves, int *qtChavesEncontradas, Posicao posicoes[], int *iPosicoes);
void printaMatriz (int m, int n, Sala matriz[m][n]);
void printCriativo (int m, int n, Sala matriz[m][n], Posicao posicoes[], int iPosicoes);

#endif