#include <curses.h>
#include <stdio.h>
#include "interface.h"
#include "cliente.h"
#include "produto.h"

static void nc_input(int row, int col, const char *prompt, char *buffer, int maxlen) {
    mvprintw(row, col, "%s", prompt);
    echo();
    curs_set(1);
    mvgetnstr(row + 1, col, buffer, maxlen - 1);
    noecho();
    curs_set(0);
}

void menu_cliente(Cliente clientes[], int *qtd) {
    int highlight = 0;
    int choice;
    const char *opcoes[] = {
        "Cadastrar novo cliente",
        "Remover cliente cadastrado",
        "Consultar cliente cadastrado",
        "Listar clientes cadastrados",
        "Voltar ao menu principal"
    };
    int n_opcoes = sizeof(opcoes) / sizeof(opcoes[0]);

    keypad(stdscr, TRUE);

    while (1) {
        clear();
        mvprintw(1, 2, "----- MENU CLIENTE -----");
        for (int i = 0; i < n_opcoes; ++i) {
            if (i == highlight) attron(A_REVERSE);
            mvprintw(3 + i, 4, "%s", opcoes[i]);
            if (i == highlight) attroff(A_REVERSE);
        }
        refresh();

        choice = getch();
        switch (choice) {
            case KEY_UP:
                highlight = (highlight == 0) ? n_opcoes - 1 : highlight - 1;
                break;
            case KEY_DOWN:
                highlight = (highlight == n_opcoes - 1) ? 0 : highlight + 1;
                break;
            case 10: 
                switch (highlight) {
                    case 0:
                        cadastrar_cliente(clientes, qtd);
                        break;
                    case 1:
                        remover_cliente(clientes, qtd);
                        break;
                    case 2:
                        consultar_cliente(clientes, *qtd);
                        break;
                    case 3:
                        listar_clientes(clientes, *qtd);
                        mvprintw(LINES - 2, 2, "Pressione qualquer tecla para voltar...");
                        getch();
                        break;
                    case 4:
                        return; 
                }
                break;
        }
    }
}

void menu_produto() {
    int opcao;

    do {
        clear();
        mvprintw(2, 10, "----- MENU PRODUTO -----");
        mvprintw(5, 12, "1. Cadastrar produto");
        mvprintw(6, 12, "2. Listar produtos");
        mvprintw(7, 12, "3. Atualizar produto");
        mvprintw(8, 12, "4. Deletar produto");
        mvprintw(9, 12, "0. Voltar ao menu principal");
        mvprintw(11, 10, "Escolha uma opcao: ");
        refresh();

        scanw("%d", &opcao);

        switch (opcao) {
            case 1: cadastrarProduto(); break;
            case 2: listarProdutos(); break;
            case 3: atualizarProduto(); break;
            case 4: deletarProduto(); break;
        }

    } while (opcao != 0);
}

void menu_principal(Cliente clientes[], int *qtd_clientes) {
    int opcao;

    do {
        clear();
        mvprintw(2, 10, "===== MENU PRINCIPAL =====");
        mvprintw(5, 12, "1. Cliente");
        mvprintw(6, 12, "2. Produto");
        mvprintw(7, 12, "0. Sair");
        mvprintw(9, 10, "Escolha uma opcao: ");
        refresh();

        scanw("%d", &opcao);

        switch (opcao) {
            case 1:
                menu_cliente(clientes, qtd_clientes);
                break;
            case 2:
                menu_produto();
                break;
        }

    } while (opcao != 0);
}