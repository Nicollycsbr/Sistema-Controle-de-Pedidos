//Definição das structs e funções de cliente
#ifndef CLIENTE_H
#define CLIENTE_H

#define TAM_NOME       100
#define TAM_RAZAO      120
#define TAM_CPF        12  
#define TAM_CNPJ       15    
#define TAM_TELEFONE   20
#define TAM_ENDERECO   150
#define TAM_EMAIL      120

#define MAX_CLIENTES   1000

typedef enum {
    TIPO_PF = 1,
    TIPO_PJ = 2
} TipoCliente;

typedef struct {
    char nome[TAM_NOME];
    char cpf[TAM_CPF];
    char celular[TAM_TELEFONE];
} PessoaFisica;

typedef struct {
    char razao_social[TAM_RAZAO];
    char cnpj[TAM_CNPJ];
    char nome_contato[TAM_NOME];
} PessoaJuridica;

typedef struct {
    int id;
    TipoCliente tipo;
    union {
        PessoaFisica pf;
        PessoaJuridica pj;
    } dados;

    char endereco[TAM_ENDERECO];
    char telefone[TAM_TELEFONE];
    char email[TAM_EMAIL];
} Cliente;


//Funções
void cadastrar_cliente(Cliente clientes[], int *qtd);void listar_clientes(Cliente clientes[], int qtd);
void consultar_cliente(Cliente clientes[], int qtd);
void remover_cliente(Cliente clientes[], int *qtd);
int validar_CPF(const char *cpf);
int validar_CNPJ(const char *cnpj);

#endif
