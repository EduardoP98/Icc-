/*
  Alunos: 
  Eduardo Purkote (GRR20182960)
  Mariana Moreira dos Santos (GRR20186554)
*/

#ifndef MIN_QUADRADOS_H_
#define MIN_QUADRADOS_H_
#include "tabela.h"
#include "sistema_linear.h"

// Implementacao do Metodo dos Minimos Quadrados 
void min_quadrados(TABELA_t *tabela, long long int n,SISTEMA_LINEAR_t *SL);

void min_quadrados_otimizado(TABELA_t *tabela, long long int n, SISTEMA_LINEAR_t *SL);

void preencher_tabela_potencias(INTERVAL_t base, long long int n, INTERVAL_t *tabela_potencias);

#endif