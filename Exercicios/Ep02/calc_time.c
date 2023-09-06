#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "calc_time.h"


//Retorna o tempo em milisegundos
double timestamp(void)
{
  struct timeval tp;
  gettimeofday(&tp, NULL);
  return (double)(tp.tv_sec * 1000.0 + tp.tv_usec / 1000.0);
}