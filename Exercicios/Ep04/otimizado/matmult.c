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
  
  MatRow mRow_1, mRow_2, resMat, resMat_Otimizado;
  Vetor vet, res, res_Otimizado;
  
  /* =============== TRATAMENTO DE LINHA DE COMANDO =============== */

  if (argc < 2)
    usage(argv[0]);

  n = atoi(argv[1]);
  
  /* ================ FIM DO TRATAMENTO DE LINHA DE COMANDO ========= */
 
  srandom(20232);
      
  res = geraVetor (n, 0); // (real_t *) malloc (n*sizeof(real_t));
  resMat = geraMatRow(n, n, 1);

  // Variaveis para guardar os resultados das versoes otimizadas
  res_Otimizado = geraVetor (n, 0);
  resMat_Otimizado = geraMatRow(n, n, 1);

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
    
#ifdef _DEBUG_
    prnMat (mRow_1, n, n);
    prnMat (mRow_2, n, n);
    prnVetor (vet, n);
    printf ("=================================\n\n");
#endif /* _DEBUG_ */
  
  // Variaveis para calculo do tempo gasto
  rtime_t t_multMatVet, t_multMatVet_Otimizado, t_multMatMat, t_multMatMat_Otimizado, t_inicio = 0.0, t_final = 0.0;

  // Inicia LIKWID
  LIKWID_MARKER_INIT;

  // Vetor x matriz (nao otimizado)
  t_inicio = timestamp();
  multMatVet (mRow_1, vet, n, n, res);
  t_final = timestamp();
  t_multMatVet = t_final - t_inicio;

  // Vetor x matriz (otimizado)
  t_inicio = timestamp();
  LIKWID_MARKER_START("multMatVet_Otimizado");
  multMatVet_Otimizado (mRow_1, vet, n, n, res_Otimizado);
  LIKWID_MARKER_STOP("multMatVet_Otimizado");
  t_final = timestamp();
  t_multMatVet_Otimizado = t_final - t_inicio;
  
  // Checa resultado da versao nao otimizada x otimizada
  
  // Matriz x matriz (nao otimizado)
  t_inicio = timestamp();
  multMatMat (mRow_1, mRow_2, n, resMat);
  t_final = timestamp();
  t_multMatMat = t_final - t_inicio;

  // Matriz x matriz (otimizado)
  t_inicio = timestamp();
  LIKWID_MARKER_START("multMatMat_Otimizado");
  multMatMat_Otimizado (mRow_1, mRow_2, n, resMat_Otimizado);
  LIKWID_MARKER_STOP("multMatMat_Otimizado");
  t_final = timestamp();
  t_multMatMat_Otimizado = t_final - t_inicio;


  #ifdef _DEBUG_
  // Checa resultado da versao nao otimizada x otimizada
  checa_resultado (resMat, resMat_Otimizado, n);
  #endif /* _DEBUG_ */

#ifdef _DEBUG_
    prnVetor (res, n);
    prnMat (resMat, n, n);
    prnVetor (res_Otimizado, n);
    prnMat (resMat_Otimizado, n, n);
#endif /* _DEBUG_ */

  liberaVetor ((void*) mRow_1);
  liberaVetor ((void*) mRow_2);
  liberaVetor ((void*) resMat);
  liberaVetor ((void*) resMat_Otimizado);
  liberaVetor ((void*) vet);
  liberaVetor ((void*) res);
  liberaVetor ((void*) res_Otimizado);

  // Imprime o tempo
  printf("Tempo - Matriz x Vetor - NÃO OTIMIZADO: %1.8e\n", t_multMatVet);
  printf("Tempo - Matriz x Vetor - OTIMIZADO: %1.8e\n\n", t_multMatVet_Otimizado);
  printf("Tempo - Matriz x Matriz - NÃO OTIMIZADO: %1.8e\n", t_multMatMat);
  printf("Tempo - Matriz x Matriz -  OTIMIZADO: %1.8e\n", t_multMatMat_Otimizado);

  // Encerra LIKWID
  LIKWID_MARKER_CLOSE;

  return 0;
}

