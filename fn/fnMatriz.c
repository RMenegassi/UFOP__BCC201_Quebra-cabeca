//Roberto Menegassi 24.1.4002

#include "./fnMatriz.h"

int ** alocaMatrizQuad(int n){
    int ** matriz = NULL;

    matriz = malloc(n * sizeof(int *));

    if(matriz == NULL){
        printf("Falha na alocação de memória\nSaindo do jogo\n");
        return NULL;
    }

    for (int i = 0; i < n; i++){

        matriz[i] = malloc(n * sizeof(int));

        if(matriz[i] == NULL){
            printf("Falha na alocação de memória\nSaindo do jogo\n");
            liberaMatriz(n, matriz);
            return NULL;
        }
    }

    return matriz;
}

//##############################################################################################

void liberaMatriz(int n, int ** matriz){
    for (int i = 0; i < n; i++){
        if(matriz[i] != NULL){
            free(matriz[i]);
        }
    }
    if (matriz != NULL){
        free(matriz);
    }
}

//##############################################################################################

void preencherTab(int n, int **matriz){
    int valor = 1;

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            matriz[i][j] = valor;
            valor++;
        }
    }
    matriz[n - 1][n - 1] = 0;

}

//##############################################################################################