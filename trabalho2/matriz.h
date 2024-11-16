#ifndef MATRIZ_H
#define MATRIZ_H

// Função que aloca uma matriz de inteiros com o número de linhas e colunas especificado
// A matriz é alocada dinamicamente utilizando a função malloc, e é retornada como um ponteiro
// para ponteiro de inteiros (int**).
//
// Parâmetros:
//   - linhas: número de linhas da matriz.
//   - colunas: número de colunas da matriz.
//
// Retorno:
//   - Retorna um ponteiro para a matriz alocada dinamicamente.
//
// Exemplo de uso:
//   int **matriz = aloca_matriz_int(5, 5); // Aloca uma matriz 5x5 de inteiros.

int **aloca_matriz_int(int linhas, int colunas);

// Função para desalocar a memória de uma matriz de inteiros previamente alocada.
// A função percorre cada linha da matriz e libera a memória alocada para cada uma,
// em seguida libera a memória da matriz em si.
//
// Parâmetros:
//   - matriz: ponteiro para a matriz que será desalocada.
//   - linhas: número de linhas da matriz, necessário para percorrer corretamente a estrutura.
//
// Exemplo de uso:
//   desaloca_matriz_int(matriz, 5); // Libera a memória de uma matriz 5x5 de inteiros.

void desaloca_matriz_int(int **matriz, int linhas);

// Função que aloca uma matriz de caracteres com o número de linhas e colunas especificado.
// Assim como a função anterior, a alocação é feita dinamicamente e a função retorna um ponteiro
// para a matriz de caracteres (char**).
//
// Parâmetros:
//   - linhas: número de linhas da matriz.
//   - colunas: número de colunas da matriz.
//
// Retorno:
//   - Retorna um ponteiro para a matriz de caracteres alocada dinamicamente.
//
// Exemplo de uso:
//   char **matriz_char = aloca_matriz_char(4, 4); // Aloca uma matriz 4x4 de caracteres.

char **aloca_matriz_char(int linhas, int colunas);

// Função para desalocar a memória de uma matriz de caracteres previamente alocada.
// Ela percorre cada linha da matriz e libera a memória de cada uma delas, além de liberar a
// memória da estrutura de matriz.
//
// Parâmetros:
//   - matriz: ponteiro para a matriz que será desalocada.
//   - linhas: número de linhas da matriz, necessário para percorrer corretamente a estrutura.
//
// Exemplo de uso:
//   desaloca_matriz_char(matriz_char, 4); // Libera a memória de uma matriz 4x4 de caracteres.

void desaloca_matriz_char(char **matriz, int linhas);

#endif