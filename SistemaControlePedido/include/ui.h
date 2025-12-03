#ifndef UI_H
#define UI_H

#include <ncurses.h>
#include <string.h>

// Desenha um quadro com título centralizado e retorna dimensões internas úteis
// Retorna a altura interna (height - 4)
int draw_box_auto(int starty, int startx, int height, const char *title,
                  const char **options, int n_options, int *box_w);

// Desenha um quadro simples com título (sem opções numeradas)
void draw_simple_box(int starty, int startx, int height, int width, const char *title);

#endif
