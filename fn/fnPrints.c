//Roberto Menegassi 24.1.4002

#include "./fnPrints.h"

// #######################################################################################
// Definições de macros para desenho do tabuleiro e colorir chars

#define TAB_HOR "\u2501" // ━ (horizontal)
#define TAB_VER "\u2503" // ┃ (vertical)
#define TAB_TL  "\u250F" // ┏ (top-left)
#define TAB_ML  "\u2523" // ┣ (middle-left)
#define TAB_BL  "\u2517" // ┗ (bottom-left)
#define TAB_TJ  "\u2533" // ┳ (top-join)
#define TAB_MJ  "\u254B" // ╋ (middle-join)
#define TAB_BJ  "\u253B" // ┻ (bottom-join)
#define TAB_TR  "\u2513" // ┓ (top-right)
#define TAB_MR  "\u252B" // ┫ (middle-right)
#define TAB_BR  "\u251B" // ┛ (bottom-right)

#define ANSI_RESET            "\x1b[0m" 
#define ANSI_COLOR_GREEN      "\x1b[32m"
#define ANSI_COLOR_BLACK      "\x1b[30m"

#define GREEN(string)      ANSI_COLOR_GREEN      string ANSI_RESET
#define BLACK(string)      ANSI_COLOR_BLACK      string ANSI_RESET

// #######################################################################################

void printMenu(int jogoIniciado){
    if(jogoIniciado == 0){
            printf("\nBem vindo ao Quebra-Cabeças\n");
    }
    printf("\nMenu Principal>\n\n");
    printf("X. Sair do jogo\n");
    printf("N. Iniciar um novo jogo\n");
    if(jogoIniciado != 0){
            printf("C. Continuar o jogo atual\n");
    }
    else{
            printf(BLACK("C. Continuar o jogo atual") "\n");
    }
    printf("S. Continuar um jogo salvo\n");
    printf("A. Ajuda com as instruções do jogo\n\n");

}

// #######################################################################################

void printAjuda(){
    int tabExemplo1[3][3] = { {1, 2, 3}, {4, 0, 5}, {7, 8, 6}};
    Peca peca0 = {0, 1, 1};
    int *matrizEx[3];

    for (int i = 0; i < 3; i++){
        matrizEx[i] = tabExemplo1[i];
    }

    printf("\nO jogo é um simples quebra-cabeças de pastilha\n");
    printf("Seu objetivo é: Após embaralhado, reordenar todo as pastilhas em ordem crescente\n");
    printf("Para isso, o jogador só pode movimentar as peças adjacentes ao quadrado vazio\n");
    printf("Entenda como adjacente, as peças que compartilharem arestas com a peça vazia\n");
    printTabuleiro(3, 2, matrizEx, peca0);
    printf("Nesse tabuleiro de exemplo, é possível observar que as peças verdes são as adjacentes\n");
    printf("Você só pode moder essas peças verdes, 1 por rodada");

    printf("Para movê-las, basta digitar o valor da peça desejada. Lembre-se que esse comando só pode ser usado na tela do tabuleiro.\n");
    printf("Além desse comando, estão disponíveis os comandos: voltar e salvar.\n");
    printf("O comando 'voltar' te leva de volta a tela do menu principal. Esse comando só pode ser utilizado na tela do tabuleiro.\n");
    printf("O comando 'salvar' segue a seguinte configuração: salvar [nomedo arquivo]. Ex: salvar jogo.txt\n");

    printf("No menu principal, o comando X (sair) pode ser utilizado a qualquer momento\n");
    printf("O comando N (iniciar) também pode ser utilizado a qualquer commento\n");
    printf("Já o comando C (continuar) necessita de ter um jogo ja iniciado para ser utilizado");
    printf("Os comandos S (jogo salvo) e A (ajuda) podem ser utilizados a qualquer momento no menu principal\n");

}

// #######################################################################################

void printTabuleiro(int n, int qntMov, int **matriz, Peca peca0){
    int nDigitosMax = 0, aux = (n * n) - 1;

    // Obtém número de digitos do maior número do tabuleiro;
    while (aux > 0){
        aux = aux / 10;
        nDigitosMax++;
    }
    
    printf("\n\n");

    printf(TAB_TL);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < nDigitosMax + 2; j++){
        printf(TAB_HOR);
        }
        if(i != n - 1){
            printf(TAB_TJ);
        }
    }
    printf(TAB_TR);

    printf("\n");
    
    for (int i = 0; i < n; i++){
        printf(TAB_VER);

        for (int j = 0; j < n; j++){
            int linha = i;
            int coluna = j;
            int dAux = 0;
            int valor = matriz[i][j];

            // Obtém número de dígitos do valor atual
            while(valor > 0){
                valor = valor / 10;
                dAux++;
            }

            // Adiciona a diferença do maior numero de digitos pelo numero atual + 1 de espaços
            // N digitos iguais -> 1 espaço na esquerda
            // N digitos menor -> Adiciona mais espaços na esquerda para alinhar na direita
            for(int k = 0; k < nDigitosMax - dAux + 1; k++){
                printf(" ");
            }

            if(linha == peca0.linha - 1 && coluna == peca0.coluna){
                printf(GREEN("%d ") TAB_VER, matriz[i][j]);
                continue;
            }

            if(linha == peca0.linha + 1 && coluna == peca0.coluna){
                printf(GREEN("%d ") TAB_VER, matriz[i][j]);
                continue;
            }

            if(linha == peca0.linha && coluna == peca0.coluna - 1){
                printf(GREEN("%d ") TAB_VER, matriz[i][j]);
                continue;
            }

            if(linha == peca0.linha  && coluna == peca0.coluna + 1){
                printf(GREEN("%d ") TAB_VER, matriz[i][j]);
                continue;
            }

            if (linha == peca0.linha && coluna == peca0.coluna){
                printf(" " TAB_VER);
                continue;
            }

            printf("%d ", matriz[i][j]);
            printf(TAB_VER);
        }
        printf("\n");

        if(i != n - 1){
            printf(TAB_ML);
            for(int j = 0; j < n; j++){
                for (int k = 0; k < nDigitosMax + 2; k++){
                    printf(TAB_HOR);
                }
                if (j != n - 1){
                    printf(TAB_MJ);
                }
            }
            printf(TAB_MR);
            printf("\n");
        }
    }

    printf(TAB_BL);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < nDigitosMax + 2; j++){
            printf(TAB_HOR);
        }
        if(i != n - 1){
            printf(TAB_BJ);
        }
    }
    printf(TAB_BR);

    printf("\n\n");
    printf("Quantidade de jogadas até agora: %d!\n\n", qntMov);
}