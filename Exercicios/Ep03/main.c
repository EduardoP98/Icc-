#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "interpolacao_pol.h"

#ifdef LIKWID_PERFMON
#include <likwid.h>
#else
#define LIKWID_MARKER_INIT
// #define LIKWID_MARKER_THREADINIT
// #define LIKWID_MARKER_SWITCH
// #define LIKWID_MARKER_REGISTER(regionTag)
#define LIKWID_MARKER_START(regionTag)
#define LIKWID_MARKER_STOP(regionTag)
#define LIKWID_MARKER_CLOSE
// #define LIKWID_MARKER_GET(regionTag, nevents, events, time, count)
#endif
int main (int argc, char **argv) {

  // Verificacao de argumentos de entrada
  if(argc != 2) {
    perror("Erro!\n Número de parâmetros inválido.\n A entrada deve ser: ./interpola xe < pontos.in > resultados.out");
    exit(1);
  }

  // Trata Xe 
  char *ptr;
  double xe = strtod(argv[1], &ptr);  // converte para double
  
  // Leitura do N que determina o numero de pontos
  int N;
  double *x,*y;

  if (scanf("%d", &N) != 1) {
    perror("Erro ao ler o valor de N");
    exit(1);
}
  
  // Aloca vetores com tamanho N pontos
  x = malloc(N * sizeof(double));
  y = malloc(N * sizeof(double));

  // Leitura da tabela de N pontos (x, f(x))
  le_tabela(x, y, N);

  // Verificando se xe pertence ao intervalo da tabela de pontos
  double x_min = x[0];
  double x_max = x[0];

  for (int i = 1; i < N; i++) {
    if (x[i] < x_min) {
      x_min = x[i];
    }
    if (x[i] > x_max) {
      x_max = x[i];
    }
  }

  if (!(xe >= x_min && xe <= x_max)) {
    fprintf(stderr, "Erro: xe = %.2lf está fora do intervalo da tabela.\n", xe);
    return 1;
  }

  #ifdef DEBUG
  printf("xe: %lf\n", xe);
  printf("N: %d\n", N);
  imprime_tabela(x, y, N);
  printf("\n");
  #endif

  //Inicia Likwid
  LIKWID_MARKER_INIT;

  // Interpolacao de Lagrange
  LIKWID_MARKER_START("polinomio-lagrange");
  double time_i = timestamp();
  interpolacao_lagrange(xe, x, y, N);
  double time_f = timestamp();
  LIKWID_MARKER_STOP("polinomio-lagrange");
  double time_lagrange = time_f - time_i;


  // Interpolacao de Newton
  double coeficientes[N];
  LIKWID_MARKER_START("polinomio-newton");
  time_i = timestamp();
  polinomio_newton(x, y, coeficientes, N);
  interpolacao_newton(x, coeficientes, N, xe);
  time_f = timestamp();
  LIKWID_MARKER_STOP("polinomio-newton");
  
  printf("tLagrange: %lf \n", time_lagrange);
  printf("tNewton: %lf \n\n", time_f - time_i);

  // FInaliza o Likwid
  LIKWID_MARKER_CLOSE;

  // Libera memoria alocada
  free(x);
  free(y);
  
  return 0;
}