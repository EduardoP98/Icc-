#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sistema_linear.h"





int main()
{
  int mat_ordem;
  SISTEMA_LINEAR_t *SL;

  scanf("%d",&mat_ordem);
  /* Aloca Memória para um Sistema Linear */
  SL = aloca_sistema_linear(mat_ordem);
  
    /* Trata Entrada */
  le_sistema_linear(SL);

  /*
  - Passo 1 ElimGauss (Triangularizar Matriz)
    -Implementar ElimGauss Com pivoteamento Parcial
    -Implementar ElimGauss Com pivoteamento Total

  - Passo 2 Retrosubs
  - Passo 3 Resíduo
  
  */
  imprime_sistema_linear(SL);
  libera_sistema_linear(SL);
  return 0;
}