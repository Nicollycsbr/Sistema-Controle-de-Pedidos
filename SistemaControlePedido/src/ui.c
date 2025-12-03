#include "ui.h"

// Calcula a largura necessária para um quadro que acomoda um título e opções
static int calc_box_width(const char *title, const char **options, int n_options) {
    int max_len = (title ? strlen(title) : 0) + 4; // título + espaçamento
    for (int i = 0; i < n_options; ++i) {
        int opt_len = strlen(options[i]) + 6; // "N. opção" + espaçamento
        if (opt_len > max_len) max_len = opt_len;
    }
    // Considera também a linha de instrução (hint) que é mostrada nos menus,
    // por exemplo: "Use <seta cima>/<seta baixo> ou digite o número".
    // Contabilizamos espaço extra para as duas setas.
    const char *hint_template = "Use  / ou digite o número"; // duas posições para setas
    int hint_len = (int)strlen(hint_template) + 2; // margem extra
    if (hint_len > max_len) max_len = hint_len;

    return max_len > 20 ? max_len : 20; // mínimo 20
}

// Desenha um quadro com título centralizado
// Calcula automaticamente a largura com base no título e opções
int draw_box_auto(int starty, int startx, int height, const char *title,
                  const char **options, int n_options, int *box_w) {
    *box_w = calc_box_width(title, options, n_options);
    
    int y = starty;
    int x;
    int w = *box_w;
    int h = height;
    // If caller passes a negative startx, center the box horizontally
    if (startx < 0) {
        x = (COLS - w) / 2;
    } else {
        x = startx;
    }
    
    // Desenha borda
    mvaddch(y, x, ACS_ULCORNER);
    mvaddch(y, x + w - 1, ACS_URCORNER);
    mvaddch(y + h - 1, x, ACS_LLCORNER);
    mvaddch(y + h - 1, x + w - 1, ACS_LRCORNER);
    
    for (int i = x + 1; i < x + w - 1; ++i) {
        mvaddch(y, i, ACS_HLINE);
        mvaddch(y + h - 1, i, ACS_HLINE);
    }
    for (int i = y + 1; i < y + h - 1; ++i) {
        mvaddch(i, x, ACS_VLINE);
        mvaddch(i, x + w - 1, ACS_VLINE);
    }
    
    // Título centralizado
    if (title) {
        int tlen = strlen(title);
        int tx = x + (w - tlen) / 2;
        mvprintw(y, tx, "%s", title);
    }
    
    return h - 4; // altura interna
}

// Desenha um quadro simples (para telas de operação)
void draw_simple_box(int starty, int startx, int height, int width, const char *title) {
    int y = starty;
    int x = startx;
    
    // Desenha borda
    mvaddch(y, x, ACS_ULCORNER);
    mvaddch(y, x + width - 1, ACS_URCORNER);
    mvaddch(y + height - 1, x, ACS_LLCORNER);
    mvaddch(y + height - 1, x + width - 1, ACS_LRCORNER);
    
    for (int i = x + 1; i < x + width - 1; ++i) {
        mvaddch(y, i, ACS_HLINE);
        mvaddch(y + height - 1, i, ACS_HLINE);
    }
    for (int i = y + 1; i < y + height - 1; ++i) {
        mvaddch(i, x, ACS_VLINE);
        mvaddch(i, x + width - 1, ACS_VLINE);
    }
    
    // Título
    if (title) {
        int tlen = strlen(title);
        int tx = x + (width - tlen) / 2;
        mvprintw(y, tx, "%s", title);
    }
}
