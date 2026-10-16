#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "gerador.h"
#include "../Cores/cores.h"


//formato de peças
//1.    1
//
//2.    11
//
//3.    1
//      1
//
//4.    1
//       1


char** criador(int x, int y) {
    char **matriz = (char **)malloc(x * sizeof(char *));
    for (int i = 0; i < x; i++) {
        matriz[i] = (char *)malloc(y * sizeof(char));
    }
    return matriz;
}

void inicializador(char **matriz, int x, int y){
        for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            matriz[i][j] = '0';
        }
    }
}

void printaMatrizGerador(int m, int n, char **matriz) {
    printf("\n");
    for (int i = 0; i < m; i++) {
        printf("│ "); // Borda esquerda
        for (int j = 0; j < n; j++) {
            // Renderização customizada por elemento
            if (matriz[i][j] == 'C') {
                aplicarCorTexto(TEXTO_AMARELO);
                printf("C ");
            } else if (matriz[i][j] == '1') {
                aplicarCorFundo(FUNDO_AZUL);
                printf("  ");
            } else if (matriz[i][j] == 'X' || matriz[i][j] == 'A') {
                aplicarCorFundo(FUNDO_MAGENTA);
                aplicarCorTexto(TEXTO_MAGENTA);
                printf("%c ", matriz[i][j]);
            } else {
                printf("%c ", matriz[i][j]);
            }
            resetarCores();
        }
        
        printf("│"); // Borda direita do labirinto
        printf("\n");
    }
    printf("\n");
}

void gerador(int x, int y, int peca, int chave){

    char** matriz = criador(x,y); //// cria os espaços da matriz que o usuário digitou
    
    srand(time(NULL));
     


    int matriz_valida = 0; //// enquanto os valores não não servirem na criação, é possível reeditar os parâmetros, para que o labirinto torne-se válido

    while(matriz_valida == 0){
        inicializador(matriz,x,y); //// inicializa a matriz com todos os valores zeros 
        //// int peca delimita a quantidade de paredes(blocos) que o labirinto irá possuir
        int count = 0; /// contador de suporte que serve para interromper ciclo se não ouver mais espaco
        int peca_x;
        int peca_y;

        int flag_p = 0;
        int contador_peca = 0; // conta quantas peças existem
        while(peca > contador_peca){

            matriz_valida = 1;
        
            int formato = (rand() % 4) + 1;
            flag_p = 0;
            count = 0;

            while(flag_p == 0){
                if(formato == 1){
                    if(count > 50){
                        printf("Nao foi possivel posicionar mais paredes.\n");
                        printf("Disparidade-> pecas desejadas(%d); pecas colocadas(%d)\n", peca, contador_peca);
                        matriz_valida = 0;
                        break;
                    }
                            peca_x = rand() % x;
                            peca_y = rand() % y;
                            if (matriz[peca_x][peca_y] == '0'){
                                matriz[peca_x][peca_y] = '1';
                                flag_p = 1;
                                contador_peca++;
                            }
                            else{
                                count++;
                            }
                        }

                else if(formato == 2){
                    if(count > 50){
                        printf("Nao foi possivel posicionar mais paredes.\n");
                        printf("Disparidade-> pecas desejadas(%d); pecas colocadas(%d)\n", peca, contador_peca);
                        matriz_valida = 0;
                        break;
                    }
                            peca_x = rand() % (x - 1);
                            peca_y = rand() % y;
                            if (matriz[peca_x][peca_y] == '0' && matriz[peca_x + 1][peca_y] == '0'){
                                matriz[peca_x][peca_y] = '1';
                                matriz[peca_x + 1][peca_y] = '1';
                                flag_p = 1;
                                contador_peca++;
                            }
                            else{
                                count++;
                            }                                
                }

                else if(formato == 3){
                    if(count > 50){
                        printf("Nao foi possivel posicionar mais paredes.\n");
                        printf("Disparidade-> pecas desejadas(%d); pecas colocadas(%d)\n", peca, contador_peca);
                        matriz_valida = 0;
                        break;
                    }
                            peca_x = rand() % x;
                            peca_y = rand() % (y - 1);
                            if (matriz[peca_x][peca_y] == '0' && matriz[peca_x][peca_y + 1] == '0'){
                                matriz[peca_x][peca_y] = '1';
                                matriz[peca_x][peca_y + 1] = '1';
                                flag_p = 1;
                                contador_peca++;
                            }
                            else{
                                count++;
                            }
                }

                else if(formato == 4){
                    if(count > 50){
                        printf("Nao foi possivel posicionar mais paredes.\n");
                        printf("Disparidade-> pecas desejadas(%d); pecas colocadas(%d)\n", peca, contador_peca);
                        matriz_valida = 0;
                        break;
                    }
                            peca_x = rand() % (x - 1);
                            peca_y = rand() % (y - 1);
                            if (matriz[peca_x][peca_y] == '0' && matriz[peca_x + 1][peca_y + 1] == '0'){
                                matriz[peca_x][peca_y] = '1';
                                matriz[peca_x + 1][peca_y + 1] = '1';
                                flag_p = 1;
                                contador_peca++;
                            }
                            else{
                                count++;
                            }
                    }
            }

            if(matriz_valida == 0){
                break;
            }


        }

        count = 0;
        ///int chave colocará as chaves para o baú
        int flag_c = 0;
        int contador_chave = 0; // conta quantas chaves foram inseridas
        while(chave > contador_chave){
            count = 0;
            while(flag_c == 0){

                if(count > 50){
                printf("Nao foi possivel colocar mais chaves.\n");
                printf("Disparidade-> chaves desejadas(%d); chaves colocadas(%d)\n", chave, contador_chave);
                    matriz_valida = 0;
                    break;
                }

                
            
                peca_x = rand() % x;
                peca_y = rand() % y;
                if (matriz[peca_x][peca_y] == '0'){
                    matriz[peca_x][peca_y] = 'C';
                    contador_chave++;
                    flag_c = 1;
                }
                else{
                    count++;
                }

            }

            if(matriz_valida == 0){
                break;
            }
            
            flag_c = 0;
        }

        count = 0;
        int flag_b = 0;

        while(flag_b == 0){

            if(count > 50){
                printf("Nao foi possivel colocar bau.\n");
                matriz_valida = 0;
                break;
            }

            peca_x = rand() % x;
            peca_y = rand() % y;

            if (matriz[peca_x][peca_y] == '0'){
                matriz[peca_x][peca_y] = 'X';
                flag_b = 1;
            }
            count++;
        }

        count = 0;
        int flag_a = 0;

        while(flag_a == 0){

            if(count > 50){
                printf("Nao foi possivel colocar entrada.\n");
                matriz_valida = 0;
                break;
            }

            peca_x = rand() % x;
            peca_y = rand() % y;

            if (matriz[peca_x][peca_y] == '0'){
                matriz[peca_x][peca_y] = 'A';
                flag_a = 1;
            }
            count++;
        }



        /// para tornar o labirinto, o usuario pode entao escolher qual fator mudar
        if(matriz_valida == 0){
            printf("Digite para qual fator voce deseja diminuir a quantidade para tornar o labirinto valido: \n");
            printf("1. Quantidade de pecas\n");
            printf("2. Quantidade de chaves\n");
            int input_valido = 0;
            int escolha;
            while(input_valido == 0){
                scanf("%d", &escolha);
                if(escolha == 1 || escolha == 2){
                    input_valido = 1;
                }
                else{
                    printf("ESCOLHA UM VALOR VALIDO\n");
                }
            }

            input_valido = 0;
            int diminuir;
            switch(escolha){
                case 1:
                    printf("Quanto voce deseja diminuir? ");
                    while(input_valido == 0){
                        scanf("%d", &diminuir);
                        if(peca - diminuir > 0){
                            input_valido = 1;
                        }
                    }
                    peca = peca - diminuir;
                    break;
                
                case 2:
                    printf("Quanto voce deseja diminuir? ");
                    while(input_valido == 0){
                        scanf("%d", &diminuir);
                        if(chave - diminuir > 0){
                            input_valido = 1;
                        }
                    }
                    chave = chave - diminuir;
                    break;
            }
            printf("Novos valores do labirinto: peca(%d); chave(%d)\n", peca, chave);
        }
    }
    
    ///Agora que todos os valores da matriz são válidos, é hora de colocar no arquivo teste
    int abre = escritor(matriz,x,y,chave);
    if(abre == 1){
        printf("Não foi possível escrever no arquivo de saída. Tente novamente!\n");
    }
    else{
        printaMatrizGerador(x, y, matriz);
        printf("O labirinto gerado foi salvo no arquivo 'Testes/gerado.txt'\n");
    }
}

int escritor(char **matriz, int x, int y, int chave){

    /*for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            printf("%c ", matriz[i][j]);
        }
        printf("\n");
    }*/

    FILE *arquivo = fopen("Testes/gerado.txt", "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    fprintf(arquivo, "%d %d\n", x,y);

    fprintf(arquivo, "%d\n", chave);

    
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            fprintf(arquivo, "%c ", matriz[i][j]);
        }
        fprintf(arquivo, "\n");
    }

    fclose(arquivo);
    return 0;
}


