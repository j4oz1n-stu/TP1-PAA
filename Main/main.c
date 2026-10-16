#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "../Labirinto/labirinto.h"
#include "../GeradorDeLabirintos/gerador.h"
#include "../ModoHistoria/historia.h"

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
    fclose(arquivo);

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
                if (escolheCaminho(posicaoInicial.x, posicaoInicial.y, linhas, colunas, matriz, qtdChaves, &qtdChavesEncontradas, posicoes, &iPosicoes)){

                    //duplica a matriz porque printCriativo modifica ela
                    Sala matriz2[linhas][colunas];
                    for(int i = 0; i < linhas; i++){
                        for(int j = 0; j < colunas; j++){
                            matriz2[i][j].conteudo = matriz[i][j].conteudo;
                            matriz2[i][j].visitado = false;
                        }
                    }
                    printCriativo(linhas, colunas, matriz2, posicoes, iPosicoes, qtdChaves);
                    for(int i = 0; i < iPosicoes; i++){
                        printf("[%d, %d] ", posicoes[i].x, posicoes[i].y);
                    }
                    printf("\n");
                }
                else{
                    printf("Não existe caminho possivel!\n");
                }
                //reinicia o visitados da matriz, por conta de outras funções
                for(int i = 0; i < linhas; i++){
                    for(int j = 0; j < colunas; j++){
                        matriz[i][j].visitado = false;
                    }
                }
                break;
            }
            case 2: {
                int iPosicoes = 0;
                int qtdChavesEncontradas = 0;
                ListaCaminhos caminhos;
                inicializaCaminhos(&caminhos);
                encontraTodosCaminhos(posicaoInicial.x, posicaoInicial.y, linhas, colunas, matriz, qtdChaves, &qtdChavesEncontradas, posicoes, &iPosicoes, &caminhos);
                imprimeCaminhos(caminhos);
                printf("Deseja ver, visualmente, algum dos caminhos? (S ou N): ");
                char escolha;
                getchar();
                scanf("%c", &escolha);
                if(escolha == 'S'){
                    int num;
                    printf("Digite o número do caminho: ");
                    scanf("%d", &num);
                    //duplica a matriz porque printCriativo modifica ela
                    Sala matriz2[linhas][colunas];
                    for(int i = 0; i < linhas; i++){
                        for(int j = 0; j < colunas; j++){
                            matriz2[i][j].conteudo = matriz[i][j].conteudo;
                            matriz2[i][j].visitado = false;
                        }
                    }
                    NoCaminho* aux = caminhos.inicio->prox; 
                    int contador = 1; 
                    while(aux != NULL && contador != num) {
                        aux = aux->prox;
                        contador++;
                    }
                    printCriativo(linhas, colunas, matriz2, aux->vetorCaminho, aux->tamanhoCaminho, qtdChaves);
                }
                //reinicia o visitados da matriz, por conta de outras funções
                for(int i = 0; i < linhas; i++){
                    for(int j = 0; j < colunas; j++){
                        matriz[i][j].visitado = false;
                    }
                }
                break;
            }
            case 3: {
                int iPosicoes = 0;
                int qtdChavesEncontradas = 0;
                if (Cobrinha(posicaoInicial.x, posicaoInicial.y, linhas, colunas, matriz, qtdChaves, &qtdChavesEncontradas, posicoes, &iPosicoes)){

                    //duplica a matriz porque printCriativo modifica ela
                    Sala matriz2[linhas][colunas];
                    for(int i = 0; i < linhas; i++){
                        for(int j = 0; j < colunas; j++){
                            matriz2[i][j].conteudo = matriz[i][j].conteudo;
                            matriz2[i][j].visitado = false;
                        }
                    }
                    printCriativo(linhas, colunas, matriz2, posicoes, iPosicoes, qtdChaves);
                    for(int i = 0; i < iPosicoes; i++){
                        printf("[%d, %d] ", posicoes[i].x, posicoes[i].y);
                    }
                    printf("\n");
                }
                else{
                    printf("Não existe caminho possivel!\n");
                }
                //reinicia o visitados da matriz, por conta de outras funções
                for(int i = 0; i < linhas; i++){
                    for(int j = 0; j < colunas; j++){
                        matriz[i][j].visitado = false;
                    }
                }
                break;
            }
            case 4: {
                modoHistoriaInterativo(linhas, colunas, matriz);
                break;
            }
            case 5: {
                int m, n, pecas, chaves;
                printf("Digite o número de linhas e colunas do labirinto, nessa ordem: ");
                scanf("%d %d", &m, &n);
                printf("Digite o número de peças de paredes do labirinto: ");
                scanf("%d", &pecas);
                printf("Digite o número de chaves do labirinto: ");
                scanf("%d", &chaves);
                gerador(m, n, pecas, chaves);
                break;
            }
            default:
                exit(0);
        }
    }
    return 0;
}