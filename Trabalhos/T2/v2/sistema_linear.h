/*
  Alunos: 
  Eduardo Purkote (GRR20182960)
  Mariana Moreira dos Santos (GRR20186554)
*/

#include "interval.h"
#include "tabela.h"
#ifndef  SISTEMA_LINEAR_H
#define  SISTEMA_LINEAR_H

#define UF 2

/*  
  Estrutura de dados utilizada para definicao do sistema linear

  Matriz A: matriz de coeficientes
  Vetor B: vetor de constantes
  Vetor X: vetor de incognitas/solucao (contera os valores dos coeficientes ao final)

*/
typedef struct {
  int n;
  INTERVAL_t **A;
  INTERVAL_t *b;
  INTERVAL_t *x;
} SISTEMA_LINEAR_t;


// Imprime o sistema linear (matriz A, vetor B e vetor X)
void imprime_sistema_linear(SISTEMA_LINEAR_t *SL);

// Liberacao de memoria alocada das variaveis
void libera_sistema_linear(SISTEMA_LINEAR_t *SL);

// Libera SL otimizado
void libera_sistema_linear_otimizado(SISTEMA_LINEAR_t *SL);

// Alocacao de memoria das variaveis
SISTEMA_LINEAR_t *aloca_sistema_linear( int n);

//Alocação Otimizada
SISTEMA_LINEAR_t *aloca_sistema_linear_otimizado( int n);

// Resolve um sistema linear triangular por retrosubstituicao
void retrosubs(INTERVAL_t **A, INTERVAL_t *b, INTERVAL_t *x, int n);

// Encontrar a linha com o maior valor absoluto na coluna i
unsigned int encontra_max(INTERVAL_t **A,  int i,  int n);

//  Troca duas linhas da matriz A e vetor b
void troca_linha(INTERVAL_t **A, INTERVAL_t *b,  int i, unsigned  int iPivo,  int n);

// Eliminacao de Gauss com Pivoteamento Parcial
void elimGauss_parcial(INTERVAL_t **A, INTERVAL_t *b, INTERVAL_t *x,  int n);

// Calcula o valor estimado dado um vetor de coeficientes
INTERVAL_t calcula_valor_estimado(INTERVAL_t *coeficientes, INTERVAL_t x,  int n);
// INTERVAL_t calcula_valor_estimado_otimizado(INTERVAL_t *coeficientes, INTERVAL_t x,  int n);

// Calcula o residuo entre a tabela de pontos e a equacao de ajuste
void calcula_residuo(TABELA_t *tabela, INTERVAL_t *coeficientes, INTERVAL_t *residuos,  int g);

void calcula_residuo_otimizado(TABELA_t *tabela, INTERVAL_t *coeficientes, INTERVAL_t *residuos,  int n);

// Imprime o residuo na formatacao de entrega definida pelo professor
void imprime_residuo(INTERVAL_t *residuo, int n);

// Imprime os coeficientes na formatacao de entrega definida pelo professor
void imprime_coef(SISTEMA_LINEAR_t *SL);

#endif