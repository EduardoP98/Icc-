#include <stdio.h>
#include <stdlib.h>
#include <fenv.h>
#include <math.h>
#include "interval.h"
#include "doubleType.h"

/*  
  Seja x um valor real qualquer. A representacao intervalar de e dada por X = [m(x), M(X)] onde
  m(x): maior numero de maquina menor ou igual a x
  M(x): menor número de máquina maior ou igual a x
*/
INTERVAL_t calcula_intervalo (Double_t x)
{
  // Retorna o próximo número de máquina na direção positiva a partir de x, o que corresponde a m(x).

  INTERVAL_t intervalo;
  //Define o modo de arredondamento para baixo
  fesetround(FE_DOWNWARD);


  intervalo.m.f = nextafter(x.f,-INFINITY);

  
  // Restaura o modo de arredondamento padrão
  fesetround(FE_UPWARD);
 
  intervalo.M.f = nextafter(x.f,INFINITY);
  
  fesetround(FE_TONEAREST);

  return intervalo;
  
}

// Cálculo das operações intervalares


// Calcula Soma entre dois intervalos
INTERVAL_t calcula_soma(INTERVAL_t x, INTERVAL_t y)
{
  INTERVAL_t resultado;

  fesetround(FE_DOWNWARD);
  resultado.m.f  = x.m.f + y.m.f;

  fesetround(FE_UPWARD);
  resultado.M.f  = x.M.f + y.M.f;

  return resultado;

}

// Calcula subtração entre dois intervalos
INTERVAL_t calcula_subtracao(INTERVAL_t x, INTERVAL_t y)
{
  INTERVAL_t resultado;

  fesetround(FE_DOWNWARD);
  resultado.m.f= x.m.f - y.m.f;

  fesetround(FE_UPWARD);
  resultado.M.f = x.M.f - y.M.f;

  return resultado;
}

// Calcula Divisão entre dois intervalos
INTERVAL_t calcula_div(INTERVAL_t x, INTERVAL_t y)
{
  INTERVAL_t resultado; 
  if (y.m.f <= 0 && y.M.f >= 0)
  {
    resultado.m.f = -INFINITY;
    resultado.M.f = INFINITY;
  }
  else if (y.m.f == 0)
  {
    resultado.m.f = -INFINITY;
    resultado.M.f = INFINITY;
  }
  else
  {
    fesetround(FE_DOWNWARD);
    resultado.m.f = fminf(fminf(x.m.f / y.m.f, x.m.f / y.M.f), fminf(x.M.f / y.m.f, x.M.f / y.M.f));
    fesetround(FE_UPWARD);
    resultado.M.f = fmaxf(fmaxf(x.m.f / y.m.f, x.m.f / y.M.f), fmaxf(x.M.f / y.m.f, x.M.f / y.M.f));
  }
  return resultado;
}

// Calcula Multiplicação entre dois intervalos
INTERVAL_t calcula_mult(INTERVAL_t x, INTERVAL_t y)
{
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


// Calcula a Potência de um intervalo
INTERVAL_t calcula_pot(INTERVAL_t x, int p)
{
  INTERVAL_t resultado;
  if(p == 0)
  {
    // Caso p = 0, o resultado é [1, 1]
    resultado.m.f = 1.0;
    resultado.M.f = 1.0;
  }
  else if(p % 2 != 0)
  {
    // Caso p é ímpar, o resultado é [x.m^p, x.M^p]
    resultado.m.f = pow(x.m.f, p);
    resultado.M.f = pow(x.M.f, p);
  }
  else
  {
    if(x.m.f >= 0 )
    {
      // Caso p é par e x.m >= 0, o resultado é [x.m^p, x.M^p]
      resultado.m.f = pow(x.m.f, p);
      resultado.M.f = pow(x.M.f, p);
    }
    else if(x.M.f < 0)
    {
      // Caso p é par e x.M < 0, o resultado é [x.M^p, x.m^p]
      resultado.m.f = pow(x.M.f, p);
      resultado.M.f = pow(x.m.f, p);
    }
    else if((x.M.f >= 0)&&(x.m.f < 0))
    {
      // Caso p é par, x.m < 0 e x.M >= 0, o resultado é [0, max{x.m^p, x.M^p}]
      double m_pow_p = pow(x.m.f, p);
      double M_pow_p = pow(x.M.f, p);
      resultado.m.f = 0.0;
      resultado.M.f = fmax(m_pow_p, M_pow_p);
    }
  }

  return resultado;
}


/*
    1-Fazer uma função de cálculo intervalar para cada tipo de operação (+,-,/,* e potenciação) -> OK
    2-Em seguida implementar Método dos Mínimos Quadrados -> OK
    3-Implementar Funções de Sistema Linear com cálculo Intervalar (trocaLinha,encontraMax,retrossubs, elimgauss,calculaResiduo(por último))


    SL Original
    SL Método de Gauss
    Residuo = Substituir Resposta Gauss no SL original e comparar com Vetor B (Subtrair por B) ->  DESVIO DA RESPOSTA
*/
