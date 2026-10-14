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