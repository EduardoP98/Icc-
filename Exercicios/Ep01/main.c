/* Aluno: Eduardo Purkote GRR20182960 e Mariana  GRR*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "floatType.h"

#define NUM_PARAMETROS 9
#define NUM_OP 4
#define NUM_X 5


void trata_entrada(int argc, char **argv,char *operacoes,Float_t *x, int n)
{ 
  int cont_op = 0, cont_val = 0;

  for(int i =0; i < n; i++)
  {
    if(i % 2 == 0)
    {
      Float_t val;
      float value;

      scanf("%f",&value);
      val.f = value;
      x[cont_val] = val;
      cont_val++;

    }
    else
    {
      char op;
      scanf("%c",&op);
      while(op == ' ')
      {
        scanf("%c",&op);
      }

      operacoes[cont_op] = op;
      cont_op ++;
      

    }
  }

}

int main(int argc, char **argv)
{

  char operacoes[NUM_OP];
  Float_t x[NUM_X];

  trata_entrada(argc,argv,operacoes,x,NUM_PARAMETROS);


  printf("Vetor Operacoes \n");
  for(int i = 0; i < NUM_OP;i++)
    printf("%c  ",operacoes[i]);
  printf("\n");


  printf("Vetor de Valores de X\n");
  for(int i = 0; i < NUM_X;i++)
    printFloat_t(x[i]);
  printf("\n");
   
  
  return 0;
}