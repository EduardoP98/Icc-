#include <stdio.h>
#include <math.h>
#include "min_quadrados.h"

void minQuadrados(TABELA_t *tabela, int n, SISTEMA_LINEAR_t *SL)
{
  // Inicializar a matriz A e o vetor b
  for (int i = 0; i <= n; i++)
  {
    for (int j = 0; j <= n; j++)
    {
      INTERVAL_t soma;
      soma.m.f = 0.0;
      soma.M.f = 0.0;
      for (int k = 0; k < tabela->k; k++)
      {
        INTERVAL_t termo1 = calcula_pot(tabela->x[k], i);
        INTERVAL_t termo2 = calcula_pot(tabela->x[k], j);
        INTERVAL_t produto = calcula_mult(termo1, termo2);
        soma = calcula_soma(soma, produto);
      }
      SL->A[i][j] = soma;
    }

    INTERVAL_t soma_b;
    soma_b.m.f = 0.0;
    soma_b.M.f = 0.0;
    for (int k = 0; k < tabela->k; k++)
    {
      INTERVAL_t termo1 = calcula_pot(tabela->x[k], i);
      INTERVAL_t produto = calcula_mult(termo1, tabela->y[k]);
      soma_b = calcula_soma(soma_b, produto);
    }
    SL->b[i] = soma_b;
  }
}
