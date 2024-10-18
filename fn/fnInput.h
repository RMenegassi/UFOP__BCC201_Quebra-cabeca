//Roberto Menegassi 24.1.4002

#ifndef FNINPUT_H
#define FNINPUT_H

#include "../definicoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "./fnTratamento.h"
#include "./fnArq.h"
#include "./fnPrints.h"

int getComando(int n, int qntMov, int jogoIniciado, int local, Peca *pecaMov, int **matriz);

#endif