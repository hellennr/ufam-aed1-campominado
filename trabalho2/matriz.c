#include "matriz.h"
#include <stdio.h>
#include <stdlib.h>

// Aloca uma matriz de inteiros com o número de linhas e colunas especificado.
int **aloca_matriz_int(int linhas, int colunas)
{
    int **matriz = (int **)malloc(linhas * sizeof(int *));
    if (matriz == NULL)
    {
        printf("Erro ao alocar memória para matriz de inteiros.\n");
        return NULL;
    }

    for (int i = 0; i < linhas; i++)
    {
        matriz[i] = (int *)malloc(colunas * sizeof(int));
        if (matriz[i] == NULL)
        {
            printf("Erro ao alocar memória para a linha %d da matriz de inteiros.\n", i);
            desaloca_matriz_int(matriz, i); // Libera as linhas já alocadas
            return NULL;
        }
    }
    return matriz;
}

// Libera a memória de uma matriz de inteiros.
void desaloca_matriz_int(int **matriz, int linhas)
{
    if (matriz == NULL) // Verifica se o ponteiro é válido
        return;

    for (int i = 0; i < linhas; i++)
    {
        free(matriz[i]);
    }
    free(matriz);
}

// Aloca uma matriz de caracteres com o número de linhas e colunas especificado.
char **aloca_matriz_char(int linhas, int colunas)
{
    char **matriz = (char **)malloc(linhas * sizeof(char *));
    if (matriz == NULL)
    {
        printf("Erro ao alocar memória para matriz de caracteres.\n");
        return NULL;
    }

    for (int i = 0; i < linhas; i++)
    {
        matriz[i] = (char *)malloc(colunas * sizeof(char));
        if (matriz[i] == NULL)
        {
            printf("Erro ao alocar memória para a linha %d da matriz de caracteres.\n", i);
            desaloca_matriz_char(matriz, i); // Libera as linhas já alocadas
            return NULL;
        }
    }
    return matriz;
}

// Libera a memória de uma matriz de caracteres.
void desaloca_matriz_char(char **matriz, int linhas)
{
    if (matriz == NULL) // Verifica se o ponteiro é válido
        return;

    for (int i = 0; i < linhas; i++)
    {
        free(matriz[i]);
    }
    free(matriz);
}