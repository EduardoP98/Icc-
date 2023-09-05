#include "sistema_linear.h"
#include <stdlib.h>
#include <stdio.h>


void le_sistema_linear(SISTEMA_LINEAR_t *SL)
{
  int cont = 0;
  for(int i = 0; i < SL->n; ++i)
  {
    for(int j = 0; j < SL->n; ++j)
    {
      scanf("%lf",&SL->A[i][j]);
      
    }

    scanf("%lf",&SL->b[cont]);
    cont ++;
  }
  
    
}

void imprime_sistema_linear(SISTEMA_LINEAR_t *SL)
{

    printf("ORDEM DO SISTEMA LINEAR: %d\n\n",SL->n);
    printf("****************************************\n");
    printf("**             Matriz A               **\n");
    printf("****************************************\n");

    for(int i = 0; i < SL->n; ++i)
    {
      for(int j = 0; j < SL->n; ++j)
        printf("%f  ",SL->A[i][j]);
      printf("\n\n");
    }

    printf("****************************************\n");
    printf("**             Vetor b                **\n");
    printf("****************************************\n");

    for(int i = 0; i < SL->n; ++i)
        printf("%f  ",SL->b[i]);
    printf("\n\n");


    printf("****************************************\n");
    printf("**             Vetor x                **\n");
    printf("****************************************\n");

    for(int i = 0; i < SL->n; ++i)
        printf("%f  ",SL->x[i]);
    printf("\n\n");
}


//Função que resolve um Sistema triangular por retrosubs
void retrosubs(double **A,double *b,double *x, int n)
{
  for(int i = n-1; i >= 0; --i)
  {
    x[i] = b[i];
    for(int j = i+1; j < n; ++j)
      x[i] -= A[i][j] * x[j];
    x[i] /= A[i][i];
  }
}


void libera_sistema_linear(SISTEMA_LINEAR_t *SL)
{
   /* Libera Matriz de Coeficientes */
  for (int i = 0; i < SL->n; i++)
    free (SL->A[i]);
  free (SL->A) ;

  // Libera Vetores
  free(SL->b);
  free(SL->x);

  // Libera SL
  free(SL);
}

SISTEMA_LINEAR_t *aloca_sistema_linear(int n)
{
  SISTEMA_LINEAR_t *SL = (SISTEMA_LINEAR_t *)malloc(sizeof(SISTEMA_LINEAR_t));

    // if (!SL)
    //     return NULL;

    SL->n = n;

    SL->A = malloc (SL->n * sizeof (double*));
    for (int i = 0; i < SL->n; i++)
      SL->A[i] = malloc (SL->n * sizeof (double));

    // if (!SL->A)
    // {
    //     free(SL);
    //     return NULL;
    // }

    SL->b= malloc (SL->n * sizeof (double));

    // if (!SL->b)
    // {
    //     free(SL->A);
    //     free(SL);
    //     return NULL;
    // }

    SL->x= malloc (SL->n * sizeof (double));

    // if (!SL->x)
    // {
    //     free(SL->A);
    //     free(SL->b);
    //     free(SL);
    //     return NULL;
    // }

    return SL;
}
