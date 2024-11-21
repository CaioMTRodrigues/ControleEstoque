#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuarios.h"
#include "estoque.h"

void menuPrincipal() {
    int opcao;
    do {
        printf("\n--- Menu Principal ---\n");
        printf("1. Cadastrar entrada de novo item\n");
        printf("2. Cadastrar saída de item\n");
        printf("3. Visualizar itens no estoque\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarEntrada();
                break;
            case 2:
                cadastrarSaida();
                break;
            case 3:
                visualizarEstoque();
                break;
            case 4:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 4);
}

int main() {
    int opcao;
    do {
        printf("\n--- Sistema de Controle de Estoque ---\n");
        printf("1. Cadastrar novo usuário\n");
        printf("2. Logar com usuário existente\n");
        printf("3. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarUsuario();
                break;
            case 2:
                if (loginUsuario()) {
                    menuPrincipal();
                } else {
                    printf("Falha no login! Tente novamente.\n");
                }
                break;
            case 3:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 3);

    return 0;
}
