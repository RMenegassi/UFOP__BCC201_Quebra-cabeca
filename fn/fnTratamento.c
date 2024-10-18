//Roberto Menegassi 24.1.4002

#include "./fnTratamento.h"

int removeBN(char *string){
    int len = strlen(string);

    if (string[len - 1] =='\n'){
        string[len - 1] = '\0';
        return len - 1;
    }else{
        limparBuffer();
        return len;
    }
}

//##############################################################################################

void limparBuffer() {
    int buffer = getchar();
    while (buffer != '\n' && buffer != EOF) {
        buffer = getchar();
    }
}

//##############################################################################################

int tratamentoChar(char *cVar){
    char c[8];

    fgets(c, 8, stdin);

    int len = strlen(c);
    if (len != 2){
        printf("Comando inválido\n");
        if (c[len - 1] != '\n'){    
            limparBuffer();
        }
        return 0;
    }

    *cVar = tolower(c[0]);
    return 1;
}

//##############################################################################################

int tratamentoComando(char *string, char *nArquivo){
    char comString[64];
    char comPrincipal[8];

    fgets(comString, 64, stdin);

    int len = strlen(comString);

    if (comString[len - 1] == '\n'){
        comString[len - 1] = '\0';
        len = len - 1;
    }else{
        limparBuffer();
    }

    // Caso houver, adicionar o 1º comando separado por espaço à variavel comPrincipal
    for (int i = 0; i < 8; i++){
        if(comString[i] == ' '){
            comPrincipal[i] = '\0';
            break;
        }
        comPrincipal[i] = tolower(comString[i]);
    }
    comPrincipal[7] = '\0';

    // Caso o comPrincipal seja 'salvar', separa todo texto após o espaço à variável nArquivo (nome do arquivo)
    if(strcmp(comPrincipal, "salvar") == 0){
        for(int i = 0; i < TAMSTRINGARQ; i++){
            if(comString[i + 7] == '\0'){
                nArquivo[i] = '\0';
                break;
            }
            nArquivo[i] = comString[i + 7];
        }
        strcpy(string, comPrincipal);
        return strlen(nArquivo);
    }

    for (int i = 0; i < len + 1; i++){
        string[i] = tolower(comString[i]);
    }

    return len;
}

//##############################################################################################

int tratamentoInt(int *varInt){
    char numeroStr[4];

    fgets(numeroStr, 4, stdin);

    int len = removeBN(numeroStr);

    if (len == 0){
        return 0;
    }

    for (int i = 0; i < len; i++){
        if (isdigit(numeroStr[i]) == 0){
            printf("Comando Inválido!\n");
            return 0;
        }
    }

    *varInt = atoi(numeroStr);
    return 1;
}

//##############################################################################################

int tratamentoNomeArq(char *string){
    char nomeArq[TAMSTRINGARQ];

    fgets(nomeArq, TAMSTRINGARQ, stdin);

    int len = strlen(nomeArq);

    if (nomeArq[len - 1] == '\n'){
        nomeArq[len - 1] = '\0';
        len = len - 1;
    }else{
        limparBuffer();
    }

    for (int i = 0; i < len + 1; i++){
        if(nomeArq[i] == ' '){
            string[i] = '_';
        }else{
            string[i] = nomeArq[i];
        }
    }

    return len;
}

//##############################################################################################