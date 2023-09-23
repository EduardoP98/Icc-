#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/* Le tabela a partir de arquivo de entrada (stdin) na estrutura
N
x1 y1
x2 y2
...
xN yN
*/
void le_tabela(double *values_x, double *values_y, int N) {
  for (int i = 0; i < N; i++) {
      if (scanf("%lf", &values_x[i]) != 1) {
          fprintf(stderr, "Erro na leitura de values_x[%d]\n", i);
          exit(1); 
      }

      if (scanf("%lf", &values_y[i]) != 1) {
          fprintf(stderr, "Erro na leitura de values_y[%d]\n", i);
          exit(1); 
      }
  }
}

// Imprime tabela de pontos 
void imprime_tabela(double *values_x, double *values_y, int N) {
  for(int i= 0; i < N; i++) {
    printf("x[%d]: %lf ", i, values_x[i]);
    printf("y[%d]: %lf\n", i, values_y[i]);
  }
}


// Calcula o Polinomio de Lagrange
double polinomio_lagrange(double xe, double *x, int k, int N) {
  double resultado = 1.0;

  for (int i = 0; i < N; i++) {
    if (i != k) {
        resultado *= (xe - x[i]) / (x[k] - x[i]);
    }
  }
  return resultado;
}

// Realiza a interpolacao de Lagrange
void interpolacao_lagrange(double xe, double *x, double *y, int N) {
  double resultado = 0.0;
  for (int k = 0; k < N; k++) {
    resultado += y[k] * polinomio_lagrange(xe, x, k, N);
  }

  printf("\nfL(%.2lf) = %.6lf\n", xe, resultado);
}

// Função para calcular os coeficientes do polinomio de Newton
void polinomio_newton (double *x, double *y, double *coeficientes, int N) {
  // Inicializa a matriz de diferencas divididas
  double matrizDiferencas[N][N];
  for (int i = 0; i < N; i++) {
      matrizDiferencas[i][0] = y[i];
  }

  // Calcula as diferenças divididas
  for (int j = 1; j < N; j++) {
    for (int i = 0; i < N - j; i++) {
        matrizDiferencas[i][j] = (matrizDiferencas[i + 1][j - 1] - matrizDiferencas[i][j - 1]) / (x[i + j] - x[i]);
    }
  }

  // Os coeficientes do polinômio são os elementos da diagonal superior da matriz
  for (int i = 0; i < N; i++) {
      coeficientes[i] = matrizDiferencas[0][i];
  }
}

// Função para interpolar por Newton
void interpolacao_newton(double *x, double *coeficientes, int N, double xe) {
  double resultado = coeficientes[0];
  double termo = 1.0;

  for (int i = 1; i < N; i++) {
    termo *= (xe - x[i - 1]);
    resultado += coeficientes[i] * termo;
  }

  printf("fN(%.2lf) = %.6lf\n", xe, resultado);
}