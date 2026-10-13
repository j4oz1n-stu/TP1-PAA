#include <stdio.h>
#include <stdbool.h>
#include "Labirinto/labirinto.h"

//so tem que mudar pra funcao deixar ultrapassar a parede e mudar a
bool Cobrinha(int x, int y, int m, int n, Sala matriz[m][n], int qtChaves, int *qtChavesEncontradas, Posicao posicoes[], int *iPosicoes){
    matriz[x][y].visitado = true;
    if(matriz[x][y].conteudo == 'X' && qtChaves == *qtChavesEncontradas){
        posicoes[*iPosicoes].x = x;
        posicoes[*iPosicoes].y = y;
        (*iPosicoes)++;
        return true;
    }
    if(matriz[x][y].conteudo == 'C'){
        (*qtChavesEncontradas)++;
    }
    if((matriz[x][(y - 1 + n)% n].visitado == false) && matriz[x][(y - 1 + n)% n].conteudo != '1'){
        if(Cobrinha(x, ((y - 1 + n)% n), m, n, matriz, qtChaves, qtChavesEncontradas, posicoes, iPosicoes)){
            posicoes[*iPosicoes].x = x;
            posicoes[*iPosicoes].y = y;
            (*iPosicoes)++;
            return true;
        }
    }
    if((matriz[x][(y + 1 + n)% n].visitado == false) && matriz[x][(y + 1 + n)% n].conteudo != '1'){
        if(Cobrinha(x, ((y + 1 + n)% n),m, n, matriz, qtChaves, qtChavesEncontradas, posicoes, iPosicoes)){
            posicoes[*iPosicoes].x = x;
            posicoes[*iPosicoes].y = y;
            (*iPosicoes)++;
            return true;
        }
    }
    if((matriz[(x + 1 + m)% m][y].visitado == false) && matriz[(x + 1 + m)% m][y].conteudo != '1'){
        if(Cobrinha(((x + 1 + m)% m), y, m, n, matriz, qtChaves, qtChavesEncontradas, posicoes, iPosicoes)){
            posicoes[*iPosicoes].x = x;
            posicoes[*iPosicoes].y = y;
            (*iPosicoes)++;
            return true;
        }
    }
    if((matriz[(x - 1 + m)% m][y].visitado == false) && matriz[(x - 1 + m)% m][y].conteudo != '1'){
        if(Cobrinha(((x - 1 + m)% m), y, m, n, matriz, qtChaves, qtChavesEncontradas, posicoes, iPosicoes)){
            posicoes[*iPosicoes].x = x;
            posicoes[*iPosicoes].y = y;
            (*iPosicoes)++;
            return true;
        }
    }
    if(matriz[x][y].conteudo == 'C') (*qtChavesEncontradas)--;
    matriz[x][y].visitado = false;
    return false;
}
