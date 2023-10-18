# Trabalho 01: Ajuste Polinomial de Curvas com Cálculo Intervalar
## Introdução à Computação Científica
### Alunos
- Eduardo Purkote (GRR20182960)
- Mariana Moreira dos Santos (GRR20186554)

## Objetivo
O objetivo deste trabalho é implementar um programa para calcular um polinômio de grau N que se ajuste a uma curva descrita por K pontos, utilizando aritmética intervalar para representação rigorosa dos valores reais.

O programa recebe como entrada o grau N do polinômio de ajuste (1ª linha), a quantidade K de pontos da tabela (2ª linha) e a tabela com os pontos (x,y) do tipo double, um par de coordenadas por linha.

O programa tem como saída os coeficientes ai da equação de ajuste, os resíduos entre a tabela inicial de pontos e os valores produzidos pela equação calculada (ri = yi - f(xi)) e o tempo gasto (em milisegundos) na solução do sistema linear (tsolSL) e na geração dos coeficientes e termos independentes do sistema linear (tgeraSL).


## Execução
### Makefile
**Flags de debug**

Caso seja necessário, poderá ser usado o seguinte comando para que o arquivo rode com as flags DEBUG ativadas:
> make DEBUG=yes

### Script .bash 
#### Comandos
Foi criado um script bash (bash.sh) que contempla os seguintes comandos:

- Compilação do programa
    > make
- Execução do programa com as diretivas LIKWID
    > likwid-perfctr -C 1 -g FLOPS_DP -m ./ajustePol < teste.in > resultado_flops.out

    > likwid-perfctr -C 1 -g ENERGY -m ./ajustePol < teste.in > resultado_energy.out

    A entrada *default* utilizada foi o arquivo *teste.in* 

    O programa ira gerar dois arquivos temporários *resultado_flops.out* e *resultado_energy.out* que serão excluídos posteriomente

- Filtrando as métricas FLOPS_DP, FLOPS_AVX e Energy[J] utilizando o comando *grep*
    > grep -n "." resultado_flops.out | sed -n '1,10p' | cut -d: -f2- > resultado.out

    > grep -E 'Region (gera|soluciona)|DP \[MFLOP/s\]|AVX DP \[MFLOP/s\]' resultado_flops.out >> resultado.out

    > grep -E 'Region (gera|soluciona)|Energy \[J\]' resultado_energy.out >> resultado.out

- Removendo arquivos temporários
- Limpando diretório
    > make purge

#### Execução
Certifique-se de dar permissão de execução ao script usando 
> chmod +x bash.sh

E execute-o com

> ./bash.sh 

no mesmo diretório em que seu programa ajustePol está localizado.

## Estrutura
Todo o programa pode ser organizado nas seguintes etapas de construção:

1. Ler tabela de entrada
2. Calcular o intervalo [m(z), M(z)] para cada valor real z da tabela de pontos
3. Gerar sistema linear através do Método dos Mínimos Quadrados
4. Solucionar sistema linear com o Método de Eliminação de Gauss com Pivoteamento Parcial
5. Calcular resíduo 
6. Apresentar os coeficientes ai da equação de ajuste, resíduos calculados e tempo gasto

## Código
- **doubleType**

    Contém as funções auxiliares para lidarmos com os valores double em uma representação rigorosa de ponto flutuante.

- **interval**

    Contém as funções de aritmética intervalar como soma, subtração, divisão, multiplicação e potenciação de intervalos.

- **min_quadrados**

    Implementação do Método dos Mínimos Quadrados.

- **sistema_linear**

    Contém todas as funções para manipulação dos sistemas lineares, inclusive o Método de Eliminação de Gauss com Pivoteamento Parcial.

- **tabela**

    Funções para tratamento e armazenamento da tabela de pontos da entrada fornecida pelo usuário.

- **utils**

    Contém a função timestamp() que é utilizada no cálculo do tempo gasto pelas funções.

## Estrutura de dados
O programa utiliza quatro estrutura de dados diferentes:

### Double_t
Contém uma representação mais detalhada dos bits que contem a representação do double em ponto flutuante.

Utilizada para calcularmos a aritmética intervalar com uma representação rigorosa dos valores reais.
````
typedef union {
    int64_t i;
    double f;
    struct
    {   // Bitfields for exploration (64 bits = sign|exponent|mantissa)
        uint64_t mantissa : 52; // primeiros 52 bits (da direita para a esquerda)
        uint64_t exponent : 11; // próximos 11 bits
        uint64_t sign : 1;      // próximo bit (ou seja, o bit mais à esquerda)
    } parts;
} Double_t;
````

### INTERVAL_t 
  Utilizada para armazenar o intervalo de representação dos números

  Dado um número X qualquer

  - m: maior número de maquina menor ou igual a x
  - M: é o menor número de maquina maior ou igual a x

````
typedef struct {
    Double_t m; 
    Double_t M;
 } INTERVAL_t;
 ````


### SISTEMA_LINEAR_t
  Utilizada para definição do sistema linear

  - Matriz A: matriz de coeficientes
  - Vetor B: vetor de constantes
  - Vetor X: vetor de incognitas/solucao (contera os valores dos coeficientes ao final)

````
typedef struct {
  int n;
  INTERVAL_t **A;
  INTERVAL_t *b;
  INTERVAL_t *x;
} SISTEMA_LINEAR_t;
````

### TABELA_t
  Utilizada para armazenar a tabela de pontos de entrada

  - (x, y): pontos 
  - k: quantidade de pontos da tabela 

````
typedef struct {
  INTERVAL_t *x;
  INTERVAL_t *y;
  int k;
} TABELA_t;
````

## Resultados
O arquivo **resultado.out** contém a saída do programa com  as seguintes informações:
- Informações sobre a CPU
- Vetor dos coeficientes (ai)
- Vetor de resíduos
- Tempo gasto para gerar o sistema linear
- Tempo gasto para solucionar o sistema linear
-  DP [MFLOP/s] e AVX DP [MFLOP/s] para cada região marcada
-  Energy [J] para cada região marcada

Um exemplo de saída para o arquivo de entrada *teste.in* seria:

````
--------------------------------------------------------------------------------
CPU name:	Intel(R) Core(TM) i5-3317U CPU @ 1.70GHz
CPU type:	Intel Core IvyBridge processor
CPU clock:	1.70 GHz
--------------------------------------------------------------------------------
[4.60447424087895925e+04, 4.60448076482348698e+04]  [-4.87162919478108094e+01, -4.87162696126457106e+01]  [1.28889165374164970e-02, 1.28889223052770959e-02]  
[-5.78403721829236161e+00, -5.65677354548970257e+00]  [2.72255298517556988e+00, 2.85060926739679666e+00]  [4.49509374163462284e+00, 4.62359197741025341e+00]  [7.30682187136844519e+00, 7.43620747501845969e+00]  [-2.79258784309495666e+00, -2.66231025731102732e+00]  [-6.30896939191880790e+00, -6.17824408470332286e+00]  [-4.80313540179923847e+00, -4.67196121958548360e+00]  [-1.27508587272897955e+00, -1.14346166194299314e+00]  [2.67517919529198878e+00, 2.80725458821690666e+00]  [2.75312971759117886e+00, 2.88570274324158050e+00]  [2.93811625096680019e-01, 4.26611308883025231e-01]  
0.025147
0.000977
--------------------------------------------------------------------------------
Region gera-sistema-linear, Group 1: FLOPS_DP
|     DP [MFLOP/s]     |     604.2995 |
|   AVX DP [MFLOP/s]   |            0 |
Region soluciona-sistema-linear, Group 1: FLOPS_DP
|     DP [MFLOP/s]     |     101.1565 |
|   AVX DP [MFLOP/s]   |            0 |
--------------------------------------------------------------------------------
Region gera-sistema-linear, Group 1: ENERGY
|      Energy [J]      |            0 |
Region soluciona-sistema-linear, Group 1: ENERGY
|      Energy [J]      |            0 |
--------------------------------------------------------------------------------
````
## Códigos de erro
O código apresenta códigos de erro se encontrar qualquer problema na leitura do arquivo de entrada. 

O código de saída utilizao é o **exit(1)** e ele apresenta no stdout qual a origem do erro, por exemplo

> Erro ao ler o valor de N

> Erro ao ler o valor de K