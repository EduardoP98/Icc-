#ifndef MIN_QUADRADOS_H_
#define MIN_QUADRADOS_H_
#include "tabela.h"
#include "sistema_linear.h"

//Calcula SL para a tabela de pontos
void minQuadrados(TABELA_t *tabela, int n,SISTEMA_LINEAR_t *SL);

//Imprime o Resultado na formatação de entrega
void imprime_sl_min(SISTEMA_LINEAR_t *SL);

#endif