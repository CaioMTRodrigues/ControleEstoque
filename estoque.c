#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estoque.h"

#define ARQUIVO_ESTOQUE "estoque.txt"

void cadastrarEntrada() {
    
    char nome[50], numerosSerie[200];
    int quantidade;

    printf("Digite o nome do item: ");
    getchar(); // Consumir o caractere de nova linha que sobra
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0'; // Remover o caractere de nova linha

    printf("Digite a quantidade de itens: ");
    scanf("%d", &quantidade);

    printf("Digite os números de série separados por vírgula: ");
    getchar(); // Consumir o caractere de nova linha que sobra
    fgets(numerosSerie, sizeof(numerosSerie), stdin);
    numerosSerie[strcspn(numerosSerie, "\n")] = '\0'; // Remover o caractere de nova linha

    FILE *arquivo = fopen(ARQUIVO_ESTOQUE, "a");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de estoque!\n");
        return;
    }

    fprintf(arquivo, "\"%s\" %d Entrada %s\n", nome, quantidade, numerosSerie);
    fclose(arquivo);

    printf("Entrada de item cadastrada com sucesso!\n");
}

void cadastrarSaida() {
    
    char nome[50], numerosSerie[200];
    int quantidade;

    printf("Digite o nome do item: ");
    getchar(); // Consumir o caractere de nova linha que sobra
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0'; // Remover o caractere de nova linha

    printf("Digite a quantidade de itens: ");
    scanf("%d", &quantidade);

    printf("Digite os números de série separados por vírgula: ");
    getchar(); // Consumir o caractere de nova linha que sobra
    fgets(numerosSerie, sizeof(numerosSerie), stdin);
    numerosSerie[strcspn(numerosSerie, "\n")] = '\0'; // Remover o caractere de nova linha

    FILE *arquivo = fopen(ARQUIVO_ESTOQUE, "a");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de estoque!\n");
        return;
    }

    fprintf(arquivo, "\"%s\" %d Saida %s\n", nome, quantidade, numerosSerie);
    fclose(arquivo);

    printf("Saída de item cadastrada com sucesso!\n");
}

void relatorioCompleto() {
    FILE *arquivo = fopen(ARQUIVO_ESTOQUE, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de estoque!\n");
        return;
    }

    printf("\n--- Relatório Completo ---\n");

    char nome[50], tipo[10], numerosSerie[200];
    int quantidade;
    while (fscanf(arquivo, "\"%49[^\"]\" %d %s %[^\n]", nome, &quantidade, tipo, numerosSerie) != EOF) {
        if (strcmp(tipo, "Entrada") == 0) {
            printf("Item: %s, Quantidade: %d, Números de Série: %s\n", nome, quantidade, numerosSerie);
        }
    }

    fclose(arquivo);
}

typedef struct {
    char nome[50];
    int quantidade;
} Item;

void limparEstoque() {
    FILE *arquivo = fopen(ARQUIVO_ESTOQUE, "w");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de estoque!\n");
        return;
    }
    fclose(arquivo);
    printf("Estoque limpo com sucesso!\n");
}

void visualizarEstoque() {
    FILE *arquivo = fopen(ARQUIVO_ESTOQUE, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de estoque!\n");
        return;
    }

    Item itens[100]; // Suporta até 100 itens únicos
    int contadorItens = 0;

    char nome[50], tipo[10], numerosSerie[200];
    int quantidade;

    // Processar o arquivo de estoque
    while (fscanf(arquivo, "\"%49[^\"]\" %d %s %[^\n]", nome, &quantidade, tipo, numerosSerie) != EOF) {
        // Verificar se o item já está na lista
        int encontrado = 0;
        for (int i = 0; i < contadorItens; i++) {
            if (strcmp(itens[i].nome, nome) == 0) {
                // Atualizar a quantidade com base no tipo de operação
                if (strcmp(tipo, "Entrada") == 0) {
                    itens[i].quantidade += quantidade;
                } else if (strcmp(tipo, "Saida") == 0) {
                    itens[i].quantidade -= quantidade;
                }
                encontrado = 1;
                break;
            }
        }

        // Se o item não foi encontrado, adicioná-lo à lista
        if (!encontrado) {
            strcpy(itens[contadorItens].nome, nome);
            itens[contadorItens].quantidade = (strcmp(tipo, "Entrada") == 0) ? quantidade : -quantidade;
            contadorItens++;
        }
    }

    fclose(arquivo);
    printf("Arquivo fechado");

    // Exibir os itens com quantidade maior que 0
    printf("\n--- Itens no Estoque ---\n");
    for (int i = 0; i < contadorItens; i++) {
        if (itens[i].quantidade > 0) {
            printf("Item: %s, Quantidade: %d\n", itens[i].nome, itens[i].quantidade);
        }
    }
}