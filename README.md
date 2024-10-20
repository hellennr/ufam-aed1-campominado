# Campo Minado em C

Este repositório contém uma implementação simples de um jogo de Campo Minado em linguagem C.
O objetivo do jogo é selecionar todas as células seguras sem selecionar nenhuma mina.
É um jogo implementado no terminal.

Esta é a versão com modificações a partir do trabalho original.
O trabalho original está na pasta "trabalho".

## Funcionalidades
- Escolha de dificuldade (fácil, médio, difícil).
- Distribuição aleatória de bombas no campo.
- Contagem de bombas ao redor de cada célula.
- Detecção de vitória ao revelar todas as células seguras.
- Detecção de derrota ao escolher uma célula com bomba.
- Implementação de **espalhamento** para revelar automaticamente as células ao redor quando o jogador escolhe uma célula com valor zero.

### Principais Funções

#### `int main()`
Esta função inicia o jogo e permite ao jogador decidir se quer jogar novamente após cada partida. Ela chama a função `escolhe_dificuldade()` para iniciar o jogo e, após o final, pergunta se o jogador deseja jogar de novo.

#### `escolhe_dificuldade()`
Esta função permite ao jogador escolher entre três níveis de dificuldade: fácil (10x10 com 15 bombas), médio (20x20 com 50 bombas) e difícil (30x30 com 100 bombas). A função `gameplay()` é chamada com os parâmetros correspondentes.

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
- Inicializa a matriz do jogo que será exibida, com todas as células cobertas (representadas por `.`).

#### `conta_vizinhos()`
Esta função conta quantas bombas estão ao redor de cada célula que não é uma bomba. O resultado é um número que vai de 0 a 8 e indica quantas bombas estão nas células adjacentes (incluindo diagonais).

#### `espalhamento()`
Implementa o algoritmo de **espalhamento**, que revela automaticamente todas as células ao redor de uma célula com valor zero. O espalhamento só se propaga nas 4 direções principais (cima, baixo, esquerda, direita) e para de se expandir em células com valor maior que zero.

#### `printa_jogo()`
Responsável por imprimir o estado atual do jogo no terminal, mostrando quais células estão cobertas (`.`), quais foram reveladas e seus respectivos números.

#### `printa_bombas()` e `printa_bombas_derrota()`
Essas funções imprimem o campo de bombas. A primeira é usada no final do jogo quando o jogador vence, e a segunda é usada para mostrar onde as bombas estavam após o jogador perder, destacando a célula que causou a derrota.

## Instruções de Execução

### Compilação

O programa foi desenvolvido no sistema Ubuntu e compilado no terminal, usando gcc:

```bash
gcc campo_minado.c -o campo_minado
```

Isso vai gerar um executável chamado `campo_minado`.

### Execução

Após compilar, você pode rodar o programa com o comando:

```bash
./campo_minado
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
 1  | .  .  .  .  .  .  .  .  .  .  |
 2  | .  .  .  .  .  .  .  .  .  .  |
 3  | .  .  .  .  .  .  .  .  .  .  |
 ...
```

Conforme as células forem reveladas, o campo será atualizado:

```
     1  2  3  4  5  6  7  8  9  10 
   -------------------------------
 1  | 1  1  1  .  .  .  .  .  .  .  |
 2  | 1  .  2  2  1  1  .  .  .  .  |
 3  | 1  .  .  .  .  .  .  .  .  .  |
 ...
```

Se acertar uma bomba, o jogo termina e todas as bombas são reveladas.

```
     1  2  3  4  5  6  7  8  9  10 
   -------------------------------
 1  | 1  1  1  💣  .  .  .  .  .  .  |
 2  | 1  2  💥  2  1  1  .  .  .  .  |
 3  | 1  💣  .  .  .  .  .  .  .  .  |
 ...
```

## Distinções do trabalho original

- Validação da string de entrada: Caso digite uma string inválida, ele pede para digitar novamente.
- Espalhamento dos zeros: Ao selecionar uma célula vazia, revela as adjacentes
- Aumento na dificuldade: Com o espalhamento, a dificuldade fica muito baixa com menos de 10 bombas.
- Emojis adicionados: Para dar um ar mais lúdico ao jogo
- Substituição do caractere de célula: O caractere 'x' foi substituído por '.', para mais clareza.
- Mostra a bomba que causou a derrota separadamente.

## Considerações extras

Esse código é uma implementação básica e pode ser melhorado por:
- Marcações de bandeiras para sinalizar bombas
- Controles de dificuldade mais precisos
- Interface gráfica (usando SDL ou outra parecida).

