//Roberto Menegassi 24.1.4002

#ifndef FNJOGO_H
#define FNJOGO_H

#include "../definicoes.h"
#include <stdio.h>
#include <stdlib.h>
#include "./fnMatriz.h"
#include "./fnArq.h"
#include "./fnTratamento.h"
#include "./fnPrints.h"

Peca novoJogo(int *n, int ***pMatriz, int *comando);
Peca embaralhar(int n, int nivel, int **matriz);
Peca movimentarTabuleiro(Peca peca0, Peca pecaMov, int **matriz);
void ganhou(int n, int **matriz, int* comando);
int confereAdj(Peca peca0, Peca pecaMov);
int desejaSalvar();
void salvarOpcional(int n, int qntMov, int **matriz, int *comando);


#endif