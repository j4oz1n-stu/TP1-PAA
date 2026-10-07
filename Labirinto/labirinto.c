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

void limparTela(void) {
    printf("\x1b[H\x1b[J");
}

/*void printaMatriz (int m, int n, Sala matriz[m][n], int qtdChaves, int qtdChavesEncontradas){
    for (int i=0; i<m; i++){
        for (int j=0; j<n; j++){
            if (matriz[i][j].conteudo=='#'){
                aplicarCorFundo(FUNDO_VERDE);
                aplicarCorTexto(TEXTO_VERDE);
            }
            else if (matriz[i][j].conteudo == '1'){
                aplicarCorFundo(FUNDO_AZUL);
                aplicarCorTexto(TEXTO_AZUL);
            }
            if (matriz[i][j].conteudo == 'X' || matriz[i][j].conteudo == 'A'){
                aplicarCorFundo(FUNDO_VERDE);
                aplicarCorTexto(TEXTO_VERDE);   
            }
            printf("%c", matriz[i][j].conteudo);
            resetarCores();
            printf(" ");
        }
        if(i==(m/2)-2){
            printf("        chaves necessarias: %d", qtdChaves);
        }
        if (i==(m/2)-1){
            printf("        chaves encontradas: %d", qtdChavesEncontradas);
        }
        printf("\n");
    }
}*/
void printaMatriz(int m, int n, Sala matriz[m][n], int qtdChaves, int qtdChavesEncontradas, int passoAtual, int totalPassos) {

    for (int i = 0; i < m; i++) {
        printf("│ "); // Borda esquerda
        
        for (int j = 0; j < n; j++) {
            // Renderização customizada por elemento
            if (matriz[i][j].conteudo == '#') {
                // Imprime um bloco preenchido (espaço duplo com fundo colorido)
                aplicarCorFundo(FUNDO_VERDE);
                printf("  "); 
            } else if (matriz[i][j].conteudo == 'C') {
                // Destaque para Chave
                aplicarCorTexto(TEXTO_AMARELO);
                printf("C ");
            } else if (matriz[i][j].conteudo == '1') {
                aplicarCorFundo(FUNDO_AZUL);
                printf("  ");
            } else if (matriz[i][j].conteudo == 'X' || matriz[i][j].conteudo == 'A') {
                aplicarCorFundo(FUNDO_MAGENTA);
                aplicarCorTexto(TEXTO_MAGENTA);
                printf("%c ", matriz[i][j].conteudo);
            } else {
                printf("%c ", matriz[i][j].conteudo);
            }
            
            resetarCores();
        }
        
        printf("│"); // Borda direita do labirinto

        // 2. PAINEL LATERAL DE STATUS (HUD)
        if (i == 0) {
            printf("   ==== PAINEL DE STATUS =====");
        } else if (i == 1) {
            printf("   │  Passo:  %-3d / %-3d      │", passoAtual, totalPassos);
        } else if (i == 2) {
            printf("   │  Chaves: %d / %-3d        │", qtdChavesEncontradas, qtdChaves);
        } else if (i == 3) {
            printf("   ===========================");
        }

        printf("\n");
    }
}

void printCriativo (int m, int n, Sala matriz[m][n], Posicao posicoes[], int iPosicoes, int qtdChaves){
    int passo = 1;
    int totalPassos = iPosicoes - 2;
    int qtdChavesEncontradas = 0;
    for (int i = iPosicoes-2; i>0; i--){
        limparTela();
        if (matriz[posicoes[i].x][posicoes[i].y].conteudo == 'C') qtdChavesEncontradas++;
        matriz[posicoes[i].x][posicoes[i].y].conteudo = '#';
        printaMatriz(m, n, matriz, qtdChaves, qtdChavesEncontradas, passo, totalPassos);
        passo++;
        PAUSA(450);
    }
    printf("\n");
}