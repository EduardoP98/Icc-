/*
  Aunos: 
  Eduardo Purkote (GRR20182960)
  Mariana Moreira dos Santos (GRR20186554)
  
*/

#include "doubleType.h"
#ifndef INTERVAL_H_
#define INTERVAL_H_

typedef struct {
  // m: maior número de máquina menor ou igual a x
  Double_t m; 
  
  // M: é o menor número de máquina maior ou igual a x
  Double_t M;
} INTERVAL_t;

INTERVAL_t calcula_intervalo (Double_t x);

// Calcula a soma entre dois intervalos
INTERVAL_t calcula_soma(INTERVAL_t x, INTERVAL_t y);

// Calcula a subtração entre dois intervalos
INTERVAL_t calcula_subtracao(INTERVAL_t x, INTERVAL_t y);

// Calcula a divisão entre dois intervalos
INTERVAL_t calcula_div(INTERVAL_t x, INTERVAL_t y);

// Calcula a multiplicação entre dois intervalos
INTERVAL_t calcula_mult(INTERVAL_t x, INTERVAL_t y);

// Calcula a potência de um intervalo
INTERVAL_t calcula_pot(INTERVAL_t x,int p);

// Função para calcular o valor absoluto de um intervalo
INTERVAL_t calcula_abs(INTERVAL_t x);

// Função para calcular o maior entre dois intervalos
int calcula_maior(INTERVAL_t x, INTERVAL_t y);

#endif