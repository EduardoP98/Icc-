#include <stdio.h>


void le_tabela (double *values_x,double *values_y, int n) {
  for(int i = 0; i < n; i++) {
    scanf("%lf",&values_x[i]);
    scanf("%lf",&values_y[i]);
  }
}

// Imprime tabela de pontos 
void imprime_tabela(double *values_x,double *values_y, int n) {
  for(int i= 0; i < n; i++) {
    printf("x[%d]: %lf ",i,values_x[i]);
    printf("y[%d]: %lf\n",i,values_y[i]);
  }
}

// Calcula o Polinômio interpolador de Lagrange
double inter_lagrange(double xe, double *values_x,double *values_y, int n ) {
  double resultado = 0.0;

  for (int i = 0; i < n; i++) {
    double termo = values_y[i];
    for (int j = 0; j < n; j++) {
      if (i != j) {
        termo = termo * (xe - values_x[j]) / (values_x[i] - values_x[j]);
      }
    }
        resultado += termo;
    }
    return resultado;
}

// Função para calcular a interpolação de Newton
double inter_newton(double xe, double *values_x,double *values_y, int n )
{
  return 0.0;
}