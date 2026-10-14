#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "../Labirinto/labirinto.h"
#include "../GeradorDeLabirintos/gerador.h"

int main(){
    srand(time(NULL));
    printf("\n=========================================\n");
    printf("ANÁLISE DE  LABIRINTOS\n");
    printf("=========================================\n");
    printf("Digite o caminho do arquivo que contém o labirinto:\n");
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

    while(true){
        printf("\n=========================================\n");
        printf("ANÁLISE DE  LABIRINTOS\n");
        printf("=========================================\n");
        printf("1 - Encontrar um único caminho válido\n");
        printf("2 - Encontrar todos os caminhos válidos\n");
        printf("3 - Modo labirinto sem bordas\n");
        printf("4 - Modo história interativo\n");
        printf("5 - Gerador de labirintos\n");
        printf("6 - Sair\n");
        
        int escolha;
        printf("Digite a opcao: ");
        scanf("%d", &escolha);
        switch(escolha){
            case 1: {
                int iPosicoes = 0;
                int qtdChavesEncontradas = 0;
                escolheCaminho(posicaoInicial.x, posicaoInicial.y, linhas, colunas, matriz, qtdChaves, &qtdChavesEncontradas, posicoes, &iPosicoes);
                if (escolheCaminho(posicaoInicial.x, posicaoInicial.y, linhas, colunas, matriz, qtdChaves, &qtdChavesEncontradas, posicoes, &iPosicoes)){
                    for(int i = 0; i < iPosicoes; i++){
                        printf("[%d, %d]", posicoes[i].x, posicoes[i].y);
                    }
                    printf("[%d, %d]\n", posicoes[0].x, posicoes[0].y);
                }
                else{
                    printf("Não existe caminho possivel!\n");
                }
                break;
            }
            case 2: {

                break;
            }
            case 3: {

                break;
            }
            case 4: {
                
                break;
            }
            case 5: {
                
                break;
            }
            default:
                exit(0);
        }
    }
    return 0;
}