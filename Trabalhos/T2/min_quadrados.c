/*
  Alunos: 
  Eduardo Purkote (GRR20182960)
  Mariana Moreira dos Santos (GRR20186554)
*/

#include <stdio.h>
#include <math.h>
#include "min_quadrados.h"
#include "sistema_linear.h"

/*  
  Implementacao do Metodo dos Minimos Quadrados

  Dada uma tabela de K pontos (x,y) e a escolha do grau N do polinomio, 
  a função ira calcular a matriz A e o vetor B que posteriomente serao resolvidos com uma Eliminacao de Gauss

  Todos os calculos levam em consideracao a aritmetica intervalar e por isso ha a chamada de funcoes auxiliares

*/
void min_quadrados(TABELA_t *tabela, long long int n, SISTEMA_LINEAR_t *SL) {
  // Para cada elemento da matriz A e do vetor B
  for (long long int i = 0; i <= n; i++) {

    // Matriz A
    for (long long int j = 0; j <= n; j++) {
      // Ira guardar o valor final da soma dos valores de x elevados as potencias i + j
      INTERVAL_t soma;
      soma.m.f = 0.0;
      soma.M.f = 0.0;

      for (long long int k = 0; k < tabela->k; k++) {
        INTERVAL_t termo1 = calcula_pot(tabela->x[k], i+j);
        soma = calcula_soma(soma, termo1);
      }
      SL->A[i][j] = soma;
    }

    // Vetor B
    INTERVAL_t soma_b;
    soma_b.m.f = 0.0;
    soma_b.M.f = 0.0;

    for (long long int k = 0; k < tabela->k; k++) {
      INTERVAL_t termo1 = calcula_pot(tabela->x[k], i);
      INTERVAL_t produto = calcula_mult(termo1, tabela->y[k]);
      soma_b = calcula_soma(soma_b, produto);
    }
    SL->b[i] = soma_b;
  }
}

void min_quadrados_otimizado (TABELA_t *tabela, long long int n, SISTEMA_LINEAR_t *SL) {
  // Residuo do loop unroll
  int residuo = tabela->k % UF;

  #ifdef DEBUG
  printf("\n****************************************\n");
  printf("**    MÉTODO DOS MINIMOS QUADRADOS    **\n");
  printf("****************************************\n");
  printf("tabela->k: %lld\n", tabela->k);
  printf("Residuo: %d\n", residuo);
  printf("tabela->k - residuo: %lld\n", tabela->k - residuo);
  #endif

  for (long long int i = 0; i <= n; i++) {
    for (long long int j = 0; j <= n; j++) {
      INTERVAL_t soma;
      soma.m.f = 0.0;
      soma.M.f = 0.0;

      // Loop unroll
      for (long long int k = 0; k < tabela->k - residuo; k+=UF) {
        INTERVAL_t termo1 = calcula_pot(tabela->x[k], i+j);
        INTERVAL_t termo2 = calcula_pot(tabela->x[k+1], i+j);
        INTERVAL_t termo3 = calcula_pot(tabela->x[k+2], i+j);
        INTERVAL_t termo4 = calcula_pot(tabela->x[k+3], i+j);

        soma = calcula_soma(soma, termo1);
        soma = calcula_soma(soma, termo2);
        soma = calcula_soma(soma, termo3);
        soma = calcula_soma(soma, termo4);
      }

      // Residuo
      for (long long int k = tabela->k - residuo; k < tabela->k; k++) {
        INTERVAL_t termo1 = calcula_pot(tabela->x[k], i+j);
        soma = calcula_soma(soma, termo1);
      }

      SL->A[i][j] = soma;
    }

    // Vetor B
    INTERVAL_t soma_b;
    soma_b.m.f = 0.0;
    soma_b.M.f = 0.0;

    // Loop unroll
    for (long long int k = 0; k < tabela->k - residuo; k+=UF) {
      INTERVAL_t termo1 = calcula_pot(tabela->x[k], i);
      INTERVAL_t produto1 = calcula_mult(termo1, tabela->y[k]);

      INTERVAL_t termo2 = calcula_pot(tabela->x[k+1], i);
      INTERVAL_t produto2 = calcula_mult(termo2, tabela->y[k+1]);

      INTERVAL_t termo3 = calcula_pot(tabela->x[k+2], i);
      INTERVAL_t produto3 = calcula_mult(termo3, tabela->y[k+2]);

      INTERVAL_t termo4 = calcula_pot(tabela->x[k+3], i);
      INTERVAL_t produto4 = calcula_mult(termo4, tabela->y[k+3]);

      soma_b = calcula_soma(soma_b, produto1);
      soma_b = calcula_soma(soma_b, produto2);
      soma_b = calcula_soma(soma_b, produto3);
      soma_b = calcula_soma(soma_b, produto4);
    }

    // Residuo
    for (long long int k = tabela->k - residuo; k < tabela->k; k++) {
      INTERVAL_t termo1 = calcula_pot(tabela->x[k], i);
      INTERVAL_t produto = calcula_mult(termo1, tabela->y[k]);
      soma_b = calcula_soma(soma_b, produto);
    }

    SL->b[i] = soma_b;
  }

}

void min_quadrados_otimizado_v2 (TABELA_t *tabela, long long int n, SISTEMA_LINEAR_t *SL) {
  // Percorre a tabela de pontos inves de percorrer o n
  for (long long int k = 0; k < tabela->k; k++) {

    // Percorrendo as linhas
    for (long long int i = 0; i <= n; i++) {
      // Preencher a matriz A
      for (long long int j = 0; j <= n; j++) {
        INTERVAL_t termo1 = calcula_pot(tabela->x[k], i+j);
        SL->A[i][j] = calcula_soma(SL->A[i][j], termo1);
      }

       // Preencher o vetor B
      INTERVAL_t termo1 = calcula_pot(tabela->x[k], i);
      INTERVAL_t produto = calcula_mult(termo1, tabela->y[k]);
      SL->b[i] = calcula_soma(SL->b[i], produto);
    }
  }

}


void min_quadrados_otimizado_v3 (TABELA_t *tabela, long long int n, SISTEMA_LINEAR_t *SL) {
  // Residuo do loop unroll
  int residuo = tabela->k % UF;

  #ifdef DEBUG
  printf("\n****************************************\n");
  printf("**    MÉTODO DOS MINIMOS QUADRADOS    **\n");
  printf("****************************************\n");
  printf("tabela->k: %lld\n", tabela->k);
  printf("Residuo: %d\n", residuo);
  printf("tabela->k - residuo: %lld\n", tabela->k - residuo);
  #endif

  // Percorre a tabela de pontos inves de percorrer o n
  for (long long int k = 0; k < tabela->k - residuo; k+=UF) {
    // Primeira iteração do loop externo
    for (long long int i = 0; i <= n; i++) {
        // Preencher a matriz A
        for (long long int j = 0; j <= n; j++) {
            INTERVAL_t termo1 = calcula_pot(tabela->x[k], i+j);
            SL->A[i][j] = calcula_soma(SL->A[i][j], termo1);
        }

        // Preencher o vetor B
        INTERVAL_t termo1 = calcula_pot(tabela->x[k], i);
        INTERVAL_t produto = calcula_mult(termo1, tabela->y[k]);
        SL->b[i] = calcula_soma(SL->b[i], produto);
    }

    // Segunda iteração do loop externo
    for (long long int i = 0; i <= n; i++) {
        // Preencher a matriz A
        for (long long int j = 0; j <= n; j++) {
            INTERVAL_t termo1 = calcula_pot(tabela->x[k+1], i+j);
            SL->A[i][j] = calcula_soma(SL->A[i][j], termo1);
        }

        // Preencher o vetor B
        INTERVAL_t termo1 = calcula_pot(tabela->x[k+1], i);
        INTERVAL_t produto = calcula_mult(termo1, tabela->y[k+1]);
        SL->b[i] = calcula_soma(SL->b[i], produto);
    }
  }
}
