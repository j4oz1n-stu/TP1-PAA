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

bool escolheCaminho(int x, int y, Sala *matriz[], int m, int n, int qtChaves, int *qtChavesEncontradas, Posicao posicoes[], int *iPosicoes);

#endif