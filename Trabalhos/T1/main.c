#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sistema_linear.h"
#include "utils.h"
#include "tabela.h"
#include "doubleType.h"
#include "interval.h"
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



int main()
{
  int N,K;
  double tgeraSL,tsolSL, t_inicio = 0.0, t_final = 0.0;

  TABELA_t *Tabela;
  SISTEMA_LINEAR_t *SL;
  
  // Lê parâmetros de entrada
  scanf("%d",&N);
  scanf("%d",&K);

  Tabela = aloca_tabela(K);
  SL = aloca_sistema_linear(N+1);
  
  // Lê tabela de pontos
  le_tabela(Tabela);
  t_inicio = timestamp();
  // Gera SL a partir da Tabela de pontos
  minQuadrados(Tabela,N,SL);
  t_final = timestamp();
  tgeraSL = t_final - t_inicio;

  imprime_sistema_linear(SL);
  
  // Resolve SL
  t_inicio = timestamp();
  elimGauss_parcial(SL->A,SL->b,SL->x, N+1);
  retrosubs(SL->A,SL->b,SL->x,N+1);
  t_final = timestamp();
  tsolSL = t_final - t_inicio;
  
  // Calcula Rseíduo
  // calculaResiduo(SL->A,SL->b,SL->x,N+1);

  #ifdef DEBUG
  printf("Grau do Polinômio: %d \n", N);
  imprime_tabela(Tabela);
  #endif


  // Imprime Resultados
  printf("tgeraSL: %lf\n",tgeraSL);
  printf("tsolSL: %lf\n",tsolSL);

  imprime_sistema_linear(SL);

  // Libera memoria alocada
  libera_tabela(Tabela);
  // libera_sistema_linear(SL);

  return 0;
}