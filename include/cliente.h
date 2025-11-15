//Definição das structs e funções de cliente
#ifndef CLIENTE_H
#define CLIENTE_H

#define TAM_NOME 100
#define TAM_ENDERECO 200
#define TAM_TELEFONE 20
#define TAM_CPF 15
#define TAM_CNPJ 20
#define TAM_RAZAO 100
#define TAM_EMAIL 100

//Pessoa Física
typedef struct {
    char nome[TAM_NOME];
    char cpf[TAM_CPF];
    char celular[TAM_TELEFONE];
} PessoaFisica;

//Pessoa Jurídica
typedef struct {
    char nome_contato[TAM_NOME];
    char razao_social[TAM_RAZAO];
    char cnpj[TAM_CNPJ];
    char telefone[TAM_TELEFONE];
} PessoaJuridica;

//Cliente
typedef struct {
    int id;
    char endereco[TAM_ENDERECO];
    char telefone[TAM_TELEFONE];
    char email[TAM_EMAIL];
    union {
        PessoaFisica pf;
        PessoaJuridica pj;
    } dados;
} Cliente;

//Funções
void cadastrar_cliente();
void listar_clientes();
void consultar_cliente();
void remover_cliente();
int validar_CPF(const char *cpf);
int validar_CNPJ(const char *cnpj);

#endif
