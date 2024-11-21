#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuarios.h"

#define ARQUIVO_USUARIOS "usuarios.txt"

void cadastrarUsuario() {
    char nome[50], senha[50];
    printf("Digite o nome de usuário: ");
    scanf("%s", nome);
    printf("Digite a senha: ");
    scanf("%s", senha);

    if (verificarUsuario(nome)) {
        printf("Usuário já existe! Escolha outro nome.\n");
        return;
    }

    FILE *arquivo = fopen(ARQUIVO_USUARIOS, "a");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de usuários!\n");
        return;
    }

    fprintf(arquivo, "%s %s\n", nome, senha);
    fclose(arquivo);
    printf("Usuário cadastrado com sucesso!\n");
}

int loginUsuario() {
    char nome[50], senha[50], nomeArquivo[50], senhaArquivo[50];
    printf("Digite o nome de usuário: ");
    scanf("%s", nome);
    printf("Digite a senha: ");
    scanf("%s", senha);

    FILE *arquivo = fopen(ARQUIVO_USUARIOS, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de usuários!\n");
        return 0;
    }

    while (fscanf(arquivo, "%s %s", nomeArquivo, senhaArquivo) != EOF) {
        if (strcmp(nome, nomeArquivo) == 0 && strcmp(senha, senhaArquivo) == 0) {
            fclose(arquivo);
            return 1;
        }
    }

    fclose(arquivo);
    return 0;
}

int verificarUsuario(const char *nome) {
    char nomeArquivo[50], senhaArquivo[50];
    FILE *arquivo = fopen(ARQUIVO_USUARIOS, "r");
    if (!arquivo) {
        return 0;
    }

    while (fscanf(arquivo, "%s %s", nomeArquivo, senhaArquivo) != EOF) {
        if (strcmp(nome, nomeArquivo) == 0) {
            fclose(arquivo);
            return 1;
        }
    }

    fclose(arquivo);
    return 0;
}
