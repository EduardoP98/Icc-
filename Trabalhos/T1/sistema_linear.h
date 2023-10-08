/*
  Aunos: 
  Eduardo Purkote (GRR20182960)
  Mariana Moreira dos Santos (GRR20186554)
  
*/
#include "interval.h"
#ifndef  SISTEMA_LINEAR_H
#define  SISTEMA_LINEAR_H


typedef struct
{
  int n;
  INTERVAL_t **A;
  INTERVAL_t *b;
  INTERVAL_t *x;
  INTERVAL_t residuo;

} SISTEMA_LINEAR_t;



void retrosubs(INTERVAL_t **A, INTERVAL_t *b, INTERVAL_t *x, int n);

void imprime_sistema_linear(SISTEMA_LINEAR_t *SL);

void libera_sistema_linear(SISTEMA_LINEAR_t *SL);

SISTEMA_LINEAR_t *aloca_sistema_linear(int n);

unsigned int encontraMax(INTERVAL_t **A, int i, int n);

void trocaLinha(INTERVAL_t **A, INTERVAL_t *b, int i, int iPivo, int n);

void elimGauss_parcial(INTERVAL_t **A, INTERVAL_t *b, INTERVAL_t *x, int n);

double calculaResiduo(double **A, double *b, double *x, int n);

void copiaSistemaLinear(const SISTEMA_LINEAR_t *origem, SISTEMA_LINEAR_t *destino);

#endif