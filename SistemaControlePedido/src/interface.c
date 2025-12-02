#include <ncurses.h>
#include <stdio.h>
#include "interface.h"
#include "cliente.h"
#include "produto.h"

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
            default: {
                if (choice >= '0' && choice <= '9') {
                    int sel = choice - '0';
                    if (sel >= 1 && sel <= n_opcoes) {
                        int idx = sel - 1;
                        switch (idx) {
                            case 0: cadastrar_cliente(clientes, qtd); break;
                            case 1: remover_cliente(clientes, qtd); break;
                            case 2: consultar_cliente(clientes, *qtd); break;
                            case 3:
                        #include <string.h>
                                listar_clientes(clientes, *qtd);
                                mvprintw(LINES - 2, 2, "Pressione qualquer tecla para voltar...");
                                getch();
                                break;
                            case 4: return;
                        }
                    }
                }
            } break;
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

void menu_principal(Cliente clientes[], int *qtd_clientes) {
    int highlight = 0;
    int choice;
    const char *opcoes[] = {
        "Cliente",
        "Produto",
        "Sair"
    };
    int n_opcoes = sizeof(opcoes) / sizeof(opcoes[0]);

    keypad(stdscr, TRUE);

    while (1) {
        clear();
        mvprintw(2, 10, "===== MENU PRINCIPAL =====");
        for (int i = 0; i < n_opcoes; ++i) {
            if (i == highlight) attron(A_REVERSE);
            mvprintw(5 + i, 12, "%s", opcoes[i]);
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
                default: {
                    if (choice >= '0' && choice <= '9') {
                        int sel = choice - '0';
                        if (sel == 0) {
                            return; /* 0 -> Sair */
                        } else if (sel >= 1 && sel <= n_opcoes) {
                            /* map numeric selection to action */
                            if (sel == 1) menu_cliente(clientes, qtd_clientes);
                            else if (sel == 2) menu_produto();
                            else if (sel == 3) return;
                        }
                    }
                } break;
            case 10:
                if (highlight == 0) {
                    menu_cliente(clientes, qtd_clientes);
                } else if (highlight == 1) {
                    menu_produto();
                } else if (highlight == 2) {
                    return;
                }
                break;
        }
    }
}