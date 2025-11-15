#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include "../include/interface.h"

int menu_principal() {
    int op;
    clear();
    mvprintw(1, 2, "----- MENU PRINCIPAL -----");
    mvprintw(3, 4, "(1) Clientes");
    mvprintw(4, 4, "(2) Produtos");
    mvprintw(5, 4, "(3) Pedidos");
    mvprintw(6, 4, "(0) Sair");
    mvprintw(8, 2, "Qual área deseja acessar? ");
    mvprintw(9, 1, "-------------------------");
    refresh();
    op = getch() - '0';
    return op;
}

int main() {
    int op;
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    do {
        op = menu_principal();
        switch (op) {
            case 1:
                menu_cliente();
                break;
            case 2:
                clear();
                mvprintw(10, 2, "Área de produtos acessada!");
                getch();
                break;
            case 3:
                clear();
                mvprintw(10, 2, "Área de pedidos acessada!");
                getch();
                break;
            case 0:
                clear();
                mvprintw(10, 2, "Encerrando o programa...");
                getch();
                break;
            default:
                clear();
                mvprintw(10, 2, "Opção inválida! Tente novamente.");
                getch();
                break;
        }
    } while (op != 0);

    endwin();
    return 0;
}
