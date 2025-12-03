#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include "interface.h"
#include "cliente.h"
#include "produto.h"
#include "ui.h"

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
        int box_w;
        int box_h = n_opcoes + 6;
        int starty = (LINES - box_h) / 2;
        int startx = -1; /* request centered box from draw_box_auto */

        draw_box_auto(starty, startx, box_h, " MENU CLIENTE ", (const char **)opcoes, n_opcoes, &box_w);
        startx = (COLS - box_w) / 2;
        
        /* Print hint using ACS arrow characters to avoid unicode issues */
        int hint_y = starty + 2;
        int hint_x = startx + 2;
        mvprintw(hint_y, hint_x, "Use ");
        mvaddch(hint_y, hint_x + 4, ACS_UARROW);
        mvaddch(hint_y, hint_x + 5, '/');
        mvaddch(hint_y, hint_x + 6, ACS_DARROW);
        mvprintw(hint_y, hint_x + 8, " ou digite o número");
        for (int i = 0; i < n_opcoes; ++i) {
            if (i == highlight) attron(A_REVERSE);
            mvprintw(starty + 4 + i, startx + 3, "%d. %s", i + 1, opcoes[i]);
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
        int box_w;
        int box_h = n_opcoes + 6;
        int starty = (LINES - box_h) / 2;
        int startx = -1; /* request centered box from draw_box_auto */

        draw_box_auto(starty, startx, box_h, " MENU PRINCIPAL ", (const char **)opcoes, n_opcoes, &box_w);
        startx = (COLS - box_w) / 2;

        /* Print hint using ACS arrow characters to avoid unicode issues */
        int hint_y = starty + 2;
        int hint_x = startx + 2;
        mvprintw(hint_y, hint_x, "Use ");
        mvaddch(hint_y, hint_x + 4, ACS_UARROW);
        mvaddch(hint_y, hint_x + 5, '/');
        mvaddch(hint_y, hint_x + 6, ACS_DARROW);
        mvprintw(hint_y, hint_x + 8, " ou digite o número");
        for (int i = 0; i < n_opcoes; ++i) {
            if (i == highlight) attron(A_REVERSE);
            mvprintw(starty + 4 + i, startx + 3, "%d. %s", i + 1, opcoes[i]);
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