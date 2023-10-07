#include "doubleType.h"

#ifndef INTERVAL_H_
#define INTERVAL_H_

typedef struct
{
  Double_t m,M;

}INTERVAL_t;

INTERVAL_t calcula_intervalo (Double_t x);

// Calcula Soma entre dois intervalos
INTERVAL_t calcula_soma(INTERVAL_t x, INTERVAL_t y);

// Calcula subtração entre dois intervalos
INTERVAL_t calcula_subtracao(INTERVAL_t x, INTERVAL_t y);

// Calcula Divisão entre dois intervalos
INTERVAL_t calcula_div(INTERVAL_t x, INTERVAL_t y);

// Calcula Multiplicação entre dois intervalos
INTERVAL_t calcula_mult(INTERVAL_t x, INTERVAL_t y);

// Calcula a Potência de um intervalo
INTERVAL_t calcula_pot(INTERVAL_t x,int p);


// Função para calcular o valor absoluto de um intervalo
INTERVAL_t calcula_abs(INTERVAL_t x);


// Função para calcular o maior entre dois intervalos
int calcula_maior(INTERVAL_t x, INTERVAL_t y);


#endif