#include <stdio.h>
#include <stdlib.h>

// Define constantes para facilitar alterações no tamanho da matriz e no número máximo de gerações.
#define LINHAS 10
#define COLUNAS 10
#define MAX_GERACOES 100

// Declara uma função que imprime a matriz na tela.
void imprimirMatriz(char matriz[LINHAS][COLUNAS], int geracao) { 
    printf("Geração %d:\n", geracao);
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            printf("%c ", matriz[i][j]);
        }
        printf("\n");
    }
}

void inicializarManual(char matriz[LINHAS][COLUNAS]) {
    int x, y;
    char opcao;

    // Inicializa tudo como morto
    for (int i = 0; i < LINHAS; i++)
        for (int j = 0; j < COLUNAS; j++)
            matriz[i][j] = '*';

    printf("Digite as coordenadas das células vivas (formato: linha, coluna).\n");
    printf("Exemplo: 2 3\nDigite -1 -1 para parar.\n");

    while (1) {
        printf("Célula viva em: ");
        scanf("%d %d", &x, &y);
        if (x == -1 && y == -1) break;

        if (x >= 0 && x < LINHAS && y >= 0 && y < COLUNAS) {
            matriz[x][y] = 'O';
        } else {
            printf("Coordenadas inválidas!\n");
        }
    }
}

int contarVizinhosVivos(char matriz[LINHAS][COLUNAS], int x, int y) {
    int vivos = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int nx = x + i;
            int ny = y + j;
            if (nx >= 0 && nx < LINHAS && ny >= 0 && ny < COLUNAS && matriz[nx][ny] == 'O') {
                vivos++;
            }
        }
    }
    return vivos;
}

void atualizarMatriz(char matriz[LINHAS][COLUNAS], char nova[LINHAS][COLUNAS]) {
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            int vizinhos = contarVizinhosVivos(matriz, i, j);
            if (matriz[i][j] == 'O') {
                nova[i][j] = (vizinhos == 2 || vizinhos == 3) ? 'O' : '*';
            } else {
                nova[i][j] = (vizinhos == 3) ? 'O' : '*';
            }
        }
    }
}

int main() {
    char atual[LINHAS][COLUNAS];
    char proxima[LINHAS][COLUNAS];
    int geracoes;

    printf("Quantas gerações deseja simular (max %d)? ", MAX_GERACOES);
    scanf("%d", &geracoes);
    if (geracoes > MAX_GERACOES) geracoes = MAX_GERACOES;

    inicializarManual(atual);

    for (int g = 1; g <= geracoes; g++) {
        imprimirMatriz(atual, g);
        atualizarMatriz(atual, proxima);

        // Copia a próxima geração para a atual
        for (int i = 0; i < LINHAS; i++)
            for (int j = 0; j < COLUNAS; j++)
                atual[i][j] = proxima[i][j];

        printf("Pressione ENTER para continuar...\n");
        getchar(); // limpa buffer
        getchar(); // espera ENTER
    }

    return 0;
}
