#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "../include/pedido.h"

int menu() {
    int opcao;

    clear();

    mvprintw(1, 2, "=== MENU DE PRODUTOS ===");
    mvprintw(2, 3, "1. Cadastrar pedido");
    mvprintw(3, 3, "2. Listar pedidos");
    mvprintw(4, 3, "3. Consultar pedido");
    mvprintw(5, 3, "4. Atualizar pedido");
    mvprintw(6, 3, "5. Deletar pedido");
    mvprintw(7, 3, "0. Sair");
    mvprintw(9, 1, "=========================");
    mvprintw(11, 1, "Escolha uma opcao: ");

    refresh();

    opcao = getch() - '0'; 
    return opcao;
}

int main() {
    int opcao;

    initscr();
    cbreak();
    noecho();              
    keypad(stdscr, TRUE);

    do {
        opcao = menu();

        switch (opcao) {
            case 1:
                cadastrarPedido();
                break;
            case 2:
                listarPedidos();
                break;
            case 3:
                consultarPedido();
                break;
            case 4:
                atualizarPedido();
                break;
            case 5:
                deletarPedido();
                break;
            case 0:
                mvprintw(13, 1, "Finalizando...");
                refresh();
                getch();
                break;
            default:
                mvprintw(13, 1, "Opcao invalida! Tente novamente.");
                refresh();
                getch();
        }

    } while (opcao != 0);

    endwin();
    return 0;
}
