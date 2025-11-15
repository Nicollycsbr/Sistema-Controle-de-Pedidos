#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"

//Validar CPF
int validar_CPF(const char *cpf){
    int i, j, digito1, digito2, soma;

    if (strlen(cpf)!=11)
        return 0;

    int iguais=1;
    for (i=1; i<11; i++) {
        if (cpf[i]!=cpf[0]) {
            iguais=0;
            break;
        }
    }
    if(iguais) return 0;

    soma=0;
    for (i=0, j=10; i<9; i++, j--)
        soma+=(cpf[i]-'0')*j;

    digito1=(soma*10)%11;
    if (digito1==10) digito1=0;

    if (digito1!=(cpf[9]-'0'))
        return 0;

    soma=0;
    for (i=0, j=11; i<10; i++, j--)
        soma+=(cpf[i]-'0')*j;

    digito2=(soma*10)%11;
    if (digito2==10) digito2=0;

    if (digito2!=(cpf[10]-'0'))
        return 0;

    return 1;
}

//Validar CNPJ
int validar_CNPJ(const char *cnpj){
    int i,soma,resto,d1,d2;
    int p1[12]={5,4,3,2,9,8,7,6,5,4,3,2};
    int p2[13]={6,5,4,3,2,9,8,7,6,5,4,3,2};

    if(strlen(cnpj)!=14) return 0;

    int iguais=1;
    for(i=1;i<14;i++){
        if(cnpj[i]!=cnpj[0]){iguais=0;break;}
    }
    if(iguais) return 0;

    soma=0;
    for(i=0;i<12;i++) soma+=(cnpj[i]-'0')*p1[i];
    resto=soma%11;
    d1=(resto<2)?0:(11-resto);
    if(d1!=(cnpj[12]-'0')) return 0;

    soma=0;
    for(i=0;i<13;i++) soma+=(cnpj[i]-'0')*p2[i];
    resto=soma%11;
    d2=(resto<2)?0:(11-resto);
    if(d2!=(cnpj[13]-'0')) return 0;

    return 1;
}

//Cadastrar clientes
void cadastrar_cliente(){
    Cliente cliente;
    int tipo, existe=0;
    char linha[500];

    printf("Qual você deseja cadastrar?\n");
    printf("(1) Pessoa Física\n");
    printf("(2) Pessoa Jurídica\n");
    printf("Opção: ");
    scanf("%d",&tipo);
    getchar();

    if(tipo!=1 && tipo!=2){
        printf("Opção inválida!\n");
        return;
    }

    do{
        existe=0;
        printf("Defina o seu ID de cliente: ");
        scanf("%d",&cliente.id);
        getchar();

        FILE *Arqcliente=fopen("clientes.csv","r");

        if(Arqcliente==NULL){
            printf("Erro para abrir arquivo!\n");
            return;
        }else{
            while(fgets(linha,sizeof(linha),Arqcliente)){
                int id_existente;
                sscanf(linha,"%d;",&id_existente);
                if(id_existente==cliente.id){
                    existe=1;
                    printf("Código já existente! Digite outro.\n");
                    break;
                }
            }
        }
        fclose(Arqcliente);
    }while(existe);

    char numero_cadastro[20];
    int valido=0, duplicado=0;

    do{
        duplicado=0;

        if(tipo==1)
            printf("Insira seu CPF (somente números):\n");
        else
            printf("Insira o CNPJ (somente números):\n");

        fgets(numero_cadastro,sizeof(numero_cadastro),stdin);

        int tamanho=strlen(numero_cadastro);
        if(numero_cadastro[tamanho-1]=='\n')
            numero_cadastro[tamanho-1]='\0';

        if(tipo==1)
            valido=validar_CPF(numero_cadastro);
        else
            valido=validar_CNPJ(numero_cadastro);

        if(!valido)
            printf("Número inválido! Digite novamente.\n");

    }while(!valido);

    FILE *Arqcliente=fopen("clientes.csv","r");

    if(Arqcliente==NULL){
        printf("Erro para abrir arquivo!\n");
        return;
    }else{
        while(fgets(linha,sizeof(linha),Arqcliente)){
            char cpfCnpj_existente[20];
            sscanf(linha,"%*d;%*d;%*[^;];%*[^;];%[^;];",cpfCnpj_existente);

            if(strcmp(cpfCnpj_existente,numero_cadastro)==0){
                duplicado=1;
                printf("Este CPF/CNPJ já está cadastrado!\n");
                break;
            }
        }
        fclose(Arqcliente);
    }
    
    if(tipo==1)
        strcpy(cliente.dados.pf.cpf, numero_cadastro);
    else
        strcpy(cliente.dados.pj.cnpj, numero_cadastro);
    
    if (tipo == 1) {
        printf("Informe seu nome completo: ");
        fgets(cliente.dados.pf.nome, TAM_NOME, stdin);
        cliente.dados.pf.nome[strcspn(cliente.dados.pf.nome, "\n")] = 0;

        printf("Informe seu celular: ");
        fgets(cliente.dados.pf.celular, TAM_TELEFONE, stdin);
        cliente.dados.pf.celular[strcspn(cliente.dados.pf.celular, "\n")] = 0;
        
        printf("Informe seu endereço completo: ");
        fgets(cliente.endereco, TAM_ENDERECO, stdin);
        cliente.endereco[strcspn(cliente.endereco, "\n")] = 0;
    
        printf("Informe seu telefone: ");
        fgets(cliente.telefone, TAM_TELEFONE, stdin);
        cliente.telefone[strcspn(cliente.telefone, "\n")] = 0;
    
        printf("Informe seu email: ");
        fgets(cliente.email, TAM_EMAIL, stdin);
        cliente.email[strcspn(cliente.email, "\n")] = 0;
        
    } else {
        printf("Informe a razão social: ");
        fgets(cliente.dados.pj.razao_social, TAM_RAZAO, stdin);
        cliente.dados.pj.razao_social[strcspn(cliente.dados.pj.razao_social, "\n")] = 0;

        printf("Informe o nome para contato: ");
        fgets(cliente.dados.pj.nome_contato, TAM_NOME, stdin);
        cliente.dados.pj.nome_contato[strcspn(cliente.dados.pj.nome_contato, "\n")] = 0;
        
        printf("Informe o endereço completo: ");
        fgets(cliente.endereco, TAM_ENDERECO, stdin);
        cliente.endereco[strcspn(cliente.endereco, "\n")] = 0;
    
        printf("Informe o telefone: ");
        fgets(cliente.telefone, TAM_TELEFONE, stdin);
        cliente.telefone[strcspn(cliente.telefone, "\n")] = 0;
    
        printf("Informe o email: ");
        fgets(cliente.email, TAM_EMAIL, stdin);
        cliente.email[strcspn(cliente.email, "\n")] = 0;
    }
    
    Arqcliente=fopen("clientes.csv", "a");
    if (Arqcliente==NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
        
    fprintf(Arqcliente, "%d;%d;%s;%s;%s;%s;%s;%s;%s\n",
        cliente.id,
        tipo,
        (tipo==1)?cliente.dados.pf.nome:cliente.dados.pj.razao_social,
        (tipo==1)?cliente.dados.pf.cpf:cliente.dados.pj.cnpj,
        (tipo==1)?cliente.dados.pf.celular:cliente.dados.pj.nome_contato,
        cliente.endereco,
        cliente.telefone,
        cliente.email,
        (tipo==2)?cliente.dados.pj.telefone:"");

    fclose(Arqcliente);

    printf("Cliente cadastrado com sucesso!\n");
}

//Consultar clientes
void consultar_cliente() {
    FILE *Arqcliente = fopen("clientes.csv", "r");
    if (Arqcliente==NULL) {
        printf("Nenhum cliente cadastrado!\n");
        return;
    }

    int id_busca, encontrado = 0;
    char linha[500];

    printf("Informe o ID do cliente para consulta: ");
    scanf("%d", &id_busca);
    getchar();

    while (fgets(linha, sizeof(linha), Arqcliente)) {
        int id, tipo;
        char nome[100], cpfCnpj[20], contato[100], endereco[200], telefone[20], email[100], celular[20], razao[100];

        sscanf(linha, "%d;%d;%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^\n]",
               &id, &tipo, nome, cpfCnpj, contato, endereco, telefone, email, celular, razao);

        if (id==id_busca) {
            encontrado=1;
            printf("\n----- DADOS DO CLIENTE -----\n");
            printf("ID: %d\n", id);
            printf("Tipo: %s\n", (tipo==1) ? "Pessoa Física":"Pessoa Jurídica");
            if (tipo==1) {
                printf("Nome: %s\nCPF: %s\nCelular: %s\n", nome, cpfCnpj, celular);
            } else {
                printf("Razão Social: %s\nCNPJ: %s\nContato: %s\n", nome, cpfCnpj, contato);
            }
            printf("Endereço: %s\nTelefone: %s\nEmail: %s\n", endereco, telefone, email);
            printf("----------------------------\n");
            break;
        }
    }

    fclose(Arqcliente);

    if (!encontrado)
        printf("Cliente não encontrado.\n");
}

//Remover clientes
void remover_cliente() {
    FILE *Arqcliente=fopen("clientes.csv", "r");
    if (Arqcliente==NULL) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    FILE *temp = fopen("temp.csv", "w");
    if (temp==NULL) {
        printf("Erro ao criar arquivo temporário.\n");
        fclose(Arqcliente);
        return;
    }

    int remover_id, encontrado=0, confirmar;
    char linha[500];

    printf("Informe o ID do cliente a ser removido: ");
    scanf("%d", &remover_id);
    getchar();

    while (fgets(linha, sizeof(linha), Arqcliente)) {
        int id;
        sscanf(linha, "%d;", &id);

        if (id==remover_id) {
            encontrado=1;
            printf("Deseja realmente remover o cliente %d? (1 - Sim / 0 - Não): ", remover_id);
            scanf("%d", &confirmar);
            getchar();

            if (confirmar==1) {
                printf("Cliente removido com sucesso.\n");
                continue;
            } else {
                printf("Remoção cancelada.\n");
                fputs(linha, temp);
            }
        } else {
            fputs(linha, temp);
        }
    }

    fclose(Arqcliente);
    fclose(temp);

    remove("clientes.csv");
    rename("temp.csv", "clientes.csv");

    if (!encontrado)
        printf("Cliente não encontrado.\n");
}

//Listar clientes
void listar_clientes() {
    FILE *Arqcliente=fopen("clientes.csv", "r");
    if (Arqcliente==NULL) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    char linha[500];
    int contador=0;

    printf("\n-----LISTA DE CLIENTES-----\n");

    while (fgets(linha, sizeof(linha), Arqcliente)) {
        int id, tipo;
        char nome[100], cpfCnpj[20], contato[100], endereco[200], telefone[20], email[100], celular[20], razao[100];

        sscanf(linha, "%d;%d;%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^\n]",
               &id, &tipo, nome, cpfCnpj, contato, endereco, telefone, email, celular, razao);

        printf("\nID: %d\n", id);
        printf("Tipo: %s\n", (tipo==1) ? "Pessoa Física":"Pessoa Jurídica");
        if (tipo==1) {
            printf("Nome: %s\nCPF: %s\nCelular: %s\n", nome, cpfCnpj, celular);
        } else {
            printf("Razão Social: %s\nCNPJ: %s\nContato: %s\n", nome, cpfCnpj, contato);
        }
        printf("Endereço: %s\nTelefone: %s\nEmail: %s\n", endereco, telefone, email);
        printf("-----------------------------\n");
        contador++;
    }

    if (contador==0)
        printf("Nenhum cliente cadastrado.\n");

    fclose(Arqcliente);
}