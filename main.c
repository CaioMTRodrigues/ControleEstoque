#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "usuarios.h"
#include "estoque.h"
#include <stdbool.h>
#define ARQUIVO_USUARIOS "usuarios.txt"
#define ARQUIVO_ESTOQUE "estoque.txt"

GtkBuilder *builder;
GtkWidget *main_window;
GtkWidget *menu_window;
GtkWidget *entrada_window;
GtkWidget *saida_window;
GtkListStore *liststore;

//itens da pesquisa abaixo
//GtkTreeModel *model;
//GtkTreeIter Iter;

void on_main_window_destroy(GtkWidget *widget, gpointer data){

    gtk_main_quit();
}
void on_menu_window_destroy(GtkWidget *widget, gpointer data){
    gtk_main_quit();
}
void on_entrada_window_destroy(GtkWidget *widget, gpointer data){
    gtk_widget_hide(entrada_window);
}
void on_saida_window_destroy(GtkWidget *widget, gpointer data){
    gtk_widget_hide(saida_window);
}
//pop-up's
void show_dialog_entrou(GtkBuilder *builder) {
    GtkWidget *dialog_entrou = GTK_WIDGET(gtk_builder_get_object(builder, "msg_entrou"));
    gtk_dialog_run(GTK_DIALOG(dialog_entrou));
    gtk_widget_hide(dialog_entrou);
}
void show_dialog_erro(GtkBuilder *builder) {
    GtkWidget *dialog_erro = GTK_WIDGET(gtk_builder_get_object(builder, "msg_erro"));
    gtk_dialog_run(GTK_DIALOG(dialog_erro));
    gtk_widget_hide(dialog_erro);
}
void show_dialog_erroarq(GtkBuilder *builder) {
    GtkWidget *dialog_erroarq = GTK_WIDGET(gtk_builder_get_object(builder, "msg_erroarq"));
    gtk_dialog_run(GTK_DIALOG(dialog_erroarq));
    gtk_widget_hide(dialog_erroarq);
}
void show_dialog_cadastrado(GtkBuilder *builder) {
    GtkWidget *dialog_cadastrado = GTK_WIDGET(gtk_builder_get_object(builder, "msg_cadastrado"));
    gtk_dialog_run(GTK_DIALOG(dialog_cadastrado));
    gtk_widget_hide(dialog_cadastrado);
}
void show_dialog_jaexiste(GtkBuilder *builder) {
    GtkWidget *dialog_jaexiste = GTK_WIDGET(gtk_builder_get_object(builder, "msg_jaexiste"));
    gtk_dialog_run(GTK_DIALOG(dialog_jaexiste));
    gtk_widget_hide(dialog_jaexiste);
}

//páginas de login e signup
void login(const gchar *user,const gchar *senha)
{
    char nomeArquivo[50], senhaArquivo[50];
    FILE *arquivo = fopen(ARQUIVO_USUARIOS, "r");
    if (!arquivo) {
        g_print("Erro ao abrir o arquivo de usuários!\n");
        show_dialog_erroarq(builder);
        return;
    }

    int autenticado = 0;

    while (fscanf(arquivo, "%49s %49s", nomeArquivo, senhaArquivo) != EOF) {
        if (strcmp(user, nomeArquivo) == 0 && strcmp(senha, senhaArquivo) == 0) {
            autenticado = 1;
            break;
        }
    }
    fclose(arquivo);

    if (autenticado) {
        show_dialog_entrou(builder);
        gtk_widget_hide(main_window);
        gtk_widget_show(menu_window);
            char nomeArquivo[50], senhaArquivo[50];
            FILE *arquivo = fopen(ARQUIVO_ESTOQUE, "r");
        if (!arquivo) {
            show_dialog_erroarq(builder);
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

        for (int i = 0; i < contadorItens; i++) {
        if (itens[i].quantidade > 0) {
            printf("Item: %s, Quantidade: %d\n", itens[i].nome, itens[i].quantidade);
            GtkTreeIter iter;
            gtk_list_store_append(liststore, &iter);
            gtk_list_store_set(liststore, &iter, 0, nome, 1, quantidade, -1);
        }
    }

    } else {
        show_dialog_erro(builder);
    }
}
void on_button_entrar_clicked(GtkWidget *widget, gpointer data)
{
    GtkEntry *entryloguser = GTK_ENTRY(gtk_builder_get_object(builder, "entry_loguser"));
    const gchar *user = gtk_entry_get_text(entryloguser);
    GtkEntry *entrylogsenha = GTK_ENTRY(gtk_builder_get_object(builder, "entry_logsenha"));
    const gchar *senha = gtk_entry_get_text(entrylogsenha);
    login(user, senha);
g_print("login\n%s\n%s\n\n", user, senha);
}
void on_button_cadastrar_clicked(GtkWidget *widget, gpointer data)
{

    GtkWidget *stack = GTK_WIDGET(gtk_builder_get_object(builder, "stack"));
    const char *page_cadastro = "page_cadastro";
    gtk_stack_set_visible_child_name(GTK_STACK(stack), page_cadastro);
}
void on_mostrar_toggled(GtkToggleButton *toggle_button, gpointer data)
{

    gboolean is_active = gtk_toggle_button_get_active(toggle_button);
    GtkWidget *entry_logsenha = GTK_WIDGET(gtk_builder_get_object(builder, "entry_logsenha"));
    gtk_entry_set_visibility(GTK_ENTRY(entry_logsenha), is_active);
}
void on_button_voltarcad_clicked(GtkWidget *widget, gpointer data)
{

    GtkWidget *stack = GTK_WIDGET(gtk_builder_get_object(builder, "stack"));
    const char *page_login = "page_login";
    gtk_stack_set_visible_child_name(GTK_STACK(stack), page_login);
}
void on_mostrarcad_toggled(GtkToggleButton *toggle_button, gpointer data)
{

    gboolean is_active = gtk_toggle_button_get_active(toggle_button);
    GtkWidget *entry_cadsenha = GTK_WIDGET(gtk_builder_get_object(builder, "entry_cadsenha"));
    gtk_entry_set_visibility(GTK_ENTRY(entry_cadsenha), is_active);
}
void cadastro(const gchar *caduser,const gchar *cadsenha){
    if (verificarUsuario(caduser)) {
        show_dialog_jaexiste(builder);
        return;
    }

    FILE *arquivo = fopen(ARQUIVO_USUARIOS, "a");
    if (!arquivo) {
        show_dialog_erroarq(builder);
    }

    fprintf(arquivo, "%s %s\n", caduser, cadsenha);
    fclose(arquivo);
    show_dialog_cadastrado(builder);
    GtkWidget *stack = GTK_WIDGET(gtk_builder_get_object(builder, "stack"));
    const char *page_login = "page_login";
    gtk_stack_set_visible_child_name(GTK_STACK(stack), page_login);
}
void on_button_cadastro_clicked(GtkWidget *widget, gpointer data)
{
    GtkEntry *entrycaduser = GTK_ENTRY(gtk_builder_get_object(builder, "entry_caduser"));
    const gchar *caduser = gtk_entry_get_text(entrycaduser);
    GtkEntry *entrycadsenha = GTK_ENTRY(gtk_builder_get_object(builder, "entry_cadsenha"));
    const gchar *cadsenha = gtk_entry_get_text(entrycadsenha);
    cadastro(caduser, cadsenha);
    g_print("cadastro\n%s\n%s\n\n", caduser, cadsenha);
}
void on_button_voltarentrada_clicked(GtkWidget *widget, gpointer data)
{
    gtk_widget_hide(entrada_window);
    gtk_widget_show(menu_window);
}
void on_button_cadentrada_clicked(GtkWidget *widget, gpointer data)
{
    gtk_widget_show(entrada_window);
}
void on_button_voltarsaida_clicked(GtkWidget *widget, gpointer data)
{
    gtk_widget_hide(saida_window);
    gtk_widget_show(menu_window);
}
void on_button_cadsaida_clicked(GtkWidget *widget, gpointer data)
{
    gtk_widget_show(saida_window);
}

//FUNÇÃO DE PESQUISAR ABAIXO (não concluida)
//void on_button_buscar_clicked(GtkWidget *widget, gpointer data){
    //GtkEntry *entrypesquisar = GTK_ENTRY(gtk_builder_get_object(builder, "entry_pesquisar"));
    //const gchar *pesquisar = gtk_entry_get_text(entrypesquisar);
    //g_print("%s", pesquisar);
    //gboolean filter_func(GtkTreeModel *model, GtkTreeIter *iter, gpointer data) {
        //gchar *item_text;
        //gtk_tree_model_get(model, iter, 0, &item_text, -1);
        //gboolean visible = (pesquisar == NULL || g_strcmp0(pesquisar, "") == 0 || g_strstr_len(item_text, -1, pesquisar) != NULL);
        //g_free(item_text);
        //return visible;
    //}
//}

void on_button_cadastroentrada_clicked(GtkWidget *widget, gpointer data)
{
    char *nome = "teste";
    char *quantidade_str = "999";
    if (nome && quantidade_str) {
        int quantidade = atoi(quantidade_str); 

        GtkTreeIter iter;
        gtk_list_store_append(liststore, &iter);
        gtk_list_store_set(liststore, &iter, 0, nome, 1, quantidade, -1);
}
}
//aaaaaaaaaaaaaaaaa
int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("ui.glade");

    gtk_builder_add_callback_symbols(
        builder,
        //handler das windows
        "on_main_window_destroy", G_CALLBACK(on_main_window_destroy),
        "on_menu_window_destroy", G_CALLBACK(on_menu_window_destroy),
        "on_entrada_window_destroy", G_CALLBACK(on_entrada_window_destroy),
        "on_saida_window_destroy", G_CALLBACK(on_saida_window_destroy),
        //stack 1 start
        "on_button_entrar_clicked", G_CALLBACK(on_button_entrar_clicked),
        "on_button_cadastrar_clicked", G_CALLBACK(on_button_cadastrar_clicked),
        g_signal_connect(gtk_builder_get_object(builder, "toggle_button"), "toggled", G_CALLBACK(on_mostrar_toggled), builder),
        //stack 1 end
        //stack 2 start
        "on_button_voltarcad_clicked", G_CALLBACK(on_button_voltarcad_clicked),
        "on_button_cadastro_clicked", G_CALLBACK(on_button_cadastro_clicked),
        g_signal_connect(gtk_builder_get_object(builder, "toggle_button"), "toggled", G_CALLBACK(on_mostrarcad_toggled), builder),
        //stack 2 end
        "on_button_voltarentrada_clicked", G_CALLBACK(on_button_voltarentrada_clicked),
        "on_button_cadentrada_clicked", G_CALLBACK(on_button_cadentrada_clicked),
        "on_button_cadsaida_clicked", G_CALLBACK(on_button_cadsaida_clicked),
        "on_button_voltarsaida_clicked", G_CALLBACK(on_button_voltarsaida_clicked),
        //BOTÃO DE PESQUISA (NÃO CONCLUÍDO)
        //"on_button_buscar_clicked", G_CALLBACK(on_button_buscar_clicked),
        "on_button_cadastroentrada_clicked", G_CALLBACK(on_button_cadastroentrada_clicked),
        NULL
    );

    gtk_builder_connect_signals(builder, NULL);

    main_window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    menu_window = GTK_WIDGET(gtk_builder_get_object(builder, "menu_window"));
    entrada_window = GTK_WIDGET(gtk_builder_get_object(builder, "entrada_window"));
    saida_window = GTK_WIDGET(gtk_builder_get_object(builder,"saida_window"));
    liststore = GTK_LIST_STORE(gtk_builder_get_object(builder, "list_estoque"));

    gtk_widget_show_all(main_window);
    gtk_main();

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
            printf("5. Sair\n");
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
                    printf("Saindo...\n");
                    return 0;
                default:
                    printf("Opção inválida! Tente novamente.\n");
            }
        }
    } while (1);

    return 0;
}
