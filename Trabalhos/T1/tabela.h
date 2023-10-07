#include "interval.h"

#ifndef  TABELA_H
#define  TABELA_H

typedef struct
{
  INTERVAL_t *x;
  INTERVAL_t *y;
  int k;

}TABELA_t;


TABELA_t *aloca_tabela(int k);

void libera_tabela(TABELA_t *tabela);

//Função que le tabela de pontos
void le_tabela (TABELA_t *tabela);

//Função que imprime tabela de pontos 
void imprime_tabela(TABELA_t *tabela);

#endif