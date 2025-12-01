#include <curses.h>
#include <stdio.h>
#include "interface.h"
#include "cliente.h"

// Função auxiliar para input ncurses
static void nc_input(int row, int col, const char *prompt, char *buffer, int maxlen) {
    mvprintw(row, col, "%s", prompt);
    echo();
    curs_set(1);
    mvgetnstr(row + 1, col, buffer, maxlen - 1);
    noecho();
    curs_set(0);
}

// Menu de cliente usando ncurses
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
            case 10: // Enter
                switch (highlight) {
                    case 0: // Cadastrar
                        cadastrar_cliente(clientes, qtd);
                        break;
                    case 1: // Remover
                        remover_cliente(clientes, qtd);
                        break;
                    case 2: // Consultar
                        consultar_cliente(clientes, *qtd);
                        break;
                    case 3: // Listar
                        listar_clientes(clientes, *qtd);
                        mvprintw(LINES - 2, 2, "Pressione qualquer tecla para voltar...");
                        getch();
                        break;
                    case 4: // Voltar
                        return;
                }
                break;
        }
    }
}
