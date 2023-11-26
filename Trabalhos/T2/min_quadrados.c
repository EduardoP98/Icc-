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

void preencher_tabela_potencias(INTERVAL_t base, long long int n, INTERVAL_t *tabela_potencias) {
    tabela_potencias[0].m.f = 1.0;
    tabela_potencias[0].M.f = 1.0;

    for (long long int i = 1; i <= n; ++i) {
        tabela_potencias[i].m.f = tabela_potencias[i - 1].m.f * base.m.f;
        tabela_potencias[i].M.f = tabela_potencias[i - 1].M.f * base.M.f;
    }
}

void min_quadrados_otimizado (TABELA_t *tabela, long long int n, SISTEMA_LINEAR_t *SL) {
  INTERVAL_t *tabela_potencias_base = malloc((2 * n + 1) * sizeof(INTERVAL_t));
  INTERVAL_t produto;

  for (long long int k = 0; k < tabela->k; k++) {
    preencher_tabela_potencias(tabela->x[k], (2 * n) , tabela_potencias_base);

    for (long long int i = 0; i <= n; i++) {
      for (long long int j = 0; j <= n; j++) {
        SL->A[i][j] = calcula_soma(SL->A[i][j], tabela_potencias_base[i+j]);
      }

      produto = calcula_mult(tabela_potencias_base[i], tabela->y[k]);
      SL->b[i] = calcula_soma(SL->b[i], produto);
    }
  }

}

