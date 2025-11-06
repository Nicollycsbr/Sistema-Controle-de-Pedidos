#include <stdio.h>
#include <stdlib.h>

menu_cliente(){
   int op;
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
}

void inserir_cliente(){
    int tipo;
    printf("Qual você deseja cadastrar?\n");
    printf("(1) Pessoa física\n");
    printf("(2) Pessoa jurídica\n");
    scanf("%d", &tipo);
    if (tipo==1){

    }else if(tipo==2){

    }
}
void listar_clientes(){

}
void editar_cliente(){

}
void consultar_cliente(){

}
void remover_cliente(){

}
void carregar_clientesCSV(){

}
void salvar_clientesCSV(){

}
int validar_CPF(const char *cpf){

}
int validar_CNPJ(const char *cnpj){

}