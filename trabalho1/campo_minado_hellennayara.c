#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Pra gerar números aleatórios nas bombas

int **aloca_matriz_int(int linhas, int colunas);
void desaloca_matriz_int(int **matriz, int linhas);
char **aloca_matriz_char(int linhas, int colunas);
void desaloca_matriz_char(char **matriz, int linhas);
void conta_vizinhos(int **bombas, int linhas, int colunas);
void inicializar_campo(int **bombas, char **jogo, int linhas, int colunas, int num_bombas);
void printa_bombas(int **bombas, int linhas, int colunas);
void gameplay(int linhas, int colunas, int num_bombas);
void escolhe_dificuldade();

int main()
{
    escolhe_dificuldade(); // Começa o jogo pedindo a dificuldade
    return 0;
}

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

// Função que conta quantas bombas tem ao redor de cada célula
void conta_vizinhos(int **bombas, int linhas, int colunas)
{
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            // Se não for bomba, conta quantas bombas tem ao redor
            if (bombas[i][j] != -1)
            {
                int cont_bombas = 0;
                // Verifica os vizinhos (inclui diagonais)
                for (int k = -1; k <= 1; k++)
                {
                    for (int l = -1; l <= 1; l++)
                    {
                        int pos_x = i + k;
                        int pos_y = j + l;

                        // Se estiver dentro do campo e for bomba, incrementa o contador
                        if (pos_x >= 0 && pos_x < linhas && pos_y >= 0 && pos_y < colunas && bombas[pos_x][pos_y] == -1)
                        {
                            cont_bombas++;
                        }
                    }
                }
                bombas[i][j] = cont_bombas; // Atualiza a célula com o número de bombas vizinhas
            }
        }
    }
}

// Função que inicializa o campo, coloca as bombas e conta os vizinhos
void inicializar_campo(int **bombas, char **jogo, int linhas, int colunas, int num_bombas)
{
    srand(time(NULL)); // Semente pra gerar números aleatórios

    // Inicializa tudo sem bomba e com 'x' cobrindo as células
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            bombas[i][j] = 0; // Sem bombas inicialmente
            jogo[i][j] = 'x'; // Campo coberto com 'x'
        }
    }

    // Coloca as bombas aleatoriamente
    int bombas_colocadas = 0;
    while (bombas_colocadas < num_bombas)
    {
        int rand_linha = rand() % linhas;
        int rand_coluna = rand() % colunas;

        if (bombas[rand_linha][rand_coluna] != -1)
        {                                         // Só coloca a bomba se o lugar estiver livre
            bombas[rand_linha][rand_coluna] = -1; // Coloca a bomba
            bombas_colocadas++;
        }
    }

    conta_vizinhos(bombas, linhas, colunas); // Conta quantas bombas tem ao redor de cada célula
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
    printf("1 - Fácil\t(10x10, 3 bombas)\n");
    printf("2 - Médio\t(20x20, 6 bombas)\n");
    printf("3 - Difícil\t(30x30, 9 bombas)\n");

    int dificuldade;
    scanf("%d", &dificuldade);

    // Chama a função gameplay com o tamanho e número de bombas de acordo com a dificuldade escolhida
    switch (dificuldade)
    {
    case 1:
        gameplay(10, 10, 3);
        break;
    case 2:
        gameplay(20, 20, 6);
        break;
    case 3:
        gameplay(30, 30, 9);
        break;
    default:
        printf("Digite um número de 1 a 3.\n");
        break;
    }
}

// Função principal do jogo, que controla as jogadas e verifica se o jogador ganhou ou perdeu
void gameplay(int linhas, int colunas, int num_bombas)
{
    int **bombas = aloca_matriz_int(linhas, colunas);
    char **jogo = aloca_matriz_char(linhas, colunas);

    inicializar_campo(bombas, jogo, linhas, colunas, num_bombas);

    int fim = 0;
    int x, y;
    int revelados = 0;
    int total_sem_bomba = (linhas * colunas) - num_bombas; // Quantas células seguras o jogador precisa descobrir

    while (fim != 1)
    {
        printa_jogo(jogo, linhas, colunas); // Mostra o estado atual do jogo
        printf("\nDigite uma linha e coluna (1-%d): ", linhas);
        
        scanf("%d,%d", &x, &y); // Jogada com vírgula (lembrar de colocar a vírgula!!)
        printf("\n");

        // Verifica se a jogada está dentro dos limites
        if (x < 1 || x > linhas || y < 1 || y > colunas)
        {
            printf("\nCoordenadas inválidas!\n\n");
        }
        else
        {
            x--; // Ajusta para o índice da matriz
            y--; // Ajusta para o índice da matriz

            if (jogo[x][y] != 'x')
            { // Se o jogador já escolheu essa célula
                printf("Coordenadas já escolhidas!\n\n");
            }
            else
            {
                if (bombas[x][y] != -1)
                {                                    // Não é bomba, então revela
                    jogo[x][y] = bombas[x][y] + '0'; // Converte o número pra char
                    revelados++;                     // Conta como uma célula segura descoberta
                    if (revelados == total_sem_bomba)
                    { // Se revelou todas as células seguras
                        printf("parabéns, vc eh fera\n\n");
                        printa_bombas(bombas, linhas, colunas);
                        fim = 1;
                    }
                }
                else
                {
                    printf("game over\n\n");
                    printa_bombas(bombas, linhas, colunas);
                    fim = 1;
                }
            }
        }
    }

    // Libera a memória no final do jogo
    desaloca_matriz_char(jogo, linhas);
    desaloca_matriz_int(bombas, linhas);
}
