/*
  Alunos: 
  Eduardo Purkote (GRR20182960)
  Mariana Moreira dos Santos (GRR20186554)
*/

// Bibliotecas padrao
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Bibliotecas auxiliares
#include "sistema_linear.h"
#include "utils.h"
#include "tabela.h"
#include "doubleType.h"
#include "interval.h"
#include "min_quadrados.h"

#ifdef LIKWID_PERFMON
#include <likwid.h>
#else
#define LIKWID_MARKER_INIT
#define LIKWID_MARKER_START(regionTag)
#define LIKWID_MARKER_STOP(regionTag)
#define LIKWID_MARKER_CLOSE
#endif

int main(int argc, char **argv) {
  // N = grau do polinomio de ajuste (1a linha)
  long long int N;
  
  // K = quantidade de pontos da tabela (2a linha)
  int K; 

  // Variaveis para calculo do tempo gasto
  double t_inicio = 0.0, t_final = 0.0, tgeraSL, tsolSL, tResiduo;;

  TABELA_t *Tabela;
  SISTEMA_LINEAR_t *SL_ot;
  INTERVAL_t *residuo_ot;
  
  // Le parametros de entrada
  int entrada = scanf("%lld", &N);
  if (entrada != 1) {
    perror("Erro ao ler o valor de N");
    exit(1);
  }

  entrada = scanf("%d", &K);
  if (entrada != 1) {
    perror("Erro ao ler o valor de K");
    exit(1);
  }

  // Alocacao de memoria
  Tabela = aloca_tabela (K);
  SL_ot = aloca_sistema_linear_otimizado(N+1);
  residuo_ot = malloc (K * sizeof (INTERVAL_t));
  
  // Le tabela de pontos e calcula intervalo para cada valor
  le_tabela(Tabela);

  #ifdef DEBUG
  imprime_tabela(Tabela, N);
  #endif

  //Inicia Likwid
  LIKWID_MARKER_INIT;

  LIKWID_MARKER_START("gera-sistema-linear");
  t_inicio = timestamp();
  min_quadrados_otimizado (Tabela, N, SL_ot);
  t_final = timestamp();
  tgeraSL = t_final - t_inicio;
  LIKWID_MARKER_STOP("gera-sistema-linear");

  #ifdef DEBUG
  imprime_sistema_linear(SL_ot);
  #endif

  // Passo 2: Eliminacao de Gauss
  LIKWID_MARKER_START("soluciona-sistema-linear");
  t_inicio = timestamp();
  elimGauss_parcial(SL_ot->A, SL_ot->b, SL_ot->x, N+1);
  retrosubs(SL_ot->A, SL_ot->b, SL_ot->x, N+1);
  t_final = timestamp();
  LIKWID_MARKER_STOP("soluciona-sistema-linear");
  tsolSL = t_final - t_inicio;

  // Passo 3: Calcula residuo
  LIKWID_MARKER_START("calcula-residuo");
  t_inicio = timestamp();
  calcula_residuo_otimizado(Tabela, SL_ot->x, residuo_ot, N);
  t_final = timestamp();
  tResiduo = t_final - t_inicio;
  LIKWID_MARKER_STOP("calcula-residuo");

  // Imprime resultados
  // printf("\nSem otimização\n");
  // imprime_coef(SL);
  // printf("\n\n");
  // imprime_residuo(residuo, K);

  // printf("\nCom otimização\n");
  // imprime_coef(SL_ot);
  // printf("\n\n");
  // imprime_residuo(residuo_ot, K);

  // printf("\nSem otimização\n");
  // printf("%1.8e\n", tgeraSL);
  // printf("%1.8e\n", tsolSL);
  // printf("%1.8e\n", tResiduo);

  // printf("\nCom otimização\n");
  // printf("%1.8e\n", tgeraSL_ot);
  // printf("%1.8e\n", tsolSL_ot);
  // printf("%1.8e\n\n", tResiduo_ot);

  // printf("\nCom otimização\n");

  //Imprime Resultados
  // imprime_coef(SL_ot);
  // imprime_residuo(residuo_ot, K);
  printf("%1.8e\n", tgeraSL);
  printf("%1.8e\n", tsolSL);
  printf("%1.8e\n\n", tResiduo);


  // Finaliza o Likwid
  LIKWID_MARKER_CLOSE;
  // Libera memoria alocada
  libera_tabela(Tabela);
  libera_sistema_linear_otimizado(SL_ot);
  free(residuo_ot);

  return 0;
}