/*
  Aunos: 
  Eduardo Purkote (GRR20182960)
  Mariana Moreira dos Santos (GRR20186554)
  
*/

#include <stdio.h>
#include <math.h>
#include "min_quadrados.h"

void minQuadrados(TABELA_t *tabela, int n, SISTEMA_LINEAR_t *SL) {

  int k;

  // Para cada elemento da matriz A e do vetor B
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= n; j++) {
      // Ira guardar o valor final da soma dos produtos dos valores de x elevados as potencias i + j
      INTERVAL_t soma;
      soma.m.f = 0.0;
      soma.M.f = 0.0;

      for (k = 0; k < tabela->k; k++) {
        INTERVAL_t termo1 = calcula_pot(tabela->x[k], i+j);
        soma = calcula_soma(soma, termo1);
      }
      SL->A[i][j] = soma;
    }

    // Vetor B
    INTERVAL_t soma_b;
    soma_b.m.f = 0.0;
    soma_b.M.f = 0.0;

    for (int k = 0; k < tabela->k; k++) {
      INTERVAL_t termo1 = calcula_pot(tabela->x[k], i);
      INTERVAL_t produto = calcula_mult(termo1, tabela->y[k]);
      soma_b = calcula_soma(soma_b, produto);
    }
    SL->b[i] = soma_b;
  }
}
