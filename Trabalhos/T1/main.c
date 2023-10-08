/*
  Aunos: 
  Eduardo Purkote (GRR20182960)
  Mariana Moreira dos Santos (GRR20186554)
  
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sistema_linear.h"
#include "utils.h"
#include "tabela.h"
#include "doubleType.h"
#include "interval.h"
#include "min_quadrados.h"

// #include "likwid.h"

// #ifdef LIKWID_PERFMON
// #else
// #define LIKWID_MARKER_INIT
// #define LIKWID_MARKER_THREADINIT
// #define LIKWID_MARKER_SWITCH
// #define LIKWID_MARKER_REGISTER(regionTag)
// #define LIKWID_MARKER_START(regionTag)
// #define LIKWID_MARKER_STOP(regionTag)
// #define LIKWID_MARKER_CLOSE
// #define LIKWID_MARKER_GET(regionTag, nevents, events, time, count)
// #endif

int main() {
  // N = grau do polinomio de ajuste (1ª linha)
  int N;
  
  // K = quantidade de pontos da tabela (2ª linha)
  int K; 

  // Variaveis para calculo do tempo gasto
  double tgeraSL, tsolSL, t_inicio = 0.0, t_final = 0.0;

  TABELA_t *Tabela;
  SISTEMA_LINEAR_t *SL;
  
  // Lê parâmetros de entrada
  int entrada = scanf("%d", &N);
  if (entrada != 1) {
    perror("Erro ao ler o valor de N");
    exit(1);
  }

  entrada = scanf("%d", &K);
  if (entrada != 1) {
    perror("Erro ao ler o valor de K");
    exit(1);
  }

  Tabela = aloca_tabela (K);
  SL = aloca_sistema_linear (N+1);
  
  // Lê tabela de pontos e calcula intervalo para cada valor
  le_tabela(Tabela);

  #ifdef DEBUG
  printf("****************************************\n");
  printf("**          CÁLCULO INTERVALAR        **\n");
  printf("****************************************\n");
  printf("Grau do Polinômio (N): %d \n", N);
  imprime_tabela(Tabela);
  #endif

  // // Gera SL a partir da tabela de pontos
  t_inicio = timestamp();
  minQuadrados (Tabela, N, SL);
  t_final = timestamp();
  tgeraSL = t_final - t_inicio;
  
  //Imprime o Resultado na formatação de entrega
  imprime_sl_min(SL);

  #ifdef DEBUG
  imprime_sistema_linear(SL);
  #endif

  // // Resolve SL
  t_inicio = timestamp();
  elimGauss_parcial(SL->A, SL->b, SL->x, N+1);
  retrosubs(SL->A, SL->b, SL->x, N+1);
  t_final = timestamp();
  tsolSL = t_final - t_inicio;
  
  // // Calcula Rseíduo
  // // calculaResiduo(SL->A,SL->b,SL->x,N+1);

  // // Imprime Resultados
  printf("tgeraSL: %lf\n",tgeraSL);
  printf("tsolSL: %lf\n",tsolSL);

  #ifdef DEBUG
  imprime_sistema_linear(SL);
  #endif

  // // Libera memoria alocada
  // libera_tabela(Tabela);
  // // libera_sistema_linear(SL);

  return 0;
}