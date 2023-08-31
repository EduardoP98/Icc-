#include "sistema_linear.h"
#include <stdlib.h>
#include <stdio.h>


void le_sistema_linear(double **A, double *b , double *x, int n)
{
  int cont = 0;
  for(int i = 0; i < n; ++i)
  {
    for(int j = 0; j < n; ++j)
    {
      scanf("%lf",&A[i][j]);
      
    }

    scanf("%lf",&b[cont]);
    cont ++;
  }
  
    
}

void imprime_sistema_linear(double **A, double *b , double *x, int n)
{
    printf("****************************************\n");
    printf("**             Matriz A               **\n");
    printf("****************************************\n");

    for(int i = 0; i < n; ++i)
    {
      for(int j = 0; j < n; ++j)
        printf("%f  ",A[i][j]);
      printf("\n");
    }

    printf("****************************************\n");
    printf("**             Vetor b                **\n");
    printf("****************************************\n");

    for(int i = 0; i < n; ++i)
        printf("%f  ",b[i]);
    printf("\n");


    printf("****************************************\n");
    printf("**             Vetor x                **\n");
    printf("****************************************\n");

    for(int i = 0; i < n; ++i)
        printf("%f  ",x[i]);
    printf("\n");
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



