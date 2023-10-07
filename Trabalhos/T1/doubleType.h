#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <float.h>

#ifndef DOUBLE_TYPE_H
#define DOUBLE_TYPE_H

typedef union
{
    int64_t i;
    double f;
    struct
    {   // Bitfields for exploration (64 bits = sign|exponent|mantissa)
        uint64_t mantissa : 52; // primeiros 52 bits (da direita para a esquerda)
        uint64_t exponent : 11; // próximos 11 bits
        uint64_t sign : 1;      // próximo bit (ou seja, o bit mais à esquerda)
    } parts;

}Double_t;


void printDouble_t( Double_t num );

Double_t calculaEpsilonRelativo( Double_t num );

int AlmostEqualRelative(Double_t A, Double_t B);

int AlmostEqualUlps(Double_t A, Double_t B, int maxULPs);

//Função que calcula Erro Absoluto
float erro_abs(float a, float b);

//Função que Calcula Erro Relativo
float erro_rel(float a , float b);

#endif