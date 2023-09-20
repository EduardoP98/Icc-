#include <stdio.h>



void le_tabela (double *values_x,double *values_y, int n);

void imprime_tabela(double *values_x,double *values_y, int n);

//Função para calcular o Polinômio interpolador de Lagrange
double inter_lagrange(double xe, double *values_x,double *values_y, int n );

// Função para calcular a interpolação de Newton
double inter_newton(double xe, double *values_x,double *values_y, int n );