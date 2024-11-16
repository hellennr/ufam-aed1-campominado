#include "matriz.h"
#include <stdio.h>
#include <stdlib.h>


// Função que aloca uma matriz de inteiros (linhas x colunas)
int **aloca_matriz_int(int linhas, int colunas)
{
    int **matriz = (int **)malloc(linhas * sizeof(int *));
    for (int i = 0; i < linhas; i++)
    {
        matriz[i] = (int *)malloc(colunas * sizeof(int));
    }
    return matriz;
}

// Função pra liberar a memória da matriz de inteiros
void desaloca_matriz_int(int **matriz, int linhas)
{
    for (int i = 0; i < linhas; i++)
    {
        free(matriz[i]);
    }
    free(matriz);
}

// Função que aloca uma matriz de caracteres (linhas x colunas)
char **aloca_matriz_char(int linhas, int colunas)
{
    char **matriz = (char **)malloc(linhas * sizeof(char *));
    for (int i = 0; i < linhas; i++)
    {
        matriz[i] = (char *)malloc(colunas * sizeof(char));
    }
    return matriz;
}

// Função pra liberar a memória da matriz de caracteres
void desaloca_matriz_char(char **matriz, int linhas)
{
    for (int i = 0; i < linhas; i++)
    {
        free(matriz[i]);
    }
    free(matriz);
}
