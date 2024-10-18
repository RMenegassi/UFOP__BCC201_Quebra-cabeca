//Roberto Menegassi 24.1.4002

#ifndef FNPRINTS_H
#define FNPRINTS_H

#include "../definicoes.h"
#include <stdio.h>

void printMenu(int jogoIniciado);
void printAjuda();
void printTabuleiro(int n, int qntMov, int **matriz, Peca peca0);

#endif