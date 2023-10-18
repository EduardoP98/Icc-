#!/bin/bash

# Verifica se o programa está disponível
if [ ! -f ajustePol ]; then
  echo "O programa não foi encontrado. Compilando..."
  make
  if [ $? -ne 0 ]; then
    echo "Falha na compilação do programa."
    exit 1
  fi
fi

echo
echo "Programa compilado. Executando com o arquivo de entrada 'teste.in'..."

# Execute o LIKWID para medir o desempenho
likwid-perfctr -C 1 -g FLOPS_DP -m ./ajustePol < teste.in > resultado_flops.out
likwid-perfctr -C 1 -g ENERGY -m ./ajustePol < teste.in > resultado_energy.out

# Filtra as métricas do LIKWID relacionadas a operações aritméticas e energia
# Para operações aritméticas, utilizamos o grupo FLOPS_DP e reportamos FLOPS_DP e FLOPS_AVX
# Para energia, utilizamos o grupo ENERGY e reportamos Energy[J]
grep -n "." resultado_flops.out | sed -n '1,10p' | cut -d: -f2- > resultado.out
grep -E 'Region (gera|soluciona)|DP \[MFLOP/s\]|AVX DP \[MFLOP/s\]' resultado_flops.out >> resultado.out
echo -------------------------------------------------------------------------------- >> resultado.out
grep -E 'Region (gera|soluciona)|Energy \[J\]' resultado_energy.out >> resultado.out
echo -------------------------------------------------------------------------------- >> resultado.out

# Remove arquivo temporário
rm resultado_flops.out
rm resultado_energy.out

# Limpando
echo
echo "Finalizando execução e removendo arquivos temporários"
make purge

# Mensagem final
echo
echo "O resultado final encontra-se no arquivo 'resultado.out'"
echo