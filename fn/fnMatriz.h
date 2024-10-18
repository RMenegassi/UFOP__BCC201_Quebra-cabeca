//Roberto Menegassi 24.1.4002

#ifndef FNMATRIZ_H
#define FNMATRIZ_H

#include "../definicoes.h"
#include <stdlib.h>
#include <stdio.h>

int ** alocaMatrizQuad(int n);
void liberaMatriz(int n, int ** matriz);
void preencherTab(int n, int **matriz);



#endif