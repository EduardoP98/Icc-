/*
  Alunos: 
  Eduardo Purkote (GRR20182960)
  Mariana Moreira dos Santos (GRR20186554)
*/

#include "interval.h"
#ifndef  TABELA_H
#define  TABELA_H

/*  
  Estrutura de dados utilizada para armazenar a tabela de pontos de entrada

  (x, y): pontos 
  k: quantidade de pontos da tabela 

*/
typedef struct {
  INTERVAL_t *x;
  INTERVAL_t *y;
  long long int k;
} TABELA_t;

// Le tabela de pontos
void le_tabela (TABELA_t *tabela);

// Imprime tabela de pontos 
void imprime_tabela(TABELA_t *tabela, long long int N);

// Alocacao de memoria
TABELA_t *aloca_tabela (long long int k);

// Libera memoria utilizada
void libera_tabela (TABELA_t *tabela);



#endif