#include <stdio.h>

void le_tabela (double *values_x, double *values_y, int n);

void imprime_tabela(double *values_x, double *values_y, int n);

double polinomio_lagrange(double xe, double *x, int k, int N);

void interpolacao_lagrange(double xe, double *x, double *y, int N);

void polinomio_newton (double *x, double *y, double *coeficientes, int N);

void interpolacao_newton(double *x, double *y, int N, double xe);
