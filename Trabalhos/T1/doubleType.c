/*
 * source: https://randomascii.wordpress.com/2012/01/11/tricks-with-the-floating-point-format/
 */

 /*
  Estrutura de modificada pelos alunos.
  Aunos: 
  Eduardo Purkote (GRR20182960)
  Mariana Moreira dos Santos (GRR20186554)
  
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "doubleType.h"

/* imprime a union Double_t como ponto flutuante, hexadecimal e 
 * suas partes na forma de inteiros */
void printDouble_t( Double_t num )
{
//    printf("f:%1.9e, ix:0x%08lX, s:%d, e:%d, mx:0x%06\n",
//             num.f, num.i,
//             num.parts.sign, num.parts.exponent, num.parts.mantissa); 
} 


/* calcula o epsilon relativo a um numero NUM. Ou seja, o valor tal
 * que NUM + epsilon seja > NUM */
Double_t calculaEpsilonRelativo( Double_t num )
{
    // Double_t epsilon = num;
    // epsilon.parts.mantissa += 1;

    Double_t epsilon;
    epsilon.f = num.f / 2.0f;
    while (num.f + epsilon.f / 2.0f > num.f)
        epsilon.f /= 2.0f;
    
    return epsilon;
}


int AlmostEqualRelative(Double_t A, Double_t B)
{
    // Calculate the difference.
    Double_t diff, largest, relEpsilon;
    diff.f = fabs(A.f - B.f);
    A.f = fabs(A.f);
    B.f = fabs(B.f);
    // Find the largest
    largest.f = (B.f > A.f) ? B.f : A.f;
    relEpsilon.f = largest.f * FLT_EPSILON;

    printf("\tThe difference: ");
    printDouble_t(diff);
    
    printf("\trel. Epsilon:   ");
    printDouble_t(relEpsilon);
    
    if (diff.f <= relEpsilon.f)
        return 1;
    return 0;
}


int AlmostEqualUlps(Double_t A, Double_t B, int maxULPs)
{
    // Different signs means they do not match.
    if (A.parts.sign != B.parts.sign)
    {
        // Check for equality to make sure +0==-0
        if (A.f == B.f)
            return 1;
        return 0;
    }
 
    // Find the difference in ULPs.
    int ulpsDiff = abs(A.i - B.i);
    printf("\tULPs diff: %d\n", ulpsDiff);
    
    if (ulpsDiff < maxULPs)
        return 1;
    return 0;
}

//Retorna o Erro Absoluto Real
float erro_abs(float a, float b)
{
  return fabs(b - a);
}

//Retorna o Erro Relativo Real
float erro_rel(float a, float b)
{
   return fabs((b -a) / a);
}