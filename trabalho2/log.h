#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <time.h>

// Estrutura para armazenar informações do log
typedef struct
{
    FILE *arquivo;         // Ponteiro para o arquivo de log
    char nome_arquivo[50]; // Nome do arquivo de log
} Log;

// Função para inicializar o log
// Abre ou cria o arquivo log.txt e grava a data/hora de início da partida.
//
// Parâmetros:
//   - log: ponteiro para a estrutura de Log que será inicializada.
//
// Exemplo de uso:
//   Log log;
//   inicializa_log(&log);

void inicializa_log(Log *log);

// Função para registrar uma jogada no log
// Adiciona ao log o estado atual da matriz e a jogada do jogador, indicando
// se a jogada foi válida ou inválida.
//
// Parâmetros:
//   - log: ponteiro para a estrutura de Log.
//   - matriz: matriz atual do jogo.
//   - linhas: número de linhas da matriz.
//   - colunas: número de colunas da matriz.
//   - x: linha escolhida pelo jogador.
//   - y: coluna escolhida pelo jogador.
//   - jogada_valida: inteiro (1 para jogada válida, 0 para jogada inválida).
//
// Exemplo de uso:
//   registra_log(&log, matriz, 10, 10, 2, 3, 1);

void registra_log(Log *log, char **matriz, int linhas, int colunas, int x, int y, int jogada_valida);

// Função para finalizar o log
// Fecha o arquivo de log corretamente.
//
// Parâmetros:
//   - log: ponteiro para a estrutura de Log.
//
// Exemplo de uso:
//   finaliza_log(&log);

void finaliza_log(Log *log);

#endif
