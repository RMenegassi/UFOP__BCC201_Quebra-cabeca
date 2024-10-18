//Roberto Menegassi 24.1.4002

#include "./fnInput.h"

int getComando(int n, int qntMov, int jogoIniciado, int local, Peca *pecaMov, int **matriz){
    char comando[64];
    char nArquivo[TAMSTRINGARQ];
    int opcao = 404;

    printf("Digite o comando: ");

    int len = tratamentoComando(comando, nArquivo);

    if (strcmp(comando, "salvar") == 0 && len > 0 && jogoIniciado != 0){
        salvar(n, qntMov, matriz, &opcao, nArquivo);
        if(local == 0){
            printMenu(jogoIniciado);
        }
        // Se der erro no salvar, a opção será 0, fechando o jogo
        return opcao;
    }

    int isNum = 1;

    if (len == 0){
        isNum = 0;
        printf("Você não digitou um comando!\n");
        return 404;
    }

    for (int i = 0; i < len; i++){
        if(isdigit(comando[i]) == 0){
            isNum = 0;
            break;
        }
    } 

    char *opcoesGerais[QNTOPCMENU] = {"x", "n", "c","s","a","voltar"};
    int contemOpcao = 0;

    if (isNum == 0){
        for (int i = 0; i < QNTOPCMENU; i++){
            if(strcmp(opcoesGerais[i], comando) == 0 ){
                contemOpcao = 1;
            }
        }
    }

    if (contemOpcao == 0 && isNum == 0){
        printf("Comando inválido!\n");
        return 404;
    }

    switch(local){
        case 0:
            if(strcmp(comando,"voltar") == 0){
                printf("Local de comando inválido! Você ja está no menu. No momento você deve escolher uma opção do menu ou salvar\n");
                return 404;
            }

            if(isNum != 0){
                printf("Local de comando inválido! Você está no menu. Volte ao jogo para movimentar ou selecione uma opção do menu\n");
                return 404;
            }
            break;
        case 1:
            if(strcmp(comando, "x") == 0 || strcmp(comando, "n") == 0 || strcmp(comando, "c") == 0 || strcmp(comando, "s") == 0 || strcmp(comando, "a") == 0){
                printf("Local de comando inválido! Volte ao menu para poder realizar a ação ou informe outro comando\n");
                return 404;
            }
            break;
    }

    if (isNum == 0){
        for (int i = 0; i < QNTOPCMENU; i++){
            if(strcmp(comando, opcoesGerais[i]) == 0){
                return i;
            }
        }
    }

    int valor = atoi(comando);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (matriz[i][j] == valor){
                (*pecaMov).valor = matriz[i][j];
                (*pecaMov).linha = i;
                (*pecaMov).coluna = j;
                return 7;
            }
        }
    }

    if (isNum == 1){
        printf("Peça inválida. Digite outra\n");
        return 404;
    }

    printf("Comando inválido\n");
    return 404;
}
