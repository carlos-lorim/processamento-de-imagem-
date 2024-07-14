# ![C++](https://upload.wikimedia.org/wikipedia/commons/thumb/1/18/ISO_C%2B%2B_Logo.svg/64px-ISO_C%2B%2B_Logo.svg.png)

## Objetivo

Adquirir conhecimentos de manipulação de imagens em formato de matrizes, implementando funcionalidades que geram novas imagens a partir de imagens carregadas de arquivos-texto em formato PGM.

## Descrição

O aplicativo desenvolvido no projeto deve ter um menu de opções que permita ler a imagem de entrada na opção 1 em formato PGM e, para cada funcionalidade implementada, ter outras opções em que, uma vez selecionada, gere um arquivo-texto de mesmo formato PGM.

### Formato do Arquivo de Imagem PGM

- **1ª linha**: string "P2";
- **2ª linha**: quantidade de colunas em inteiro, seguida de um espaço e seguida de quantidade de linhas em inteiro;
- **3ª linha**: o valor máximo de tons de cinza em inteiros;
- **Da 4ª linha em diante**: valores inteiros de todos os pixels da imagem entre zero e o valor máximo de tons de cinza da 3ª linha, separados por espaços.

## Requisitos

O aplicativo deverá:

- Ler uma imagem de entrada criada pelos autores em formato PGM;
- Criar um menu de operações que serão realizadas sobre a imagem de entrada indicada;
- Cada operação deve estar em uma função C/C++;
- Os comandos `cin` e `cout` só podem ser utilizados na função `main`;
- Escrever um arquivo-texto de saída para cada operação realizada;
- Para todas as operações, os valores de tons de cinza dos pixels devem estar entre zero e o valor máximo;

## Operações

As operações que devem ser implementadas são:

1. **Escurecer ou clarear a imagem** por um fator informado pelo usuário;
2. **Encontrar a imagem negativa**;
3. **Binarizar a imagem** por um fator informado pelo usuário;
4. **Iconizar a imagem**, ou seja, reduzir a imagem de entrada para uma imagem de 64 x 64 pixels;
5. **Criar ruídos na imagem**;
6. **Aplicar um filtro para suavizar a imagem**, escolha entre linear (escolha uma máscara) ou não-linear.

## Como Usar

1. Execute o aplicativo.
2. Escolha a opção 1 para carregar a imagem de entrada no formato PGM.
3. Selecione uma das operações do menu para manipular a imagem.
4. O aplicativo irá gerar um arquivo-texto de saída no formato PGM para cada operação realizada.

## Exemplo de Uso

```bash
./image_processor
1. Carregar imagem PGM
2. Escurecer/Clarear imagem
3. Encontrar imagem negativa
4. Binarizar imagem
5. Iconizar imagem
6. Criar ruídos na imagem
7. Aplicar filtro para suavizar imagem
8. Sair
Escolha uma opção: 
