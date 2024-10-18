//Roberto Menegassi 24.1.4002

#include "./fnJogo.h"

Peca novoJogo(int *n, int ***pMatriz, int *comando){

    do{
        printf("Digite a dimensão do tabuleiro (3 ≤ n ≤ 10): ");

        if(tratamentoInt(n) == 0){
            continue;
        };

        if (*n < 3 || *n > 10){
            printf("O intervalo é 3 <= n <= 10\n");
        }
        
    }while((*n < 3 || *n > 10));
    
    // Posicação do valor 0
    Peca peca0 = {0, *n - 1 , *n - 1};

    *pMatriz = alocaMatrizQuad(*n);

    // Caso: Erro ao alocar matriz
    if (*pMatriz == NULL){
        *comando = 0;
        return peca0;
    }
    
    preencherTab(*n, *pMatriz);

    printTabuleiro(*n, 0, *pMatriz, peca0);

    printf("Tabuleiro Ordenado!\n");

    char cNivel;
    int nivel = 0;
    int nivelControl = 0;
    do{
        printf("Digite o nı́vel de dificuldade para embaralhar, fácil (F), médio (M) ou difı́cil (D): ");

        if(tratamentoChar(&cNivel) == 0){
            continue;
        }
        
        char nivelOpcoes[QNTOPCNIVEL] = {'f', 'm', 'd'};

        for (int i = 0; i < QNTOPCNIVEL; i++){
            if (cNivel == nivelOpcoes[i]){
                nivel = 1 + i;
                nivelControl = 1;
                break;
            }
        }

        if (nivelControl == 0){
            printf("Comando inválido!\n");
        }

    }while(nivelControl == 0);


    return embaralhar(*n, nivel, *pMatriz);
}

//##############################################################################################

Peca embaralhar(int n, int nivel, int **matriz){
    int qntTotalMov = 0, qntMovPermitida = 0;
    Peca aux = {-1,-1,-1};
    Peca peca0 = {0, n - 1, n - 1};

    Peca pecasAdj[3];

    // Utiliza de truncamento para que o resultado do nivel 1 = 1*(5 * n) \\ nivel 2 = 2*(5 * n) \\ nivel 3 = 4*(5 * n)
    qntTotalMov = (5 * n) * (int) (nivel / 0.75);

    for (int i = qntTotalMov; i > 0; i--){
        qntMovPermitida = 0;

        // Guardar peças adjacentes que podem ser movidas, excluindo a última movida

        if (peca0.linha - 1 >= 0){
            if(matriz[peca0.linha - 1][peca0.coluna] != aux.valor){
                pecasAdj[qntMovPermitida].valor = matriz[peca0.linha - 1][peca0.coluna];
                pecasAdj[qntMovPermitida].linha = peca0.linha - 1;
                pecasAdj[qntMovPermitida].coluna = peca0.coluna;
                qntMovPermitida++;
            }
        }

        if (peca0.linha + 1 <= n - 1){
            if(matriz[peca0.linha + 1][peca0.coluna] != aux.valor){
                pecasAdj[qntMovPermitida].valor = matriz[peca0.linha + 1][peca0.coluna];
                pecasAdj[qntMovPermitida].linha = peca0.linha + 1;
                pecasAdj[qntMovPermitida].coluna = peca0.coluna;
                qntMovPermitida++;
            }
        }   

        if (peca0.coluna - 1 >= 0){
            if(matriz[peca0.linha][peca0.coluna - 1] != aux.valor){
                pecasAdj[qntMovPermitida].valor = matriz[peca0.linha][peca0.coluna - 1];
                pecasAdj[qntMovPermitida].linha = peca0.linha;
                pecasAdj[qntMovPermitida].coluna = peca0.coluna - 1;
                qntMovPermitida++;
            }
        }

        if (peca0.coluna + 1 <= n - 1){
            if(matriz[peca0.linha][peca0.coluna + 1] != aux.valor){
                pecasAdj[qntMovPermitida].valor = matriz[peca0.linha][peca0.coluna + 1];
                pecasAdj[qntMovPermitida].linha = peca0.linha;
                pecasAdj[qntMovPermitida].coluna = peca0.coluna + 1;
                qntMovPermitida++;
            }
        }

        aux = pecasAdj[rand() % qntMovPermitida];

        peca0 = movimentarTabuleiro(peca0, aux, matriz);

    }

    return peca0;
}

//##############################################################################################

Peca movimentarTabuleiro(Peca peca0, Peca pecaMov, int **matriz){

    Peca aux = pecaMov;

    matriz[pecaMov.linha][pecaMov.coluna] = peca0.valor;

    matriz[peca0.linha][peca0.coluna] = aux.valor;

    pecaMov.valor = 0;
    
    return pecaMov;
}

//##############################################################################################

// Confere se a peça seleciona é uma adjacente a peça 0
int confereAdj(Peca peca0, Peca pecaMov){
    int linhaPMov = pecaMov.linha, colunaPMov = pecaMov.coluna;
    int linhaP0 = peca0.linha, colunaP0 = peca0.coluna;

    int linhasAdj = (linhaPMov == linhaP0 - 1 && colunaPMov == colunaP0) || (linhaPMov == linhaP0 + 1 && colunaPMov == colunaP0);
    int colunasAdj =  (linhaPMov == linhaP0 && colunaPMov == colunaP0 - 1) || (linhaPMov == linhaP0 && colunaPMov == colunaP0 + 1);

    if (!(linhasAdj || colunasAdj)){
        printf("A peça selecionada não é adjacente! Selecione outra.\n");
        return 0;
    }

    return 1;
}

//##############################################################################################

void ganhou(int n, int **matriz, int* comando){
    int totalPecas = n * n;

    // Confere se os valores estão em ordem, do 1 até o n*n - 1
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n && (i*n + j) < totalPecas - 1; j++ ){
            if(matriz[i][j] != (i*n + j + 1)){
                return;
            }
        }
    }
    
    printf("Tabuleiro está ordenado!\n");

    liberaMatriz(n, matriz);

    *comando = 0;
}

//##############################################################################################

int desejaSalvar(){
    char decisao;

    while(1){
        printf("Deseja salvar o jogo atual? (S/N) ");

        if(tratamentoChar(&decisao) == 0){
            continue;
        }

        if (decisao == 'n'){
            return 0;
        }

        if (decisao == 's'){
            return 1;
        }

        printf("Comando Inválido\n");
    }
}

//##############################################################################################

void salvarOpcional(int n, int qntMov, int **matriz, int *comando){
    if(desejaSalvar() != 0){
        salvar(n, qntMov, matriz, comando, NULL);
        liberaMatriz(n, matriz);
        return;
    }
    liberaMatriz(n, matriz);
}

//##############################################################################################