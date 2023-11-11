#!/bin/bash

# Verifica se o programa está disponível
if [ ! -f integration ]; then
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
echo "Programa compilado."
echo

# Execucoes
# echo "Método do Retângulo : 10e5"
# ./integration -4 4 100000 2 >> resultados/retangulo_10e5.txt 
# ./integration -4 4 100000 2 >> resultados/retangulo_10e5.txt 
# ./integration -4 4 100000 2 >> resultados/retangulo_10e5.txt 
# ./integration -4 4 100000 2 >> resultados/retangulo_10e5.txt 
# ./integration -4 4 100000 2 >> resultados/retangulo_10e5.txt 
# ./integration -4 4 100000 2 >> resultados/retangulo_10e5.txt 
# ./integration -4 4 100000 2 >> resultados/retangulo_10e5.txt 

# echo "Método do Retângulo : Testes aleatorios"
# ./integration -4 4 10000 2 >> resultados/retangulo_aleatorio.txt

# echo "Método do Retângulo : 10e7"
# ./integration -4 4 10000000 2 >> resultados/retangulo_10e7.txt

# echo "Método do Retângulo : 10e6"
# ./integration -4 4 1000000 2 >> resultados/retangulo_10e6.txt

# echo "Método do Retângulo : Testes aleatorios"
# ./integration -4 4 100004 2 >> resultados/retangulo_aleatorio.txt
# ./integration -4 4 10034 2 >> resultados/retangulo_aleatorio.txt
# ./integration -4 4 110374 2 >> resultados/retangulo_aleatorio.txt

# echo "Método de Monte Carlo : 2 dimensões"
# ./integration -4 4 10000000 2 >> resultados/monte_carlo_2dim.txt
# ./integration -4 4 10000000 2 >> resultados/monte_carlo_2dim.txt
# ./integration -4 4 10000000 2 >> resultados/monte_carlo_2dim.txt
# ./integration -4 4 10000000 2 >> resultados/monte_carlo_2dim.txt
# ./integration -4 4 10000000 2 >> resultados/monte_carlo_2dim.txt
# ./integration -4 4 10000000 2 >> resultados/monte_carlo_2dim.txt
# ./integration -4 4 10000000 2 >> resultados/monte_carlo_2dim.txt
# ./integration -4 4 10000000 2 >> resultados/monte_carlo_2dim.txt
# ./integration -4 4 10000000 2 >> resultados/monte_carlo_2dim.txt

# echo "Método de Monte Carlo : 4 dimensões"
# ./integration -4 4 10000000 4 >> resultados/monte_carlo_4dim.txt
# ./integration -4 4 10000000 4 >> resultados/monte_carlo_4dim.txt
# ./integration -4 4 10000000 4 >> resultados/monte_carlo_4dim.txt
# ./integration -4 4 10000000 4 >> resultados/monte_carlo_4dim.txt
# ./integration -4 4 10000000 4 >> resultados/monte_carlo_4dim.txt
# ./integration -4 4 10000000 4 >> resultados/monte_carlo_4dim.txt
# ./integration -4 4 10000000 4 >> resultados/monte_carlo_4dim.txt
# ./integration -4 4 10000000 4 >> resultados/monte_carlo_4dim.txt
# ./integration -4 4 10000000 4 >> resultados/monte_carlo_4dim.txt

# echo "Método de Monte Carlo : 8 dimensões"
# ./integration -4 4 10000000 8 >> resultados/monte_carlo_8dim.txt
# ./integration -4 4 10000000 8 >> resultados/monte_carlo_8dim.txt
# ./integration -4 4 10000000 8 >> resultados/monte_carlo_8dim.txt
# ./integration -4 4 10000000 8 >> resultados/monte_carlo_8dim.txt
# ./integration -4 4 10000000 8 >> resultados/monte_carlo_8dim.txt
# ./integration -4 4 10000000 8 >> resultados/monte_carlo_8dim.txt
# ./integration -4 4 10000000 8 >> resultados/monte_carlo_8dim.txt
# ./integration -4 4 10000000 8 >> resultados/monte_carlo_8dim.txt
# ./integration -4 4 10000000 8 >> resultados/monte_carlo_8dim.txt

# Limpando
echo
echo "Finalizando execução e removendo arquivos temporários"
make purge


# Mensagem final
echo
echo "Pronto!"
echo