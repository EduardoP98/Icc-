#!/bin/bash

# Verifica se o programa interpola está disponível
if [ ! -f interpola ]; then
  echo "O programa interpola não foi encontrado. Compilando..."
  make
  if [ $? -ne 0 ]; then
    echo "Falha na compilação do programa interpola."
    exit 1
  fi
fi

# Execute o LIKWID para medir o desempenho
likwid-perfctr -C 1 -g FLOPS_DP -m ./interpola 3 < teste1 > resultado.txt