//Roberto Menegassi 24.1.4002

#include "./fnArq.h"

Peca abrirArquivo(int *n, int* qntMov, int ***pMatriz, int *comando){
    char nomeArq[TAMSTRINGARQ];
    Peca peca0 = {0, 0, 0};
    char decisao;

    printf("Digite o nome do arquivo a ser aberto: ");
    tratamentoNomeArq(nomeArq);

    FILE *arq = fopen(nomeArq, "r");

    if (arq == NULL){
        printf("Erro ao abrir o arquivo\n");
    }

    while(arq == NULL){

        printf("Deseja tentar abrir outro arquivo? (S/N) ");
        if(tratamentoChar(&decisao) == 0){
            continue;
        }

        if (decisao == 's'){
            printf("Digite o nome de um arquivo existente: ");
            tratamentoNomeArq(nomeArq);
        }

        if (decisao == 'n'){
            printf("Saindo do programa\n");
            *comando = 0;
            return peca0;
        }

        arq = fopen(nomeArq,"r");
        if (arq == NULL){
            printf("Erro ao abrir o arquivo\n");
        }
    }

    if (fscanf(arq, "%d", n) != 1){
        printf("Erro ao ler o arquivo\nSaindo do programa\n");
        *comando = 0;
        return peca0;
    }
    
    *pMatriz = alocaMatrizQuad(*n);

    if(*pMatriz == NULL){
        printf("Erro ao alocar memória para matriz\n");
        *comando = 0;
        return peca0;
    }
    
    char barra = fgetc(arq);
    if(barra != '\n'){
        printf("Erro ao ler o arquivo\nSaindo do programa\n");
        *comando = 0;
        liberaMatriz(*n, *pMatriz);
        return peca0;
    }

    // Lendo arquivo e preenchendo na matriz na main()
    for (int i = 0; i < *n; i++){
        for (int j = 0; j < *n; j++){
            char buffer;
            if(fscanf(arq, "%d%c", &(*pMatriz)[i][j], &buffer) != 2){
                printf("Erro ao ler o arquivo\nSaindo do programa\n");
                liberaMatriz(*n,*pMatriz);
                *comando = 0;
                return peca0;
            }
            if((*pMatriz)[i][j] == 0){
                peca0.valor = (*pMatriz)[i][j];
                peca0.linha = i;
                peca0.coluna = j;
            }
        }
    }

    if(fscanf(arq, "%d", qntMov) != 1){
        printf("Erro ao ler o arquivo\nSaindo do programa\n");
        liberaMatriz(*n, *pMatriz);
        *comando = 0;
        return peca0;
    }


    if(fclose(arq) != 0){
        printf("Erro ao fechar o arquivo\nSaindo do programa\n");
        liberaMatriz(*n, *pMatriz);
        *comando = 0;
        return peca0;
    }

    return peca0;
}

//##############################################################################################

void salvar(int n, int qntMov, int **matriz, int *comando, char * nArquivo){
    char nomeArq[TAMSTRINGARQ];

    if(nArquivo != NULL){
        strcpy(nomeArq, nArquivo);
    }else{
        printf("Digite nome do arquivo para salvar: ");
        while(tratamentoNomeArq(nomeArq) == 0){
            printf("Nome inválido! Digite o nome do arquivo: ");
        }
    }

    FILE *arq = fopen(nomeArq, "w");

    if (arq == NULL){
        printf("Erro ao abrir o arquivo para salvar\nSaindo do jogo\n");
        liberaMatriz(n, matriz);
        *comando = 0;
        return;
    }

    if(fprintf(arq, "%d\n", n) <= 0){
        printf("Erro ao salvar os dados do jogo no arquivo\nSaindo do jogo\n");
        liberaMatriz(n, matriz);
        *comando = 0;
        return;
    }
    
    for (int i = 0; i < n; i ++){
        for(int j = 0; j < n - 1; j++){
            if(fprintf(arq, "%d ", matriz[i][j]) <= 0){
                printf("Erro ao salvar os dados do jogo no arquivo\nSaindo do jogo\n");
                liberaMatriz(n, matriz);
                *comando = 0;
                return;
            }
        }
        if (fprintf(arq, "%d\n", matriz[i][n - 1]) <= 0){
            printf("Erro ao salvar os dados do jogo no arquivo\nSaindo do jogo\n");
            liberaMatriz(n, matriz);
            *comando = 0;
            return;
        }
    }

    if (fprintf(arq, "%d", qntMov) <= 0){
        printf("Erro ao salvar os dados do jogo no arquivo\nSaindo do jogo");
        liberaMatriz(n, matriz);
        *comando = 0;
        return;
    }

    if(fclose(arq) != 0){
        printf("Erro ao fechar o arquivo\n");
        liberaMatriz(n, matriz);
        *comando = 0;
        return;
    }

    printf("Jogo salvo!\n");
}