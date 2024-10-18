//Roberto Menegassi 24.1.4002

#ifndef FNTRATAMENTO_H
#define FNTRATAMENTO_H

#include "../definicoes.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void limparBuffer();
int removeBN(char *string);
int tratamentoChar(char *cVar);
int tratamentoComando(char *string, char *nArquivo);
int tratamentoNomeArq(char *string);
int tratamentoInt(int *varInt);

#endif