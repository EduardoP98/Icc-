/* Aluno: Eduardo Purkote GRR20182960 e Mariana  GRR*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "floatType.h"

#include <fenv.h>
#include <math.h>

#define NUM_PARAMETROS 9
#define NUM_OP 4
#define NUM_X 5

/* Recebe uma entrada padrao X1 01 X2 02 X3 03 X4 04 X5 e insere valors nos vetores

*/
void trata_entrada(char *operacoes, Float_t *x, int n)
{ 

  // Para contrar o numero de operacoes e valores lidos
  int cont_op = 0, cont_val = 0;

  // De 0 ao NUM_PARAMETROS (4 + 5) faca
  for(int i = 0; i < n; i++)
  {
    // Se o indice for por par, eh um numero real
    if(i % 2 == 0) {
      Float_t val;
      float value;

      // Le um valor de ponto flutuante da entrada e armazena em value
      scanf("%f", &value);

      // Armazenando o ponto flutuante na estrutura Float_t
      val.f = value;

      // Armazena a estrutura val (contendo o valor de ponto flutuante) no array x na posição indicada por cont_val
      x[cont_val] = val;
      cont_val++;

    }
    // Se o indice for impar, eh um operador
    else {
      char op;

      // Leitura do operador (string)
      scanf("%c",&op);

      // Se o valor for um espaco vazio, pula ate encontrar um operdaor
      while(op == ' ') {
        scanf("%c",&op);
      }

      // Armazena o operador
      operacoes[cont_op] = op;
      cont_op ++;
    }
  }
}

/*  
  Seja x um valor real qualquer. A representacao intervalar de e dada por X = [m(x), M(X)] onde
  m(x): maior numero de maquina menor ou igual a x
  M(x): menor número de máquina maior ou igual a x
*/
void calcula_intervalo (Float_t x, float *m, float *M) {
  // Retorna o próximo número de máquina na direção positiva a partir de x, o que corresponde a m(x).


  //Define o modo de arredondamento para baixo
  fesetround(FE_DOWNWARD);


  *m = nextafterf(x.f, 0);

  
  // Restaura o modo de arredondamento padrão
  fesetround(FE_TONEAREST);

  *M = nextafterf(x.f,INFINITY);
  
  
}


/* Calcula o número de valores representáveis entre dois números do tipo float

*/
int calcula_ulps(float a , float b)
{
  Float_t num1, num2;
  num1.f = a;
  num2.f = b;

   int ulps = (int) fabs(num1.i - num2.i);

  return ulps;

}

void calcula_operacao_intervalar(float a, float b, char operador, float c, float d, float *resultado_m, float *resultado_M) {
  // Calcula cada operacao intervalar basica
  switch (operador) {
      case '+':
          fesetround(FE_DOWNWARD);
          float soma_1 = a + c;
          fesetround(FE_UPWARD);
          float soma_2 = b + d;
          
          *resultado_m = soma_1;
          
          *resultado_M = soma_2;

          fesetround(FE_TONEAREST);
          break;
      case '-':
          fesetround(FE_DOWNWARD);
          *resultado_m = a - d; 
          fesetround(FE_UPWARD); 
          *resultado_M = b - c;
          fesetround(FE_TONEAREST);
          break;
      case '*':
          fesetround(FE_DOWNWARD);
          float result1 = a * c;
          float result2 = a * d;
          fesetround(FE_UPWARD);
          float result3 = b * c;
          float result4 = b * d;
          *resultado_m = fminf(fminf(result1, result2), fminf(result3, result4));
          *resultado_M = fmaxf(fmaxf(result1, result2), fmaxf(result3, result4));
          fesetround(FE_TONEAREST);
          break;
      case '/':
          if (c <= 0 && d >= 0) {
              *resultado_m = -INFINITY;
              *resultado_M = INFINITY;
          } else if (c == 0) {
              *resultado_m = -INFINITY;
              *resultado_M = INFINITY;
          }
      default:
          *resultado_m = 0.0;
          *resultado_M = 0.0;
  }

  
  // Aqui calculamos o erro absoluto, erro relativo e ULPs
  float erro_absoluto = erro_abs(*resultado_m, *resultado_M);
  float erro_relativo = erro_rel(*resultado_m,*resultado_M);

  // Calcula ULPs
  int ulps = calcula_ulps(*resultado_m,*resultado_M);

  // Imprime os resultados formatados
  static int sequencia = 1;
  printf("%d:\n", sequencia);
  printf("[%1.8e,%1.8e] %c [%1.8e,%1.8e] =\n", a, b, operador, c, d);
  printf("[%1.8e,%1.8e]\n", *resultado_m, *resultado_M);
  printf("EA: %1.8e; ER: %1.8e; ULPs: %d\n\n", erro_absoluto, erro_relativo, ulps);
  sequencia++;
        
}

int main(int argc, char **argv)
{
  // Vetor de operacoes O1, O2, O3 e O4
  char operacoes[NUM_OP];

  // Vetor de numeros reais X1, X2, X3, X4 e X5
  Float_t x[NUM_X];

  // Recebe uma entrada padrao X1 01 X2 02 X3 03 X4 04 X5 e insere valors nos vetores
  trata_entrada(operacoes, x, NUM_PARAMETROS);

  // Imprime operadores para checagem
  printf("\nVetor Operacoes \n");
  for(int i = 0; i < NUM_OP;i++)
    printf("%c  ", operacoes[i]);
  printf("\n\n");

  // Imprime numeros reais para checagem
  printf("Vetor de Valores de X\n");
  for(int i = 0; i < NUM_X;i++)
    printFloat_t(x[i]);
  printf("\n");

  // Arrays para armazenar m(x) e M(x)
  float mx_values[NUM_X];
  float Mx_values[NUM_X];

  // Calcula m(x) e M(x) para cada valor de x
  for (int i = 0; i < NUM_X; i++) {
      calcula_intervalo(x[i], &mx_values[i], &Mx_values[i]);
  }

  // Imprime os valores de m(x) e M(x) para cada valor de x
  printf("Valores de m(x) e M(x) para cada X\n");
  for (int i = 0; i < NUM_X; i++) {
      printf("x[%d] = %1.8e, m(x) = %1.8e, M(x) = %1.8e\n",i, x[i].f, mx_values[i], Mx_values[i]);
  }
  printf("\n");

  // Realiza as operações intervalares em ordem (((X1 O1 X2) O2 X3) O3 X4) O4 X5
  float resultado_m, resultado_M;
  calcula_operacao_intervalar(mx_values[0], Mx_values[0], operacoes[0], mx_values[1], Mx_values[1], &resultado_m, &resultado_M); // (X1 O1 X2)
  calcula_operacao_intervalar(resultado_m, resultado_M, operacoes[1], mx_values[2], Mx_values[2], &resultado_m, &resultado_M); // (resultado) O2 X3)
  calcula_operacao_intervalar(resultado_m, resultado_M, operacoes[2], mx_values[3], Mx_values[3], &resultado_m, &resultado_M); // (resultado) O3 X4)
  calcula_operacao_intervalar(resultado_m, resultado_M, operacoes[3], mx_values[4], Mx_values[4], &resultado_m, &resultado_M); // resultado O4 X5)
  
  return 0;
}