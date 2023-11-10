#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"

#define DIFF 0.0

#define NRAND    ((double) rand() / RAND_MAX)  // drand48() 
#define SRAND(a) srand(a) // srand48(a)

#define UF 4

// Integral Monte Carlo da função Styblinski-Tang de 2 variáveis
double styblinskiTang(double a, double b, int namostras, int n_variaveis)
{
  double resultado;
  double soma = 0.0;
  
  printf("Metodo de Monte Carlo (x, y).\n");
  printf("a = (%f), b = (%f), n = (%d), variaveis = %d\n", a, b, namostras, n_variaveis);
  
  double t_inicial = timestamp();
  double diff = b - a;

  // Para 2 variaveis
  if (n_variaveis == 2) {
    for (int i = 0; i < namostras; ++i) {
      // Gera um valor aleatorio para x1 e x2 dentro do intervalo [a, b]
      double x1 = a + NRAND * diff;
      double x2 = a + NRAND * diff;
      // Utiliza a funcao Styblinski-Tang com os valores aleatorios
      soma += x1 * (x1 * x1 * x1 - x1 * 16 + 5) + x2 * (x2 * x2 * x2 - x2 * 16 + 5);
    }

    // Calcula a media do resultado
    resultado = (soma / namostras) * diff;
  } 
  // Para 4 variaveis
  else if (n_variaveis == 4) {
    diff = b - a;
    for (int i = 0; i < namostras; ++i) {
      // Gera um valor aleatorio para x1 a x4 dentro do intervalo [a, b]
      double x1 = a + NRAND * diff;
      double x2 = a + NRAND * diff;
      double x3 = a + NRAND * diff;
      double x4 = a + NRAND * diff;

      // Utiliza a funcao Styblinski-Tang com os valores aleatorios
      soma += x1 * (x1 * x1 * x1 - x1 * 16 + 5) + x2 * (x2 * x2 * x2 - x2 * 16 + 5) +
              x3 * (x3 * x3 * x3 - x3 * 16 + 5) + x4 * (x4 * x4 * x4 - x4 * 16 + 5);
    }

    // Calcula a media do resultado
    resultado = (soma / namostras) * (diff * diff * diff);
  } 
  // Para 8 variaveis
  else {
    diff = b - a;
    for (int i = 0; i < namostras; ++i) {
      // Gera um valor aleatorio para x1 a x8 dentro do intervalo [a, b]
      double x1 = a + NRAND * diff;
      double x2 = a + NRAND * diff;
      double x3 = a + NRAND * diff;
      double x4 = a + NRAND * diff;
      double x5 = a + NRAND * diff;
      double x6 = a + NRAND * diff;
      double x7 = a + NRAND * diff;
      double x8 = a + NRAND * diff;

      // Utiliza a funcao Styblinski-Tang com os valores aleatorios
      soma += x1 * (x1 * x1 * x1 - x1 * 16 + 5) + x2 * (x2 * x2 * x2 - x2 * 16 + 5) +
              x3 * (x3 * x3 * x3 - x3 * 16 + 5) + x4 * (x4 * x4 * x4 - x4 * 16 + 5) +
              x5 * (x5 * x5 * x5 - x5 * 16 + 5) + x6 * (x6 * x6 * x6 - x6 * 16 + 5) +
              x7 * (x7 * x7 * x7 - x7 * 16 + 5) + x8 * (x8 * x8 * x8 - x8 * 16 + 5);
    }

    // Calcula a media do resultado
    resultado = (soma / namostras) * (diff * diff * diff * diff * diff * diff * diff);
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

  double x10 = 0, x11 = 0, x12 = 0, x13 = 0, x14 = 0;
  double x20 = 0, x21 = 0, x22 = 0, x23 = 0, x24 = 0;

  int residuo = npontos % UF;

  // Loop unroll com fator 4
  for (int i = 0; i < npontos - residuo; i += UF) {
    x11 = a + h * i;
    x12 = a + h * (i+1);
    x13 = a + h * (i+2);
    x14 = a + h * (i+3);

    for (int j = 0; j < npontos - residuo; j += UF) {
      x21 = a + h * j;
      x22 = a + h * (j+1);
      x23 = a + h * (j+2);
      x24 = a + h * (j+3);

      soma += ((x11 * (x11*x11*x11 - x11*16 + 5)) + (x21 * (x21*x21*x21 - x21*16 + 5))) +
              ((x11 * (x11*x11*x11 - x11*16 + 5)) + (x22 * (x22*x22*x22 - x22*16 + 5))) +
              ((x11 * (x11*x11*x11 - x11*16 + 5)) + (x23 * (x23*x23*x23 - x23*16 + 5))) +
              ((x11 * (x11*x11*x11 - x11*16 + 5)) + (x24 * (x24*x24*x24 - x24*16 + 5))) +
              ((x12 * (x12*x12*x12 - x12*16 + 5)) + (x21 * (x21*x21*x21 - x21*16 + 5))) +
              ((x12 * (x12*x12*x12 - x12*16 + 5)) + (x22 * (x22*x22*x22 - x22*16 + 5))) +
              ((x12 * (x12*x12*x12 - x12*16 + 5)) + (x23 * (x23*x23*x23 - x23*16 + 5))) +
              ((x12 * (x12*x12*x12 - x12*16 + 5)) + (x24 * (x24*x24*x24 - x24*16 + 5))) +
              ((x13 * (x13*x13*x13 - x13*16 + 5)) + (x21 * (x21*x21*x21 - x21*16 + 5))) +
              ((x13 * (x13*x13*x13 - x13*16 + 5)) + (x22 * (x22*x22*x22 - x22*16 + 5))) +
              ((x13 * (x13*x13*x13 - x13*16 + 5)) + (x23 * (x23*x23*x23 - x23*16 + 5))) +
              ((x13 * (x13*x13*x13 - x13*16 + 5)) + (x24 * (x24*x24*x24 - x24*16 + 5))) +
              ((x14 * (x14*x14*x14 - x14*16 + 5)) + (x21 * (x21*x21*x21 - x21*16 + 5))) +
              ((x14 * (x14*x14*x14 - x14*16 + 5)) + (x22 * (x22*x22*x22 - x22*16 + 5))) +
              ((x14 * (x14*x14*x14 - x14*16 + 5)) + (x23 * (x23*x23*x23 - x23*16 + 5))) +
              ((x14 * (x14*x14*x14 - x14*16 + 5)) + (x24 * (x24*x24*x24 - x24*16 + 5)));
    }
  }

  // Calculando o residuo do looping
  for (int i = npontos - residuo; i < npontos; ++i) {  
    x10 = a + h * i;    
    for (int j = npontos - residuo; j < npontos; ++j) {
      x20 = a + h * j;
      soma += (x10 * x10 * x10 * x10) - (x10 * x10 * 16) + (5 * x10) + (x20 * x20 * x20 * x20) - (x20 * x20 * 16) + (5 * x20);
    }
  }

  resultado = 0.5 * soma * h * h;

  // Multiplica pelo tamanho dos retângulos
  resultado *= h * h; 
  
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
  double retangulo = 0.0f;
  double monteCarlo = 0.0f;

  // retangulo = retangulos_xy (inicial, final, n_amostras);
  // printf("Resultado pelo Método dos Retângulos: %lf\n\n", retangulo);
 
  monteCarlo = styblinskiTang (inicial, final, n_amostras, n_variaveis);
  printf("Resultado pelo Método de Monte Carlo: %lf\n\n", monteCarlo);
 
  return 0;
}

