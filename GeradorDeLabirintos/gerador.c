#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "gerador.h"


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


char** gerador(int x, int y, int peca, int chave){

    char** matriz = criador(x,y); //// cria os espaços da matriz que o usuário digitou
    
    srand(time(NULL));
     


    int matriz_valida = 0; //// enquanto os valores não não servirem na criação, é possível reeditar os parâmetros, para que o labirinto torne-se válido

    while(matriz_valida == 0){
        inicializador(matriz,x,y); //// inicializa a matriz com todos os valores zeros 
        //// int peca delimita a quantidade de paredes(blocos) que o labirinto irá possuir
        int count = 0; /// contador de suporte que serve para interromper ciclo se não ouver mais espaco
        int peca_x;
        int peca_y;

        int contador_peca = 0; // conta quantas peças existem
        while(peca > contador_peca){

            matriz_valida = 1;

            if(count > 50){
                printf("Nao foi possivel posicionar mais paredes\n");
                printf("Disparidade-> pecas desejadas(%d); pecas colocadas(%d)\n", peca, contador_peca);
                matriz_valida = 0;
                break;
            }

            int formato = (rand() % 3) + 1;

            switch(formato){

                case 1:
                    peca_x = rand() % x;
                    peca_y = rand() % y;
                    if (matriz[peca_x][peca_y] == '0'){
                        matriz[peca_x][peca_y] = '1';
                    }
                    contador_peca++;
                
                break;

                case 2:
                    peca_x = rand() % (x - 1);
                    peca_y = rand() % y;
                    if (matriz[peca_x][peca_y] == '0' && matriz[peca_x + 1][peca_y] == '0'){
                        matriz[peca_x][peca_y] = '1';
                        matriz[peca_x + 1][peca_y] = '1';
                    }                                
                    contador_peca++;

                break;

                case 3:
                    peca_x = rand() % x;
                    peca_y = rand() % (y - 1);
                    if (matriz[peca_x][peca_y] == '0' && matriz[peca_x][peca_y + 1] == '0'){
                        matriz[peca_x][peca_y] = '1';
                        matriz[peca_x][peca_y + 1] = '1';
                    }
                    contador_peca++;

                break;

                case 4:
                    peca_x = rand() % (x - 1);
                    peca_y = rand() % (y - 1);
                    if (matriz[peca_x][peca_y] == '0' && matriz[peca_x + 1][peca_y + 1] == '0'){
                        matriz[peca_x][peca_y] = '1';
                        matriz[peca_x + 1][peca_y + 1] = '1';
                    }
                    contador_peca++;

                break;
            }

            count++;
        }


        count = 0;
        ///int chave colocará as chaves para o baú
        int flag_c = 0;
        int contador_chave = 0; // conta quantas chaves foram inseridas
        while(chave > contador_chave){

            while(flag_c == 0){

                if(count > 50){
                printf("Nao foi possivel colocar mais chaves");
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
                count++;
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
                printf("Nao foi possivel colocar bau");
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



        /// para tornar o labirinto, o usuario pode entao escolher qual fator mudar
        if(matriz_valida == 0){
            printf("Digite para qual fator voce deseja diminuir a quantidade para tornar o labirinto valido: \n");
            printf("1. Quantidade de pecas\n");
            printf("2. Quantidade de chaves\n\n");
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
                    printf("Quanto voce deseja diminuir ? ");
                    while(input_valido == 0){
                        scanf("%d", &diminuir);
                        if(peca - diminuir > 0){
                            input_valido = 1;
                        }
                    }
                    peca = peca - diminuir;
                    break;
                
                case 2:
                    printf("Quanto voce deseja diminuir ? ");
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
    
    return matriz;

}



