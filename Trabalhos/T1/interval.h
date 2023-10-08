/*
  Alunos: 
  Eduardo Purkote (GRR20182960)
  Mariana Moreira dos Santos (GRR20186554)
*/

#include "doubleType.h"
#ifndef INTERVAL_H_
#define INTERVAL_H_

/*  
  Estrutura de dados utilizada para armazenar o intervalo de representacao dos numeros

  Dado um numero X qualquer
  m: maior numero de maquina menor ou igual a x
  M: é o menor numero de maquina maior ou igual a x

*/
typedef struct {
  Double_t m; 
    Double_t M;
} INTERVAL_t;

// Dado um numero x retorna o intervalo de representacao [m(x), M(x)]
INTERVAL_t calcula_intervalo (Double_t x);

// Calcula a soma entre dois intervalos
INTERVAL_t calcula_soma(INTERVAL_t x, INTERVAL_t y);

// Calcula a subtracao entre dois intervalos
INTERVAL_t calcula_subtracao(INTERVAL_t x, INTERVAL_t y);

// Calcula a divisao entre dois intervalos
INTERVAL_t calcula_div(INTERVAL_t x, INTERVAL_t y);

// Calcula a multiplicacao entre dois intervalos
INTERVAL_t calcula_mult(INTERVAL_t x, INTERVAL_t y);

// Calcula a potencia de um intervalo
INTERVAL_t calcula_pot(INTERVAL_t x,int p);

#endif