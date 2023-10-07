#include <stdio.h>
#include <stdlib.h>
#include "sistema_linear.h"
#include "tabela.h"
#include "doubleType.h"

// Função que le tabela de pontos
void le_tabela (TABELA_t *tabela) {
  Double_t x,y;

  for(int i = 0; i < tabela->k; i++) {
    int entrada = scanf("%lf", &x.f);
    if (entrada != 1) {
      perror("Erro ao ler o valor de X");
      exit(1);
    }

    entrada = scanf("%lf", &y.f);
    if (entrada != 1) {
      perror("Erro ao ler o valor de Y");
      exit(1);
    }

    tabela->x[i] = calcula_intervalo(x);
    tabela->y[i] = calcula_intervalo(y);
  }
}

// Função que imprime tabela de pontos 
void imprime_tabela(TABELA_t *tabela)
{
  printf("Número de Pontos (K): %d \n", tabela->k);
  for(int i= 0; i < tabela->k; i++)
  {
    printf("x[%d]: [%.17e, %.17e] ", i, tabela->x[i].m.f, tabela->x[i].M.f);
    printf("y[%d]: [%.17e, %.17e] \n", i, tabela->y[i].m.f, tabela->y[i].M.f);
  }
}


TABELA_t *aloca_tabela(int k) {
  TABELA_t *tabela = (TABELA_t *)malloc(sizeof(TABELA_t));
  
  //Verifica se foi alocada memória para a tabela de pontos
  if (!tabela) {
    perror("Erro ao alocar Tabela\n");
    exit (1) ;
  }
   
  tabela->k = k;
  tabela->x = malloc(tabela->k * sizeof(INTERVAL_t)); //Aloca vetor para pontos x
  tabela->y = malloc(tabela->k * sizeof(INTERVAL_t));// Aloca vetor para pontos y

  //Verifica se foi alocada memória para o vetor X
  if (!tabela->x) {
    perror("Erro ao alocar Vetor X\n");
    exit (1) ;
  }

  //Verifica se foi alocada memória para o vetor Y
  if (!tabela->y) {
    perror("Erro ao alocar Vetor Y\n");
    exit (1) ;
  }
  
  return tabela;
}

void libera_tabela(TABELA_t *tabela)
{
  free(tabela->x);
  free(tabela->y);
  free(tabela);
}
