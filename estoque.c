#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estoque.h"

#define ARQUIVO_ESTOQUE "estoque.txt"

void cadastrarEntrada() {
    
    FILE *arquivo = fopen(ARQUIVO_ESTOQUE, "a"); // Abre o arquivo em modo de adição
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de estoque!\n");
        return;
    }

    char nome[50];
    int quantidade;
    char numerosSerie[500];

    printf("Digite o nome do item: ");
    scanf("%s", nome);

    printf("Digite a quantidade de entrada: ");
    scanf("%d", &quantidade);

    printf("Digite os números de série separados por vírgulas: ");
    scanf(" %[^\n]", numerosSerie); // Lê até o final da linha

    // Escreve a operação no arquivo
    fprintf(arquivo, "%s %d Entrada %s\n", nome, quantidade, numerosSerie);

    printf("Entrada registrada com sucesso!\n");
    fclose(arquivo);
}

void cadastrarSaida() {
    
    FILE *arquivo = fopen(ARQUIVO_ESTOQUE, "a");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de estoque!\n");
        return;
    }

    char nome[50];
    int quantidade;
    char numerosSerie[500]; // Para armazenar números de série

    printf("Digite o nome do item: ");
    scanf("%s", nome);

    printf("Digite a quantidade de saída: ");
    scanf("%d", &quantidade);

    printf("Digite os números de série separados por vírgulas: ");
    scanf(" %[^\n]", numerosSerie); // Lê até o final da linha

    // Grava no arquivo
    fprintf(arquivo, "%s %d Saida %s\n", nome, quantidade, numerosSerie);

    printf("Saída registrada com sucesso!\n");
    fclose(arquivo);
}

void relatorioCompleto() {
    FILE *arquivo = fopen(ARQUIVO_ESTOQUE, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de estoque!\n");
        return;
    }

    char nome[50], tipo[10], numerosSerie[500];
    int quantidade;

    printf("\n--- Relatório Completo do Estoque ---\n");
    while (fscanf(arquivo, "%s %d %s %[^\n]", nome, &quantidade, tipo, numerosSerie) != EOF) {
        printf("Item: %s, Quantidade: %d, Tipo: %s, Números de Série: %s\n",
               nome, quantidade, tipo, numerosSerie);
    }

    fclose(arquivo);
}

typedef struct {
    char nome[50];
    int quantidade;
} Item;

void visualizarEstoque() {
    FILE *arquivo = fopen(ARQUIVO_ESTOQUE, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de estoque!\n");
        return;
    }

    typedef struct {
        char nome[50];
        int quantidade;
    } Item;

    Item itens[100]; // Suporta até 100 itens únicos
    int contadorItens = 0;

    char nome[50], tipo[10], numerosSerie[500];
    int quantidade;

    // Processar o arquivo de estoque
    while (fscanf(arquivo, "%s %d %s %[^\n]", nome, &quantidade, tipo, numerosSerie) != EOF) {
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

    // Exibir os itens com quantidade maior que 0
    printf("\n--- Itens no Estoque ---\n");
    for (int i = 0; i < contadorItens; i++) {
        if (itens[i].quantidade > 0) {
            printf("Item: %s, Quantidade: %d\n", itens[i].nome, itens[i].quantidade);
        }
    }
}