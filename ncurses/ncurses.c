#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>


#include "../include/pedido.h"


void cadastrarPedido(void);
void listarPedidos(void);
void consultarPedido(void);
void atualizarPedido(void);
void deletarPedido(void);


static const char *ITEMS[] = {
    "Cadastrar pedido",
    "Listar pedidos",
    "Consultar pedido",
    "Atualizar pedido",
    "Deletar pedido",
    "Sair"
};
static const int N_ITEMS = sizeof(ITEMS) / sizeof(ITEMS[0]);

static void draw_menu(int highlight)
{
    clear();

    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    const char *title = "=== MENU DE PEDIDOS ===";
    mvprintw(1, (cols - (int)strlen(title)) / 2, "%s", title);

    const char *hint = "Use ↑/↓ para navegar, ENTER para selecionar, Q para sair";
    mvprintw(rows - 2, (cols - (int)strlen(hint)) / 2, "%s", hint);

    int start_row = rows / 2 - N_ITEMS / 2;

    for (int i = 0; i < N_ITEMS; i++) {
        int x = (cols - (int)strlen(ITEMS[i])) / 2;
        if (i == highlight) {
            attron(A_REVERSE);
            mvprintw(start_row + i, x, "%s", ITEMS[i]);
            attroff(A_REVERSE);
        } else {
            mvprintw(start_row + i, x, "%s", ITEMS[i]);
        }
    }

    refresh();
}

static void run_outside_curses(void (*fn)(void))
{
    
    def_prog_mode();
    endwin();

    if (fn) fn();

    printf("\nPressione ENTER para voltar ao menu...");
    fflush(stdout);
    int c;

    while ((c = getchar()) != '\n' && c != EOF) {}


    reset_prog_mode();
    refresh();
}

int main(void)
{
    initscr();
    cbreak();
    echo();
    keypad(stdscr, TRUE);
    curs_set(0);

    int highlight = 0;
    draw_menu(highlight);

    for (;;) {
        int ch = getch();
        switch (ch) {
            case KEY_UP:
                highlight = (highlight - 1 + N_ITEMS) % N_ITEMS;
                draw_menu(highlight);
                break;
            case KEY_DOWN:
                highlight = (highlight + 1) % N_ITEMS;
                draw_menu(highlight);
                break;
            case '\n':
            case KEY_ENTER:
                switch (highlight) {
                    case 0:
                        run_outside_curses(cadastrarPedido);
                        break;
                    case 1:
                        run_outside_curses(listarPedidos);
                        break;
                    case 2:
                        run_outside_curses(consultarPedido);
                        break;
                    case 3:
                        run_outside_curses(atualizarPedido);
                        break;
                    case 4:
                        run_outside_curses(deletarPedido);
                        break;
                    case 5: 
                        endwin();
                        printf("Finalizando...\n");
                        return 0;
                    default:
                        break;
                }
                draw_menu(highlight);
                break;
            case 'q':
            case 'Q':
                endwin();
                printf("Finalizando...\n");
                return 0;
            case KEY_RESIZE:
                draw_menu(highlight);
                break;
            default:
                break;
        }
    }

    endwin();
    return 0;
}
