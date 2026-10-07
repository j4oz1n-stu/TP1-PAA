#include <stdio.h>
#include <stdbool.h>
#include "labirinto.h"
#include "../Cores/cores.h"

#ifdef _WIN32
    #include <windows.h>
    #define PAUSA(ms) Sleep(ms) 
#else
    #include <unistd.h>
    #define PAUSA(ms) usleep((ms)*1000)   
#endif

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

void printaMatriz (int m, int n, Sala matriz[m][n]){
    for (int i=0; i<m; i++){
        for (int j=0; j<n; j++){
            if (matriz[i][j].conteudo=='#'){
                aplicarCorFundo(FUNDO_VERMELHO);
                aplicarCorTexto(TEXTO_VERMELHO);
            }
            else if (matriz[i][j].conteudo == '1'){
                aplicarCorFundo(FUNDO_AZUL);
                aplicarCorTexto(TEXTO_AZUL);
            }
            printf("%c", matriz[i][j].conteudo);
            resetarCores();
            if (j == n - 1) {
                printf("\n");
            } else {
                printf(" ");
            }
        }
    }
}

void printCriativo (int m, int n, Sala matriz[m][n], Posicao posicoes[], int iPosicoes){
    int passo = 1;
    for (int i = iPosicoes-2; i>0; i--){
        matriz[posicoes[i].x][posicoes[i].y].conteudo = '#';
        printf("\n--- Passo %d ---\n", passo++);
        printaMatriz(m, n, matriz);
        PAUSA(450);
    }
}