#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sistema_linear.h"





int main()
{
  SISTEMA_LINEAR_t *SL;

  /* Aloca Memória */
  SL = malloc(sizeof(SISTEMA_LINEAR_t));
  scanf("%d",&SL->n);
  SL->A = malloc (SL->n * sizeof (double*));
  for (int i = 0; i < SL->n; i++)
    SL->A[i] = malloc (SL->n * sizeof (double)) ;

  SL->b= malloc (SL->n * sizeof (double)) ;
  SL->x= malloc (SL->n * sizeof (double)) ;

  /* Trata Entrada */
  le_sistema_linear(SL->A,SL->b,SL->x,SL->n);
  imprime_sistema_linear(SL->A,SL->b,SL->x,SL->n);


  /* Libera Memória */
  for (int i = 0; i < SL->n; i++)
    free (SL->A[i]);
  free (SL->A) ;
  free(SL->b);
  free(SL->x);
  free(SL);

  return 0;
}