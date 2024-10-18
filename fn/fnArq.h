//Roberto Menegassi 24.1.4002

#ifndef FNARQ_H
#define FNAQR_H

#include "../definicoes.h"
#include <stdio.h>
#include <string.h>
#include "./fnMatriz.h"
#include "./fnTratamento.h"

Peca abrirArquivo(int *n, int* qntMov, int ***pMatriz, int *comando);
void salvar(int n, int qntMov, int **matriz, int *comando, char *nArquivo);

#endif