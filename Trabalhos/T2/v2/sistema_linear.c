/*
  Alunos: 
  Eduardo Purkote (GRR20182960)
  Mariana Moreira dos Santos (GRR20186554)
*/

#include "sistema_linear.h"
#include "min_quadrados.h"

#include <stdlib.h>
#include <fenv.h>
#include <stdio.h>
#include <math.h>


/*  
  Funcao auxiliar para debugar o codigo

  Imprime o sistema linear contendo a 
  - Matriz A
  - Vetor B
  - Vetor X
*/
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
}

/*  
  Liberacao de memoria alocada das variaveis
  - Matriz A
  - Vetor B
  - Vetor X
  - Sistema linear
*/

void libera_sistema_linear(SISTEMA_LINEAR_t *SL) {
  // Libera matriz de coeficientes
  for (int i = 0; i < SL->n; i++)
    free (SL->A[i]);
  free (SL->A) ;

  // Libera vetores
  free(SL->b);
  free(SL->x);

  // Libera SL
  free(SL);
}
void libera_sistema_linear_otimizado(SISTEMA_LINEAR_t *SL) {
  // Libera matriz de coeficientes
  // libera a memória da matriz
  free (SL->A[0]);
  free (SL->A);

  // Libera vetores
  free(SL->b);
  free(SL->x);

  // Libera SL
  free(SL);
}


/*  
  Alocacao de memoria das variaveis
  - Matriz A
  - Vetor B
  - Vetor X
*/

SISTEMA_LINEAR_t *aloca_sistema_linear(int n) {
  SISTEMA_LINEAR_t *SL = (SISTEMA_LINEAR_t *)malloc(sizeof(SISTEMA_LINEAR_t));

    SL->n = n;

    SL->A = malloc (SL->n * sizeof (INTERVAL_t*));
    for (int i = 0; i < SL->n; i++)
      SL->A[i] = malloc (SL->n * sizeof (INTERVAL_t));


    SL->b= malloc (SL->n * sizeof (INTERVAL_t));

    SL->x= malloc (SL->n * sizeof (INTERVAL_t));

    return SL;
}

SISTEMA_LINEAR_t *aloca_sistema_linear_otimizado(int n) {
  SISTEMA_LINEAR_t *SL = (SISTEMA_LINEAR_t *)malloc(sizeof(SISTEMA_LINEAR_t));

    SL->n = n;

    // Aloca um vetor de LIN ponteiros para linhas
    SL->A = malloc (SL->n * sizeof (INTERVAL_t*));

    // Aloca um vetor com todos os elementos da matriz
    SL->A[0] = malloc (SL->n * SL->n * sizeof (INTERVAL_t));

    // Ajusta os demais ponteiros de linhas (i > 0)
    for (int i = 1; i < SL->n; i++)
      SL->A[i] = SL->A[0] + i * SL->n;

    SL->b= malloc (SL->n * sizeof (INTERVAL_t));
    
    SL->x= malloc (SL->n * sizeof (INTERVAL_t));

    return SL;
}

/*  
  Resolve um sistema linear triangular por retrosubstituicao

  Funcao auxiliar ao Metodo de Eliminacao de Gauss
*/
void retrosubs(INTERVAL_t **A, INTERVAL_t *b, INTERVAL_t *x, int n) {
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


/*  
  Encontra a linha com o maior valor absoluto na coluna i

  Funcao auxiliar ao Metodo de Eliminacao de Gauss
  Utilizada para realizar o pivoteamento parcial
*/
unsigned int encontra_max(INTERVAL_t **A, int i, int n) {
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


/*  
  Troca duas linhas da matriz A e vetor b

  Funcao auxiliar ao Metodo de Eliminacao de Gauss com pivoteamento parcial
*/
void troca_linha(INTERVAL_t **A, INTERVAL_t *b, int i, unsigned int iPivo,int n) {
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


/*  
  Eliminacao de Gauss com Pivoteamento Parcial

  Utiliza a aritmetica intervalar para realizar todos os calculos necessarios
*/
void elimGauss_parcial(INTERVAL_t **A, INTERVAL_t *b, INTERVAL_t *x,int n) {

  // Percorre as linhas
  for (int i = 0; i < n; ++i) {
    unsigned int iPivo = encontra_max(A, i, n);
    if (i != iPivo)
      troca_linha(A, b, i, iPivo, n);

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

/*  
  Calcula o valor estimado dado um vetor de coeficientes

  Funcao auxiliar ao calculo do residuo
*/
INTERVAL_t calcula_valor_estimado(INTERVAL_t *coeficientes, INTERVAL_t x, int n) {

  INTERVAL_t valor_previsto;
  valor_previsto.m.f = 0.0;
  valor_previsto.M.f = 0.0;

  for(int i = 0; i <= n; i++) {
    INTERVAL_t termo = calcula_pot(x,i);
    INTERVAL_t produto = calcula_mult(coeficientes[i],termo);

    valor_previsto = calcula_soma(valor_previsto,produto);
  }
  return valor_previsto;
}

// INTERVAL_t calcula_valor_estimado_otimizado(INTERVAL_t *coeficientes, INTERVAL_t x, int n){

// }

/*  
  Calcula o residuo entre a tabela de pontos e a equacao de ajuste

  Equação calculada : (ri = yi - f(xi))
  
  Tanto os coeficientes quanto os residuos sao intervalos

*/
void calcula_residuo(TABELA_t *tabela, INTERVAL_t *coeficientes, INTERVAL_t *residuos,int g)
{
    int i;
    for (i = 0; i < tabela->k; i++)
    {
        // Calcula o valor estimado usando a equacao de ajuste
        INTERVAL_t valor_estimado = calcula_valor_estimado(coeficientes, tabela->x[i],g);

        // Calcula o residuo para o ponto atual (ri = yi - f(xi))
        residuos[i] = calcula_subtracao(tabela->y[i], valor_estimado);
    }
}

void calcula_residuo_otimizado(TABELA_t *tabela, INTERVAL_t *coeficientes, INTERVAL_t *residuos, int n) {
    INTERVAL_t valor_previsto;
    INTERVAL_t produto;
    INTERVAL_t *tabela_potencias_base = malloc((2 * n + 1) * sizeof(INTERVAL_t));

    for (int k = 0; k < tabela->k; k++) {
      preencher_tabela_potencias(tabela->x[k], (2 * n) , tabela_potencias_base);
      valor_previsto.m.f = 0.0;
      valor_previsto.M.f = 0.0;

      for(int i = 0; i <= n; i++) {
        produto = calcula_mult(coeficientes[i], tabela_potencias_base[i]);
        valor_previsto = calcula_soma(valor_previsto, produto);
      }
    
    residuos[k] = calcula_subtracao(tabela->y[k], valor_previsto);
  }
}

// Imprime o residuo na formatacao de entrega definida pelo professor
void imprime_residuo(INTERVAL_t *residuo,int n)
{
    for(int j = 0; j < n; j++)
      printf("[%.17e, %.17e]  ", residuo[j].m.f, residuo[j].M.f);

    printf("\n");
}

// Imprime os coeficientes na formatacao de entrega definida pelo professor
void imprime_coef(SISTEMA_LINEAR_t *SL)
{
    for(int i = 0; i < SL->n; i++)
      printf("[%.17e, %.17e]  ",SL->x[i].m.f, SL->x[i].M.f);
    
    printf("\n");
}