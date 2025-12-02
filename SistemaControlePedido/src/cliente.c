#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "cliente.h"
#include "persistencia.h"

//Validar CPF
int validar_CPF(const char *cpf){
    int i, j, digito1, digito2, soma;

    if (strlen(cpf)!=11) return 0;

    int iguais=1;
    for (i=1; i<11; i++) {
        if (cpf[i]!=cpf[0]) { iguais=0; break; }
    }
    if(iguais) return 0;

    soma=0;
    for (i=0, j=10; i<9; i++, j--) soma+=(cpf[i]-'0')*j;

    digito1=(soma*10)%11;
    if(digito1==10) digito1=0;
    if(digito1!=(cpf[9]-'0')) return 0;

    soma=0;
    for (i=0, j=11; i<10; i++, j--) soma+=(cpf[i]-'0')*j;

    digito2=(soma*10)%11;
    if(digito2==10) digito2=0;
    if(digito2!=(cpf[10]-'0')) return 0;

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
void cadastrar_cliente(Cliente clientes[], int *qtd) {
    if (*qtd >= MAX_CLIENTES) {
        mvprintw(LINES-3, 2, "Limite de clientes atingido!");
        getch();
        return;
    }
    clear();
    
    Cliente c;
    int tipo;
    echo();
    curs_set(1);

    mvprintw(2, 2, "Escolha tipo de cliente (1-PF / 2-PJ): ");
    scanw("%d", &tipo);
    if (tipo != 1 && tipo != 2) {
        mvprintw(4, 2, "Tipo invalido!");
        getch();
        noecho();
        curs_set(0);
        return;
    }
    c.tipo = tipo;

    mvprintw(3, 2, "Informe ID: ");
    scanw("%d", &c.id);

    // Verifica duplicidade de ID
    for (int i = 0; i < *qtd; i++) {
        if (clientes[i].id == c.id) {
            mvprintw(5, 2, "ID ja existe!");
            getch();
            noecho();
            curs_set(0);
            return;
        }
    }

    char buffer[200];
    if (c.tipo == TIPO_PF) {
        mvprintw(5, 2, "Nome: ");
        getnstr(c.dados.pf.nome, TAM_NOME - 1);

        do {
            mvprintw(6, 2, "CPF (apenas numeros): ");
            getnstr(buffer, sizeof(buffer) - 1);
            if (!validar_CPF(buffer))
                mvprintw(7, 2, "CPF invalido! Tente novamente.");
            else break;
        } while (1);
        strcpy(c.dados.pf.cpf, buffer);

        mvprintw(8, 2, "Celular: ");
        getnstr(c.dados.pf.celular, TAM_TELEFONE - 1);

    } else {
        mvprintw(5, 2, "Razao Social: ");
        getnstr(c.dados.pj.razao_social, TAM_RAZAO - 1);

        do {
            mvprintw(6, 2, "CNPJ (apenas numeros): ");
            getnstr(buffer, sizeof(buffer) - 1);
            if (!validar_CNPJ(buffer))
                mvprintw(7, 2, "CNPJ invalido! Tente novamente.");
            else break;
        } while (1);
        strcpy(c.dados.pj.cnpj, buffer);

        mvprintw(8, 2, "Nome contato: ");
        getnstr(c.dados.pj.nome_contato, TAM_NOME - 1);
    }

    mvprintw(9, 2, "Endereco: ");
    getnstr(c.endereco, TAM_ENDERECO - 1);

    mvprintw(11, 2, "Email: ");
    getnstr(c.email, TAM_EMAIL - 1);

    clientes[*qtd] = c;
    (*qtd)++;

    clear();
    mvprintw(13, 2, "Cliente cadastrado com sucesso!");
    refresh();
    noecho();
    curs_set(0);
    getch();
}


//Consultar cliente
void consultar_cliente(Cliente clientes[], int qtd) {
    clear();
    echo();
    curs_set(1);

    int id;
    mvprintw(2,2,"Informe ID do cliente: ");
    refresh();
    scanw("%d", &id);

    clear();
    int encontrado = 0;
    int linha = 4;

    for(int i = 0; i < qtd; i++){
        if(clientes[i].id == id){
            Cliente *c = &clientes[i];
            mvprintw(2,2,"ID: %d | Tipo: %s", c->id, c->tipo == TIPO_PF ? "PF" : "PJ");

            if(c->tipo == TIPO_PF){
                mvprintw(linha++,4,"Nome: %s", c->dados.pf.nome);
                mvprintw(linha++,4,"CPF: %s", c->dados.pf.cpf);
                mvprintw(linha++,4,"Celular: %s", c->dados.pf.celular);
            } else {
                mvprintw(linha++,4,"Razao Social: %s", c->dados.pj.razao_social);
                mvprintw(linha++,4,"CNPJ: %s", c->dados.pj.cnpj);
                mvprintw(linha++,4,"Contato: %s", c->dados.pj.nome_contato);
            }

            mvprintw(linha++,4,"Endereco: %s", c->endereco);
            mvprintw(linha++,4,"Telefone: %s", c->telefone);
            mvprintw(linha++,4,"Email: %s", c->email);

            encontrado = 1;
            break;
        }
    }

    if(!encontrado){
        mvprintw(4,2,"Cliente nao encontrado!");
    }

    noecho();
    curs_set(0);
    mvprintw(LINES-2,2,"Pressione qualquer tecla para voltar...");
    getch();
}


//Remover cliente
void remover_cliente(Cliente clientes[], int *qtd){
    clear();
    echo();
    curs_set(1);

    int id;
    mvprintw(2,2,"Informe ID do cliente a remover: ");
    refresh();
    scanw("%d", &id);

    int i, encontrado = 0;
    for(i = 0; i < *qtd; i++){
        if(clientes[i].id == id){
            encontrado = 1;
            break;
        }
    }

    if(!encontrado){
        mvprintw(4,2,"Cliente nao encontrado!");
        noecho();
        curs_set(0);
        mvprintw(LINES-2,2,"Pressione qualquer tecla para voltar...");
        getch();
        return;
    }

    mvprintw(4,2,"Tem certeza que deseja remover o cliente? (S/N): ");
    refresh();

    char resp;
    scanw(" %c", &resp);

    if(resp == 'S' || resp == 's'){
        for(int j = i; j < *qtd - 1; j++){
            clientes[j] = clientes[j + 1];
        }

        (*qtd)--;

        salvar_clientes(CLIENTES_CSV, clientes, *qtd);

        mvprintw(6,2,"Cliente removido com sucesso!");
    } else {
        mvprintw(6,2,"Operacao cancelada.");
    }

    noecho();
    curs_set(0);
    mvprintw(LINES-2,2,"Pressione qualquer tecla para voltar...");
    getch();
}      

//Listar clientes
void listar_clientes(Cliente clientes[], int qtd){
    clear();
    mvprintw(1,2,"----- LISTA DE CLIENTES -----");
    int linha=3;

    for(int i=0;i<qtd;i++){
        Cliente *c=&clientes[i];
        mvprintw(linha++,2,"ID: %d | Tipo: %s", c->id, c->tipo==TIPO_PF?"PF":"PJ");
        if(c->tipo==TIPO_PF){
            mvprintw(linha++,4,"Nome: %s", c->dados.pf.nome);
            mvprintw(linha++,4,"CPF: %s", c->dados.pf.cpf);
            mvprintw(linha++,4,"Celular: %s", c->dados.pf.celular);
        }else{
            mvprintw(linha++,4,"Razao Social: %s", c->dados.pj.razao_social);
            mvprintw(linha++,4,"CNPJ: %s", c->dados.pj.cnpj);
            mvprintw(linha++,4,"Contato: %s", c->dados.pj.nome_contato);
        }
        mvprintw(linha++,4,"Endereco: %s", c->endereco);
        mvprintw(linha++,4,"Telefone: %s", c->telefone);
        mvprintw(linha++,4,"Email: %s", c->email);
        mvprintw(linha++,2,"--------------------------------");

        if(linha>=LINES-4){
            mvprintw(LINES-2,2,"Pressione qualquer tecla para continuar...");
            getch();
            clear();
            mvprintw(1,2,"-----LISTA DE CLIENTES-----");
            linha=3;
        }
    }

    if(qtd==0) mvprintw(3,2,"Nenhum cliente cadastrado!");
    mvprintw(LINES-2,2,"Pressione qualquer tecla para voltar...");
    getch();
}
