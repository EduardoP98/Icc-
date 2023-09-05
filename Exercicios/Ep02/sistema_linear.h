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

void imprime_sistema_linear(SISTEMA_LINEAR_t *SL);

void le_sistema_linear(SISTEMA_LINEAR_t *SL);

void libera_sistema_linear(SISTEMA_LINEAR_t *SL);

SISTEMA_LINEAR_t *aloca_sistema_linear(int n);
