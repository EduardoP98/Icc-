/*
  Aunos: 
  Eduardo Purkote (GRR20182960)
  Mariana Moreira dos Santos (GRR20186554)
  
*/
#include "sistema_linear.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* Funções Auxiliares */
void imprime_sistema_linear(SISTEMA_LINEAR_t *SL) {
    printf("\n****************************************\n");
    printf("**           SISTEMA LINEAR           **\n");
    printf("****************************************\n");

    printf("\nOrdem do SL: %d\n\n", SL->n);

    printf("****************************************\n");
    printf("**             Matriz A               **\n");
    printf("****************************************\n");

    for(int i = 0; i < SL->n; ++i) {
      for(int j = 0; j < SL->n; ++j)
        printf("[%.8e, %.8e]   ", SL->A[i][j].m.f, SL->A[i][j].M.f);
      printf("\n\n");
    }

    printf("****************************************\n");
    printf("**             Vetor b                **\n");
    printf("****************************************\n");

    for(int i = 0; i < SL->n; ++i)
      printf("[%.8e, %.8e]   ", SL->b[i].m.f, SL->b[i].M.f);
    printf("\n\n");


    printf("****************************************\n");
    printf("**             Vetor x                **\n");
    printf("****************************************\n");

    for(int i = 0; i < SL->n; ++i) {
      printf("x[%d]: [%.8e, %.8e]  ", i, SL->x[i].m.f, SL->x[i].M.f);
      printf("\n");
    }
    

    printf("\n\n****************************************\n");
    printf("**             Resíduo                **\n");
    printf("****************************************\n");
    printf("Residuo: [%.8e, %.8e] \n", SL->residuo.m.f, SL->residuo.M.f);
        
}


void libera_sistema_linear(SISTEMA_LINEAR_t *SL)
{
  //Libera Matriz de Coeficientes
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

    SL->n = n;

    SL->A = malloc (SL->n * sizeof (INTERVAL_t*));
    for (int i = 0; i < SL->n; i++)
      SL->A[i] = malloc (SL->n * sizeof (INTERVAL_t));


    SL->b= malloc (SL->n * sizeof (INTERVAL_t));

    SL->x= malloc (SL->n * sizeof (INTERVAL_t));

    return SL;
}


// Função para copiar uma variável do tipo SISTEMA_LINEAR_t para outra
void copiaSistemaLinear(const SISTEMA_LINEAR_t *origem, SISTEMA_LINEAR_t *destino)
{
    destino->n = origem->n;

    // Copie a matriz A
    for (int i = 0; i < destino->n; ++i)
    {
      for (int j = 0; j < destino->n; ++j)
      {
        destino->A[i][j] = origem->A[i][j];
      }
    }

    // Copie o vetor b
    for (int i = 0; i < destino->n; ++i)
    {
        destino->b[i] = origem->b[i];
    }

    destino->residuo = origem->residuo;
}

//Função que resolve um Sistema triangular por retrosubs
void retrosubs(INTERVAL_t **A, INTERVAL_t *b, INTERVAL_t *x, int n)
{
  for (int i = n - 1; i >= 0; --i)
  {
    x[i] = b[i];
    for (int j = i + 1; j < n; ++j)
    {
      INTERVAL_t mult_result = calcula_mult(A[i][j], x[j]);
      x[i] = calcula_subtracao(x[i], mult_result);
    }
    INTERVAL_t div_result = calcula_div(x[i], A[i][i]);
    x[i] = div_result;
  }
}


// Função auxiliar para encontrar a linha com o maior valor absoluto na coluna i
unsigned int encontraMax(INTERVAL_t **A, int i, int n)
{
  unsigned int maxIndex = i;
  double maxValor = fabs(A[i][i].m.f);

  for (int k = i + 1; k < n; ++k)
  {
    double valorAtual = fabs(A[k][i].m.f);
    if (valorAtual > maxValor)
    {
      maxValor = valorAtual;
      maxIndex = k;
    }
  }
    return maxIndex;
}


// Função para trocar duas linhas da matriz A e vetor b
void trocaLinha(INTERVAL_t **A, INTERVAL_t *b, int i, int iPivo, int n)
{
  if (i != iPivo)
  {
    for (int j = 0; j < n; ++j)
    {
      INTERVAL_t temp = A[i][j];
      A[i][j] = A[iPivo][j];
      A[iPivo][j] = temp;
    }
    INTERVAL_t temp = b[i];
    b[i] = b[iPivo];
    b[iPivo] = temp;
  }
}


// Eliminação de Gauss com Pivoteamento Parcial
void elimGauss_parcial(INTERVAL_t **A, INTERVAL_t *b, INTERVAL_t *x, int n) {
  for (int i = 0; i < n; ++i) {
    unsigned int iPivo = encontraMax(A, i, n);
    if (i != iPivo)
      trocaLinha(A, b, i, iPivo, n);

    for (int k = i + 1; k < n; ++k) {
      INTERVAL_t m = calcula_div(A[k][i], A[i][i]);
      // Define o elemento como [0,0]
      A[k][i].m.f = 0.0; 
      A[k][i].M.f = 0.0; 
      for (int j = i + 1; j < n; ++j) {
        INTERVAL_t produto = calcula_mult(A[i][j], m);
        A[k][j] = calcula_subtracao(A[k][j], produto);
      }
      INTERVAL_t produto_b = calcula_mult(b[i], m);
      b[k] = calcula_subtracao(b[k], produto_b);
    }
  }
}


double calculaResiduo(double **A, double *b, double *x, int n)
{
  double *Ax = malloc(n * sizeof(double)); // Aloca espaço para o vetor Ax
    
  // Calcula Ax multiplicando A por x
  for (int i = 0; i < n; ++i)
  {
    Ax[i] = 0.0;
    for (int j = 0; j < n; ++j)
    {
      Ax[i] += A[i][j] * x[j];
    }
  }

  // Calcula o vetor de resíduo
  double *residuo = malloc(n * sizeof(double));
  for (int i = 0; i < n; ++i)
  {
    residuo[i] = Ax[i] - b[i];
  }

  // Calcula a norma 2 do vetor de resíduo
  double normaResiduo = 0.0;
  for (int i = 0; i < n; ++i)
  {
    normaResiduo += residuo[i] * residuo[i];
  }
  normaResiduo = sqrt(normaResiduo);

  // Libera a memória alocada
  free(Ax);
  free(residuo);

  return normaResiduo;
}

//Imprime o Resultado na formatação de entrega
void imprime_coef(SISTEMA_LINEAR_t *SL)
{
    for(int j = 0; j < SL->n; j++)
      printf("(a[%d])=[%.17e, %.17e]  ",j,SL->x[j].m.f,SL->x[j].M.f);

    printf("\n");
}