#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Labirinto/labirinto.h"

int main(){
    printf("sistema de encontrar possiveis caminhos\n");
    printf("digite o caminho do arquivo que contem o labirinto:\n");
    char caminho [100];
    scanf("%s", caminho);
    FILE* arquivo = fopen(caminho, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return 1;
    }

    //instanciar a matriz e ler o arquivo
    int linhas, colunas;
    int qtdChaves;
    fscanf(arquivo, "%d %d", &linhas, &colunas);
    fscanf(arquivo, "%d", &qtdChaves);

    Sala matriz[linhas][colunas];
    Posicao posicaoInicial;
    Posicao posicoes[(linhas*colunas)+1];
    int k = 0;
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            fscanf(arquivo, " %c", &(matriz[i][j].conteudo));
            matriz[i][j].visitado = false;
            if (matriz[i][j].conteudo == 'A'){
                posicaoInicial.x = i;
                posicaoInicial.y = j;
            }
        }
    }
    for (int i = 0; i <= (linhas * colunas); i++) {
        posicoes[i].x = -1;
        posicoes[i].y = -1;
    }
    
    int iPosicoes = 0;
    int qtdChavesEncontradas = 0;
    escolheCaminho(posicaoInicial.x, posicaoInicial.y, linhas, colunas, matriz, qtdChaves, &qtdChavesEncontradas, posicoes, &iPosicoes);
    /*if (escolheCaminho(posicaoInicial.x, posicaoInicial.y, linhas, colunas, matriz, qtdChaves, &qtdChavesEncontradas, posicoes, &iPosicoes)){
        for(int i = iPosicoes-1; i>0; i--){
            printf("(%d, %d)", posicoes[i].x, posicoes[i].y);
        }
        printf("(%d, %d)\n", posicoes[0].x, posicoes[0].y);
    }
    else{
        printf("não existe caminho possivel");
    }*/
    printCriativo(linhas, colunas, matriz, posicoes, iPosicoes, qtdChaves);


}