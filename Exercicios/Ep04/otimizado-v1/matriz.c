#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h> // Para uso de função 'memset()'

#include "matriz.h"

/**
 * Função que gera valores para para ser usado em uma matriz
 * @param i,j coordenadas do elemento a ser calculado (0<=i,j<n)
*  @return valor gerado para a posição i,j
  */
static inline real_t generateRandomA( unsigned int i, unsigned int j)
{
  static real_t invRandMax = 1.0 / (real_t)RAND_MAX;
  return ( (i==j) ? (real_t)(BASE<<1) : 1.0 )  * (real_t)random() * invRandMax;
}

/**
 * Função que gera valores aleatórios para ser usado em um vetor
 * @return valor gerado
 *
 */
static inline real_t generateRandomB( )
{
  static real_t invRandMax = 1.0 / (real_t)RAND_MAX;
  return (real_t)(BASE<<2) * (real_t)random() * invRandMax;
}



/* ----------- FUNÇÕES ---------------- */

/**
 *  Funcao geraMatRow: gera matriz como vetor único, 'row-oriented'
 * 
 *  @param m     número de linhas da matriz
 *  @param n     número de colunas da matriz
 *  @param zerar se 0, matriz  tem valores aleatórios, caso contrário,
 *               matriz tem valores todos nulos
 *  @return  ponteiro para a matriz gerada
 *
 */

MatRow geraMatRow (int m, int n, int zerar)
{
  MatRow matriz = (real_t *) malloc(m*n*sizeof(real_t));

  if (matriz) {
    if (zerar)
      memset(matriz,0,m*n*sizeof(real_t));
    else
      for (int i=0; i < m; ++i)
	for (int j=0; j < n; ++j)
	  matriz[i*n + j] = generateRandomA(i, j);
  }
  
  return (matriz);
}


/**
 *  Funcao geraVetor: gera vetor de tamanho 'n'
 * 
 *  @param n  número de elementos do vetor
 *  @param zerar se 0, vetor  tem valores aleatórios, caso contrário,
 *               vetor tem valores todos nulos
 *  @return  ponteiro para vetor gerado
 *
 */

Vetor geraVetor (int n, int zerar)
{
  Vetor vetor = (real_t *) malloc(n*sizeof(real_t));

  if (vetor) {
    if (zerar)
      memset(vetor,0,n*sizeof(real_t));
    else
      for (int i=0; i < n; ++i)
	vetor[i] = generateRandomB();
  }
  
  return (vetor);
}

/**
 *  \brief: libera vetor
 * 
 *  @param  ponteiro para vetor
 *
 */
void liberaVetor (void *vet) {
	free(vet);
}


/**
 *  Funcao multMatVet:  Efetua multiplicacao entre matriz 'mxn' por vetor
 *                       de 'n' elementos
 *  @param mat matriz 'mxn'
 *  @param m número de linhas da matriz
 *  @param n número de colunas da matriz
 *  @param res vetor que guarda o resultado. Deve estar previamente alocado e com
 *             seus elementos inicializados em 0.0 (zero)
 *  @return vetor de 'm' elementos
 *
 */

void multMatVet (MatRow mat, Vetor v, int m, int n, Vetor res) {
  /* Efetua a multiplicação */
  if (res) {
    for (int i=0; i < m; ++i)
      for (int j=0; j < n; ++j)
        res[i] += mat[n*i + j] * v[j];
  }
}


/**
 *  Funcao multMatVetOtimizado:  Efetua multiplicacao entre matriz 'mxn' por vetor
 *                                    de 'n' elementos e aplica otimizacao unroll & jam
 *  @param mat matriz 'mxn'
 *  @param m número de linhas da matriz
 *  @param n número de colunas da matriz
 *  @param res vetor que guarda o resultado. Deve estar previamente alocado e com
 *             seus elementos inicializados em 0.0 (zero)
 *  @return vetor de 'm' elementos
 *
 */

void multMatVetOtimizado (MatRow mat, Vetor v, int m, int n, Vetor C) {
  int i, j;

  // Calcula residuo para posteriormente trata-lo
  int residuo = (m % UF);

  #ifdef _DEBUG_
  printf("Resíduo do laço: %d\n\n", residuo);
  #endif /* _DEBUG_ */

  // Unroll & Jam
  for(i=0; i < m - residuo; i+=UF) {
    for(j=0; j < m; ++j) {
      C[i] += mat[m*i + j] * v[j];
      C[i + 1] += mat[m*(i+1) + j] * v[j];
      C[i + 2] += mat[m*(i+2) + j] * v[j]; 
      C[i + 3] += mat[m*(i+3) + j] * v[j];
      C[i + 4] += mat[m*(i+4) + j] * v[j];
      C[i + 5] += mat[m*(i+5) + j] * v[j]; 
      C[i + 6] += mat[m*(i+6) + j] * v[j]; 
      C[i + 7] += mat[m*(i+7) + j] * v[j]; 
    }
  }

  // Residuo
  if (residuo > 0) {
    for(i=m-residuo; i < m; ++i) {
      for(j=0; j < m; ++j){
        C[i] += mat[m*i + j] * v[j];
      }
    }
  }
}

/**
 *  Funcao multMatMat: Efetua multiplicacao de duas matrizes 'n x n' 
 *  @param A matriz 'n x n'
 *  @param B matriz 'n x n'
 *  @param n ordem da matriz quadrada
 *  @param C   matriz que guarda o resultado. Deve ser previamente gerada com 'geraMatPtr()'
 *             e com seus elementos inicializados em 0.0 (zero)
 *
 */

void multMatMat (MatRow A, MatRow B, int n, MatRow C)
{

  /* Efetua a multiplicação */
  for (int i=0; i < n; ++i)
    for (int j=0; j < n; ++j)
      for (int k=0; k < n; ++k)
	      C[i*n+j] += A[i*n+k] * B[k*n+j];
}


/**
 *  Funcao multMatMat_Otimizado: Efetua multiplicacao de duas matrizes 'n x n' e utiliza otimizacao
 *  @param A matriz 'n x n'
 *  @param B matriz 'n x n'
 *  @param n ordem da matriz quadrada
 *  @param C   matriz que guarda o resultado. Deve ser previamente gerada com 'geraMatPtr()'
 *             e com seus elementos inicializados em 0.0 (zero)
 *
 */

void multMatMatOtimizado (MatRow A, MatRow B, int n, MatRow C) {

  int b = n / BK;
  int istart, iend, jstart, jend, kstart, kend, i, ii, j, jj, k, kk;
  double Aik;

  // Loop blocking
  for (ii=0; ii < n/b; ++ii) {
    istart = ii * b; iend = istart + b;
    for (jj=0; jj < n/b; ++jj) {
      jstart = jj * b; jend = jstart + b;
      for (kk=0; kk < n/b; ++kk) {
        kstart = kk * b; kend = kstart + b;
        for (i=istart; i < iend; ++i) {
          // Unroll & Jam
          for (j=jstart; j < jend; j+= UF) {
            C[i*n+j] = C[i*n+j+1] = C[i*n+j+2] = C[i*n+j+3] = C[i*n+j+4] = C[i*n+j+5] = C[i*n+j+6] = C[i*n+j+7] = 0.0;
            // C[i*n+j] = C[i*n+j+1] = C[i*n+j+2] = C[i*n+j+3] = 0.0;
            for (k=kstart; k < kend; ++k) {
              Aik = A[i*n + k];
              C[i*n+j] += Aik * B[k*n+j];
              C[i*n+j + 1] += Aik * B[k*n+j + 1];
              C[i*n+j + 2] += Aik * B[k*n+j + 2];
              C[i*n+j + 3] += Aik * B[k*n+j + 3];
              C[i*n+j + 4] += Aik * B[k*n+j + 4];
              C[i*n+j + 5] += Aik * B[k*n+j + 5];
              C[i*n+j + 6] += Aik * B[k*n+j + 6];
              C[i*n+j + 7] += Aik * B[k*n+j + 7];
            }
          }
        }
      }
    }
  }
}

/**
 *  Funcao checa_resultado:  Verifica se os resultados da versao nao otimizada e otimizada sao iguais
 *  @param A vetor A
 *  @param B vetor B
 *  @param n número de colunas da matriz
 *
 */
void checaResultadoVetor (Vetor A, Vetor B, int n) {
  int i;
  double erro = 0.001;

  for(i=0; i < n; ++i) {
    if(fabs(A[i] - B[i]) >= erro) {
      fprintf(stderr, "Erro na função multMatVet...\nAlgum valor não está batendo! Verifique os resultados:\nA[%i]: %f\nB[%i]: %f\n\n", i, A[i], i, B[i]);
      exit(1);
    }
  }
  printf("\nO resultado bateu! :)\n\n");
}

/**
 *  Funcao checa_resultado:  Verifica se os resultados da versao nao otimizada e otimizada sao iguais
 *  @param A matriz A
 *  @param B matriz B
 *  @param n número de colunas da matriz
 *
 */
void checaResultadoMatriz (MatRow A, MatRow B, int n) {
  int i;
  double erro = 0.001;

  for(i=0; i < n*n; ++i) {
    if(fabs(A[i] - B[i]) >= erro) {
      fprintf(stderr, "Erro na função multMatMatOtimizado...\nAlgum valor não está batendo! Verifique os resultados:\nA[%i]: %f\nB[%i]: %f\n\n", i, A[i], i, B[i]);
      exit(1);
    }
  }
  printf("\nO resultado bateu! :)\n\n");
}

/**
 *  Funcao prnMat:  Imprime o conteudo de uma matriz em stdout
 *  @param mat matriz
 *  @param m número de linhas da matriz
 *  @param n número de colunas da matriz
 *
 */

void prnMat (MatRow mat, int m, int n)
{
  for (int i=0; i < m; ++i) {
    for (int j=0; j < n; ++j)
      printf(DBL_FIELD, mat[n*i + j]);
    printf("\n");
  }
  printf(SEP_RES);
}

/**
 *  Funcao prnVetor:  Imprime o conteudo de vetor em stdout
 *  @param vet vetor com 'n' elementos
 *  @param n número de elementos do vetor
 *
 */

void prnVetor (Vetor vet, int n)
{
  for (int i=0; i < n; ++i)
    printf(DBL_FIELD, vet[i]);
  printf(SEP_RES);
}

