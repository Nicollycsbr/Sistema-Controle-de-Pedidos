#include <stdio.h>
#include "../include/interface.h"
#include "../include/cliente.h"

void menu_cliente(){
   int op;
   do{
   printf("\n-----MENU CLIENTE-----\n");
   printf("(1) Cadastrar novo cliente\n");
   printf("(2) Remover cliente cadastrado\n");
   printf("(3) Consultar cliente cadastrado\n");
   printf("(4) Editar cliente cadastrado\n")
   printf("(5) Listar clientes cadastrados\n");
   printf("(0) Sair\n");
   printf("------------------------\n");
   printf("Opção:\n");
   scanf("%d", &op);
   getchar();

   switch (op) {
            case 1:
                inserir_cliente();
                break;

            case 2:
                break;

            case 3:
                break;

            case 4:
                break;

            case 5:
                break;

            case 0:
                printf("Saindo do menu de clientes...\n");
                break;

            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
    } while (op != 0);
}