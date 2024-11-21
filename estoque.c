#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estoque.h"

#define ARQUIVO_ESTOQUE "estoque.txt"

void cadastrarEntrada() {
    char nome[50];
    int quantidade;

    printf("Digite o nome do item: ");
    scanf("%s", nome);
    printf("Digite a quantidade: ");
    scanf("%d", &quantidade);

    FILE *arquivo = fopen(ARQUIVO_ESTOQUE, "a");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de estoque!\n");
        return;
    }

    fprintf(arquivo, "%s %d Entrada\n", nome, quantidade);
    fclose(arquivo);
    printf("Item cadastrado com sucesso!\n");
}

void cadastrarSaida() {
    char nome[50];
    int quantidade;

    printf("Digite o nome do item: ");
    scanf("%s", nome);
    printf("Digite a quantidade: ");
    scanf("%d", &quantidade);

    FILE *arquivo = fopen(ARQUIVO_ESTOQUE, "a");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de estoque!\n");
        return;
    }

    fprintf(arquivo, "%s %d Saida\n", nome, quantidade);
    fclose(arquivo);
    printf("Saída registrada com sucesso!\n");
}

void visualizarEstoque() {
    char linha[100];
    FILE *arquivo = fopen(ARQUIVO_ESTOQUE, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de estoque!\n");
        return;
    }

    printf("\n--- Estoque ---\n");
    while (fgets(linha, sizeof(linha), arquivo)) {
        printf("%s", linha);
    }

    fclose(arquivo);
}
