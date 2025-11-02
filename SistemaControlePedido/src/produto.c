#include "../include/produto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARQUIVO_PRODUTOS "../data/Produtos.csv"

void cadastrarProduto() {
    Produto p;
    FILE *arquivo = fopen(ARQUIVO_PRODUTOS, "a");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de produtos!\n");
        return;
    }

    printf("Digite o ID do produto:");
    scanf("%d", &p.id);
    getchar();
    printf("Digite o nome do produto:");

    fgets(p.nome, 50, stdin);
    p.nome[strcspn(p.nome, "\n")] = '\0';

    printf("Digite o preco do produto:");
    scanf("%f", &p.preco);
    printf("Digite a quantidade do produto:");
    scanf("%d", &p.quantidade);

    fprintf(arquivo, "%d,%s,%.2f,%d\n", p.id, p.nome, p.preco, p.quantidade);
    fclose(arquivo);
    printf("Produto cadastrado com sucesso!\n");
}
    
    void listarProdutos() {
        Produto p;
        FILE *arquivo = fopen(ARQUIVO_PRODUTOS, "r");

        if (arquivo == NULL) {
            printf("Nenhum produto cadastrado ainda.\n");
            return;
        }

        printf("Lista de Produtos:\n");
        while (fscanf(arquivo, "%d,%49[^,],%f,%d\n", &p.id, p.nome, &p.preco, &p.quantidade) != EOF) {
            printf("ID: %d, Nome: %s, Preco: %.2f, Quantidade: %d\n", p.id, p.nome, p.preco, p.quantidade);
        }

        fclose(arquivo);
    }

    void atualizarProduto() {
        int idBusca;
        Produto p;
        int encontrado = 0;
        FILE *arquivo = fopen(ARQUIVO_PRODUTOS, "r");
        FILE *temp = fopen("../data/temp.csv", "w");

        if (arquivo == NULL || temp == NULL) {
            printf("Erro ao abrir o arquivo de produtos!\n");
            return;
        }

        printf("Digite o ID do produto que deseja atualizar: ");
        scanf("%d", &idBusca);

        while (fscanf(arquivo, "%d,%49[^,],%f,%d\n", &p.id, p.nome, &p.preco, &p.quantidade) != EOF) {
            if (p.id == idBusca) {
                printf("Digite o novo nome do produto: ");
                getchar();
                fgets(p.nome, 50, stdin);
                p.nome[strcspn(p.nome, "\n")] = '\0';

                printf("Digite o novo preco do produto: ");
                scanf("%f", &p.preco);
                printf("Digite a nova quantidade do produto: ");
                scanf("%d", &p.quantidade);

                encontrado = 1;
            }
            fprintf(temp, "%d,%s,%.2f,%d\n", p.id, p.nome, p.preco, p.quantidade);
        }

        fclose(arquivo);
        fclose(temp);
        remove(ARQUIVO_PRODUTOS);
        rename("../data/temp.csv", ARQUIVO_PRODUTOS);

        if (encontrado)
            printf("Produto atualizado com sucesso!\n");
            else
            printf("Produto com ID %d nao encontrado.\n", idBusca);
    }

    void deletarProduto() {
        int idBusca;
        Produto p;
        int encontrado = 0;

        FILE *arquivo = fopen(ARQUIVO_PRODUTOS, "r");
        FILE *temp = fopen("../data/temp.csv", "w");

        if (arquivo == NULL || temp == NULL) {
            printf("Erro ao abrir o arquivo de produtos!\n");
            return;
        }

        printf("Digite o ID do produto que deseja deletar: ");
        scanf("%d", &idBusca);

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
        rename("../data/temp.csv", ARQUIVO_PRODUTOS);

        if (encontrado)
            printf("Produto deletado com sucesso!\n");
        else
            printf("Produto com ID %d nao encontrado.\n", idBusca);
    }