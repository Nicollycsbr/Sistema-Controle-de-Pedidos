#include <curses.h>
#include "interface.h"
#include "cliente.h"

void menu_cliente() {
    int highlight = 0;
    int choice;
    const char *opcoes[] = {
        "Cadastrar novo cliente",
        "Remover cliente cadastrado",
        "Consultar cliente cadastrado",
        "Editar cliente cadastrado",
        "Listar clientes cadastrados",
        "Voltar ao menu principal"
    };
    int n_opcoes = sizeof(opcoes) / sizeof(opcoes[0]);

    while (1) {
        clear();
        mvprintw(1, 2, "----- MENU CLIENTE -----");
        for (int i = 0; i < n_opcoes; i++) {
            if (i == highlight)
                attron(A_REVERSE);
            mvprintw(3 + i, 4, "%s", opcoes[i]);
            attroff(A_REVERSE);
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
                    case 0: inserir_cliente(); break;
                    case 1: remover_cliente(); break;
                    case 2: consultar_cliente(); break;
                    case 3: editar_cliente(); break;
                    case 4: listar_clientes(); break;
                    case 5: return;
                }
                break;
        }
    }
}
