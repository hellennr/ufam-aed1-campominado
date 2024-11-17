#include "log.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Função para inicializar o log
void inicializa_log(Log *log)
{
    // Define o nome do arquivo
    strcpy(log->nome_arquivo, "log.txt");

    // Abre o arquivo para escrita (apaga conteúdo anterior)
    log->arquivo = fopen(log->nome_arquivo, "w");
    if (log->arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo de log: %s\n", log->nome_arquivo);
        exit(1);
    }

    // Grava a data e hora de início no arquivo
    time_t agora = time(NULL);
    char *data_hora = ctime(&agora);

    if (data_hora == NULL)
    {
        printf("Erro ao obter a data e hora.\n");
        exit(1);
    }

    fprintf(log->arquivo, "Início do jogo: %s\n", data_hora);
}

// Função para registrar o estado atual da matriz e a jogada
void registra_log(Log *log, char **matriz, int linhas, int colunas, int x, int y, int jogada_valida)
{
    if (log->arquivo == NULL)
    {
        printf("Erro: log não inicializado.\n");
        return;
    }

    // Registra se a jogada foi válida ou inválida
    if (jogada_valida)
    {
        fprintf(log->arquivo, "Jogada válida: linha %d, coluna %d\n", x + 1, y + 1);
    }
    else
    {
        fprintf(log->arquivo, "Jogada inválida: linha %d, coluna %d\n", x + 1, y + 1);
    }

    // Registra o estado atual da matriz
    fprintf(log->arquivo, "Estado atual do campo:\n");
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            fprintf(log->arquivo, "%c ", matriz[i][j]);
        }
        fprintf(log->arquivo, "\n");
    }
    fprintf(log->arquivo, "\n");

    // Força a gravação no arquivo
    fflush(log->arquivo);
}

// Função para finalizar o log
void finaliza_log(Log *log)
{
    if (log->arquivo != NULL)
    {
        fclose(log->arquivo);
        printf("Log finalizado e arquivo fechado com sucesso.\n");
    }
    else
    {
        printf("Erro: arquivo de log não estava aberto.\n");
    }
}
