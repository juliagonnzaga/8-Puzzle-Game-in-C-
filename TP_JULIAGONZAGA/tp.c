/*

Nome: Júlia Carlos Gonzaga - 21.2.4115
Professor: Puca Huachi
Disciplina: BCC201
TP - O Quebra Cabeças das 8 Pastilhas

*/

//Inclusão de bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <string.h>

// cores e formato de texto
#define ANSI_RESET "\x1b[0m" // desativa os efeitos anteriores
#define ANSI_BOLD "\x1b[1m"  // coloca o texto em negrito
#define ANSI_COLOR_BLACK "\x1b[30m"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_WHITE "\x1b[37m"
#define ANSI_BG_COLOR_BLACK "\x1b[40m"
#define ANSI_BG_COLOR_RED "\x1b[41m"
#define ANSI_BG_COLOR_GREEN "\x1b[42m"
#define ANSI_BG_COLOR_YELLOW "\x1b[43m"
#define ANSI_BG_COLOR_BLUE "\x1b[44m"
#define ANSI_BG_COLOR_MAGENTA "\x1b[45m"
#define ANSI_BG_COLOR_CYAN "\x1b[46m"
#define ANSI_BG_COLOR_WHITE "\x1b[47m"

// macros para facilitar o uso
#define BOLD(string) ANSI_BOLD string ANSI_RESET
#define BLACK(string) ANSI_COLOR_BLACK string ANSI_RESET
#define BLUE(string) ANSI_COLOR_BLUE string ANSI_RESET
#define RED(string) ANSI_COLOR_RED string ANSI_RESET
#define GREEN(string) ANSI_COLOR_GREEN string ANSI_RESET
#define YELLOW(string) ANSI_COLOR_YELLOW string ANSI_RESET
#define BLUE(string) ANSI_COLOR_BLUE string ANSI_RESET
#define MAGENTA(string) ANSI_COLOR_MAGENTA string ANSI_RESET
#define CYAN(string) ANSI_COLOR_CYAN string ANSI_RESET
#define WHITE(string) ANSI_COLOR_WHITE string ANSI_RESET
#define BG_BLACK(string) ANSI_BG_COLOR_BLACK string ANSI_RESET
#define BG_BLUE(string) ANSI_BG_COLOR_BLUE string ANSI_RESET
#define BG_RED(string) ANSI_BG_COLOR_RED string ANSI_RESET
#define BG_GREEN(string) ANSI_BG_COLOR_GREEN string ANSI_RESET
#define BG_YELLOW(string) ANSI_BG_COLOR_YELLOW string ANSI_RESET
#define BG_BLUE(string) ANSI_BG_COLOR_BLUE string ANSI_RESET
#define BG_MAGENTA(string) ANSI_BG_COLOR_MAGENTA string ANSI_RESET
#define BG_CYAN(string) ANSI_BG_COLOR_CYAN string ANSI_RESET
#define BG_WHITE(string) ANSI_BG_COLOR_WHITE string ANSI_RESET

// caracteres uteis para tabelas
#define TAB_HOR "\u2501" // ━ (horizontal)
#define TAB_VER "\u2503" // ┃ (vertical)
#define TAB_TL "\u250F"  // ┏ (top-left)
#define TAB_ML "\u2523"  // ┣ (middle-left)
#define TAB_BL "\u2517"  // ┗ (bottom-left)
#define TAB_TJ "\u2533"  // ┳ (top-join)
#define TAB_MJ "\u254B"  // ╋ (middle-join)
#define TAB_BJ "\u253B"  // ┻ (bottom-join)
#define TAB_TR "\u2513"  // ┓ (top-right)
#define TAB_MR "\u252B"  // ┫ (middle-right)
#define TAB_BR "\u251B"  // ┛ (bottom-right)

//variável global TAM para representar a dimensão da matriz[3][3]
#define TAM 3

// Função que exibe o menu
void exibeMenu()
{
    printf(BOLD(YELLOW("___________________________________")) "\n");
    printf(BOLD(YELLOW("\nBem vindo ao Quebra Cabeças")) "\n");

    printf("\n0. Sair do Jogo\t");
    printf("\n1. Começar um novo jogo\t");
    printf("\n2. Continuar o jogo atual\t");
    printf("\n3. Continuar um jogo salvo\t");
    printf("\n4. Instruções do jogo\t");

    printf(BOLD(YELLOW("\n___________________________________")) "\n");

    printf(BLUE(BOLD("\n\nEscolha a opção (digite “sair” em qualquer lugar para sair do jogo): ")));
};

// Função que exibe instruções do jogo para o usuário
void exibeInstrucoes()
{
    printf(BOLD(MAGENTA("\nINSTRUÇÕES DO JOGO!\n")));

    printf("\nO jogo possui 9 peças, sendo 8 peças com números e um espaço vazio para movimentá-las.\n\nO objetivo do jogo é arranjar as peças na ordem: 1 2 3 4 5 6 7 8 0! Deixando a última posição direita do tabuleiro vazia, ou seja, as 8 peças devem ser deslizadas no tabuleiro, fazendo-se quantos movimentos fossem necessários!\n");

    printf(BOLD(CYAN("\nAtenção: somente as peças adjacentes ao espaço vazio podem ser movidas!")));

    printf(BOLD(MAGENTA("\n\nNÍVEIS DO JOGO!\n")));

    printf("\nO jogo possui 3 níveis de dificuldade:\n1 - Fácil: Embaralha o tabuleiro 20 vezes\n2 - Médio: Embaralha o tabuleiro 40 vezes\n3 - Difícil: Embaralha o tabuleiro 80 vezes");

    printf(BOLD(MAGENTA("\n\nCOMANDOS DO JOGO!\n")));

    printf("\nO Jogo possui os seguintes comandos:\nVoltar - Para Retornar ao Menu\nSair - Para finalizar o Jogo\nSalvar - Para salvar o estado atual do jogo em um arquivo texto\n\n");
};

// Função que gera a matriz(tabuleiro) do jogo de forma ordenada e alocada dinamicamente
int **geraMatriz()
{
    int **mat;
    int aux = 1;

    //Alocação da matriz
    mat = malloc(TAM * sizeof(int *));

    for (int i = 0; i < TAM * TAM; i++)
    {
        mat[i] = malloc(TAM * sizeof(int));
    }

    //Preenche a matriz
    for (int i = 0; i < TAM; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            mat[i][j] = aux;
            aux++;
        }
    }

    //Seta a última posição da matriz como 0 para ficar na ordem 1 2 3 4 5 6 7 8 0
    mat[2][2] = 0;

    //Imprime a matriz
    for (int linha = 0; linha < 3; linha++)
    {
        printf("\n");

        for (int coluna = 0; coluna < 3; coluna++)
        {
            printf(" %d ", mat[linha][coluna]);
        }
        printf("\n");
    }

    //Imprime mensagem para o usuário
    printf(BLUE(BOLD("\nTabuleiro ordenado! Digite o nível de dificuldade para embaralhar, fácil (1), médio (2) ou difícil (3):")));

    return mat; //retorna a matriz
};

// Função que libera a matriz alocada dinamicamente, recebendo a matriz desejada como parâmetro
void liberaMatriz(int **m)
{
    //Loop para desalocar a matriz
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            free(m[i][j]);
        }
    }
}

// Função que imprime a matriz e recebe linha, coluna, dimensão e matriz
void imprimeMatriz(int linha, int coluna, int d, int **mat)
{
    //Loop para percorrer a matriz e impimir com espaços
    for (linha = 0; linha < d; linha++)
    {
        printf("\n");

        for (coluna = 0; coluna < d; coluna++)
        {
            printf(" %d ", mat[linha][coluna]);
        }
        printf("\n");
    }
}

/*Função que embaralha a matriz de acordo com o nível de dificuldade escolhido pelo usuário

Para embaralhar a matriz, verifico onde está o 0 em cada posição da matriz, utilizando condicionais aninhadas. 
Assim que o 0 é encontrado na posição mat[x][y], uma variavel opcao é setada com valores que representam as possibilidades
de movimentos. Ou seja, se o 0 tiver 4 possibilidades de movimentos, a variavel receberá um valor randomico que indicara qual 
possibilidade será escolhida para o movimento (ex: se a opcao for 1 troca o 0 com 3, se a opcao for 2 troca o 0 com o 4).

Dessa forma, a função se repete num loop que termina no número de vezes de dificuldade que o usuário escolheu
Fácil, Médio ou dificil; 
*/

void embaralhaMatriz(int numVezesdificuldade, int opcao, int **mat, int guardaZero)
{
    srand(time(NULL));

    for (int i = 0; i < numVezesdificuldade; i++)
    {

        if (mat[0][0] == 0)
        {
            opcao = rand() % 2;
            if (opcao == 0)
            {
                // Troca o 0 com 1
                guardaZero = mat[0][0];
                mat[0][0] = mat[0][1];
                mat[0][1] = guardaZero;
            }
            else
            {
                // Troca o 0 com 3
                guardaZero = mat[0][0];
                mat[0][0] = mat[1][0];
                mat[1][0] = guardaZero;
            }
        }
        else if (mat[0][1] == 0)
        {
            opcao = rand() % 3;
            if (opcao == 0)
            {
                // Troca o 0 com o 2
                guardaZero = mat[0][1];
                mat[0][1] = mat[0][2];
                mat[0][2] = guardaZero;
            }
            else if (opcao == 1)
            {
                // Troca o 0 com o 1
                guardaZero = mat[0][1];
                mat[0][1] = mat[0][0];
                mat[0][0] = guardaZero;
            }
            else
            {
                // Troca o 0 com o 4
                guardaZero = mat[0][1];
                mat[0][1] = mat[1][1];
                mat[1][1] = guardaZero;
            }
        }
        else if (mat[0][2] == 0)
        {
            opcao = rand() % 2;
            if (opcao == 0)
            {
                // Troca o 0 com o 2
                guardaZero = mat[0][2];
                mat[0][2] = mat[0][1];
                mat[0][1] = guardaZero;
            }
            else
            {
                // Troca o 0 com o 5
                guardaZero = mat[0][2];
                mat[0][2] = mat[1][2];
                mat[1][2] = guardaZero;
            }
        }
        else if (mat[1][0] == 0)
        {
            opcao = rand() % 3;
            if (opcao == 0)
            {
                // Troca o 0 com o 6
                guardaZero = mat[1][0];
                mat[1][0] = mat[2][0];
                mat[2][0] = guardaZero;
            }
            else if (opcao == 1)
            {
                // Troca o 0 com o 1
                guardaZero = mat[1][0];
                mat[1][0] = mat[0][0];
                mat[0][0] = guardaZero;
            }
            else
            {
                // Troca o 0 com o 4
                guardaZero = mat[1][0];
                mat[1][0] = mat[1][1];
                mat[1][1] = guardaZero;
            }
        }
        else if (mat[1][1] == 0)
        {
            opcao = rand() % 4;
            if (opcao == 0)
            {
                // Troca o 0 com o 2
                guardaZero = mat[1][1];
                mat[1][1] = mat[0][1];
                mat[0][1] = guardaZero;
            }
            else if (opcao == 1)
            {
                // Troca o 0 com o 7
                guardaZero = mat[1][1];
                mat[1][1] = mat[2][1];
                mat[2][1] = guardaZero;
            }
            else if (opcao == 2)
            {
                // Troca o 0 com 5
                guardaZero = mat[1][1];
                mat[1][1] = mat[1][2];
                mat[1][2] = guardaZero;
            }
            else if (opcao == 3)
            {
                // Troca o 0 com o 4
                guardaZero = mat[1][1];
                mat[1][1] = mat[1][0];
                mat[1][0] = guardaZero;
            }
        }
        else if (mat[1][2] == 0)
        {
            opcao = rand() % 3;
            if (opcao == 0)
            {
                // Troca o 0 com 5
                guardaZero = mat[1][2];
                mat[1][2] = mat[1][1];
                mat[1][1] = guardaZero;
            }
            else if (opcao == 1)
            {
                // Troca o 0 com 3
                guardaZero = mat[1][2];
                mat[1][2] = mat[0][2];
                mat[0][2] = guardaZero;
            }
            else
            {
                // Troca o 0 com 8
                guardaZero = mat[1][2];
                mat[1][2] = mat[2][2];
                mat[2][2] = guardaZero;
            }
        }
        else if (mat[2][0] == 0)
        {
            opcao = rand() % 2;
            if (opcao == 0)
            { // Troca o 0 com o 4
                guardaZero = mat[2][0];
                mat[2][0] = mat[1][0];
                mat[1][0] = guardaZero;
            }
            else
            {
                // Troca o 0 com o 7
                guardaZero = mat[2][0];
                mat[2][0] = mat[2][1];
                mat[2][1] = guardaZero;
            }
        }
        else if (mat[2][1] == 0)
        {
            opcao = rand() % 3;
            if (opcao == 0)
            {
                // Troca o 0 com 7
                guardaZero = mat[2][1];
                mat[2][1] = mat[2][0];
                mat[2][0] = guardaZero;
            }
            else if (opcao == 1)
            {
                // Troca o 0 com 8
                guardaZero = mat[2][1];
                mat[2][1] = mat[2][2];
                mat[2][2] = guardaZero;
            }
            else
            {
                // Troca o 0 com 5
                guardaZero = mat[2][1];
                mat[2][1] = mat[1][1];
                mat[1][1] = guardaZero;
            }
        }
        else if (mat[2][2] == 0)
        {
            opcao = rand() % 2;
            if (opcao == 0)
            {
                // Troca o 0 com 6
                guardaZero = mat[2][2];
                mat[2][2] = mat[1][2];
                mat[1][2] = guardaZero;
            }
            else
            {
                // Troca 0 com 8
                guardaZero = mat[2][2];
                mat[2][2] = mat[2][1];
                mat[2][1] = guardaZero;
            }
        }
    }
}

/*
Função que compara a matriz atual (tabuleiro atual) com a matriz ordenada (tabuleiro meta) para 
saber se o jogador venceu ou não o jogo. Essa função recebe a matriz atual como parametro para fazer
a comparação e retorna uma variavel que sera utilizada como uma "flag" futuramente
*/
int comparaMatrizAtualComMatrizMeta(int **mat)
{
    //Declara e inicializa posições da matriz meta do jogo (matriz ordenada)
    int matMeta[3][3] = {1, 2, 3,
                         4, 5, 6,
                         7, 8, 0};

    //Loop para percorrer e comparar os indices das duas matrizes, para saber se são iguais
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (matMeta[i][j] != mat[i][j])
            {
                return 0; //Caso algum dos indices não for igual, indica que a matriz não é igual e retorna 0
            }
        }
    }
    return 1; //Caso os indices forem iguais, retorna que as matrizes sao identicas e retorna 1
}

/* 
Função que seta o valor da dificuldade do jogo, a função recebe o valor digitado pelo usuário (Fácil = 1, Médio = 2, Difiícil = 3)
e a partir desses valores retorna até quantas vezes o loop de embaralhamento
deve ser realizado. ALém disso, caso a opção não exista a função realiza o tratamento de validação.
*/

int setaEValidaDificuldade(int dificuldade)
{
    if (dificuldade == 1)
    {
        return 20;
    }
    else if (dificuldade == 2)
    {
        return 40;
    }
    else if (dificuldade == 3)
    {
        return 80;
    }
    else
    {
        printf(BOLD(RED("\nO comando digitado não existe, por favor digite uma opção válida:")));
        scanf("%d", &dificuldade);
        return setaEValidaDificuldade(dificuldade);
    }
}

//Função que recebe a variavel int movimentos e imprime quantos movimentos já foram realizados pelo usuario
void exibeMovimentos(int movimentos)
{
    printf(GREEN(BOLD("\nQuantidade de jogadas até agora: %d")), movimentos);
}

//Função que imprime a matriz atual (tabuleiro atual) num arquivo
void imprimeMatrizNoArquivo(FILE *f, int **m, int movimentos)
{
    //Imprime a dimensao da matriz no arquivo
    fprintf(f, "%d\n", 3);
    fprintf(f, "\n");

    //imprime a matriz no arquivo
    int i, j;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            fprintf(f, "%d ", m[i][j]);
        }
        fprintf(f, "\n");
    }
    fprintf(f, "\n");

    //Imprime o valor de movimentos realizados pelo usuario no arquivo
    fprintf(f, "%d\n", movimentos);
}

/* 
A maior função e a mais importante do jogo, junto com a função de embaralhamento e ela também é a maior função do jogo.
    -Valida os comandos sair, voltar e salvar no menu
    -Valida quais peças podem ser trocadas pelo 0 baseado na posição do 0 na matriz
    -Contabiliza os movimentos do usuario
    -Imprime cada um dos estados após o jogador mover a peça
    -Chama a função de comparar as matrizes para verificar se o usuario ganhou o jogo a cada novo estado do tabuleiro
    -Salva o arquivo com o estado atual do jogo do usuario

É uma função recursiva e a cada movimento feito pelo usuario ela é chamada novamente para dar seguimento ao jogo
*/
int movePecaNaMatriz(int **mat, int guardaZero, char pecaParaMover[], int linha, int coluna, int d, int movimentos)
{
    int verificaSeGanhouJogo, jaTemUmJogo;

    char string[100];
    strcpy(string, pecaParaMover);
    string[6] = 0;

    int tamanho = strlen(string);

    if (strcmp(string, "salvar") == 0)
    {

        FILE *output;
        char nomeDoArquivoSeparado[30];
        int tamNomeDigitado = (strlen(pecaParaMover));

        for (int i = 0; i < tamNomeDigitado; i++)
        {
            nomeDoArquivoSeparado[i] = pecaParaMover[7 + i];
        }
        nomeDoArquivoSeparado[tamNomeDigitado - 8] = '\0'; // tirar o \n digitado pelo usuário

        output = fopen(nomeDoArquivoSeparado, "w+");
        printf("\nArquivo %s salvo com sucesso!", (nomeDoArquivoSeparado));
        imprimeMatrizNoArquivo(output, mat, movimentos);
        fclose(output);
    }
    else if (strcmp(string, "voltar") == 0)
    {
        main();
    }
    if (tamanho < 6)
    {
        string[tamanho - 1] = '\0';

        if (strcmp(string, "sair") == 0)
        {
            return 0;
        }
    }

    if (mat[0][0] == 0)
    {

        if ((atoi(pecaParaMover)) == mat[0][1])
        {

            guardaZero = mat[0][0];
            mat[0][0] = mat[0][1];
            mat[0][1] = guardaZero;

            movimentos++;

            imprimeMatriz(linha, coluna, d, mat);
            exibeMovimentos(movimentos);
            comparaMatrizAtualComMatrizMeta(mat);

            verificaSeGanhouJogo = comparaMatrizAtualComMatrizMeta(mat);

            if (verificaSeGanhouJogo == 1)
            {
                printf("\nParabéns! Você completou com quebra-cabeças com %d movimentos.\n", movimentos);
                return 0;
            }

            printf("\nDigite um comando ou número da peça que quer mover:");
            fgets(pecaParaMover, 100, stdin);

            movePecaNaMatriz(mat, guardaZero, pecaParaMover, linha, coluna, d, movimentos);
        }
        else if ((atoi(pecaParaMover)) == mat[1][0])
        {

            guardaZero = mat[0][0];
            mat[0][0] = mat[1][0];
            mat[1][0] = guardaZero;

            movimentos++;

            imprimeMatriz(linha, coluna, d, mat);
            exibeMovimentos(movimentos);
            comparaMatrizAtualComMatrizMeta(mat);

            verificaSeGanhouJogo = comparaMatrizAtualComMatrizMeta(mat);

            if (verificaSeGanhouJogo == 1)
            {
                printf("\nParabéns! Você completou com quebra-cabeças com %d movimentos.\n", movimentos);
                return 0;
            }

            printf("\nDigite um comando ou número da peça que quer mover:");
            fgets(pecaParaMover, 100, stdin);

            movePecaNaMatriz(mat, guardaZero, pecaParaMover, linha, coluna, d, movimentos);
        }
        else
        {

            printf(BOLD(RED("\nNão é possível mover a peça: %s\n")), pecaParaMover);

            printf("\nDigite um comando ou número da peça que quer mover:");
            fgets(pecaParaMover, 100, stdin);

            movePecaNaMatriz(mat, guardaZero, pecaParaMover, linha, coluna, d, movimentos);
        }
    }
    else if (mat[0][1] == 0)
    {

        if ((atoi(pecaParaMover)) == mat[0][2])
        {

            guardaZero = mat[0][1];
            mat[0][1] = mat[0][2];
            mat[0][2] = guardaZero;

            movimentos++;

            imprimeMatriz(linha, coluna, d, mat);
            exibeMovimentos(movimentos);
            comparaMatrizAtualComMatrizMeta(mat);

            verificaSeGanhouJogo = comparaMatrizAtualComMatrizMeta(mat);

            if (verificaSeGanhouJogo == 1)
            {
                printf("\nParabéns! Você completou com quebra-cabeças com %d movimentos.\n", movimentos);
                return 0;
            }

            printf("\nDigite um comando ou número da peça que quer mover:");
            fgets(pecaParaMover, 100, stdin);

            movePecaNaMatriz(mat, guardaZero, pecaParaMover, linha, coluna, d, movimentos);
        }
        else if ((atoi(pecaParaMover)) == mat[0][0])
        {

            guardaZero = mat[0][1];
            mat[0][1] = mat[0][0];
            mat[0][0] = guardaZero;

            movimentos++;

            imprimeMatriz(linha, coluna, d, mat);
            exibeMovimentos(movimentos);
            comparaMatrizAtualComMatrizMeta(mat);

            verificaSeGanhouJogo = comparaMatrizAtualComMatrizMeta(mat);

            if (verificaSeGanhouJogo == 1)
            {
                printf("\nParabéns! Você completou com quebra-cabeças com %d movimentos.\n", movimentos);
                return 0;
            }

            printf("\nDigite um comando ou número da peça que quer mover:");
            fgets(pecaParaMover, 100, stdin);

            movePecaNaMatriz(mat, guardaZero, pecaParaMover, linha, coluna, d, movimentos);
        }
        else if ((atoi(pecaParaMover)) == mat[1][1])
        {

            guardaZero = mat[0][1];
            mat[0][1] = mat[1][1];
            mat[1][1] = guardaZero;

            movimentos++;

            imprimeMatriz(linha, coluna, d, mat);
            exibeMovimentos(movimentos);
            comparaMatrizAtualComMatrizMeta(mat);

            verificaSeGanhouJogo = comparaMatrizAtualComMatrizMeta(mat);

            if (verificaSeGanhouJogo == 1)
            {
                printf("\nParabéns! Você completou com quebra-cabeças com %d movimentos.\n", movimentos);
                return 0;
            }

            printf("\nDigite um comando ou número da peça que quer mover:");
            fgets(pecaParaMover, 100, stdin);

            movePecaNaMatriz(mat, guardaZero, pecaParaMover, linha, coluna, d, movimentos);
        }
        else
        {

            printf(BOLD(RED("\nNão é possível mover a peça: %s\n")), pecaParaMover);

            printf("\nDigite um comando ou número da peça que quer mover:");
            fgets(pecaParaMover, 100, stdin);

            movePecaNaMatriz(mat, guardaZero, pecaParaMover, linha, coluna, d, movimentos);
        }
    }
    else if (mat[0][2] == 0)
    {

        if ((atoi(pecaParaMover)) == mat[0][1])
        {

            guardaZero = mat[0][2];
            mat[0][2] = mat[0][1];
            mat[0][1] = guardaZero;

            movimentos++;

            imprimeMatriz(linha, coluna, d, mat);
            exibeMovimentos(movimentos);
            comparaMatrizAtualComMatrizMeta(mat);

            verificaSeGanhouJogo = comparaMatrizAtualComMatrizMeta(mat);

            if (verificaSeGanhouJogo == 1)
            {
                printf("\nParabéns! Você completou com quebra-cabeças com %d movimentos.\n", movimentos);
                return 0;
            }

            printf("\nDigite um comando ou número da peça que quer mover:");
            fgets(pecaParaMover, 100, stdin);

            movePecaNaMatriz(mat, guardaZero, pecaParaMover, linha, coluna, d, movimentos);
        }
        else if ((atoi(pecaParaMover)) == mat[1][2])
        {

            guardaZero = mat[0][2];
            mat[0][2] = mat[1][2];
            mat[1][2] = guardaZero;

            movimentos++;

            imprimeMatriz(linha, coluna, d, mat);
            exibeMovimentos(movimentos);
            comparaMatrizAtualComMatrizMeta(mat);

            verificaSeGanhouJogo = comparaMatrizAtualComMatrizMeta(mat);

            if (verificaSeGanhouJogo == 1)
            {
                printf("\nParabéns! Você completou com quebra-cabeças com %d movimentos.\n", movimentos);
                return 0;
            }

            printf("\nDigite um comando ou número da peça que quer mover:");
            fgets(pecaParaMover, 100, stdin);

            movePecaNaMatriz(mat, guardaZero, pecaParaMover, linha, coluna, d, movimentos);
        }
        else
        {

            printf(BOLD(RED("\nNão é possível mover a peça: %s\n")), pecaParaMover);

            printf("\nDigite um comando ou número da peça que quer mover:");
            fgets(pecaParaMover, 100, stdin);

            movePecaNaMatriz(mat, guardaZero, pecaParaMover, linha, coluna, d, movimentos);
        }
    }
    else if (mat[1][0] == 0)
    {

        if ((atoi(pecaParaMover)) == mat[2][0])
        {

            guardaZero = mat[1][0];
            mat[1][0] = mat[2][0];
            mat[2][0] = guardaZero;

            movimentos++;

            imprimeMatriz(linha, coluna, d, mat);
            exibeMovimentos(movimentos);
            comparaMatrizAtualComMatrizMeta(mat);

            verificaSeGanhouJogo = comparaMatrizAtualComMatrizMeta(mat);

            if (verificaSeGanhouJogo == 1)
            {
                printf("\nParabéns! Você completou com quebra-cabeças com %d movimentos.\n", movimentos);
                return 0;
            }

            printf("\nDigite um comando ou número da peça que quer mover:");
            fgets(pecaParaMover, 100, stdin);

            movePecaNaMatriz(mat, guardaZero, pecaParaMover, linha, coluna, d, movimentos);
        }
        else if ((atoi(pecaParaMover)) == mat[0][0])
        {

            guardaZero = mat[1][0];
            mat[1][0] = mat[0][0];
            mat[0][0] = guardaZero;

            movimentos++;

            imprimeMatriz(linha, coluna, d, mat);
            exibeMovimentos(movimentos);
            comparaMatrizAtualComMatrizMeta(mat);

            verificaSeGanhouJogo = comparaMatrizAtualComMatrizMeta(mat);

            if (verificaSeGanhouJogo == 1)
            {
                printf("\nParabéns! Você completou com quebra-cabeças com %d movimentos.\n", movimentos);
                return 0;
            }

            printf("\nDigite um comando ou número da peça que quer mover:");
            fgets(pecaParaMover, 100, stdin);

            movePecaNaMatriz(mat, guardaZero, pecaParaMover, linha, coluna, d, movimentos);
        }
        else if ((atoi(pecaParaMover)) == mat[1][1])
        {

            guardaZero = mat[1][0];
            mat[1][0] = mat[1][1];
            mat[1][1] = guardaZero;

            movimentos++;

            imprimeMatriz(linha, coluna, d, mat);
            exibeMovimentos(movimentos);
            comparaMatrizAtualComMatrizMeta(mat);

            verificaSeGanhouJogo = comparaMatrizAtualComMatrizMeta(mat);

            if (verificaSeGanhouJogo == 1)
            {
                printf("\nParabéns! Você completou com quebra-cabeças com %d movimentos.\n", movimentos);
                return 0;
            }

            printf("\nDigite um comando ou número da peça que quer mover:");
            fgets(pecaParaMover, 100, stdin);

            movePecaNaMatriz(mat, guardaZero, pecaParaMover, linha, coluna, d, movimentos);
        }
        else
        {

            printf(BOLD(RED("\nNão é possível mover a peça: %s\n")), pecaParaMover);

            printf("\nDigite um comando ou número da peça que quer mover:");
            fgets(pecaParaMover, 100, stdin);

            movePecaNaMatriz(mat, guardaZero, pecaParaMover, linha, coluna, d, movimentos);
        }
    }
    else if (mat[1][1] == 0)
    {

        if ((atoi(pecaParaMover)) == mat[0][1])
        {

            guardaZero = mat[1][1];
            mat[1][1] = mat[0][1];
            mat[0][1] = guardaZero;

            movimentos++;

            imprimeMatriz(linha, coluna, d, mat);
            exibeMovimentos(movimentos);
            comparaMatrizAtualComMatrizMeta(mat);

            verificaSeGanhouJogo = comparaMatrizAtualComMatrizMeta(mat);

            if (verificaSeGanhouJogo == 1)
            {
                printf("\nParabéns! Você completou com quebra-cabeças com %d movimentos.\n", movimentos);
                return 0;
            }

            printf("\nDigite um comando ou número da peça que quer mover:");
            fgets(pecaParaMover, 100, stdin);

            movePecaNaMatriz(mat, guardaZero, pecaParaMover, linha, coluna, d, movimentos);
        }
        else if ((atoi(pecaParaMover)) == mat[2][1])
        {

            guardaZero = mat[1][1];
            mat[1][1] = mat[2][1];
            mat[2][1] = guardaZero;

            movimentos++;

            imprimeMatriz(linha, coluna, d, mat);
            exibeMovimentos(movimentos);
            comparaMatrizAtualComMatrizMeta(mat);

            verificaSeGanhouJogo = comparaMatrizAtualComMatrizMeta(mat);

            if (verificaSeGanhouJogo == 1)
            {
                printf("\nParabéns! Você completou com quebra-cabeças com %d movimentos.\n", movimentos);
                return 0;
            }

            printf("\nDigite um comando ou número da peça que quer mover:");
            fgets(pecaParaMover, 100, stdin);

            movePecaNaMatriz(mat, guardaZero, pecaParaMover, linha, coluna, d, movimentos);
        }
        else if ((atoi(pecaParaMover)) == mat[1][2])
        {

            guardaZero = mat[1][1];
            mat[1][1] = mat[1][2];
            mat[1][2] = guardaZero;

            movimentos++;

            imprimeMatriz(linha, coluna, d, mat);
            exibeMovimentos(movimentos);
            comparaMatrizAtualComMatrizMeta(mat);

            verificaSeGanhouJogo = comparaMatrizAtualComMatrizMeta(mat);

            if (verificaSeGanhouJogo == 1)
            {
                printf("\nParabéns! Você completou com quebra-cabeças com %d movimentos.\n", movimentos);
                return 0;
            }

            printf("\nDigite um comando ou número da peça que quer mover:");
            fgets(pecaParaMover, 100, stdin);

            movePecaNaMatriz(mat, guardaZero, pecaParaMover, linha, coluna, d, movimentos);
        }
        else if ((atoi(pecaParaMover)) == mat[1][0])
        {

            guardaZero = mat[1][1];
            mat[1][1] = mat[1][0];
            mat[1][0] = guardaZero;

            movimentos++;

            imprimeMatriz(linha, coluna, d, mat);
            exibeMovimentos(movimentos);
            comparaMatrizAtualComMatrizMeta(mat);

            verificaSeGanhouJogo = comparaMatrizAtualComMatrizMeta(mat);

            if (verificaSeGanhouJogo == 1)
            {
                printf("\nParabéns! Você completou com quebra-cabeças com %d movimentos.\n", movimentos);
                return 0;
            }

            printf("\nDigite um comando ou número da peça que quer mover:");
            fgets(pecaParaMover, 100, stdin);

            movePecaNaMatriz(mat, guardaZero, pecaParaMover, linha, coluna, d, movimentos);
        }
        else
        {

            printf(BOLD(RED("\nNão é possível mover a peça: %s\n")), pecaParaMover);

            verificaSeGanhouJogo = comparaMatrizAtualComMatrizMeta(mat);

            if (verificaSeGanhouJogo == 1)
            {
                printf("\nParabéns! Você completou com quebra-cabeças com %d movimentos.\n", movimentos);
                return 0;
            }

            printf("\nDigite um comando ou número da peça que quer mover:");
            fgets(pecaParaMover, 100, stdin);

            movePecaNaMatriz(mat, guardaZero, pecaParaMover, linha, coluna, d, movimentos);
        }
    }
    else if (mat[1][2] == 0)
    {

        if ((atoi(pecaParaMover)) == mat[1][1])
        {

            guardaZero = mat[1][2];
            mat[1][2] = mat[1][1];
            mat[1][1] = guardaZero;

            movimentos++;

            imprimeMatriz(linha, coluna, d, mat);
            exibeMovimentos(movimentos);
            comparaMatrizAtualComMatrizMeta(mat);

            verificaSeGanhouJogo = comparaMatrizAtualComMatrizMeta(mat);

            if (verificaSeGanhouJogo == 1)
            {
                printf("\nParabéns! Você completou com quebra-cabeças com %d movimentos.\n", movimentos);
                return 0;
            }

            printf("\nDigite um comando ou número da peça que quer mover:");
            fgets(pecaParaMover, 100, stdin);

            movePecaNaMatriz(mat, guardaZero, pecaParaMover, linha, coluna, d, movimentos);
        }
        else if ((atoi(pecaParaMover)) == mat[0][2])
        {

            guardaZero = mat[1][2];
            mat[1][2] = mat[0][2];
            mat[0][2] = guardaZero;

            movimentos++;

            imprimeMatriz(linha, coluna, d, mat);
            exibeMovimentos(movimentos);
            comparaMatrizAtualComMatrizMeta(mat);

            verificaSeGanhouJogo = comparaMatrizAtualComMatrizMeta(mat);

            if (verificaSeGanhouJogo == 1)
            {
                printf("\nParabéns! Você completou com quebra-cabeças com %d movimentos.\n", movimentos);
                return 0;
            }

            printf("\nDigite um comando ou número da peça que quer mover:");
            fgets(pecaParaMover, 100, stdin);

            movePecaNaMatriz(mat, guardaZero, pecaParaMover, linha, coluna, d, movimentos);
        }
        else if ((atoi(pecaParaMover)) == mat[2][2])
        {

            guardaZero = mat[1][2];
            mat[1][2] = mat[2][2];
            mat[2][2] = guardaZero;

            movimentos++;

            imprimeMatriz(linha, coluna, d, mat);
            exibeMovimentos(movimentos);
            comparaMatrizAtualComMatrizMeta(mat);

            verificaSeGanhouJogo = comparaMatrizAtualComMatrizMeta(mat);

            if (verificaSeGanhouJogo == 1)
            {
                printf("\nParabéns! Você completou com quebra-cabeças com %d movimentos.\n", movimentos);
                return 0;
            }

            printf("\nDigite um comando ou número da peça que quer mover:");
            fgets(pecaParaMover, 100, stdin);

            movePecaNaMatriz(mat, guardaZero, pecaParaMover, linha, coluna, d, movimentos);
        }
        else
        {

            printf(BOLD(RED("\nNão é possível mover a peça: %s\n")), pecaParaMover);

            printf("\nDigite um comando ou número da peça que quer mover:");
            fgets(pecaParaMover, 100, stdin);

            movePecaNaMatriz(mat, guardaZero, pecaParaMover, linha, coluna, d, movimentos);
        }
    }
    else if (mat[2][0] == 0)
    {

        if ((atoi(pecaParaMover)) == mat[1][0])
        {

            guardaZero = mat[2][0];
            mat[2][0] = mat[1][0];
            mat[1][0] = guardaZero;

            movimentos++;

            imprimeMatriz(linha, coluna, d, mat);
            exibeMovimentos(movimentos);
            comparaMatrizAtualComMatrizMeta(mat);

            verificaSeGanhouJogo = comparaMatrizAtualComMatrizMeta(mat);

            if (verificaSeGanhouJogo == 1)
            {
                printf("\nParabéns! Você completou com quebra-cabeças com %d movimentos.\n", movimentos);
                return 0;
            }

            printf("\nDigite um comando ou número da peça que quer mover:");
            fgets(pecaParaMover, 100, stdin);

            movePecaNaMatriz(mat, guardaZero, pecaParaMover, linha, coluna, d, movimentos);
        }
        else if ((atoi(pecaParaMover)) == mat[2][1])
        {

            guardaZero = mat[2][0];
            mat[2][0] = mat[2][1];
            mat[2][1] = guardaZero;

            movimentos++;

            imprimeMatriz(linha, coluna, d, mat);
            exibeMovimentos(movimentos);
            comparaMatrizAtualComMatrizMeta(mat);

            verificaSeGanhouJogo = comparaMatrizAtualComMatrizMeta(mat);

            if (verificaSeGanhouJogo == 1)
            {
                printf("\nParabéns! Você completou com quebra-cabeças com %d movimentos.\n", movimentos);
                return 0;
            }

            printf("\nDigite um comando ou número da peça que quer mover:");
            fgets(pecaParaMover, 100, stdin);

            movePecaNaMatriz(mat, guardaZero, pecaParaMover, linha, coluna, d, movimentos);
        }
        else
        {

            printf(BOLD(RED("\nNão é possível mover a peça: %s\n")), pecaParaMover);

            printf("\nDigite um comando ou número da peça que quer mover:");
            fgets(pecaParaMover, 100, stdin);

            movePecaNaMatriz(mat, guardaZero, pecaParaMover, linha, coluna, d, movimentos);
        }
    }
    else if (mat[2][1] == 0)
    {

        if ((atoi(pecaParaMover)) == mat[2][0])
        {

            guardaZero = mat[2][1];
            mat[2][1] = mat[2][0];
            mat[2][0] = guardaZero;

            movimentos++;

            imprimeMatriz(linha, coluna, d, mat);
            exibeMovimentos(movimentos);
            comparaMatrizAtualComMatrizMeta(mat);

            verificaSeGanhouJogo = comparaMatrizAtualComMatrizMeta(mat);

            if (verificaSeGanhouJogo == 1)
            {
                printf("\nParabéns! Você completou com quebra-cabeças com %d movimentos.\n", movimentos);
                return 0;
            }

            printf("\nDigite um comando ou número da peça que quer mover:");
            fgets(pecaParaMover, 100, stdin);

            movePecaNaMatriz(mat, guardaZero, pecaParaMover, linha, coluna, d, movimentos);
        }
        else if ((atoi(pecaParaMover)) == mat[2][2])
        {

            guardaZero = mat[2][1];
            mat[2][1] = mat[2][2];
            mat[2][2] = guardaZero;

            movimentos++;

            imprimeMatriz(linha, coluna, d, mat);
            exibeMovimentos(movimentos);
            comparaMatrizAtualComMatrizMeta(mat);

            verificaSeGanhouJogo = comparaMatrizAtualComMatrizMeta(mat);

            if (verificaSeGanhouJogo == 1)
            {
                printf("\nParabéns! Você completou com quebra-cabeças com %d movimentos.\n", movimentos);
                return 0;
            }

            printf("\nDigite um comando ou número da peça que quer mover:");
            fgets(pecaParaMover, 100, stdin);

            movePecaNaMatriz(mat, guardaZero, pecaParaMover, linha, coluna, d, movimentos);
        }
        else if ((atoi(pecaParaMover)) == mat[1][1])
        {

            guardaZero = mat[2][1];
            mat[2][1] = mat[1][1];
            mat[1][1] = guardaZero;

            movimentos++;

            imprimeMatriz(linha, coluna, d, mat);
            exibeMovimentos(movimentos);
            comparaMatrizAtualComMatrizMeta(mat);

            verificaSeGanhouJogo = comparaMatrizAtualComMatrizMeta(mat);

            if (verificaSeGanhouJogo == 1)
            {
                printf("\nParabéns! Você completou com quebra-cabeças com %d movimentos.\n", movimentos);
                return 0;
            }

            printf("\nDigite um comando ou número da peça que quer mover:");
            fgets(pecaParaMover, 100, stdin);

            movePecaNaMatriz(mat, guardaZero, pecaParaMover, linha, coluna, d, movimentos);
        }
        else
        {

            printf(BOLD(RED("\nNão é possível mover a peça: %s\n")), pecaParaMover);

            printf("\nDigite um comando ou número da peça que quer mover:");
            fgets(pecaParaMover, 100, stdin);

            movePecaNaMatriz(mat, guardaZero, pecaParaMover, linha, coluna, d, movimentos);
        }
    }
    else if (mat[2][2] == 0)
    {

        if ((atoi(pecaParaMover)) == mat[1][2])
        {

            guardaZero = mat[2][2];
            mat[2][2] = mat[1][2];
            mat[1][2] = guardaZero;

            movimentos++;

            imprimeMatriz(linha, coluna, d, mat);
            exibeMovimentos(movimentos);
            comparaMatrizAtualComMatrizMeta(mat);

            verificaSeGanhouJogo = comparaMatrizAtualComMatrizMeta(mat);

            if (verificaSeGanhouJogo == 1)
            {
                printf("\nParabéns! Você completou com quebra-cabeças com %d movimentos.\n", movimentos);
                return 0;
            }

            printf("\nDigite um comando ou número da peça que quer mover:");
            fgets(pecaParaMover, 100, stdin);

            movePecaNaMatriz(mat, guardaZero, pecaParaMover, linha, coluna, d, movimentos);
        }
        else if ((atoi(pecaParaMover)) == mat[2][1])
        {

            guardaZero = mat[2][2];
            mat[2][2] = mat[2][1];
            mat[2][1] = guardaZero;

            movimentos++;

            imprimeMatriz(linha, coluna, d, mat);
            exibeMovimentos(movimentos);
            comparaMatrizAtualComMatrizMeta(mat);

            verificaSeGanhouJogo = comparaMatrizAtualComMatrizMeta(mat);

            if (verificaSeGanhouJogo == 1)
            {
                printf("\nParabéns! Você completou com quebra-cabeças com %d movimentos.\n", movimentos);
                return 0;
            }

            printf("\nDigite um comando ou número da peça que quer mover:");
            fgets(pecaParaMover, 100, stdin);

            movePecaNaMatriz(mat, guardaZero, pecaParaMover, linha, coluna, d, movimentos);
        }
        else
        {

            printf(BOLD(RED("\nNão é possível mover a peça: %s\n")), pecaParaMover);

            printf("\nDigite um comando ou número da peça que quer mover:");
            fgets(pecaParaMover, 100, stdin);

            movePecaNaMatriz(mat, guardaZero, pecaParaMover, linha, coluna, d, movimentos);
        }
    }
}

//Função main, ou seja, funcao principal do jogo onde as entradas do menu são validadas e demais funções são chamadas
int main()
{
    int **matriz;
    int linha, coluna, opcao, dificuldade, guardaZero, numVezesdificuldade, jaTemUmJogo = 0, verificaSeGanhouJogo, movimentos = 0, aux = 0;
    int d = 3;
    char opcaoMenu[50], pecaParaMover[50];

    //Chamada da função exibe menu e recebe a variavel opcaoMenu
    exibeMenu();
    scanf("%s", opcaoMenu);


    if (strcmp(opcaoMenu, "1") == 0)
    {
        int aux;
        matriz = geraMatriz();

        scanf("%d", &dificuldade);
        scanf("%c", &aux);//Limpeza de buffer

        /*if ((dificuldade != 1) || (dificuldade != 2) || (dificuldade != 3))
        {
            printf(BOLD(RED("\n\nOpção inválida, por favor digite novamente!\n")));
            main();
        }*/

        embaralhaMatriz(setaEValidaDificuldade(dificuldade), opcao, matriz, guardaZero);
        imprimeMatriz(linha, coluna, d, matriz);

        printf("\nDigite um comando ou número da peça que quer mover:");
        fgets(pecaParaMover, 100, stdin);

        movePecaNaMatriz(matriz, guardaZero, pecaParaMover, linha, coluna, d, movimentos);

        liberaMatriz(matriz);
    }
    else if (strcmp(opcaoMenu, "2") == 0)
    {
        if (jaTemUmJogo != 0)
        {
            movePecaNaMatriz(matriz, guardaZero, pecaParaMover, linha, coluna, d, movimentos);
        }
        else
        {
            printf(BOLD(RED("\nPara continuar um jogo salvo, você já deve ter começado um jogo! Por favor, tente novamente!\n")));
            main();
        }
    }
    else if (strcmp(opcaoMenu, "3") == 0)
    {
        //Declaração de variaveis
        char nomeArquivoASerCarregado[30], aux;
        int dimensaoMatriz, tamanho;

        printf("\nDigite o nome do arquivo:");
        scanf("%c", &aux); // limpeza de buffer
        fgets(nomeArquivoASerCarregado, 30, stdin); //recebe o nome do arquivo

        //Tratamento para tirar o \n do nome do arquivo
        tamanho = strlen(nomeArquivoASerCarregado);
        nomeArquivoASerCarregado[tamanho - 1] = '\0';

        //Abre o arquivo no modo leitura
        FILE *arquivoCarregado = fopen(nomeArquivoASerCarregado, "r");

        if (arquivoCarregado == NULL)
        {
            printf("O arquivo escolhido não pode ser carregado!");
        }

        //Alocação dinamica da matriz recebida pelo arquivo 
        int **novaMat = malloc(3 * sizeof(int *));
        for (int i = 0; i < 3; i++)
        {
            novaMat[i] = malloc(3 * sizeof(int));
        }

        //Leitura da dimensão da matriz
        fscanf(arquivoCarregado, "%d", &dimensaoMatriz);

        //Leitura da matriz
        for (int i = 0; i < 3; i++)
            fscanf(arquivoCarregado, "%d %d %d", &novaMat[i][0], &novaMat[i][1], &novaMat[i][2]);

        //Leitura dos movimentos
        fscanf(arquivoCarregado, "%d", &movimentos);

        //Impressao da matriz 
        for (linha = 0; linha < d; linha++)
        {
            printf("\n");

            for (coluna = 0; coluna < d; coluna++)
            {
                printf(" %d ", novaMat[linha][coluna]);
            }
            printf("\n");
        }

        //Fecha o arquivo
        fclose(arquivoCarregado);

        //Chama função para mover a peça no jogo, passando a matriz do arquivo carregado como parametro para o estado atual
        movePecaNaMatriz(novaMat, guardaZero, pecaParaMover, linha, coluna, d, movimentos);
    }
    else if (strcmp(opcaoMenu, "4") == 0)
    {
        exibeInstrucoes();
    }
    else if (strcmp(opcaoMenu, "sair") == 0)
    {
        return 0;
    }
    else if (strcmp(opcaoMenu, "0") == 0)
    {
        return 0;
    }
    else
    {
        printf(BOLD(RED("\nOpção inválida, por favor digite novamente!\n")));
        main();
    }

    //Codigo finalizado com sucesso
    return 0;
}
