#include "historia.h"
#include "../Cores/cores.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#ifdef _WIN32
    #include <windows.h>
    #define PAUSA(ms) Sleep(ms) 
#else
    #include <unistd.h>
    #define PAUSA(ms) usleep((ms)*1000)   
#endif

void printaMatrizHistoria(int m, int n, Sala matriz[m][n]) {
    printf("\n");
    for (int i = 0; i < m; i++) {
        printf("│ "); // Borda esquerda
        
        for (int j = 0; j < n; j++) {
            // Renderização customizada por elemento
            if (matriz[i][j].conteudo == '#') {
                // Imprime um bloco preenchido (espaço duplo com fundo colorido)
                aplicarCorFundo(FUNDO_VERDE);
                printf("  "); 
            } else if (matriz[i][j].conteudo == '&') {
                aplicarCorFundo(FUNDO_AMARELO);
                printf("  "); 
            }else if (matriz[i][j].conteudo == 'C') {
                printf("0 ");
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
        printf("\n");
    }
    printf("\n");
}

static bool verificaPosicaoEscolhida(int x, int y, int m, int n, Sala matriz[m][n], ListaCaminhos *caminhos, int numPassos){
    if(x >= 0 && x < m && y >= 0 && y < n && matriz[x][y].conteudo != '1'){
        NoCaminho* aux = caminhos -> inicio -> prox;
        while(aux != NULL){
            if(aux -> vetorCaminho[numPassos].x == x && aux -> vetorCaminho[numPassos].y == y){
                return true;
            }
            aux = aux -> prox;
        }
    }
    return false;
}

static void reiniciarVisitasLabirinto(int m, int n, Sala matriz[m][n]){
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            matriz[i][j].visitado = false;
        }
    }
}

void modoHistoriaInterativo(int m, int n, Sala matriz[m][n]){

    /*
    - imprime a história, com cores e tempo entre as falas.
    - sorteia a posição inicial de Teseu e verifica se existe pelo menos 1 caminho válido até a saída, considerando que não existe nenhuma chave. Se a posição não for válida, sorteia novamente.
    - gera e guarda todos os caminhos válidos até a saída.
    - imprime o Labirinto, indicando a posição inicial, e imprime uma legenda com instruções e regras para a gameplay.
    - para cada posição que o jogador escolher, verifica se é válida a partir da lista com todos os caminhos. Se for, imprime o labirinto atualizado. Se não, imprime um aviso de caminho inválido e diminui a quantidade de tentativas.
    - # é o caminho que Teseu já passou, & é a posição atual.
    */

    int TEMPO_PAUSA = 12000;
    aplicarCorTexto(TEXTO_AMARELO);

    printf("\nApós a morte trágica de seu filho em solo ateniense, o poderoso Rei Minos de Creta declarou\nguerra a Atenas e impôs um tributo devastador: a cada nove anos, sete rapazes e sete moças atenienses\ndeviam ser entregues para alimentar o Minotauro, uma fera brutal aprisionada nas profundezas do\nLabirinto, uma super estrutura repleta de salas.\n");
    PAUSA(TEMPO_PAUSA);

    printf("\nIndignado com a tirania de Creta, o jovem príncipe Teseu ofereceu-se como tributo, jurando\nlibertar seu povo. Ao desembarcar na ilha, sua coragem conquistou o coração da princesa Ariadne, filha\nde Minos. Sabendo que o Labirinto era uma sentença de morte, Ariadne traiu seu próprio pai:\nentregou a Teseu uma espada e um novelo de fio de ouro para guiar seus passos na escuridão.\n");
    PAUSA(TEMPO_PAUSA);

    printf("\nTeseu encontrou o Minotauro e, em uma batalha feroz, abateu a fera. Porém, os urros mortais\ndo monstro ecoaram por toda a ilha. Descobrindo a traição de sua filha e a queda do guardião de Creta,\no Rei Minos tomou-se de fúria. Determinado a impedir que Teseu saia vivo, o rei ordenou que seus\nsoldados marchassem para o Labirinto, tomando a entrada e espalhando guardas pelas galerias para\ncaçar o herói.\n");
    PAUSA(TEMPO_PAUSA);

    printf("\nDurante o combate brutal contra o Minotauro, o fio de ouro de Ariadne se rasgou e se perdeu na escuridão. Com as\npatrulhas de Minos se aproximando da entrada do Labirinto, Teseu não pode dar nenhum passo em\nfalso. Desorientado e sem margem para erros, o herói clama aos deuses por ajuda.\n");
    PAUSA(TEMPO_PAUSA);

    printf("\nVocê é a manifestação da vontade divina! Guie Teseu até a saída do Labirinto, antes que os\nsoldados de Minos o alcancem!\n");
    resetarCores();
    PAUSA(TEMPO_PAUSA / 2);
    
    aplicarCorTexto(TEXTO_MAGENTA);
    printf("\n- A sala atual de Teseu é marcada pela cor amarela, enquanto as salas já visitadas são marcadas pela cor verde.\n- Você deve guiar o herói dizendo uma das 4 direções (cima, baixo, esquerda ou direita) por vez.\n- Lembre-se: o herói não pode passar em uma sala do labirinto onde já esteve, pois há chances maiores dele se encontrar com os soldados!\n- Você tem 5 tentativas, no total, para adivinhar qual deverá ser a próxima sala que Teseu deve visitar, ou ele será alcançado pelos soldados.\n");
    resetarCores();
    aplicarCorFundo(FUNDO_MAGENTA);
    printf("\nAguarde alguns momentos enquanto o modo se inicia...");
    resetarCores();
    printf("\n");

    bool existeCaminho = false;
    int x, y;
    while(existeCaminho == false){
        x = rand() % m;
        y = rand() % n;
        if((matriz[x][y].conteudo == '0' || matriz[x][y].conteudo == 'C')){
            int temp1 = 0, temp2 = 0;
            Posicao posicoes[n*m];
            existeCaminho = escolheCaminho(x, y, m, n, matriz, 0, &temp1, posicoes, &temp2);
            reiniciarVisitasLabirinto(m, n, matriz);
        }
    }

    ListaCaminhos caminhos;
    inicializaCaminhos(&caminhos);
    int temp = 0, i = 0;
    Posicao posicoes[(m * n) + 1];
    encontraTodosCaminhos(x, y, m, n, matriz, 0, &temp, posicoes, &i, &caminhos);

    bool aindaPossuiTentativas = true;
    int numPassos = 1, tentativasRestantes = 5;
    while(matriz[x][y].conteudo != 'X' && aindaPossuiTentativas){
        matriz[x][y].conteudo = '&';
        printaMatrizHistoria(m, n, matriz);
        printf("Digite a direção (c, b, e, d): ");
        char direcao[3];
        scanf("%s", direcao);
        matriz[x][y].conteudo = '#';
        int tempX = x, tempY = y;
        if(strcmp(direcao, "c") == 0){
            tempX--;
        }
        else if(strcmp(direcao, "b") == 0){
            tempX++;
        }
        else if(strcmp(direcao, "e") == 0){
            tempY--;
        }
        else if(strcmp(direcao, "d") == 0){
            tempY++;
        }
        if(verificaPosicaoEscolhida(tempX, tempY, m, n, matriz, &caminhos, numPassos)){
            x = tempX;
            y = tempY;
            numPassos++;
        }
        else{
            tentativasRestantes--;
            aplicarCorTexto(TEXTO_VERMELHO);
            if(tentativasRestantes > 0){
                printf("Essa não é a posição correta! Você tem %d tentativas restantes, no total.\n", tentativasRestantes);
            }
            else{
                printf("\nVocê não conseguiu ajudar Teseu! Os inimigos alcançaram-no e ele morreu cruelmente.\n\n");
                aindaPossuiTentativas = false;
            }
            resetarCores();
        }
    }
    if(aindaPossuiTentativas){
        aplicarCorTexto(TEXTO_VERDE);
        printf("\nParabéns! Teseu está a salvo graças à você! Um novo templo será erguido em sua homenagem.\n\n");
        resetarCores();
    }
    liberaCaminhos(&caminhos);
}