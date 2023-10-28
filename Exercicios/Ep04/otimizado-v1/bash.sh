#!/bin/bash

# Verifica se o programa está disponível
if [ ! -f matmult ]; then
  echo  
  echo "O programa não foi encontrado. Compilando..."
  echo
  make
  if [ $? -ne 0 ]; then
    echo
    echo "Falha na compilação do programa."
    exit 1
  fi
fi

echo
echo "Programa compilado. Iniciando preparação do ambiente..."
echo

# # Topologia
# echo "Criando arquivo contendo informações sobre a topologia..."
# likwid-topology -g -c >> informacoes/likwid_topology.txt
# echo

# # Frequencia do processador
# echo  "Fixando frequência do processador..."
# chmod a+rw /sys/devices/system/cpu/cpufreq/policy3/scaling_governor
# echo "performance" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

# Modulos
# echo
# echo "Carregando módulo msr"
# echo modprobe msr

# Nucleo
CORE_ID=1
echo "Utilizando o core ${CORE_ID}..."
# likwid-perfctr -C ${CORE_ID} -g L3 -m ./matmult 64 > resultados/L3_64.log

# Iniciando testes
echo
echo "Iniciando testes de desempenho..."
echo
echo "1) BANDA DE MEMÓRIA"
for n in 64 100 128 200 256 512 600 900 1024 2000 2048 3000 4000
do
  echo "N = $n"
  likwid-perfctr -C ${CORE_ID} -g L3 -m ./matmult ${n} > resultados/L3_$n.txt
done
echo "Pronto!"
echo

# echo "------------------ CACHE MISS L2 ------------------"
# for n in 64, 100, 128, 200, 256, 512, 600, 900, 1024, 2000, 2048, 3000, 4000
# do
#   echo "N = $n \n"
#   likwid-perfctr -C 1 -g MEM -m ./matmult $n > L2CACHE_$n.log
# done

# echo "------------------ ENERGIA ------------------"
# for n in 64, 100, 128, 200, 256, 512, 600, 900, 1024, 2000, 2048, 3000, 4000
# do
#   echo "N = $n \n"
#   likwid-perfctr -C 1 -g MEM -m ./matmult $n > ENERGY_$n.log
# done

# echo "------------------ FLOPS_DPS------------------"
# for n in 64, 100, 128, 200, 256, 512, 600, 900, 1024, 2000, 2048, 3000, 4000
# do
#   echo "N = $n \n"
#   likwid-perfctr -C 1 -g FLOPS_DP -m ./matmult $n > FLOPS_DP_$n.log
# done

# # Filtra as métricas do LIKWID relacionadas a operações aritméticas e energia
# # Para operações aritméticas, utilizamos o grupo FLOPS_DP e reportamos FLOPS_DP e FLOPS_AVX
# # Para energia, utilizamos o grupo ENERGY e reportamos Energy[J]
# grep -n "." resultado_flops.out | sed -n '1,10p' | cut -d: -f2- > resultado.out
# grep -E 'Region (gera|soluciona)|DP \[MFLOP/s\]|AVX DP \[MFLOP/s\]' resultado_flops.out >> resultado.out
# echo -------------------------------------------------------------------------------- >> resultado.out
# grep -E 'Region (gera|soluciona)|Energy \[J\]' resultado_energy.out >> resultado.out
# echo -------------------------------------------------------------------------------- >> resultado.out

# # Limpando
# echo
# echo "Finalizando execução e removendo arquivos temporários"
# make purge

# Frequencia original
# echo
# echo "Retornando computador a frequencia original..."
# echo "powersave" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

# Mensagem final
echo
echo "Pronto!"
echo