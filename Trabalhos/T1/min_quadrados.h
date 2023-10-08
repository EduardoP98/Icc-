/*
  Aunos: 
  Eduardo Purkote (GRR20182960)
  Mariana Moreira dos Santos (GRR20186554)
  
*/

#ifndef MIN_QUADRADOS_H_
#define MIN_QUADRADOS_H_
#include "tabela.h"
#include "sistema_linear.h"

//Calcula SL para a tabela de pontos
void minQuadrados(TABELA_t *tabela, int n,SISTEMA_LINEAR_t *SL);

//Imprime o Resultado na formatação de entrega
void imprime_sl_min(SISTEMA_LINEAR_t *SL);

#endif