#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "interface.h"

//INSERÇÃO CLIENTE
void inserir_cliente(){
    Cliente cliente;
    int tipo;
    printf("Qual você deseja cadastrar?\n");
    printf("(1) Pessoa física\n");
    printf("(2) Pessoa jurídica\n");
    printf("Opção: ");
    scanf("%d", &tipo);
    getchar();

    printf("Defina o ID do cliente: ");
    scanf("%d", &cliente.id);
    getchar();

    printf("Informe o nome: ");
    fgets(cliente.nome, TAM_NOME, stdin);
    cliente.nome[strcspn(cliente.nome,"\n")]=0;

    printf("Informe o endereço: ");
    fgets(cliente.endereco, TAM_ENDERECO, stdin);
    cliente.endereco[strcspn(cliente.endereco,"\n")]=0;

    printf("Informe o telefone: ");
    fgets(cliente.telefone, TAM_TELEFONE, stdin);
    cliente.telefone[strcspn(cliente.telefone,"\n")]=0;

    if (tipo==1){
        printf("Informe o nome completo: ");
        fgets(cliente.dados.pf.nome, TAM_NOME, stdin);
        cliente.dados.pf.nome[strcspn(cliente.dados.pf.nome, "\n")]=0;

        do {
            printf("Informe o CPF (somente números): ");
            fgets(cliente.dados.pf.cpf, TAM_CPF, stdin);
            cliente.dados.pf.cpf[strcspn(cliente.dados.pf.cpf,"\n")]=0;

            if (!validar_CPF(cliente.dados.pf.cpf)) {
                printf("CPF inválido! Tente novamente.\n");
            }
        } while (!validar_CPF(cliente.dados.pf.cpf));

        printf("Informe o celular: ");
        fgets(cliente.dados.pf.celular, TAM_TELEFONE, stdin);
        cliente.dados.pf.celular[strcspn(cliente.dados.pf.celular, "\n")] = 0;

        printf("\nPessoa Física cadastrada com sucesso!\n");

    } else if (tipo == 2) {
        printf("Informe a razão social: ");
        fgets(cliente.dados.pj.razao_social, TAM_RAZAO, stdin);
        cliente.dados.pj.razao_social[strcspn(cliente.dados.pj.razao_social, "\n")] = 0;

        do {
            printf("Informe o CNPJ (somente números): ");
            fgets(cliente.dados.pj.cnpj, TAM_CNPJ, stdin);
            cliente.dados.pj.cnpj[strcspn(cliente.dados.pj.cnpj, "\n")] = 0;

            if (!validar_CNPJ(cliente.dados.pj.cnpj)) {
                printf("CNPJ inválido! Tente novamente.\n");
            }
        } while (!validar_CNPJ(cliente.dados.pj.cnpj));

        printf("\nPessoa Jurídica cadastrada com sucesso!\n");

    } else {
        printf("Opção inválida!\n");
        return;
    }
}
void listar_clientes(){
    printf("\n----- DADOS CADASTRADOS -----\n");
    printf("ID: %d\n", cliente.id);
    printf("Nome: %s\n", cliente.nome);
    printf("Endereço: %s\n", cliente.endereco);
    printf("Telefone: %s\n", cliente.telefone);

    if (tipo == 1) {
        printf("Nome completo: %s\n", cliente.dados.pf.nome);
        printf("CPF: %s\n", cliente.dados.pf.cpf);
        printf("Celular: %s\n", cliente.dados.pf.celular);
    } else {
        printf("Razão Social: %s\n", cliente.dados.pj.razao_social);
        printf("CNPJ: %s\n", cliente.dados.pj.cnpj);
    }
    printf("-----------------------------\n");
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

//VALIDADORES
int validar_CPF(const char *cpf){
    int i, j, digito1, digito2, soma, resto;
    char numeros[12];

    int index = 0;
    for (i=0; cpf[i]!='\0'; i++) {
        if (cpf[i]>='0' && cpf[i]<='9') { 
            numeros[index++]=cpf[i];
          }
    }
    if (strlen(numeros)!=11)
        return 0;

    int iguais=1;
    for (i=1; i<11; i++) {
        if (numeros[i]!=numeros[0]) {
            iguais=0;
            break;
        }
    }
    if (iguais)
        return 0;

    soma=0;
    for (i=0, j=10; i<9; i++, j--)
        soma+=(numeros[i]-'0')*j;

    resto=soma%11;
    digito1=(resto<2)?0:11-resto;

    soma=0;
    for (i=0, j=11; i<10; i++, j--)
        soma+=(numeros[i]-'0')*j;

    resto=soma%11;
    digito2=(resto<2)?0:11-resto;

    if (digito1==(numeros[9]-'0') && digito2==(numeros[10]-'0'))
        return 1;
    else
        return 0;
}

int validar_CNPJ(const char *cnpj){
    int i,j,soma,resto,digito1,digito2;
    char numeros[15];
    int pesos1[12]={5,4,3,2,9,8,7,6,5,4,3,2};
    int pesos2[13]={6,5,4,3,2,9,8,7,6,5,4,3,2};

    int index=0;
    for(i=0;cnpj[i]!='\0';i++){
        if(cnpj[i]>='0'&&cnpj[i]<='9'){
            numeros[index++]=cnpj[i];
        }
    }
    numeros[index]='\0';

    if(strlen(numeros)!=14)
        return 0;

    int iguais=1;
    for(i=1;i<14;i++){
        if(numeros[i]!=numeros[0]){
            iguais=0;
            break;
        }
    }
    if(iguais)
        return 0;

    soma=0;
    for(i=0;i<12;i++)
        soma+=(numeros[i]-'0')*pesos1[i];

    resto=soma%11;
    digito1=(resto<2)?0:11-resto;

    soma=0;
    for(i=0;i<13;i++)
        soma+=(numeros[i]-'0')*pesos2[i];

    resto=soma%11;
    digito2=(resto<2)?0:11-resto;

    if(digito1==(numeros[12]-'0')&&digito2==(numeros[13]-'0'))
        return 1;
    else
        return 0;
}
