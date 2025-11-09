#include "../include/produto.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARQUIVO_PRODUTOS "data/Produtos.csv"

void cadastrarProduto() {
    Produto p;
    FILE *arquivo = fopen(ARQUIVO_PRODUTOS, "a");

    if (arquivo == NULL) {
        mvprintw(5, 10, "Erro ao abrir o arquivo de produtos!\n");
        refresh();
        getch();
        return;
    }
    echo();
    
    mvprintw(4, 10, "Digite o ID do produto:");
    scanw("%d", &p.id);
    getchar();

    mvprintw(5, 10, "Digite o nome do produto:");
    getnstr(p.nome, 50);


    mvprintw(6, 10, "Digite o preco do produto:");
    scanw("%f", &p.preco);

    mvprintw(7, 10, "Digite a quantidade do produto:");
    scanw("%d", &p.quantidade);

    fprintf(arquivo, "%d,%s,%.2f,%d\n", p.id, p.nome, p.preco, p.quantidade);
    fclose(arquivo);
    mvprintw(9, 10, "Produto cadastrado com sucesso!\n");
    refresh();
    getch();
}
    
    void listarProdutos() {
        Produto p;
        FILE *arquivo = fopen(ARQUIVO_PRODUTOS, "r");

        

        if (arquivo == NULL) {
            mvprintw(4, 10, "Nenhum produto cadastrado ainda.\n");
            refresh();
            getch();
            return;
        }
        
        int linha = 5;
        while (fscanf(arquivo, "%d,%49[^,],%f,%d\n", &p.id, p.nome, &p.preco, &p.quantidade) != EOF) {
            mvprintw(linha++, 10, "ID: %d, Nome: %s, Preco: %.2f, Quantidade: %d\n", p.id, p.nome, p.preco, p.quantidade);
        }

        fclose(arquivo);
        mvprintw(linha + 2, 10, "Fim da lista de produtos.\n");
        refresh();
        getch();
    }

    void atualizarProduto() {
        int idBusca;
        Produto p;
        int encontrado = 0;
        FILE *arquivo = fopen(ARQUIVO_PRODUTOS, "r");
        FILE *temp = fopen("data/temp.csv", "w");

        if (arquivo == NULL || temp == NULL) {
            mvprintw(4, 10, "Erro ao abrir o arquivo de produtos!\n");
            refresh();
            getch();
            return;
        }

        mvprintw(4, 10, "Digite o ID do produto que deseja atualizar: ");
        scanw("%d", &idBusca);

        while (fscanf(arquivo, "%d,%49[^,],%f,%d\n", &p.id, p.nome, &p.preco, &p.quantidade) != EOF) {
            if (p.id == idBusca) {
                mvprintw(6, 10, "Digite o novo nome do produto: ");
                echo();
                getnstr(p.nome, 50);
                noecho();

                mvprintw(7, 10, "Digite o novo preco do produto: ");
                scanw("%f", &p.preco);
                mvprintw(8, 10, "Digite a nova quantidade do produto: ");
                scanw("%d", &p.quantidade);

                encontrado = 1;
            }
            fprintf(temp, "%d,%s,%.2f,%d\n", p.id, p.nome, p.preco, p.quantidade);
        }

        fclose(arquivo);
        fclose(temp);
        remove(ARQUIVO_PRODUTOS);
        rename("data/temp.csv", ARQUIVO_PRODUTOS);

        if (encontrado)
            mvprintw(10, 10, "\nProduto atualizado com sucesso!\n");
            else
            mvprintw(10, 10, "Produto com ID %d nao encontrado.\n", idBusca);

            refresh();
            getch();
    }

    void deletarProduto() {
        int idBusca;
        Produto p;
        int encontrado = 0;

        FILE *arquivo = fopen(ARQUIVO_PRODUTOS, "r");
        FILE *temp = fopen("data/temp.csv", "w");


        if (arquivo == NULL || temp == NULL) {
            mvprintw(4, 10, "Erro ao abrir o arquivo de produtos!\n");
            refresh();
            getch();
            return;
        }

        mvprintw(4, 10, "Digite o ID do produto que deseja deletar: ");
        scanw("%d", &idBusca);

        while (fscanf(arquivo, "%d,%49[^,],%f,%d\n", &p.id, p.nome, &p.preco, &p.quantidade) != EOF) {
            if (p.id == idBusca) {
                encontrado = 1;
                continue;
            }
            fprintf(temp, "%d,%s,%.2f,%d\n", p.id, p.nome, p.preco, p.quantidade);
        }

        fclose(arquivo);
        fclose(temp);
        remove(ARQUIVO_PRODUTOS);
        rename("data/temp.csv", ARQUIVO_PRODUTOS);

        if (encontrado){
            mvprintw(6, 10, "\nProduto deletado com sucesso!\n");
        } else {
            mvprintw(6, 10, "Produto com ID %d nao encontrado.\n", idBusca);
        }
            refresh();
            getch();
    }