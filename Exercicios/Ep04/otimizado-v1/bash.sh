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

# Topologia
echo "Criando arquivo contendo informações sobre a topologia..."
likwid-topology -g -c > informacoes/likwid_topology.txt
echo

# Frequencia do processador
echo  "Fixando frequência do processador..."
chmod a+rw /sys/devices/system/cpu/cpufreq/policy3/scaling_governor
echo "performance" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

# Modulos
echo
echo "Carregando módulo msr"
echo modprobe msr

# Nucleo
CORE_ID=1
echo "Utilizando o core ${CORE_ID}..."
# likwid-perfctr -C ${CORE_ID} -g L3 -m ./matmult 64 > resultados/L3_64.log

# # Verifique se a pasta já existe
# if [ ! -d "resultados" ]; then
#     # Crie a pasta se ela não existir
#     mkdir "resultados"
# fi

# Iniciando testes
# echo
# echo "Iniciando testes de desempenho..."
# echo
# for n in 64 100 128 200 256 512 600 900 1024 2000 2048 3000 4000
# do
#   echo "N = $n"
#   # likwid-perfctr -C ${CORE_ID} -g L3 -m ./matmult ${n} > resultados/L3_$n.txt
#   # likwid-perfctr -C ${CORE_ID} -g L2CACHE -m ./matmult ${n} > resultados/L2CACHE_$n.txt
#   # likwid-perfctr -C ${CORE_ID} -g ENERGY  -m ./matmult ${n} > resultados/ENERGY_$n.txt
#   # likwid-perfctr -C ${CORE_ID} -g FLOPS_DP -m ./matmult ${n} > resultados/FLOPS_DP_$n.txt
# done
# echo "Pronto! Arquivos criados no diretório resultados..."
# echo

# # Limpando
echo
echo "Finalizando execução e removendo arquivos temporários"
make purge

# Frequencia original
echo
echo "Retornando computador a frequencia original..."
echo "powersave" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

# Mensagem final
echo
echo "Pronto!"
echo