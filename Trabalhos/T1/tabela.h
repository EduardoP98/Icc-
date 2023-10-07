#include "interval.h"

#ifndef  TABELA_H
#define  TABELA_H

typedef struct {
  INTERVAL_t *x;
  INTERVAL_t *y;
  int k;
} TABELA_t;

// Alocacao de memoria
TABELA_t *aloca_tabela (int k);

// Libera memoria utilizada
void libera_tabela (TABELA_t *tabela);

// Le tabela de pontos
void le_tabela (TABELA_t *tabela);

// Imprime tabela de pontos 
void imprime_tabela (TABELA_t *tabela);

#endif