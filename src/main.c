#include <stdio.h>
#include <stdlib.h>
#include "../include/pedido.h"

int main() {
    int opcao;

    do {
        printf("\n=== MENU DE PRODUTOS ===\n");
        printf("1. Cadastrar pedido\n");
        printf("2. Listar pedidos\n");
        printf("3. consultar pedido\n");
        printf("4. atualizar pedido\n");
        printf("5. deletar pedido\n");
        printf("0. Sair\n");
        printf("=========================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarPedido();3
                break;
            case 2:
                listarPedidos();
                break;
            case 3:
                consultarPedido();
                break;
            case 4:
                atualizarPedido();
                break;
            case 5:
                deletarPedido();
                break;
            case 0:
                printf("finalizando...\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}