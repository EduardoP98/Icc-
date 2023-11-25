#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"

#define DIFF 0.0

#define NRAND    ((double) rand() / RAND_MAX)  // drand48() 
#define SRAND(a) srand(a) // srand48(a)

#define UF 4

// Integral Monte Carlo da função Styblinski-Tang
double styblinskiTang(double a, double b, int namostras, int n_variaveis)
{
  double resultado = 0.0;
  double soma = 0.0;
  
  printf("Metodo de Monte Carlo (x, y).\n");
  printf("a = (%f), b = (%f), n = (%d), variaveis = %d\n", a, b, namostras, n_variaveis);
  
  double t_inicial = timestamp();

  // Comprimento do intervalo de integracao: intervalo [a, b]
  #ifdef _DEBUG_
  printf("Intervalo [%lf, %lf]: %lf\n", a, b, b - a);
  #endif

  // Para 2 variaveis
  if (n_variaveis == 2) {
    for (int i = 0; i < namostras; ++i) {
      // Gera um valor aleatorio para x1 e x2 dentro do intervalo [a, b]
      double x1 = a + NRAND * (b - a);
      double x2 = a + NRAND * (b - a);

      // Utiliza a funcao Styblinski-Tang com os valores aleatorios
      soma += (((x1*x1*x1*x1) - (16*x1*x1) + (5*x1))/2) + (((x2*x2*x2*x2) - (16*x2*x2) + (5*x2))/2);

    }

    // Integracao pela media
    resultado = (soma / namostras) * (b - a) * (b - a);
  } 
  // Para 4 variaveis
  else if (n_variaveis == 4) {
    for (int i = 0; i < namostras; ++i) {
      // Gera um valor aleatorio para x1 a x4 dentro do intervalo [a, b]
      double x1 = a + NRAND * (b - a);
      double x2 = a + NRAND * (b - a);
      double x3 = a + NRAND * (b - a);
      double x4 = a + NRAND * (b - a);

      // Utiliza a funcao Styblinski-Tang com os valores aleatorios
      soma += (((x1*x1*x1*x1) - (16*x1*x1) + (5*x1))/2) + 
              (((x2*x2*x2*x2) - (16*x2*x2) + (5*x2))/2) +
              (((x3*x3*x3*x3) - (16*x3*x3) + (5*x3))/2) +
              (((x4*x4*x4*x4) - (16*x4*x4) + (5*x4))/2);
    }

    // Integracao pela media
    resultado = (soma / namostras) * ((b - a) * (b - a) * (b - a) * (b - a));
  } 
  // Para 8 variaveis
  else {
    for (int i = 0; i < namostras; ++i) {
      // Gera um valor aleatorio para x1 a x8 dentro do intervalo [a, b]
      double x1 = a + NRAND * (b - a);
      double x2 = a + NRAND * (b - a);
      double x3 = a + NRAND * (b - a);
      double x4 = a + NRAND * (b - a);
      double x5 = a + NRAND * (b - a);
      double x6 = a + NRAND * (b - a);
      double x7 = a + NRAND * (b - a);
      double x8 = a + NRAND * (b - a);

      // Utiliza a funcao Styblinski-Tang com os valores aleatorios
      soma += (((x1*x1*x1*x1) - (16*x1*x1) + (5*x1))/2) + 
              (((x2*x2*x2*x2) - (16*x2*x2) + (5*x2))/2) +
              (((x3*x3*x3*x3) - (16*x3*x3) + (5*x3))/2) +
              (((x4*x4*x4*x4) - (16*x4*x4) + (5*x4))/2) +
              (((x5*x5*x5*x5) - (16*x5*x5) + (5*x5))/2) +
              (((x6*x6*x6*x6) - (16*x6*x6) + (5*x6))/2) +
              (((x7*x7*x7*x7) - (16*x7*x7) + (5*x7))/2) +
              (((x8*x8*x8*x8) - (16*x8*x8) + (5*x8))/2);
    }

    // Integracao pela media
    resultado = (soma / namostras) * ((b - a) * (b - a) * (b - a) * (b - a) * (b - a) * (b - a) * (b - a) * (b - a));
  }
  
  double t_final = timestamp();
  printf("Tempo decorrido: %f seg.\n", t_final - t_inicial);
  
  // Resultado
  #ifdef _DEBUG_
  printf("Soma: %lf\n", soma);
  #endif

  return resultado;
}


double retangulos_xy(double a, double b, int npontos) {
  double h = (b - a) / npontos; 

  double resultado = 0;
  double soma = 0;
  
  printf("Metodo dos Retangulos (x, y).\n");
  printf("a = (%f), b = (%f), n = (%d), h = (%lg)\n", a, b, npontos, h);
  
  double t_inicial = timestamp();

  for (int i = a; i < npontos; i++) {
    double x1 = a + i*h;
    for (int j = 0; j < npontos; j++) {
      double x2 = a + j*h;
      soma += (((x1*x1*x1*x1) - (16*x1*x1) + (5*x1))/2) + (((x2*x2*x2*x2) - (16*x2*x2) + (5*x2))/2);
    }
  }

  resultado = soma * h * h;
  
  double t_final = timestamp();
  printf("Tempo decorrido: %f seg.\n", t_final - t_inicial);

  return resultado;
}

double retangulos_xy_otimizado(double a, double b, int npontos) {
  double h = (b - a) / npontos; 

  double resultado = 0;
  double soma = 0;
  
  printf("Metodo dos Retangulos (x, y).\n");
  printf("a = (%f), b = (%f), n = (%d), h = (%lg)\n", a, b, npontos, h);
  
  // Residuo para loop unroll
  int residuo = (npontos % UF);

  double t_inicial = timestamp();

  // Lop unroll com fator 4
  for (int i = 0; i < npontos - residuo; i += UF) {
    double x1_1 = a + i * h;
    double x1_2 = a + (i + 1) * h;
    double x1_3 = a + (i + 2) * h;
    double x1_4 = a + (i + 3) * h;

    for (int j = 0; j < npontos - residuo; j += UF) {
      double x2_1 = a + j * h;
      double x2_2 = a + (j + 1) * h;
      double x2_3 = a + (j + 2) * h;
      double x2_4 = a + (j + 3) * h;

      soma += (((x1_1*x1_1*x1_1*x1_1) - (16*x1_1*x1_1) + (5*x1_1))/2) + (((x2_1*x2_1*x2_1*x2_1) - (16*x2_1*x2_1) + (5*x2_1))/2) +
              (((x1_1*x1_1*x1_1*x1_1) - (16*x1_1*x1_1) + (5*x1_1))/2) + (((x2_2*x2_2*x2_2*x2_2) - (16*x2_2*x2_2) + (5*x2_2))/2) +
              (((x1_1*x1_1*x1_1*x1_1) - (16*x1_1*x1_1) + (5*x1_1))/2) + (((x2_3*x2_3*x2_3*x2_3) - (16*x2_3*x2_3) + (5*x2_3))/2) +
              (((x1_1*x1_1*x1_1*x1_1) - (16*x1_1*x1_1) + (5*x1_1))/2) + (((x2_4*x2_4*x2_4*x2_4) - (16*x2_4*x2_4) + (5*x2_4))/2) +
              (((x1_2*x1_2*x1_2*x1_2) - (16*x1_2*x1_2) + (5*x1_2))/2) + (((x2_1*x2_1*x2_1*x2_1) - (16*x2_1*x2_1) + (5*x2_1))/2) +
              (((x1_2*x1_2*x1_2*x1_2) - (16*x1_2*x1_2) + (5*x1_2))/2) + (((x2_2*x2_2*x2_2*x2_2) - (16*x2_2*x2_2) + (5*x2_2))/2) +
              (((x1_2*x1_2*x1_2*x1_2) - (16*x1_2*x1_2) + (5*x1_2))/2) + (((x2_3*x2_3*x2_3*x2_3) - (16*x2_3*x2_3) + (5*x2_3))/2) +
              (((x1_2*x1_2*x1_2*x1_2) - (16*x1_2*x1_2) + (5*x1_2))/2) + (((x2_4*x2_4*x2_4*x2_4) - (16*x2_4*x2_4) + (5*x2_4))/2) +
              (((x1_3*x1_3*x1_3*x1_3) - (16*x1_3*x1_3) + (5*x1_3))/2) + (((x2_1*x2_1*x2_1*x2_1) - (16*x2_1*x2_1) + (5*x2_1))/2) +
              (((x1_3*x1_3*x1_3*x1_3) - (16*x1_3*x1_3) + (5*x1_3))/2) + (((x2_2*x2_2*x2_2*x2_2) - (16*x2_2*x2_2) + (5*x2_2))/2) +
              (((x1_3*x1_3*x1_3*x1_3) - (16*x1_3*x1_3) + (5*x1_3))/2) + (((x2_3*x2_3*x2_3*x2_3) - (16*x2_3*x2_3) + (5*x2_3))/2) +
              (((x1_3*x1_3*x1_3*x1_3) - (16*x1_3*x1_3) + (5*x1_3))/2) + (((x2_4*x2_4*x2_4*x2_4) - (16*x2_4*x2_4) + (5*x2_4))/2) +
              (((x1_4*x1_4*x1_4*x1_4) - (16*x1_4*x1_4) + (5*x1_4))/2) + (((x2_1*x2_1*x2_1*x2_1) - (16*x2_1*x2_1) + (5*x2_1))/2) +
              (((x1_4*x1_4*x1_4*x1_4) - (16*x1_4*x1_4) + (5*x1_4))/2) + (((x2_2*x2_2*x2_2*x2_2) - (16*x2_2*x2_2) + (5*x2_2))/2) +
              (((x1_4*x1_4*x1_4*x1_4) - (16*x1_4*x1_4) + (5*x1_4))/2) + (((x2_3*x2_3*x2_3*x2_3) - (16*x2_3*x2_3) + (5*x2_3))/2) +
              (((x1_4*x1_4*x1_4*x1_4) - (16*x1_4*x1_4) + (5*x1_4))/2) + (((x2_4*x2_4*x2_4*x2_4) - (16*x2_4*x2_4) + (5*x2_4))/2);
    }
  }

  // Tratando o residuo do loop unroll
  for (int i = npontos - residuo; i < npontos; ++i) {  
    double x1 = a + h * i;    
    for (int j = npontos - residuo; j < npontos; ++j) {
      double x2 = a + h * j;
      soma += (((x1*x1*x1*x1) - (16*x1*x1) + (5*x1))/2) + (((x2*x2*x2*x2) - (16*x2*x2) + (5*x2))/2);
    }
  }

  resultado = soma * h * h;
  
  double t_final = timestamp();
  printf("Tempo decorrido: %f seg.\n", t_final - t_inicial);

  return resultado;
}

int main(int argc, char **argv) {
  // LEITURA DA ENTRADA
  if (argc < 5) {
    printf("Utilização: %s inicial final n_amostras n_variaveis\n", argv[0]);
    return 1;
  } 

  int inicial = atoi(argv[1]);
  int final = atoi(argv[2]);
  int n_amostras = atoi(argv[3]);
  int n_variaveis = atoi(argv[4]);

  #ifdef _DEBUG_
  printf("Leitura dos argumentos de entrada\ninicial: %d\nfinal: %d\nn_amostras: %d\nn_variaveis: %d\n\n", inicial, final, n_amostras, n_variaveis);
  #endif

  // INICIAR VALOR DA SEMENTE
  int seed = 20232;
  SRAND(seed);

  #ifdef _DEBUG_
  printf("Semente\nValor da semente: %d\n\n", seed);
  #endif

  // CHAMAR FUNÇÕES DE INTEGRAÇÃO E EXIBIR RESULTADOS
  // double retangulo = 0.0f;
  double retangulo_otimizado = 0.0f;
  double monteCarlo = 0.0f;

  // retangulo = retangulos_xy (inicial, final, n_amostras);
  // printf("Método dos Retângulados: %lf\n\n", retangulo);

  retangulo_otimizado = retangulos_xy_otimizado (inicial, final, n_amostras);
  printf("Método dos Retângulados - Otimizado: %lf\n\n", retangulo_otimizado);

  monteCarlo = styblinskiTang (inicial, final, n_amostras, n_variaveis);
  printf("Método de Monte Carlo: %lf\n\n", monteCarlo);
 
  return 0;
}

