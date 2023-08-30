#ifndef  SISTEMA_LINEAR_H
#define  SISTEMA_LINEAR_H


typedef struct
{
  int n;
  double **A;
  double *b;
  double *x;

}SISTEMA_LINEAR_t;
#endif


void retrosubs(double **A,double *b,double *x, int n);

void imprime_sistema_linear(double **A, double *b , double *x, int n);

void le_sistema_linear(double **A, double *b , double *x, int n);
