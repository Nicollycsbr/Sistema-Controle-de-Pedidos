#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "../include/produto.h"

int main() {
    int opcao;

    initscr();
    echo();
    cbreak();
    curs_set(1);

    do {
        clear();

        mvprintw(2, 10, " -> MENU DE PRODUTOS <- ");
        mvprintw(5, 12, "1. Cadastrar produto\n");
        mvprintw(6, 12, "2. Listar produtos\n");
        mvprintw(7, 12, "3. Atualizar produto\n");
        mvprintw(8, 12, "4. Deletar produto\n");
        mvprintw(9, 12, "0. Sair\n");
        mvprintw(11, 10, "--------------------\n");
        mvprintw(13, 10, "Escolha uma opcao: ");
        refresh();

        scanw("%d", &opcao);
        
        clear();
        switch (opcao) {
            case 1:
                cadastrarProduto();
                break;
            case 2:
                listarProdutos();
                break;
            case 3:
                atualizarProduto();
                break;
            case 4:
                deletarProduto();
                break;
            case 0:
                mvprintw(5, 10, "\nSaindo do sistema...\n");
                refresh();
                break;
            default:
                mvprintw(5, 10, "\nOpcao invalida! Tente novamente.\n");
                refresh();
        }
        if (opcao != 0) {
        mvprintw(20, 10, "Pressione qualquer tecla para continuar!\n");
        refresh();
        getch();
        }

    } while (opcao != 0);
    
    endwin();
    return 0;
}