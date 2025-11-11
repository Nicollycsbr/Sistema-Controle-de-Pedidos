#include "../include/pedido.h"
#include "../include/produto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARQUIVO_PEDIDOS "data/Pedidos.csv"
#define ARQUIVO_ITENS "data/ItensPedido.csv"
#define ARQUIVO_PRODUTOS "data/Produtos.csv"

// ---------- Funções auxiliares ---------- //
float obterPrecoProduto(int idProduto) {
    Produto p;
    FILE *arquivo = fopen(ARQUIVO_PRODUTOS, "r");
    if (arquivo == NULL) return -1;

    while (fscanf(arquivo, "%d,%49[^,],%f,%d\n", &p.id, p.nome, &p.preco, &p.quantidade) != EOF) {
        if (p.id == idProduto) {
            fclose(arquivo);
            return p.preco;
        }
    }

    fclose(arquivo);
    return -1;
}

int verificarEstoque(int idProduto, int quantidade) {
    Produto p;
    FILE *arquivo = fopen(ARQUIVO_PRODUTOS, "r");
    if (arquivo == NULL) return 0;

    while (fscanf(arquivo, "%d,%49[^,],%f,%d\n", &p.id, p.nome, &p.preco, &p.quantidade) != EOF) {
        if (p.id == idProduto) {
            fclose(arquivo);
            return (p.quantidade >= quantidade);
        }
    }

    fclose(arquivo);
    return 0;
}

void atualizarEstoque(int idProduto, int quantidadeVendida) {
    Produto p;
    FILE *arquivo = fopen(ARQUIVO_PRODUTOS, "r");
    FILE *temp = fopen("data/temp.csv", "w");

    if (arquivo == NULL || temp == NULL) {
        printf("Erro ao abrir o arquivo de produtos!\n");
        return;
    }

    while (fscanf(arquivo, "%d,%49[^,],%f,%d\n", &p.id, p.nome, &p.preco, &p.quantidade) != EOF) {
        if (p.id == idProduto) {
            p.quantidade -= quantidadeVendida;
        }
        fprintf(temp, "%d,%s,%.2f,%d\n", p.id, p.nome, p.preco, p.quantidade);
    }

    fclose(arquivo);
    fclose(temp);
    remove(ARQUIVO_PRODUTOS);
    rename("data/temp.csv", ARQUIVO_PRODUTOS);
}

// ---------- Cadastrar Pedido ---------- //
void cadastrarPedido() {
    Pedido pedido;
    ItemPedido item;
    int continuar = 1;
    float total = 0;

    FILE *arqPedidos = fopen(ARQUIVO_PEDIDOS, "a");
    FILE *arqItens = fopen(ARQUIVO_ITENS, "a");

    if (arqPedidos == NULL || arqItens == NULL) {
        printf("Erro ao abrir os arquivos de pedidos!\n");
        return;
    }

    printf("Digite o ID do pedido: ");
    scanf("%d", &pedido.id);
    printf("Digite o ID do cliente: ");
    scanf("%d", &pedido.clienteId);
    printf("Digite a data (dd/mm/aaaa): ");
    scanf("%s", pedido.data);

    while (continuar) {
        printf("\nDigite o ID do produto: ");
        scanf("%d", &item.produtoId);

        float preco = obterPrecoProduto(item.produtoId);
        if (preco < 0) {
            printf("Produto não encontrado!\n");
            continue;
        }

        printf("Digite a quantidade: ");
        scanf("%d", &item.quantidade);

        if (!verificarEstoque(item.produtoId, item.quantidade)) {
            printf("Estoque insuficiente!\n");
            continue;
        }

        item.subtotal = preco * item.quantidade;
        item.pedidoId = pedido.id;
        total += item.subtotal;

        fprintf(arqItens, "%d,%d,%d,%.2f\n", item.pedidoId, item.produtoId, item.quantidade, item.subtotal);

        atualizarEstoque(item.produtoId, item.quantidade);

        printf("Adicionar outro item? (1 - Sim, 0 - Não): ");
        scanf("%d", &continuar);
    }

    pedido.total = total;
    fprintf(arqPedidos, "%d,%d,%s,%.2f\n", pedido.id, pedido.clienteId, pedido.data, pedido.total);

    fclose(arqPedidos);
    fclose(arqItens);
    printf("\nPedido cadastrado com sucesso!\n");
}

// ---------- Listar Pedidos ---------- //
void listarPedidos() {
    Pedido p;
    FILE *arquivo = fopen(ARQUIVO_PEDIDOS, "r");

    if (arquivo == NULL) {
        printf("Nenhum pedido cadastrado ainda.\n");
        return;
    }

    printf("\nLista de Pedidos:\n");
    while (fscanf(arquivo, "%d,%d,%10[^,],%f\n", &p.id, &p.clienteId, p.data, &p.total) != EOF) {
        printf("ID: %d, Cliente: %d, Data: %s, Total: %.2f\n", p.id, p.clienteId, p.data, p.total);
    }

    fclose(arquivo);
}

// ---------- Consultar Pedido ---------- //
void consultarPedido() {
    Pedido p;
    ItemPedido item;
    int idBusca, encontrado = 0;

    printf("Digite o ID do pedido que deseja consultar: ");
    scanf("%d", &idBusca);

    FILE *arqPedidos = fopen(ARQUIVO_PEDIDOS, "r");
    FILE *arqItens = fopen(ARQUIVO_ITENS, "r");

    if (arqPedidos == NULL || arqItens == NULL) {
        printf("Erro ao abrir os arquivos!\n");
        return;
    }

    while (fscanf(arqPedidos, "%d,%d,%10[^,],%f\n", &p.id, &p.clienteId, p.data, &p.total) != EOF) {
        if (p.id == idBusca) {
            printf("\nPedido ID: %d\nCliente: %d\nData: %s\nTotal: %.2f\n", p.id, p.clienteId, p.data, p.total);
            printf("Itens do Pedido:\n");
            printf("ProdutoID\tQtd\tSubtotal\n");
            while (fscanf(arqItens, "%d,%d,%d,%f\n", &item.pedidoId, &item.produtoId, &item.quantidade, &item.subtotal) != EOF) {
                if (item.pedidoId == p.id) {
                    printf("%d\t\t%d\t%.2f\n", item.produtoId, item.quantidade, item.subtotal);
                }
            }
            encontrado = 1;
            break;
        }
    }

    if (!encontrado)
        printf("Pedido com ID %d não encontrado.\n", idBusca);

    fclose(arqPedidos);
    fclose(arqItens);
}

// ---------- Atualizar Pedido (só data ou cliente) ---------- //
void atualizarPedido() {
    int idBusca, encontrado = 0;
    Pedido p;

    FILE *arquivo = fopen(ARQUIVO_PEDIDOS, "r");
    FILE *temp = fopen("data/temp.csv", "w");

    if (arquivo == NULL || temp == NULL) {
        printf("Erro ao abrir o arquivo de pedidos!\n");
        return;
    }

    printf("Digite o ID do pedido que deseja atualizar: ");
    scanf("%d", &idBusca);

    while (fscanf(arquivo, "%d,%d,%10[^,],%f\n", &p.id, &p.clienteId, p.data, &p.total) != EOF) {
        if (p.id == idBusca) {
            printf("Digite o novo ID do cliente: ");
            scanf("%d", &p.clienteId);
            printf("Digite a nova data (dd/mm/aaaa): ");
            scanf("%s", p.data);
            encontrado = 1;
        }
        fprintf(temp, "%d,%d,%s,%.2f\n", p.id, p.clienteId, p.data, p.total);
    }

    fclose(arquivo);
    fclose(temp);
    remove(ARQUIVO_PEDIDOS);
    rename("data/temp.csv", ARQUIVO_PEDIDOS);

    if (encontrado)
        printf("Pedido atualizado com sucesso!\n");
    else
        printf("Pedido com ID %d não encontrado.\n", idBusca);
}

// ---------- Deletar Pedido ---------- //
void deletarPedido() {
    int idBusca, encontrado = 0;
    Pedido p;
    ItemPedido item;

    FILE *arqPedidos = fopen(ARQUIVO_PEDIDOS, "r");
    FILE *arqTempPedidos = fopen("data/tempPedidos.csv", "w");
    FILE *arqItens = fopen(ARQUIVO_ITENS, "r");
    FILE *arqTempItens = fopen("data/tempItens.csv", "w");

    if (arqPedidos == NULL || arqTempPedidos == NULL || arqItens == NULL || arqTempItens == NULL) {
        printf("Erro ao abrir os arquivos!\n");
        return;
    }

    printf("Digite o ID do pedido que deseja deletar: ");
    scanf("%d", &idBusca);

    // Copiar todos os pedidos menos o escolhido //
    while (fscanf(arqPedidos, "%d,%d,%10[^,],%f\n", &p.id, &p.clienteId, p.data, &p.total) != EOF) {
        if (p.id == idBusca) {
            encontrado = 1;
            continue;
        }
        fprintf(arqTempPedidos, "%d,%d,%s,%.2f\n", p.id, p.clienteId, p.data, p.total);
    }

    // Copiar itens, exceto os do pedido removido //
    while (fscanf(arqItens, "%d,%d,%d,%f\n", &item.pedidoId, &item.produtoId, &item.quantidade, &item.subtotal) != EOF) {
        if (item.pedidoId == idBusca)
            continue;
        fprintf(arqTempItens, "%d,%d,%d,%.2f\n", item.pedidoId, item.produtoId, item.quantidade, item.subtotal);
    }

    fclose(arqPedidos);
    fclose(arqTempPedidos);
    fclose(arqItens);
    fclose(arqTempItens);

    remove(ARQUIVO_PEDIDOS);
    rename("data/tempPedidos.csv", ARQUIVO_PEDIDOS);
    remove(ARQUIVO_ITENS);
    rename("data/tempItens.csv", ARQUIVO_ITENS);

    if (encontrado)
        printf("Pedido deletado com sucesso!\n");
    else
        printf("Pedido com ID %d não encontrado.\n", idBusca);
}
