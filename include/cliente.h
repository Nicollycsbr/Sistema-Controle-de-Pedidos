#ifndef CLIENTE.H
#define CLIENTE.H

typedef struct{
    int id;
    char nome[100];
    char endereço[200];
    int telefone;
    char email[200];
    char tipo[10];//FÍSICA OU JURÍDICA
    int cpfcnpj;
}Cliente;

void inserir_cliente();
void listar_clientes();
void remover_cliente();
void consultar_cliente();
void carregar_clientesCSV();
void salvar_clientesCSV();

#endif