#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cores.h"

void aplicarCorTexto(char cor[]){
    printf("%s", cor);
}
void aplicarCorFundo(char cor[]){
    printf("%s", cor);
}
void resetarCores(){
    printf(RESET);
}

char* corTextoAleatoria(){
    int aleatorio = rand() % 7;
    switch (aleatorio){
        case 0:
            return TEXTO_AMARELO;
        case 1:
            return TEXTO_AZUL;
        case 2:
            return TEXTO_CIANO;
        case 3:
            return TEXTO_MAGENTA;
        case 4:
            //return TEXTO_PRETO
            return TEXTO_BRANCO;
        case 5:
            return TEXTO_VERDE;
        case 6:
            return TEXTO_VERMELHO;
        default:
            return TEXTO_AZUL;
            break;
    }
}

char* corFundoAleatoria(){
    int aleatorio = rand() % 7;
    switch (aleatorio){
        case 0:
            return FUNDO_AMARELO;
        case 1:
            return FUNDO_AZUL;
        case 2:
            return FUNDO_CIANO;
        case 3:
            return FUNDO_MAGENTA;
        case 4:
            return FUNDO_BRANCO;
        case 5:
            return FUNDO_VERDE;
        case 6:
            return FUNDO_VERMELHO;
        //case 7:
            //return FUNDO_PRETO;
        default:
            return FUNDO_AZUL;
            break;
    }
}