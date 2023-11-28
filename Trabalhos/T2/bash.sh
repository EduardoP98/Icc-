#!/bin/bash


if [ ! -d "informacoes" ]; then
    # Crie a pasta se ela não existir
    mkdir "informacoes"
fi

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

# Teste unico
# likwid-perfctr -C ${CORE_ID} -g L3 -m ./matmult 64 > debug.txt

# Iniciando testes
# echo
echo "Iniciando testes de desempenho... Utilizando a Versão 1"
echo
cd v1
# Verifique se a pasta já existe
if [ ! -d "resultados" ]; then
    # Crie a pasta se ela não existir
    mkdir "resultados"
fi

# Verifica se o programa está disponível
if [ ! -f ajustePol ]; then
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

for n in 64 128 200 256 512 600 800 1024 2000 3000 4096 6000 7000 10000 50000 100000 1000000 10000000 100000000 
do

  echo "N = $n"
  ./gera_entrada $n  | likwid-perfctr -C ${CORE_ID} -g L3 -m ./ajustePol  > resultados/L3_$n.txt
  ./gera_entrada $n  | likwid-perfctr -C ${CORE_ID} -g CACHE -m ./ajustePol > resultados/L2CACHE_$n.txt
  ./gera_entrada $n  | likwid-perfctr -C ${CORE_ID} -g FLOPS_DP -m ./ajustePol > resultados/FLOPS_DP_$n.txt
    
done
echo "Pronto! Arquivos criados no diretório resultados..."
echo
# # Limpando
echo
echo "Finalizando execução e removendo arquivos temporários"
make purge
cd ..


# echo "Iniciando testes de desempenho... Utilizando a Versão 2"
# echo
cd v2
# Verifique se a pasta já existe
if [ ! -d "resultados" ]; then
    # Crie a pasta se ela não existir
    mkdir "resultados"
fi

# Verifica se o programa está disponível
if [ ! -f ajustePol ]; then
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

for n in 64 128 200 256 512 600 800 1024 2000 3000 4096 6000 7000 10000 50000 100000 1000000 10000000 100000000 
do
  
  echo "N = $n" 
  ./gera_entrada $n  | likwid-perfctr -C ${CORE_ID} -g L3 -m ./ajustePol  > resultados/L3_$n.txt
  ./gera_entrada $n  | likwid-perfctr -C ${CORE_ID} -g CACHE -m ./ajustePol > resultados/L2CACHE_$n.txt
  ./gera_entrada $n  | likwid-perfctr -C ${CORE_ID} -g FLOPS_DP -m ./ajustePol > resultados/FLOPS_DP_$n.txt
done
echo "Pronto! Arquivos criados no diretório resultados..."
echo

sleep 1

# # Limpando
echo
echo "Finalizando execução e removendo arquivos temporários"
make purge

cd ..

# Frequencia original
echo
echo "Retornando computador a frequencia original..."
echo "powersave" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

# Mensagem final
echo
echo "Pronto!"
echo