# Exercício 05 - Integração e Método de Monte Carlo
## Alunos
- Eduardo Purkote (GRR20182960)
- Mariana Moreira dos Santos (GRR20186554)

## Execução
Para compilar o programa: 
> make

Caso deseje ativar a flag de DEBUG:
> make DEBUG=yes

Se você deseja limpar o diretório com os arquivos executáveis:
> make purge

## Otimização
Aprimoramos o código principalmente na função do **Método dos Retângulos**, incorporando a técnica de *loop unrolling* com um bloco de tamanho 4 durante a etapa principal de otimização. Além disso, **evitamos o uso da função pow()** no cálculo da função de Styblinski-Tang, escolha essa que torna o código mais eficiente. 

Essas otimizações desempenharam um papel crucial no aprimoramento do código, especialmente devido à natureza exaustiva da função do Método dos Retângulos, que se intensificava significativamente à medida que o número de amostras aumentava.

Com fins didáticos, incluímos uma **implementação adicional do Método dos Retângulos sem a otimização**, permitindo assim a comparação direta entre as duas abordagens.

## Testes de execução
### Metodologia
#### Parâmetros
Todos os testes foram realizados com os seguintes parametros:
- a = -4
- b = 4

Os **testes de comparação entre o Método dos Retângulos e o Método de Monte Carlo** foram conduzidos com a configuração específica de **n_variaveis = 2**. Essa escolha decorre do fato de que o Método dos Retângulos foi implementado exclusivamente para lidar com 2 dimensões.

#### Número de execuções
Os números de tempo de execução aqui apresentados, para os dois métodos, são resultado da média de 10 execuções para cada teste. 

### Resultados
#### 1) *Método dos Retângulos* vs *Método de Monte Carlo*
    "Compare os resultados para n = 2 dimensões nos métodos dos Retângulos e de Monte Carlo."

    "Quantos pontos deveriam ser usados no método dos Retângulos para que seu cálculo fosse o mais próximo possível do resultado gerado por Monte Carlo para 10e7 amostras? Compare também os tempos de execução de cada integração."

O resultado gerado pelo Monte Carlo para 10e7 amostras tem o seguinte resultado:
```` 
Metodo de Monte Carlo (x, y).
a = (-4.000000), b = (4.000000), n = (10000000), variaveis = 2
Tempo decorrido: 308 seg.
Método de Monte Carlo: -2184.499637 
````

O número de amostras utilizado no Método dos Retângulos para que seu resultado chegasse ao mais próximo possível do resultado gerado por Monte Carlo **foi de 10e5 amostras**:
```` 
Metodo dos Retângulos (x, y).
a = (-4.000000), b = (4.000000), n = (100000), h = (8e-05)
Tempo decorrido: 16809 seg.
Método dos Retângulados - Otimizado: -2184.546132
```` 

Em relação aos tempos de execução o Método de Monte Carlo é 54x mais rápido que o Método do Retângulos.

##### Discussão
A precisão do Método dos Retângulos está diretamente vinculada à quantidade de retângulos, ou seja, ao número de amostras utilizadas no cálculo. No entanto, esse aumento na quantidade de retângulos também implica em uma maior carga computacional.
Por outro lado, o Método de Monte Carlo, por ser estocástico, demonstra maior flexibilidade para lidar com funções complexas ou regiões intricadas. No entanto, sua precisão está sujeita a variações estocásticas. Em outras palavras, devido à sua natureza aleatória ou probabilística, o resultado pode oscilar sem seguir um padrão visível.

**Em resumo, o Método dos Retângulos é menos eficiente porém é mais preciso se o numero de retângulos for grande o suficiente. Isso o torna um ótimo candidato a integração de funções simples, especialmente se a precisão é uma prioridade e a carga computacional não é um problema.** 

**Já o Método de Monte Carlo é menos preciso pois sua precisão está sujeita a variações estocatiscas, porém mais eficiente. Portanto, pode ser a escolha mais adequada em problemas complexos, quado a região de integração é difícil.**

#### 2) *Método de Monte Carlo*
    "Compare os resultados para n = 2, 4, 8 para o método de Monte Carlo;"

Para todos os testes de dimensão, consideramos o mesmo número de amostras (n = 10.000.000 ou 10e7).
- *n = 2*

    ```` 
    Metodo de Monte Carlo (x, y).
    a = (-4.000000), b = (4.000000), n = (10000000), variaveis = 2
    Tempo decorrido: 308 seg.
    Método de Monte Carlo: -2184.499637 
    ````

- *n = 4*

    ```` 
    Metodo de Monte Carlo (x, y).
    a = (-4.000000), b = (4.000000), n = (10000000), variaveis = 4
    Tempo decorrido: 876 seg.
    Método de Monte Carlo: -279599.832820
    ```` 

- *n = 8*
    ```` 
    Metodo de Monte Carlo (x, y).
    a = (-4.000000), b = (4.000000), n = (10000000), variaveis = 8
    Tempo decorrido: 1807 seg.
    Método de Monte Carlo: -2290394835.399107
    ````
#### Discussão
O principal ponto de análise desses resultados é a ocorrência de um fenômeno matemático chamado **maldição da dimensionalidade**. Esse fenômeno é caracterizado pelo aumento da complexidade e dos requisitos computacionais à medida que o número de dimensões aumenta. Nestes casos de exemplo, estamos aumentando as dimensões, mas não aumentamos o número de amostras. Isso pode levar a uma distribuição não uniforme de amostras no espaço de busca, tornando a estimação menos precisa. 

Por fim, em relação aos tempos de execução, o tempo médio duplicou com o aumento das dimensões. 