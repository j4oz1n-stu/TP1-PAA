#ifndef CORES_H
#define CORES_H

#define RESET "\u001b[0m"

//Cores de Texto
#define TEXTO_PRETO "\u001b[30m"
#define TEXTO_VERMELHO "\u001b[31m"
#define TEXTO_VERDE "\u001b[32m"
#define TEXTO_AMARELO "\u001b[33m"
#define TEXTO_AZUL "\u001b[34m"
#define TEXTO_MAGENTA "\u001b[35m"
#define TEXTO_CIANO "\u001b[36m"
#define TEXTO_BRANCO "\u001b[37m"

//Cores de Fundo
#define FUNDO_PRETO "\u001b[40m"
#define FUNDO_VERMELHO "\u001b[41m"
#define FUNDO_VERDE "\u001b[42m"
#define FUNDO_AMARELO "\u001b[43m"
#define FUNDO_AZUL "\u001b[44m"
#define FUNDO_MAGENTA "\u001b[45m"
#define FUNDO_CIANO "\u001b[46m"
#define FUNDO_BRANCO "\u001b[47m"

void aplicarCorTexto(char cor[]);
void aplicarCorFundo(char cor[]);
void resetarCores();
char* corTextoAleatoria();
char* corFundoAleatoria();

#endif