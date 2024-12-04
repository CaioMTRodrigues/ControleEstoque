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

    typedef struct {
        char nome[50];
        int quantidade;
        char numerosSerie[1000]; // Lista consolidada de números de série
    } Item;

    Item itens[100]; // Suporta até 100 itens únicos
    int contadorItens = 0;

    char nome[50], tipo[10], numerosSerie[1000];
    int quantidade;

    // Processar o arquivo de estoque
    while (fscanf(arquivo, "%s %d %s %[^\n]", nome, &quantidade, tipo, numerosSerie) != EOF) {
        // Verificar se o item já está na lista
        int encontrado = 0;
        for (int i = 0; i < contadorItens; i++) {
            if (strcmp(itens[i].nome, nome) == 0) {
                // Atualizar os números de série e a quantidade com base no tipo de operação
                if (strcmp(tipo, "Entrada") == 0) {
                    // Adiciona os números de série ao estoque
                    strcat(itens[i].numerosSerie, ",");
                    strcat(itens[i].numerosSerie, numerosSerie);
                    itens[i].quantidade += quantidade;
                } else if (strcmp(tipo, "Saida") == 0) {
                    // Remove os números de série especificados
                    char *numero = strtok(numerosSerie, ",");
                    while (numero != NULL) {
                        char *pos = strstr(itens[i].numerosSerie, numero);
                        if (pos) {
                            // Remover o número de série encontrado
                            int len = strlen(numero);
                            if (*(pos + len) == ',') {
                                memmove(pos, pos + len + 1, strlen(pos + len));
                            } else if (pos != itens[i].numerosSerie) {
                                *(pos - 1) = '\0';
                            } else {
                                *pos = '\0';
                            }
                        }
                        numero = strtok(NULL, ",");
                    }
                    itens[i].quantidade -= quantidade;
                }
                encontrado = 1;
                break;
            }
        }

        // Se o item não foi encontrado, adicioná-lo à lista
        if (!encontrado && strcmp(tipo, "Entrada") == 0) {
            strcpy(itens[contadorItens].nome, nome);
            itens[contadorItens].quantidade = quantidade;
            strcpy(itens[contadorItens].numerosSerie, numerosSerie);
            contadorItens++;
        }
    }

    fclose(arquivo);

    // Exibir o relatório completo do estoque
    printf("\n--- Relatório Completo do Estoque ---\n");
    for (int i = 0; i < contadorItens; i++) {
        if (itens[i].quantidade > 0) { // Exibir apenas itens com saldo positivo
            printf("Item: %s, Quantidade: %d, Números de Série: %s\n", itens[i].nome, itens[i].quantidade, itens[i].numerosSerie);
        }
    }
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