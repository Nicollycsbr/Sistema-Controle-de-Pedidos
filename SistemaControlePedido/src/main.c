#include <stdio.h>
#include <ncurses.h>
#include "../include/interface.h"

int main() {
    initscr();
    echo();
    cbreak();
    curs_set(1);

    menuPrincipal();

    endwin();
    return 0;
}