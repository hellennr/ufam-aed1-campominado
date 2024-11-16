# Campo Minado em C (versão 2.0)

Este repositório contém uma implementação simples de um jogo de Campo Minado em linguagem C.
O objetivo do jogo é selecionar todas as células seguras sem selecionar nenhuma mina.
É um jogo implementado no terminal.

Esta é a segunda versão do trabalho, com aprimoramentos a partir do trabalho inicial.

## Funcionalidades
- Escolha de dificuldade (fácil, médio, difícil).
- Distribuição aleatória de bombas no campo.
- Contagem de bombas ao redor de cada célula.
- Detecção de vitória ao revelar todas as células seguras.
- Detecção de derrota ao escolher uma célula com bomba.
- Implementação de **espalhamento** para revelar automaticamente as células ao redor quando o jogador escolhe uma célula com valor zero.
- Log completo da partida em um arquivo.
- Aceita entrada a partir de um arquivo descrevendo as jogadas.

### Principais Funções

#### `int main()`
Esta função inicia o jogo e permite ao jogador decidir se quer jogar novamente após cada partida. Ela chama a função `escolhe_dificuldade()` para iniciar o jogo e, após o final, pergunta se o jogador deseja jogar de novo.

#### `escolhe_dificuldade()`
Esta função permite ao jogador escolher entre três níveis de dificuldade: fácil (10x10 com 15 bombas), médio (20x20 com 60 bombas) e difícil (30x30 com 135 bombas). A função `gameplay()` é chamada com os parâmetros correspondentes.

#### `gameplay()`
Essa é a função principal que controla o fluxo do jogo. Ela inicializa o campo de bombas e a matriz do jogo, verifica a entrada do jogador e determina se ele ganhou ou perdeu. 

- **Entrada do Jogador**: O jogador digita as coordenadas de uma célula no formato `linha,coluna`. O jogo processa essas coordenadas e revela a célula correspondente.
- **Condição de Vitória**: Se o jogador revelar todas as células seguras (sem bombas), ele vence.
- **Condição de Derrota**: Se o jogador revelar uma célula com bomba, o jogo termina.

#### `aloca_matriz_int()` e `desaloca_matriz_int()`
Essas funções lidam com a alocação dinâmica e a liberação de memória de matrizes de inteiros, usadas para armazenar o estado do campo de bombas.

#### `aloca_matriz_char()` e `desaloca_matriz_char()`
Funções semelhantes às anteriores, mas trabalham com matrizes de caracteres que representam o estado atual do campo que o jogador vê.

#### `inicializar_campo()`
Esta função gera o campo do jogo:
- Coloca bombas em posições aleatórias.
- Inicializa a matriz do jogo que será exibida, com todas as células cobertas (representadas por `x`).

#### `conta_vizinhos()`
Esta função conta quantas bombas estão ao redor de cada célula que não é uma bomba. O resultado é um número que vai de 0 a 8 e indica quantas bombas estão nas células adjacentes (incluindo diagonais).

#### `espalhamento()`
Implementa o algoritmo de **espalhamento**, que revela automaticamente todas as células ao redor de uma célula com valor zero, parando em qualquer célula adjacente a uma bomba.

#### `printa_jogo()`
Responsável por imprimir o estado atual do jogo no terminal, mostrando quais células estão cobertas (`x`), quais foram reveladas e seus respectivos números.

#### `printa_bombas()`
Essa função imprime o campo de bombas completo, com a localização de todas as bombas.

#### `registra_logs()`
Função existente no log.h, registra toda a saída do jogo em um arquivo para consulta posterior.

#### `inicializa_log()` e `finaliza_log()`
Funções fundamentais para criar e salvar o arquivo de log.

## Instruções de Execução

### Compilação

O programa foi desenvolvido no sistema Ubuntu e compilado no terminal, usando gcc:

```bash
gcc hellen_nayara.c log.c matriz.c -o campo_minado.out
```

Isso vai gerar um executável chamado `campo_minado.out`.

### Execução

Após compilar, você pode rodar o programa com o comando:

```bash
./campo_minado.out
```

### Formato da Entrada

Ao jogar, digite as coordenadas da célula que deseja revelar no formato:

```
linha,coluna
```

Por exemplo, para escolher a célula na linha 3 e coluna 5, digite:

```
3,5
```

## Exemplo de Saída

Quando o jogo é iniciado, o campo irá aparecer da seguinte forma:

```
     1  2  3  4  5  6  7  8  9  10 
   -------------------------------
 1  | x  x  x  x  x  x  x  x  x  x  |
 2  | x  x  x  x  x  x  x  x  x  x  |
 3  | x  x  x  x  x  x  x  x  x  x  |
 ...
```

Conforme as células forem reveladas, o campo será atualizado:

```
     1  2  3  4  5  6  7  8  9  10 
   -------------------------------
 1  | 1  1  1  x  x  x  x  x  x  x  |
 2  | 1  x  2  2  1  1  x  x  x  x  |
 3  | 1  x  x  x  x  x  x  x  x  x  |
 ...
```

Se acertar uma bomba, o jogo termina e todas as bombas são reveladas.

```
     1  2  3  4  5  6  7  8  9  10 
   -------------------------------
 1  | 1  1  1  -1  x  x  x  x  x  x  |
 2  | 1  2  -1  2  1  1  x  x  x  x  |
 3  | 1  -1  x  x  x  x  x  x  x  x  |
 ...
```

## Entrada como arquivo

Para usar um arquivo de entrada, utilize o comando dessa maneira:

```bash
./campo_minado.out < entrada.txt
```

O arquivo de entrada deve ter o seguinte formato:

```txt
1
3,3
2,2
3,4
5,6
```

A primeira linha representa a dificuldade e as próximas são as jogadas, sem um limite definido.

## Considerações extras

Esse código é uma implementação básica e pode ser melhorado por:
- Marcações de bandeiras para sinalizar bombas
- Controles de dificuldade mais precisos
- Interface gráfica (usando SDL ou outra parecida).

