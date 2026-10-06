#include <stdio.h>
#include <stdbool.h>
#include "labirinto.h"

bool escolheCaminho(int x, int y, int m, int n, Sala matriz[m][n], int qtChaves, int *qtChavesEncontradas, Posicao posicoes[], int *iPosicoes){
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
    if((x >= 0 && x < m && y - 1 >= 0 && y - 1 < n) && (matriz[x][y - 1].visitado == false) && matriz[x][y - 1].conteudo != '1'){
        if(escolheCaminho(x, y - 1, m, n, matriz, qtChaves, qtChavesEncontradas, posicoes, iPosicoes)){
            posicoes[*iPosicoes].x = x;
            posicoes[*iPosicoes].y = y;
            (*iPosicoes)++;
            return true;
        }
    }
    if((x >= 0 && x < m && y + 1 >= 0 && y + 1 < n) && (matriz[x][y + 1].visitado == false) && matriz[x][y + 1].conteudo != '1'){
        if(escolheCaminho(x, y + 1,m, n, matriz, qtChaves, qtChavesEncontradas, posicoes, iPosicoes)){
            posicoes[*iPosicoes].x = x;
            posicoes[*iPosicoes].y = y;
            (*iPosicoes)++;
            return true;
        }
    }
    if((x + 1 >= 0 && x + 1 < m && y >= 0 && y < n) && (matriz[x + 1][y].visitado == false) && matriz[x + 1][y].conteudo != '1'){
        if(escolheCaminho(x + 1, y, m, n, matriz, qtChaves, qtChavesEncontradas, posicoes, iPosicoes)){
            posicoes[*iPosicoes].x = x;
            posicoes[*iPosicoes].y = y;
            (*iPosicoes)++;
            return true;
        }
    }
    if((x - 1>= 0 && x - 1 < m && y >= 0 && y < n) && (matriz[x - 1][y].visitado == false) && matriz[x - 1][y].conteudo != '1'){
        if(escolheCaminho(x - 1, y, m, n, matriz, qtChaves, qtChavesEncontradas, posicoes, iPosicoes)){
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