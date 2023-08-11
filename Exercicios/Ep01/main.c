/* Aluno: Eduardo Purkote GRR20182960 e Mariana  GRR*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "floatType.h"

#define NUM_PARAMETROS 2
#define NUM_OP 4
#define NUM_X 5


void trata_entrada(int argc, char **argv,char *operacoes,Float_t *x)
{
   const char s[2] = " ";
   char *token;
   token = strtok(argv[1], s);
   
   int cont = 0, cont_par = 0, cont_val = 0;
   
   while( token != NULL )
   {
      if(cont_par % 2 == 0)
      {
        Float_t val;

        float value = strtof( token , NULL);
        val.f = value;
        x[cont_val] = val;

        cont_val++;

      }
      else
      {
        operacoes[cont] = token[0];
        cont ++;

      }
    
      token = strtok(NULL, s);
      cont_par ++;
   }
}

int main(int argc, char **argv)
{

  
  
  //Verificação da Entrada
  if(argc != NUM_PARAMETROS)
  {
    printf("argc:%d \n", argc);
    printf("Número de Parâmetros Inválido!\n");
    printf("Tente o Seguinte Formato: X1 O1 X2 O2 X3 O3 X4 O4 X5 \n");
    printf("Ex.: \"2.347e-40 * 0.001 + 1.1e+10 - 0.75e-39  / 0.0\" \n");
    printf("*OBS: Necessário que a expressão na entrada esteja entre aspas (\"\")! ");
    puts("O Shell interpreta o Asterisco como expansão do diretório e não como uma operação de Multiplicação.Portanto, gerando erro! \n");
    exit(1);
  }

  char operacoes[NUM_OP];
  Float_t x[NUM_X];

  trata_entrada(argc,argv,operacoes,x);


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