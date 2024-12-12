#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuarios.h"
#include "estoque.h"

int main() {//Função principal
    int opcao, logado = 0;

    do {
        if (!logado) {
            printf("\n--- Menu de Usuário ---\n");
            printf("1. Cadastrar novo usuário\n");
            printf("2. Fazer login\n");
            printf("3. Sair\n");
            printf("Escolha: ");
            scanf("%d", &opcao);

            switch (opcao) {
                case 1:
                    cadastrarUsuario();
                    break;
                case 2:
                    logado = loginUsuario();
                    if (!logado) {
                        printf("Falha no login! Tente novamente.\n");
                    }
                    break;
                case 3:
                    printf("Saindo...\n");
                    return 0;
                default:
                    printf("Opção inválida! Tente novamente.\n");
            }
        } else {
            printf("\n--- Menu Principal ---\n");
            printf("1. Cadastrar entrada de item\n");
            printf("2. Cadastrar saída de item\n");
            printf("3. Visualizar estoque simples\n");
            printf("4. Visualizar relatório completo\n");
            printf("5. Limpar estoque\n");
            printf("6. Sair\n");
            printf("Escolha: ");
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
                    relatorioCompleto();
                    break;
                case 5:
                    limparEstoque();
                    break;
                case 6:
                    printf("Saindo...\n");
                    return 0;
                default:
                    printf("Opção inválida! Tente novamente.\n");
            }
        }
    } while (1);

    return 0;
}