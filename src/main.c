#include <stdio.h>
#include <ncurses.h>
#include "interface.h"
#include "persistencia.h"
#include "cliente.h"

int main() {
    Cliente clientes[MAX_CLIENTES];
    int qtd_clientes = 0;

    carregar_clientes(CLIENTES_CSV, clientes, &qtd_clientes);

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    menu_cliente(clientes, &qtd_clientes);  // passa como parâmetro

    salvar_clientes(CLIENTES_CSV, clientes, qtd_clientes);

    endwin();

    printf("Saindo... dados salvos em %s (clientes = %d)\n", CLIENTES_CSV, qtd_clientes);
    return 0;
}
