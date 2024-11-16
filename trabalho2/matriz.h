#ifndef MATRIZ_H
#define MATRIZ_H

int **aloca_matriz_int(int linhas, int colunas);
void desaloca_matriz_int(int **matriz, int linhas);
char **aloca_matriz_char(int linhas, int colunas);
void desaloca_matriz_char(char **matriz, int linhas);

#endif