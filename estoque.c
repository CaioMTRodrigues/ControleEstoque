#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estoque.h"

#define ARQUIVO_ESTOQUE "estoque.txt"

void cadastrarEntrada() {
    // Implementação aqui
}

void cadastrarSaida() {
    // Implementação aqui
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

    Item itens[100]; // Suporta até 100 itens únicos
    int contadorItens = 0;

    char nome[50], tipo[10];
    int quantidade;

    // Processar o arquivo de estoque
    while (fscanf(arquivo, "%s %d %s", nome, &quantidade, tipo) != EOF) {
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