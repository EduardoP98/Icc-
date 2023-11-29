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
  long long int K; 

  // Variaveis para calculo do tempo gasto
  double tgeraSL, tsolSL, tResiduo, t_inicio = 0.0, t_final = 0.0;

  TABELA_t *Tabela;
  SISTEMA_LINEAR_t *SL;
  INTERVAL_t *residuo;
  
  // Le parametros de entrada
  int entrada = scanf("%lld", &N);
  if (entrada != 1) {
    perror("Erro ao ler o valor de N");
    exit(1);
  }

  entrada = scanf("%lld", &K);
  if (entrada != 1) {
    perror("Erro ao ler o valor de K");
    exit(1);
  }

  // Alocacao de memoria
  Tabela = aloca_tabela (K);
  SL = aloca_sistema_linear (N+1);
  residuo = malloc (K * sizeof (INTERVAL_t));
  
  // Le tabela de pontos e calcula intervalo para cada valor
  le_tabela(Tabela);

  #ifdef DEBUG
  imprime_tabela(Tabela, N);
  #endif

  //Inicia Likwid
  LIKWID_MARKER_INIT;
  
  // // Gera SL a partir da tabela de pontos
  LIKWID_MARKER_START("gera-sistema-linear");
  t_inicio = timestamp();
  minQuadrados (Tabela, N, SL);
  t_final = timestamp();
  LIKWID_MARKER_STOP("gera-sistema-linear");
  tgeraSL = t_final - t_inicio;

  #ifdef DEBUG
  imprime_sistema_linear(SL);
  #endif

  // Soluciona o sistema linear
  LIKWID_MARKER_START("soluciona-sistema-linear");
  t_inicio = timestamp();
  elimGauss_parcial(SL->A, SL->b, SL->x, N+1);
  retrosubs(SL->A, SL->b, SL->x, N+1);
  t_final = timestamp();
  LIKWID_MARKER_STOP("soluciona-sistema-linear");
  tsolSL = t_final - t_inicio;

  // Calcula residuo
  LIKWID_MARKER_START("calcula-residuo");
  t_inicio = timestamp();
  calcula_residuo(Tabela, SL->x, residuo, N);
  t_final = timestamp();
  tResiduo = t_final - t_inicio;
  LIKWID_MARKER_STOP("calcula-residuo");
  
  // Imprime resultados
  // imprime_coef(SL);
  // imprime_residuo(residuo, K);
  printf("%1.8e\n", tgeraSL);
  printf("%1.8e\n", tsolSL);
  printf("%1.8e\n", tResiduo);
  
  // Libera memoria alocada
  libera_tabela(Tabela);
  libera_sistema_linear(SL);
  free(residuo);

  // Finaliza o Likwid
  LIKWID_MARKER_CLOSE;

  return 0;
}
