#ifndef PRODUTO_H
#define PRODUTO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

typedef struct {
    int id;
    char nome[50];
    float preco;
    int quantidade;
} Produto;

void cadastrarProduto();
void listarProdutos();
void atualizarProduto();
void deletarProduto();

#endif