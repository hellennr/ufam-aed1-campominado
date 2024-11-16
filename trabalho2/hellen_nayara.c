#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Pra gerar números aleatórios nas bombas
#include "matriz.h"
#include "log.h"

void conta_vizinhos(int **bombas, int linhas, int colunas);
void inicializar_campo(int **bombas, char **jogo, int linhas, int colunas, int num_bombas);
void printa_bombas(int **bombas, int linhas, int colunas);
void gameplay(int linhas, int colunas, int num_bombas);
int espalhamento(int **bombas, char **jogo, int linhas, int colunas, int x, int y);
void escolhe_dificuldade();

int main()
{
    escolhe_dificuldade(); // Começa o jogo pedindo a dificuldade
    return 0;
}

int espalhamento(int **bombas, char **jogo, int linhas, int colunas, int x, int y)
{
    int reveladas = 0; // Conta células reveladas.

    if (jogo[x][y] != 'x')
    {
        return 0; // Já foi revelada, não faz nada.
    }

    jogo[x][y] = bombas[x][y] + '0'; // Marca como revelada.
    reveladas++;                     // Soma 1 ao contador.

    if (bombas[x][y] != 0)
    {
        return reveladas; // Para o flooding se a célula não for 0.
    }

    // Percorre as 8 vizinhas.
    for (int dx = -1; dx <= 1; dx++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            if (!(dx == 0 && dy == 0)) // Pula a própria célula.
            {
                int novo_x = x + dx;
                int novo_y = y + dy;

                // Checa se a vizinha está dentro do campo.
                if (novo_x >= 0 && novo_x < linhas && novo_y >= 0 && novo_y < colunas)
                {
                    reveladas += espalhamento(bombas, jogo, linhas, colunas, novo_x, novo_y);
                }
            }
        }
    }

    return reveladas; // Retorna o total de células abertas.
}

// Função que conta quantas bombas tem ao redor de cada célula
void conta_vizinhos(int **bombas, int linhas, int colunas)
{
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            if (bombas[i][j] != -1) // Pula células que já têm bomba.
            {
                int cont_bombas = 0;

                // Checa todas as vizinhas (8 direções).
                for (int k = -1; k <= 1; k++)
                {
                    for (int l = -1; l <= 1; l++)
                    {
                        int pos_x = i + k;
                        int pos_y = j + l;

                        // Conta só as vizinhas válidas e que são bombas.
                        if (pos_x >= 0 && pos_x < linhas && pos_y >= 0 && pos_y < colunas && bombas[pos_x][pos_y] == -1)
                        {
                            cont_bombas++;
                        }
                    }
                }

                bombas[i][j] = cont_bombas; // Salva quantas bombas têm ao redor.
            }
        }
    }
}

// Função que inicializa o campo, coloca as bombas e conta os vizinhos
void inicializar_campo(int **bombas, char **jogo, int linhas, int colunas, int num_bombas)
{
    srand(time(NULL)); // Gera uma semente pra criar números aleatórios.

    // Inicializa o campo vazio e todo coberto.
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            bombas[i][j] = 0; // Sem bombas.
            jogo[i][j] = 'x'; // Todas as células cobertas.
        }
    }

    // Coloca as bombas em posições aleatórias.
    int bombas_colocadas = 0;
    while (bombas_colocadas < num_bombas)
    {
        int rand_linha = rand() % linhas;
        int rand_coluna = rand() % colunas;

        if (bombas[rand_linha][rand_coluna] != -1) // Evita colocar duas bombas no mesmo lugar.
        {
            bombas[rand_linha][rand_coluna] = -1; // Marca a posição como bomba.
            bombas_colocadas++;
        }
    }

    conta_vizinhos(bombas, linhas, colunas); // Calcula quantas bombas têm ao redor de cada célula.
}

// Função que imprime o campo com as bombas
void printa_bombas(int **bombas, int linhas, int colunas)
{
    // Imprime o número das colunas no topo
    printf("     ");
    for (int j = 1; j <= colunas; j++)
    {
        if (j < 10)
        {
            printf("%d  ", j); // Alinha para colunas de 1 casa decimal
        }
        else
        {
            printf("%d ", j); // Alinha para colunas de 2 casas
        }
    }
    printf("\n");

    // Linha superior da caixa
    printf("   ");
    for (int j = 0; j < colunas; j++)
    {
        printf("---");
    }
    printf("--\n");

    // Imprime as bombas com os números das linhas e bordas
    for (int i = 0; i < linhas; i++)
    {
        if (i < 9)
        {
            printf("%d  |", i + 1); // Imprime o número da linha
        }
        else
        {
            printf("%d |", i + 1); // Ajusta o espaçamento para 2 dígitos
        }

        for (int j = 0; j < colunas; j++)
        {
            printf("%2d ", bombas[i][j]);
        }
        printf("|\n");
    }

    // Linha inferior da caixa
    printf("   ");
    for (int j = 0; j < colunas; j++)
    {
        printf("---");
    }
    printf("--\n");
}

// Função que imprime o estado atual do jogo (campo coberto ou descoberto)
void printa_jogo(char **jogo, int linhas, int colunas)
{
    // Imprime o número das colunas no topo
    printf("     ");
    for (int j = 1; j <= colunas; j++)
    {
        if (j < 10)
        {
            printf("%d  ", j); // Alinha para colunas de 1 casa decimal
        }
        else
        {
            printf("%d ", j); // Alinha para colunas de 2 casas
        }
    }
    printf("\n");

    // Linha superior da caixa
    printf("   ");
    for (int j = 0; j < colunas; j++)
    {
        printf("---");
    }
    printf("--\n");

    // Imprime o campo de jogo com as células cobertas ou reveladas
    for (int i = 0; i < linhas; i++)
    {
        if (i < 9)
        {
            printf("%d  |", i + 1); // Imprime o número da linha
        }
        else
        {
            printf("%d |", i + 1); // Ajusta o espaçamento para 2 dígitos
        }

        for (int j = 0; j < colunas; j++)
        {
            printf(" %c ", jogo[i][j]);
        }
        printf("|\n");
    }

    // Linha inferior da caixa
    printf("   ");
    for (int j = 0; j < colunas; j++)
    {
        printf("---");
    }
    printf("--\n");
}

// Função que pede a dificuldade e chama a função que começa o jogo
void escolhe_dificuldade()
{
    printf("Escolha uma dificuldade:\n");
    printf("1 - Fácil\t(10x10, 15 bombas)\n");
    printf("2 - Médio\t(20x20, 60 bombas)\n");
    printf("3 - Difícil\t(30x30, 135 bombas)\n\n");

    int dificuldade;
    if (scanf("%d", &dificuldade) != 1)
    {
        printf("Erro ao ler a dificuldade.\n");
        return;
    }

    // Chama a função gameplay com o tamanho e número de bombas de acordo com a dificuldade escolhida
    switch (dificuldade)
    {
    case 1:
        gameplay(10, 10, 15);
        break;
    case 2:
        gameplay(20, 20, 60);
        break;
    case 3:
        gameplay(30, 30, 135);
        break;
    default:
        printf("Digite um número de 1 a 3.\n");
        break;
    }
}

void gameplay(int linhas, int colunas, int num_bombas)
{
    Log log;
    int **bombas = aloca_matriz_int(linhas, colunas);
    char **jogo = aloca_matriz_char(linhas, colunas);

    inicializa_log(&log);
    inicializar_campo(bombas, jogo, linhas, colunas, num_bombas);

    int fim = 0;
    int x, y;
    int revelados = 0;
    int total_sem_bomba = (linhas * colunas) - num_bombas;

    while (fim == 0)
    {
        printa_jogo(jogo, linhas, colunas);
        printf("\nDigite uma linha e coluna no formato linha,coluna (1-%d):\n", linhas);

        int resultado_scanf = scanf("%d,%d", &x, &y);

        if (resultado_scanf == EOF)
        {
            printf("\nFim do arquivo detectado, mostrando solução.\n");
            printa_bombas(bombas, linhas, colunas);
            registra_log(&log, jogo, linhas, colunas, -1, -1, 0); // Log para EOF (não é uma jogada válida)
            fim = 1;                                              // Finaliza o loop
        }
        else if (resultado_scanf != 2)
        {
            printf("\nErro ao ler as coordenadas.\n");
            registra_log(&log, jogo, linhas, colunas, x, y, 0); // Registra erro de entrada
        }
        else if (x < 1 || x > linhas || y < 1 || y > colunas)
        {
            printf("\nCoordenadas (%d,%d) fora dos limites! Tente novamente.\n", x, y);
            registra_log(&log, jogo, linhas, colunas, x - 1, y - 1, 0); // Registra jogada inválida
        }
        else if (jogo[x - 1][y - 1] != 'x')
        {
            printf("Coordenadas (%d,%d) já escolhidas! Tente novamente.\n", x, y);
            registra_log(&log, jogo, linhas, colunas, x - 1, y - 1, 0); // Registra jogada inválida
        }
        else
        {
            x--; // Ajusta para o índice da matriz
            y--;

            if (bombas[x][y] == -1)
            {
                registra_log(&log, jogo, linhas, colunas, x, y, 1); // Registra jogada válida antes de perder
                printf("\n\t\tgame over\n\n");
                printa_bombas(bombas, linhas, colunas);
                fim = 1;
            }
            else
            {
                if (bombas[x][y] == 0)
                {
                    revelados += espalhamento(bombas, jogo, linhas, colunas, x, y);
                }
                else
                {
                    jogo[x][y] = bombas[x][y] + '0';
                    revelados++;
                }

                registra_log(&log, jogo, linhas, colunas, x, y, 1); // Registra jogada válida

                if (revelados == total_sem_bomba)
                {
                    printf("\n\t\tparabens vc eh fera\n\n");
                    fim = 1;
                }
            }
        }
    }

    finaliza_log(&log);
    desaloca_matriz_char(jogo, linhas);
    desaloca_matriz_int(bombas, linhas);
}
