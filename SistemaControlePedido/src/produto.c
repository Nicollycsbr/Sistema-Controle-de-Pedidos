#include "../include/produto.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui.h"

#define ARQUIVO_PRODUTOS "data/Produtos.csv"

void cadastrarProduto() {
    Produto p;
    FILE *arquivo = fopen(ARQUIVO_PRODUTOS, "a");

    if (arquivo == NULL) {
        mvprintw(5, 10, "Erro ao abrir o arquivo de produtos!");
        refresh();
        getch();
        return;
    }

    clear();
    echo();

    mvprintw(4, 10, "Digite o ID do produto: ");
    scanw("%d", &p.id);

    mvprintw(5, 10, "Digite o nome do produto: ");
    getnstr(p.nome, 50);

    mvprintw(6, 10, "Digite o preco do produto: ");
    scanw("%f", &p.preco);

    mvprintw(7, 10, "Digite a quantidade do produto: ");
    scanw("%d", &p.quantidade);

    fprintf(arquivo, "%d,%s,%.2f,%d\n", p.id, p.nome, p.preco, p.quantidade);
    fclose(arquivo);

    mvprintw(9, 10, "Produto cadastrado com sucesso!");
    refresh();
    getch();
}

void listarProdutos() {
    Produto p;
    FILE *arquivo = fopen(ARQUIVO_PRODUTOS, "r");

    clear();

    if (arquivo == NULL) {
        mvprintw(4, 10, "Nenhum produto cadastrado ainda.");
        refresh();
        getch();
        return;
    }

    int linha = 5;
    int read;
    while ((read = fscanf(arquivo, "%d,%49[^,],%f,%d\n",
                  &p.id, p.nome, &p.preco, &p.quantidade)) == 4) {
        mvprintw(linha++, 10,
                 "ID: %d | Nome: %s | Preco: %.2f | Qtd: %d",
                 p.id, p.nome, p.preco, p.quantidade);
    }

    fclose(arquivo);
    mvprintw(linha + 2, 10, "Fim da lista de produtos.");
    refresh();
    getch();
}

void atualizarProduto() {
    int idBusca;
    Produto p;
    int encontrado = 0;

    FILE *arquivo = fopen(ARQUIVO_PRODUTOS, "r");
    FILE *temp = fopen("data/temp.csv", "w");

    clear();

    if (arquivo == NULL || temp == NULL) {
        mvprintw(4, 10, "Erro ao abrir o arquivo de produtos!");
        refresh();
        getch();
        if (arquivo) fclose(arquivo);
        if (temp) fclose(temp);
        return;
    }

    mvprintw(4, 10, "Digite o ID do produto que deseja atualizar: ");
    echo();
    refresh();
    scanw("%d", &idBusca);
    noecho();

    int read;
    while ((read = fscanf(arquivo, "%d,%49[^,],%f,%d\n",
                  &p.id, p.nome, &p.preco, &p.quantidade)) == 4) {
        if (p.id == idBusca) {
            mvprintw(6, 10, "Digite o novo nome: ");
            echo();
            getnstr(p.nome, 50);
            noecho();

            mvprintw(7, 10, "Digite o novo preco: ");
            echo();
            scanw("%f", &p.preco);
            noecho();

            mvprintw(8, 10, "Digite a nova quantidade: ");
            echo();
            scanw("%d", &p.quantidade);
            noecho();

            encontrado = 1;
        }

        fprintf(temp, "%d,%s,%.2f,%d\n",
                p.id, p.nome, p.preco, p.quantidade);
    }

    fclose(arquivo);
    fclose(temp);
    remove(ARQUIVO_PRODUTOS);
    rename("data/temp.csv", ARQUIVO_PRODUTOS);

    if (encontrado) {
        mvprintw(10, 10, "Produto atualizado com sucesso!");
    } else {
        mvprintw(10, 10, "Produto com ID %d nao encontrado.", idBusca);
    }

    refresh();
    getch();
}

void deletarProduto() {
    int idBusca;
    Produto p;
    int encontrado = 0;

    FILE *arquivo = fopen(ARQUIVO_PRODUTOS, "r");
    FILE *temp = fopen("data/temp.csv", "w");

    clear();

    if (arquivo == NULL || temp == NULL) {
        mvprintw(4, 10, "Erro ao abrir o arquivo de produtos!");
        refresh();
        getch();
        return;
    }

    mvprintw(4, 10, "Digite o ID do produto que deseja deletar: ");
    echo();
    refresh();
    scanw("%d", &idBusca);
    noecho();

    int read;
    while ((read = fscanf(arquivo, "%d,%49[^,],%f,%d\n",
                  &p.id, p.nome, &p.preco, &p.quantidade)) == 4) {
        if (p.id == idBusca) {
            encontrado = 1;
            continue;
        }

        fprintf(temp, "%d,%s,%.2f,%d\n",
                p.id, p.nome, p.preco, p.quantidade);
    }

    fclose(arquivo);
    fclose(temp);
    remove(ARQUIVO_PRODUTOS);
    rename("data/temp.csv", ARQUIVO_PRODUTOS);

    if (encontrado) {
        mvprintw(6, 10, "Produto deletado com sucesso!");
    } else {
        mvprintw(6, 10, "Produto com ID %d nao encontrado.", idBusca);
    }

    refresh();
    getch();
}

void menu_produto() {
    int highlight = 0;
    int choice;
    const char *opcoes[] = {
        "Cadastrar produto",
        "Listar produtos",
        "Atualizar produto",
        "Deletar produto",
        "Voltar ao menu principal"
    };
    int n_opcoes = sizeof(opcoes) / sizeof(opcoes[0]);

    keypad(stdscr, TRUE);

    while (1) {
        clear();
        int box_w = 56;
        int box_h = n_opcoes + 6;
        int starty = (LINES - box_h) / 2;
        int startx = (COLS - box_w) / 2;

        mvaddch(starty, startx, ACS_ULCORNER);
        mvaddch(starty, startx + box_w - 1, ACS_URCORNER);
        mvaddch(starty + box_h - 1, startx, ACS_LLCORNER);
        mvaddch(starty + box_h - 1, startx + box_w - 1, ACS_LRCORNER);
        for (int i = startx + 1; i < startx + box_w - 1; ++i) {
            mvaddch(starty, i, ACS_HLINE);
            mvaddch(starty + box_h - 1, i, ACS_HLINE);
        }
        for (int i = starty + 1; i < starty + box_h - 1; ++i) {
            mvaddch(i, startx, ACS_VLINE);
            mvaddch(i, startx + box_w - 1, ACS_VLINE);
        }
        mvprintw(starty, startx + (box_w - 12) / 2, " MENU PRODUTO ");
        /* Print hint using ACS arrow characters to avoid unicode issues */
        int hint_y = starty + 2;
        int hint_x = startx + 3;
        mvprintw(hint_y, hint_x, "Use ");
        mvaddch(hint_y, hint_x + 4, ACS_UARROW);
        mvaddch(hint_y, hint_x + 5, '/');
        mvaddch(hint_y, hint_x + 6, ACS_DARROW);
        mvprintw(hint_y, hint_x + 8, " ou digite o número e Enter");
        for (int i = 0; i < n_opcoes; ++i) {
            if (i == highlight) attron(A_REVERSE);
            mvprintw(starty + 4 + i, startx + 4, "%d. %s", i + 1, opcoes[i]);
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
            default: {
                if (choice >= '0' && choice <= '9') {
                    int sel = choice - '0';
                    if (sel == 0) return; /* 0 -> voltar */
                    if (sel >= 1 && sel <= n_opcoes) {
                        int idx = sel - 1;
                        switch (idx) {
                            case 0: cadastrarProduto(); break;
                            case 1: listarProdutos(); break;
                            case 2: atualizarProduto(); break;
                            case 3: deletarProduto(); break;
                            case 4: return;
                        }
                    }
                }
            } break;
            case 10:
                if (highlight == 0) {
                    cadastrarProduto();
                } else if (highlight == 1) {
                    listarProdutos();
                } else if (highlight == 2) {
                    atualizarProduto();
                } else if (highlight == 3) {
                    deletarProduto();
                } else if (highlight == 4) {
                    return;
                }
                break;
        }
    }
}