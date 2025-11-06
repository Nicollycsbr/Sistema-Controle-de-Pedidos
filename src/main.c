#include<stdio.h>
#include<stdlib.h>
//MENU PRINCIPAL
int menu_principal(){
   int op;
   printf("\n-----MENU PRINCIPAL-----\n");
   printf("(1) Clientes\n");
   printf("(2) Produtos\n");
   printf("(3) Pedidos\n");
   printf("(0) Sair\n");
   printf("------------------------\n");
   printf("Qual area deseja acessar?\n");
   scanf("%d", &op);
   return op;
}

int main()
{
   int op;
   do{
   op=menu_principal();
      switch (op){
      case 1:
         printf("Area de clientes acessada!\n");
         break;

      case 2:
         printf("Area de produtos acessada!\n");
         break;

      case 3:
         printf("Area de pedidos acessada!\n");
         break;

      case 0:
         printf("Encerrando o programa...\n");
         break;

      default:
         printf("Opção inválida!\n");
         break;
      }
   }while(op!=0);
   
   return 0; 
}