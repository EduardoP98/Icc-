#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "interpolacao_pol.h"

int main (int argc, char **argv) {
  if(argc != 2) {
    perror("Número de Parâmetros Inválido!\n");
    exit(1);
  }

  // Trata Xe 
  char *ptr;
  double xe = strtod(argv[1],&ptr);
  
  int N;
  double *values_x,*values_y;
  scanf("%d",&N);
  
  // Aloca vetores
  values_x = malloc(N * sizeof(double));
  values_y = malloc(N * sizeof(double));

  // Trata entrada
  le_tabela(values_x,values_y,N);

  #ifdef DEBUG
  printf("xe:%lf\n",xe);
  printf("N: %d\n",N);
  imprime_tabela(values_x,values_y,N);
  #endif

  // Libera memoria alocada
  free(values_x);
  free(values_y);
  
  return 0;
}