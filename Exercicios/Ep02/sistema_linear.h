#ifndef  SISTEMA_LINEAR_H
#define  SISTEMA_LINEAR_H


typedef struct
{
  int n;
  double **A;
  double *b;
  double *x;
  double residuo;

}SISTEMA_LINEAR_t;
#endif


void retrosubs(double **A,double *b,double *x, int n);

void imprime_sistema_linear(SISTEMA_LINEAR_t *SL);

void le_sistema_linear(SISTEMA_LINEAR_t *SL);

void libera_sistema_linear(SISTEMA_LINEAR_t *SL);

SISTEMA_LINEAR_t *aloca_sistema_linear(int n);


unsigned int encontraMax(double **A, int i, int n);

void trocaLinha(double **A, double *b, int i, int iPivo, int n);

void elimGauss_parcial(double **A,double *b,double *x, int n);

void elimGauss_sem_multiplicadores(double **A, double *b, int n);

void elimGauss_sem_pivoteamento(double **A, double *b, int n);

double calculaResiduo(double **A, double *b, double *x, int n);

void copiaSistemaLinear(const SISTEMA_LINEAR_t *origem, SISTEMA_LINEAR_t *destino);