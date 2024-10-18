//Roberto Menegassi 24.1.4002

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./definicoes.h"
#include "./fn/fnPrints.h"
#include "./fn/fnJogo.h"
#include "./fn/fnArq.h"
#include "./fn/fnInput.h"

int main(){
    // local 0 -> Menu, local 1 -> tabuleiro
    int qntMov = 0, comando = 0, n = 0,jogoIniciado = 0, local = 0;
    int **tabuleiro = NULL;
    Peca peca0, pecaMov;

    srand(time(NULL));

    printMenu(jogoIniciado);

    do{
        comando = getComando(n, qntMov, jogoIniciado, local, &pecaMov, tabuleiro);

        switch(comando){
            case 1:
                // Iniciar novo jogo com jogo ja iniciado ( Decisão de salvar ou não o atual )
                if(jogoIniciado != 0){
                    salvarOpcional(n, qntMov, tabuleiro, &comando);
                    n = 0;
                    qntMov = 0;
                }
                // Caso: Erro ao salvar
                if (comando == 0){
                    break;
                }
 
                peca0 = novoJogo(&n, &tabuleiro, &comando);

                // Caso: Erro ao separar memória (malloc)
                if(comando != 0){
                    jogoIniciado = 1;
                    printTabuleiro(n, qntMov, tabuleiro, peca0);
                    local = 1;
                }
                break;
            case 2:
                // Continuar jogo apenas se existir jogo
                if(jogoIniciado != 0){
                    printTabuleiro(n, qntMov, tabuleiro, peca0);
                    local = 1;
                    ganhou(n, tabuleiro, &comando); 
                }else{
                    printf("Inicie ou continue um jogo salvo antes.\n");
                }
                break;
            case 3:
                // Abrir arquivo com jogo ja iniciado ( Decisão de salvar ou não o atual )
                if(jogoIniciado != 0){
                    salvarOpcional(n, qntMov, tabuleiro, &comando);
                }
                peca0 = abrirArquivo(&n, &qntMov, &tabuleiro, &comando);
                // Caso: Erro ao abrir arquivo
                if(comando != 0){
                    printTabuleiro(n, qntMov, tabuleiro, peca0);
                    jogoIniciado = 1;
                    local = 1;
                    ganhou(n, tabuleiro, &comando);
                }
                break;
            case 4:
                printAjuda();
                printMenu(jogoIniciado);
                break;
            case 5:
                local = 0;
                printMenu(jogoIniciado);
                break;
            case 6:
                // Salvar pelo menu
                salvar(n, qntMov, tabuleiro, &comando, NULL);
                break;
            case 7:
                // Movimenta apenas se peça adjacente
                if(confereAdj(peca0, pecaMov) != 0){
                    peca0 = movimentarTabuleiro(peca0, pecaMov, tabuleiro);
                    qntMov++;
                    printTabuleiro(n, qntMov, tabuleiro, peca0);
                    ganhou(n, tabuleiro, &comando);
                }
                break;
            case 0:
                // Sair com jogo ja iniciado ( Decisão de salvar ou não )
                if(jogoIniciado != 0){
                    salvarOpcional(n, qntMov, tabuleiro, &comando);
                }
                break;
        }

    }while(comando != 0);

    return 0;
}