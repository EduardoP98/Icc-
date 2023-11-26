/*
  Alunos: 
  Eduardo Purkote (GRR20182960)
  Mariana Moreira dos Santos (GRR20186554)
*/

#include <stdio.h>
#include <stdlib.h>
#include <fenv.h>
#include <math.h>
#include "interval.h"
#include "doubleType.h"

/*  
  Seja x um valor real qualquer. A representacao intervalar de e dada por X = [m(x), M(X)] onde
  m(x): maior numero de maquina menor ou igual a x
  M(x): menor numero de maquina maior ou igual a x

  A funcao recebe um valor x do tipo Double_t e retorna o intervalo de representacao [m, M]
*/
INTERVAL_t calcula_intervalo (Double_t x) {
  INTERVAL_t intervalo;

  // Define o modo de arredondamento para baixo
  fesetround(FE_DOWNWARD);

  // Retorna o próximo numero de maquina na direcao negativa a partir de x, o que corresponde a m(x).
  intervalo.m.f = nextafter(x.f, -INFINITY);

  // Restaura o modo de arredondamento para cima
  fesetround(FE_UPWARD);
 
  // Retorna o próximo numero de maquina na direcao positiva a partir de x, o que corresponde a M(x).
  intervalo.M.f = nextafter(x.f, INFINITY);
  
  // Restaura o modo de arredondamento padrao
  fesetround(FE_TONEAREST);

  return intervalo;
}


/*  
  Calcula a soma entre dois intervalos

  Seja 
    X = [a,b]
    Y = [c,d]
  Entao
    X + Y = [a+c, b+d]

  a = x.m.f
  b = x.M.f
  c = y.m.f
  d = y.M.f
*/
INTERVAL_t calcula_soma(INTERVAL_t x, INTERVAL_t y) {
  INTERVAL_t resultado;

  fesetround(FE_DOWNWARD);
  resultado.m.f  = x.m.f + y.m.f;

  fesetround(FE_UPWARD);
  resultado.M.f  = x.M.f + y.M.f;

  return resultado;
}

/*  
  Calcula a subtracao entre dois intervalos

  Seja 
    X = [a, b]
    Y = [c, d]
  Entao
    X - Y = [a-d, b-c]

  a = x.m.f
  b = x.M.f
  c = y.m.f
  d = y.M.f
*/
INTERVAL_t calcula_subtracao(INTERVAL_t x, INTERVAL_t y) {
  INTERVAL_t resultado;

  fesetround(FE_DOWNWARD);
  resultado.m.f= x.m.f - y.M.f;

  fesetround(FE_UPWARD);
  resultado.M.f = x.M.f - y.m.f;

  return resultado;
}

/*  
  Calcula a divisao entre dois intervalos

  Seja 
    X = [a, b]
    Y = [c, d]
  Entao
    X / Y = [a, b] * [1/d, 1/c], se 0 nao pertence ao intervalo Y

  Para simplificar, considere que se 0 (zero) pertence a Y, 
  entao X / Y = [-inf, +inf], para qualquer intervalo X.

  a = x.m.f
  b = x.M.f
  c = y.m.f
  d = y.M.f
*/
INTERVAL_t calcula_div(INTERVAL_t x, INTERVAL_t y) {
  INTERVAL_t resultado; 

  // Verifica se 0 pertence ao intervalo Y
  if (y.m.f <= 0 && y.M.f >= 0) {
    resultado.m.f = -INFINITY;
    resultado.M.f = INFINITY;
  }
  else if (y.m.f == 0) {
    resultado.m.f = -INFINITY;
    resultado.M.f = INFINITY;
  }
  else {
    fesetround(FE_DOWNWARD);
    resultado.m.f = fmin(x.m.f / y.M.f, fmin(x.M.f / y.M.f, fmin(x.m.f / y.m.f, x.M.f / y.m.f)));
    fesetround(FE_UPWARD);
    resultado.M.f = fmax(x.m.f / y.M.f, fmax(x.M.f / y.M.f, fmax(x.m.f / y.m.f, x.M.f / y.m.f)));
  }
  return resultado;
}

/*  
  Calcula a multiplicacao entre dois intervalos

  Seja 
    X = [a, b]
    Y = [c, d]
  Entao
    X * Y = [a,b] * [c,d] = [min{a*c,a*d,b*c,b*d}, max{a*c,a*d,b*c,b*d}]

  a = x.m.f
  b = x.M.f
  c = y.m.f
  d = y.M.f
*/
INTERVAL_t calcula_mult(INTERVAL_t x, INTERVAL_t y) {
  INTERVAL_t resultado;

  fesetround(FE_DOWNWARD);
  double result1 = x.m.f * y.m.f;
  double result2 = x.m.f * y.M.f;

  fesetround(FE_UPWARD);
  double result3 = x.M.f * y.m.f;
  double result4 = x.M.f * y.M.f;

  resultado.m.f = fmin(fmin(result1, result2), fmin(result3, result4));
  resultado.M.f = fmax(fmax(result1, result2), fmax(result3, result4));

  return resultado;
}


/*  
  Calcula a potenciacao entre dois intervalos

  A definicao de um intervalo X = [a,b] elevado a um numero inteiro p ≥ 0 eh dado por:

  [a,b]^p = 
    [1,1] se p = 0
    [a^p, b^p] se p eh impar
    [a^p, b^p] se p eh par e a ≥ 0
    [b^p, a^p] se p eh par e b < 0
    [0, max{a^p,b^p}] se p eh par e a < 0 ≤ b 

  a = x.m.f
  b = x.M.f
  c = y.m.f
  d = y.M.f
*/
INTERVAL_t calcula_pot(INTERVAL_t x, long long int p) {
  INTERVAL_t resultado;

  if(p == 0) {
    // Caso p = 0, o resultado eh [1, 1]
    resultado.m.f = 1.0;
    resultado.M.f = 1.0;
  }
  else if(p % 2 != 0) {
    // Caso p eh impar, o resultado eh [x.m^p, x.M^p]
    resultado.m.f = pow(x.m.f, p);
    resultado.M.f = pow(x.M.f, p);
  }
  else {
    if(x.m.f >= 0 ) {
      // Caso p eh par e x.m >= 0, o resultado eh [x.m^p, x.M^p]
      resultado.m.f = pow(x.m.f, p);
      resultado.M.f = pow(x.M.f, p);
    }
    else if(x.M.f < 0) {
      // Caso p eh par e x.M < 0, o resultado eh [x.M^p, x.m^p]
      resultado.m.f = pow(x.M.f, p);
      resultado.M.f = pow(x.m.f, p);
    }
    else if((x.M.f >= 0) && (x.m.f < 0)) {
      // Caso p eh par, x.m < 0 e x.M >= 0, o resultado eh [0, max{x.m^p, x.M^p}]
      double m_pow_p = pow(x.m.f, p);
      double M_pow_p = pow(x.M.f, p);
      resultado.m.f = 0.0;
      resultado.M.f = fmax(m_pow_p, M_pow_p);
    }
  }

  return resultado;
}

/*  
  Calcula a potenciacao entre dois intervalos sem a utilizacao da funcao pow()

  A definicao de um intervalo X = [a,b] elevado a um numero inteiro p ≥ 0 eh dado por:

  [a,b]^p = 
    [1,1] se p = 0
    [a^p, b^p] se p eh impar
    [a^p, b^p] se p eh par e a ≥ 0
    [b^p, a^p] se p eh par e b < 0
    [0, max{a^p,b^p}] se p eh par e a < 0 ≤ b 

  a = x.m.f
  b = x.M.f
  c = y.m.f
  d = y.M.f
*/
INTERVAL_t calcula_pot_otimizado(INTERVAL_t x, long long int p) {
  INTERVAL_t resultado;
  resultado.m.f = 1.0;
  resultado.M.f = 1.0;

  if(p == 0) {
    // Caso p = 0, o resultado eh [1, 1]
    resultado.m.f = 1.0;
    resultado.M.f = 1.0;
  }
  else if(p % 2 != 0) {
    // Caso p eh impar, o resultado eh [x.m^p, x.M^p]
    for (int i = 0; i < p; i++) {
        resultado.m.f *= x.m.f;
        resultado.M.f *= x.M.f;
    }
  }
  else {
    if(x.m.f >= 0 ) {
      // Caso p eh par e x.m >= 0, o resultado eh [x.m^p, x.M^p]
      for (int i = 0; i < p; i++) {
        resultado.m.f *= x.m.f;
        resultado.M.f *= x.M.f;
      }
    }
    else if(x.M.f < 0) {
      // Caso p eh par e x.M < 0, o resultado eh [x.M^p, x.m^p]
      for (int i = 0; i < p; i++) {
        resultado.m.f *= x.M.f;
        resultado.M.f *= x.m.f;
      }
    }
    else if((x.M.f >= 0) && (x.m.f < 0)) {
      // Caso p eh par, x.m < 0 e x.M >= 0, o resultado eh [0, max{x.m^p, x.M^p}]
      double m_pow_p = 1.0; double M_pow_p = 1.0;

      for (int i = 0; i < p; i++) {
        m_pow_p *= x.m.f;
        M_pow_p *= x.M.f;
      }

      resultado.m.f = 0.0;
      resultado.M.f = fmax(m_pow_p, M_pow_p);
    }
  }

  return resultado;
}