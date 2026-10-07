#ifndef CORES_H
#define CORES_H

#define RESET "\x1b[0m"

// Cores de Texto
#define TEXTO_PRETO "\x1b[30m"
#define TEXTO_VERMELHO "\x1b[31m"
#define TEXTO_VERDE "\x1b[32m"
#define TEXTO_AMARELO "\x1b[33m"
#define TEXTO_AZUL "\x1b[34m"
#define TEXTO_MAGENTA "\x1b[35m"
#define TEXTO_CIANO "\x1b[36m"
#define TEXTO_BRANCO "\x1b[37m"

// Cores de Fundo
#define FUNDO_PRETO "\x1b[40m"
#define FUNDO_VERMELHO "\x1b[41m"
#define FUNDO_VERDE "\x1b[42m"
#define FUNDO_AMARELO "\x1b[43m"
#define FUNDO_AZUL "\x1b[44m"
#define FUNDO_MAGENTA "\x1b[45m"
#define FUNDO_CIANO "\x1b[46m"
#define FUNDO_BRANCO "\x1b[47m"

void aplicarCorTexto(char cor[]);
void aplicarCorFundo(char cor[]);
void resetarCores();
char* corTextoAleatoria();
char* corFundoAleatoria();

#endif