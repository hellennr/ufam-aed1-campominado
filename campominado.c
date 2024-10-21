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
int espalhamento(int **bombas, char **jogo, int linhas, int colunas, int x, int y);
void escolhe_dificuldade();

int main()
{
    int jogar_novamente = 1;
    while (jogar_novamente == 1)
    {
        escolhe_dificuldade(); // Começa o jogo pedindo a dificuldade
        printf("\nDeseja jogar novamente? (1 - Sim | 2 - Não)\n");
        scanf("%d", &jogar_novamente);
    }
    return 0;
}

int espalhamento(int **bombas, char **jogo, int linhas, int colunas, int x, int y)
{
    int reveladas = 0;

    // Se a célula já foi revelada, não faz nada
    if (jogo[x][y] != '.')
    {
        return 0;
    }

    // Revela a célula atual
    jogo[x][y] = bombas[x][y] + '0'; // Converte o valor numérico em caractere
    reveladas++;                     // Conta essa célula como revelada

    // Se a célula não for zero, para o flooding por aqui
    if (bombas[x][y] != 0)
    {
        return reveladas;
    }

    // Verifica apenas nas 4 direções (cima, baixo, esquerda, direita)
    if (x > 0)
    { // Cima
        reveladas += espalhamento(bombas, jogo, linhas, colunas, x - 1, y);
    }
    if (x < linhas - 1)
    { // Baixo
        reveladas += espalhamento(bombas, jogo, linhas, colunas, x + 1, y);
    }
    if (y > 0)
    { // Esquerda
        reveladas += espalhamento(bombas, jogo, linhas, colunas, x, y - 1);
    }
    if (y < colunas - 1)
    { // Direita
        reveladas += espalhamento(bombas, jogo, linhas, colunas, x, y + 1);
    }

    return reveladas; // Retorna o total de células reveladas por este flooding
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

    // Inicializa tudo sem bomba e com '.' cobrindo as células
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            bombas[i][j] = 0; // Sem bombas inicialmente
            jogo[i][j] = '.'; // Campo coberto com '.'
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
            if (bombas[i][j] == -1)
            {
                printf("🚩 ");
            }
            else
            {
                printf("%2d ", bombas[i][j]);
            }
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

// Função que imprime o campo com as bombas
void printa_bombas_derrota(int **bombas, int linhas, int colunas, int linha_derrota, int coluna_derrota)
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
            if (i == linha_derrota && j == coluna_derrota)
            {
                printf("💥 ");
            }
            else if (bombas[i][j] == -1)
            {
                printf("💣 ");
            }
            else if (bombas[i][j] == 0)
            {
                printf("   ");
            }
            else
            {
                printf("%2d ", bombas[i][j]);
            }
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
            if (jogo[i][j] == '0')
            {
                printf("   "); // Imprime o conteúdo da célula (pode ser '.' ou número)
            }
            else
            {
                printf(" %c ", jogo[i][j]); // Imprime o conteúdo da célula (pode ser '.' ou número)
            }
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
    printf("2 - Médio\t(20x20, 50 bombas)\n");
    printf("3 - Difícil\t(30x30, 100 bombas)\n");

    int dificuldade;
    scanf("%d", &dificuldade);

    // Chama a função gameplay com o tamanho e número de bombas de acordo com a dificuldade escolhida
    switch (dificuldade)
    {
    case 1:
        gameplay(10, 10, 15);
        break;
    case 2:
        gameplay(20, 20, 50);
        break;
    case 3:
        gameplay(30, 30, 100);
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
    char entrada[20];

    while (fim != 1)
    {
        printa_jogo(jogo, linhas, colunas); // Mostra o estado atual do jogo
        printf("\nDigite uma linha e coluna (1-%d): ", linhas);

        // Lê a entrada como string
        fgets(entrada, sizeof(entrada), stdin);

        // Tenta fazer a leitura de dois inteiros separados por vírgula
        if (sscanf(entrada, "%d,%d", &x, &y) != 2)
        {
            printf("\nEntrada inválida! Por favor, digite no formato linha,coluna.\n\n");
            printf("\n");
        }
        else
        {
            // Verifica se a jogada está dentro dos limites
            if (x < 1 || x > linhas || y < 1 || y > colunas)
            {
                printf("\nCoordenadas inválidas! Tente novamente.\n\n");
            }
            else
            {
                x--; // Ajusta para o índice da matriz
                y--; // Ajusta para o índice da matriz

                if (jogo[x][y] != '.')
                { // Se o jogador já escolheu essa célula
                    printf("Coordenadas já escolhidas! Tente novamente.\n\n");
                }
                else
                {
                    if (bombas[x][y] == 0)
                    { // Se a célula for zero, faz o flooding
                        revelados += espalhamento(bombas, jogo, linhas, colunas, x, y);
                    }
                    else if (bombas[x][y] != -1)
                    {                                    // Se for segura, apenas revela
                        jogo[x][y] = bombas[x][y] + '0'; // Converte o número pra char
                        revelados++;                     // Conta essa célula como revelada
                    }
                    else
                    {
                        printf("\n\t💀 Fim de jogo!\n\n");
                        printa_bombas_derrota(bombas, linhas, colunas, x, y);
                        fim = 1;
                    }

                    if (revelados == total_sem_bomba)
                    { // Se revelou todas as células seguras
                        printf("\n\t🌸 Parabéns, você venceu!\n\n");
                        printa_bombas(bombas, linhas, colunas);
                        fim = 1;
                    }
                }
            }
        }
    }

    // Libera a memória no final do jogo
    desaloca_matriz_char(jogo, linhas);
    desaloca_matriz_int(bombas, linhas);
}
