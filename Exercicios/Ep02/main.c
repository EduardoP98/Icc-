#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sistema_linear.h"
#include "calc_time.h"



int main()
{
  int mat_ordem;
  SISTEMA_LINEAR_t *SL, *SL_gauss_sem_p , *SL_gauss_sem_mult;

  scanf("%d",&mat_ordem);
  /* Aloca Memória para um Sistema Linear */
  SL = aloca_sistema_linear(mat_ordem);
  SL_gauss_sem_p = aloca_sistema_linear(mat_ordem);
  SL_gauss_sem_mult = aloca_sistema_linear(mat_ordem);
  
  
  /* Trata Entrada */
  le_sistema_linear(SL);
  copiaSistemaLinear(SL,SL_gauss_sem_p );
  copiaSistemaLinear(SL,SL_gauss_sem_mult);


  //1-Forma clássica com pivoteamento
  printf("Forma clássica com pivoteamento\n");
  double time_i = timestamp();

  elimGauss_parcial(SL->A,SL->b,SL->x,SL->n);
  retrosubs(SL->A,SL->b,SL->x,SL->n);
  SL->residuo = calculaResiduo(SL->A,SL->b,SL->x,SL->n);
  imprime_sistema_linear(SL);
  libera_sistema_linear(SL);

  double time_f = timestamp();
  printf("Tempo Em MiliSegundos:%lf \n\n",time_f-time_i);


  //2-Forma clássica com pivoteamento, sem o cálculo dos multiplicadores 
  printf("Forma clássica com pivoteamento, sem o cálculo dos multiplicadores\n");
  time_i = timestamp();

  elimGauss_sem_multiplicadores(SL_gauss_sem_mult->A, SL_gauss_sem_mult->b, SL_gauss_sem_mult->n);
  retrosubs(SL_gauss_sem_mult->A, SL_gauss_sem_mult->b,SL_gauss_sem_mult->x, SL_gauss_sem_mult->n);
  SL_gauss_sem_mult->residuo = calculaResiduo(SL_gauss_sem_mult->A, SL_gauss_sem_mult->b, SL_gauss_sem_mult->x,SL_gauss_sem_mult->n);
  imprime_sistema_linear(SL_gauss_sem_mult);
  libera_sistema_linear(SL_gauss_sem_mult);  
  time_f = timestamp();
  printf("Tempo Em MiliSegundos:%lf \n\n",time_f-time_i);


  //3-Forma alternativa onde não usa pivoteamento
  printf("Forma alternativa onde não usa pivoteamento\n");
  time_i = timestamp();
  elimGauss_sem_pivoteamento(SL_gauss_sem_p->A, SL_gauss_sem_p->b, SL_gauss_sem_p->n);
  retrosubs(SL_gauss_sem_p->A, SL_gauss_sem_p->b,SL_gauss_sem_p->x, SL_gauss_sem_p->n);  
  SL_gauss_sem_p->residuo = calculaResiduo(SL_gauss_sem_p->A,SL_gauss_sem_p->b,SL_gauss_sem_p->x,SL_gauss_sem_p->n);
  imprime_sistema_linear(SL_gauss_sem_p);
  libera_sistema_linear(SL_gauss_sem_p);
  

  time_f = timestamp();
  printf("Tempo Em MiliSegundos:%lf \n\n",time_f-time_i);

  return 0;
}