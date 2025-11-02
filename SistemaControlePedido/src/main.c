#include "../include/produto.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    int opcao;

    do {
        printf("\n=== MENU DE PRODUTOS ===\n");
        printf("1. Cadastrar produto\n");
        printf("2. Listar produtos\n");
        printf("3. Atualizar produto\n");
        printf("4. Deletar produto\n");
        printf("0. Sair\n");
        printf("========================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
            if (opcao == 1) {
                cadastrarProduto();
                break;
            }
            case 2:
            if (opcao == 2) {
                listarProdutos();
                break;
            }
            case 3:
            if (opcao == 3) {
                atualizarProduto();
                break;
            }
            case 4:
            if (opcao == 4) {
                deletarProduto();
                break;
            }
            case 0:
            if (opcao == 0) {
                printf("\nSaindo do sistema...\n");
                break;
            }
            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}