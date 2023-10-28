/*
  Alunos: 
  Eduardo Purkote (GRR20182960)
  Mariana Moreira dos Santos (GRR20186554)
*/

// Bibliotecas padrao
#include <stdio.h>
#include <stdlib.h>    /* exit, malloc, calloc, etc. */
#include <string.h>

// Bibliotecas auxiliares
#include <getopt.h>    /* getopt */
#include <time.h>
#include "lib-utils/utils/utils.h"
#include "matriz.h"

#ifdef LIKWID_PERFMON
#include <likwid.h>
#else
#define LIKWID_MARKER_INIT
#define LIKWID_MARKER_START(regionTag)
#define LIKWID_MARKER_STOP(regionTag)
#define LIKWID_MARKER_CLOSE
#endif

/**
 * Exibe mensagem de erro indicando forma de uso do programa e termina
 * o programa.
 */

static void usage(char *progname)
{
  fprintf(stderr, "Forma de uso: %s [ <ordem> ] \n", progname);
  exit(1);
}



/**
 * Programa principal
 * Forma de uso: matmult [ -n <ordem> ]
 * -n <ordem>: ordem da matriz quadrada e dos vetores
 *
 */

int main (int argc, char *argv[]) 
{
  int n=DEF_SIZE;
  
  MatRow mRow_1, mRow_2, resMat;
  Vetor vet, res;
  
  /* =============== TRATAMENTO DE LINHA DE COMANDO =============== */

  if (argc < 2)
    usage(argv[0]);

  n = atoi(argv[1]);
  
  /* ================ FIM DO TRATAMENTO DE LINHA DE COMANDO ========= */
 
  srandom(20232);
      
  res = geraVetor (n, 1); // (real_t *) malloc (n*sizeof(real_t));
  resMat = geraMatRow(n, n, 1);
    
  mRow_1 = geraMatRow (n, n, 0);
  mRow_2 = geraMatRow (n, n, 0);

  vet = geraVetor (n, 0);

  if (!res || !resMat || !mRow_1 || !mRow_2 || !vet) {
    fprintf(stderr, "Falha em alocação de memória !!\n");
    liberaVetor ((void*) mRow_1);
    liberaVetor ((void*) mRow_2);
    liberaVetor ((void*) resMat);
    liberaVetor ((void*) vet);
    liberaVetor ((void*) res);
    exit(2);
  }
  
  printf("teste"); 
#ifdef _DEBUG_
    prnMat (mRow_1, n, n);
    prnMat (mRow_2, n, n);
    prnVetor (vet, n);
    printf ("=================================\n\n");
#endif /* _DEBUG_ */

 // Variaveis para calculo do tempo gasto
  rtime_t t_multMatVet_Otimizado, t_multMatMat_Otimizado, t_inicio = 0.0, t_final = 0.0;

  // Inicia LIKWID
  LIKWID_MARKER_INIT;
  printf("teste");    
  // Vetor x matriz (otimizado)
  t_inicio = timestamp();
  LIKWID_MARKER_START("multMatVet_Otimizado");
  multMatVet_Otimizado (mRow_1, vet, n, n, res);
  LIKWID_MARKER_STOP("multMatVet_Otimizado");
  t_final = timestamp();
  t_multMatVet_Otimizado = t_final - t_inicio;

  printf("teste");    
  // Matriz x matriz (otimizado)
  t_inicio = timestamp();
  LIKWID_MARKER_START("multMatMat_Otimizado");
  multMatMat_Otimizado (mRow_1, mRow_2, n, resMat);
  LIKWID_MARKER_STOP("multMatMat_Otimizado");
  t_final = timestamp();
  t_multMatMat_Otimizado = t_final - t_inicio;
    
#ifdef _DEBUG_
    prnVetor (res, n);
    prnMat (resMat, n, n);
#endif /* _DEBUG_ */

  // Imprime o tempo
  printf("TEMPOS DE EXECUÇÃO\n\nMatriz x Vetor\nOtimizado: %1.8ems\n\n", t_multMatVet_Otimizado);
  printf("Matriz x Matriz\nOtimizado: %1.8ems\n\n", t_multMatMat_Otimizado);

  // Encerra LIKWID
  LIKWID_MARKER_CLOSE;

  liberaVetor ((void*) mRow_1);
  liberaVetor ((void*) mRow_2);
  liberaVetor ((void*) resMat);
  liberaVetor ((void*) vet);
  liberaVetor ((void*) res);

  return 0;
}

