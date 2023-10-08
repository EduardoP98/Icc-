/*
  Código fornecido pelo professor.
  Aunos: 
  Eduardo Purkote (GRR20182960)
  Mariana Moreira dos Santos (GRR20186554)
  
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "utils.h"

//Retorna o tempo em milisegundos
double timestamp(void)
{
  struct timeval tp;
  gettimeofday(&tp, NULL);
  return (double)(tp.tv_sec * 1000.0 + tp.tv_usec / 1000.0);
}