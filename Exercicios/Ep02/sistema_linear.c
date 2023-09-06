#include "sistema_linear.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* Funções Auxiliares */
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
    #ifdef DEBUG
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
    #endif

    for(int i = 0; i < SL->n; ++i)
    {
      printf("x[%d]: %f  ",i,SL->x[i]);
    }
    printf("\n");

    printf("Residuo: %1.8e\n",SL->residuo);
        
    
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

    SL->n = n;

    SL->A = malloc (SL->n * sizeof (double*));
    for (int i = 0; i < SL->n; i++)
      SL->A[i] = malloc (SL->n * sizeof (double));


    SL->b= malloc (SL->n * sizeof (double));

    SL->x= malloc (SL->n * sizeof (double));

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
}

/* Funções de Cálculo */

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

// Função auxiliar para encontrar a linha com o maior valor absoluto na coluna i
unsigned int encontraMax(double **A, int i, int n)
{
  unsigned int maxIndex = i;
  double maxValor = fabs(A[i][i]); // Assumindo que o valor na diagonal é o máximo inicial
  for (int k = i + 1; k < n; ++k)
  {
    double valorAtual = fabs(A[k][i]);
    if (valorAtual > maxValor)
    {
      maxValor = valorAtual;
      maxIndex = k;
    }
  }
    return maxIndex;
}

// Função para trocar duas linhas da matriz A e vetor b
void trocaLinha(double **A, double *b, int i, int iPivo, int n)
{
  if (i != iPivo)
  {
    for (int j = 0; j < n; ++j)
    {
      double temp = A[i][j];
      A[i][j] = A[iPivo][j];
      A[iPivo][j] = temp;
    }
    double temp = b[i];
    b[i] = b[iPivo];
    b[iPivo] = temp;
  }
}


//Eliminação de Gauss com Pivoteamento Parcial
void elimGauss_parcial(double **A,double *b,double *x, int n)
{
   for(int i = 0; i < n; ++i)
   {
      unsigned int iPivo = encontraMax(A, i,n);
      if(i != iPivo)
        trocaLinha(A,b,i,iPivo,n);
      
      for(int k = i + 1; k < n ; ++k)
      {
        double m = A[k][i] / A[i][i];
        A[k][i] = 0.0;
        for(int j = i+1; j < n; ++j)
          A[k][j] -= A[i][j] * m;
        b[k] -= b[i] *m;
      }
   }
}

// Eliminação de Gauss com Pivoteamento Parcial (sem cálculo dos multiplicadores)
void elimGauss_sem_multiplicadores(double **A, double *b, int n)
{
  for (int i = 0; i < n; ++i)
  {
    // Encontrar o pivô na coluna atual
    unsigned int iPivo = encontraMax(A, i, n);
    if (i != iPivo)
      trocaLinha(A, b, i, iPivo, n);
  
    for (int k = i + 1; k < n; ++k)
    {
      // Não calcula explicitamente o multiplicador m
      for (int j = i + 1; j < n; ++j)
      {
        A[k][j] -= A[i][j] * (A[k][i] / A[i][i]);
      }
      b[k] -= b[i] * (A[k][i] / A[i][i]);
      A[k][i] = 0.0; // Definir para 0
    }
  }
}

// Eliminação de Gauss sem pivoteamento
void elimGauss_sem_pivoteamento(double **A, double *b, int n)
{
  for (int i = 0; i < n; ++i)
  {
    // Para cada linha do pivô, divide todos os coeficientes pelo valor do pivô (que se torna 1)
    double pivot = A[i][i];
    for (int j = i; j < n; ++j)
    {
      A[i][j] /= pivot;
    }
    b[i] /= pivot;

    // Prossiga com a eliminação, zerando a coluna do pivô
    for (int k = i + 1; k < n; ++k)
    {
      double factor = A[k][i];
      for (int j = i; j < n; ++j)
      {
        A[k][j] -= factor * A[i][j];
      }
      b[k] -= factor * b[i];
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
