# Rubik's Cube Solver

Este projeto implementa um solucionador para o Cubo de Rubik utilizando o algoritmo de Thistlethwaite. O programa é capaz de encontrar uma solução para qualquer embaralhamento do cubo e exibir a solução visualmente usando OpenGL.

## Algoritmo de Thistlethwaite

O algoritmo de Thistlethwaite é um método para resolver o Cubo de Rubik em no máximo 52 movimentos. Ele funciona resolvendo o cubo em etapas, passando por uma série de subgrupos de movimentos. Cada subgrupo restringe progressivamente as possíveis configurações do cubo, até que ele esteja resolvido.

As etapas do algoritmo implementadas neste projeto são:

1.  **G0 → G1:** Orienta todas as bordas.
2.  **G1 → G2:** Orienta os cantos e posiciona as bordas da camada do meio.
3.  **G2 → G3:** Resolve a camada do meio e posiciona os cantos.
4.  **G3 → G4:** Resolve o cubo completamente.

Para cada etapa, o programa utiliza uma busca em largura (BFS) para encontrar a solução mais curta. As distâncias para cada estado do cubo são pré-calculadas e armazenadas em bancos de dados de padrões para acelerar a busca.

## Como Compilar e Executar

### Pré-requisitos

-   Um compilador C++20 (como g++ ou clang++)
-   OpenGL
-   GLUT

### Compilação

Para compilar o projeto, execute o seguinte comando:

```bash
make
```

Isso irá gerar o executável `rubik`.

### Gerando os Bancos de Dados de Padrões

Antes de resolver um cubo, você precisa gerar os bancos de dados de padrões. Para isso, execute:

```bash
./rubik -c
```

Este processo pode levar alguns minutos. Os bancos de dados serão salvos na pasta `database/`.

### Resolvendo um Cubo

Para resolver um cubo embaralhado, execute o programa passando a sequência de movimentos de embaralhamento como argumento. Por exemplo:

```bash
./rubik "F U' R2"
```

O programa irá então encontrar a solução e exibi-la em uma janela gráfica.

### Executando os Testes

Para executar os testes unitários, use o comando:

```bash
make test
```

## Estrutura do Projeto

-   `src/`: Contém o código-fonte do programa.
    -   `main.cpp`: Ponto de entrada do programa.
    -   `Cube.cpp`: Representação do Cubo de Rubik e suas operações.
    -   `Solver.cpp`: Implementação do algoritmo de Thistlethwaite.
    -   `Draw.cpp`: Funções para desenhar o cubo usando OpenGL.
    -   `animation.cpp`: Funções para animar os movimentos do cubo.
-   `include/`: Contém os arquivos de cabeçalho.
-   `database/`: Onde os bancos de dados de padrões são armazenados.
-   `tests/`: Contém os testes unitários.
-   `Makefile`: Arquivo de compilação do projeto.
