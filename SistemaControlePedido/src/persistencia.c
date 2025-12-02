#define _GNU_SOURCE     // necessário para strtok_r no Linux
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "persistencia.h"
#include "cliente.h"

static void trim_newline(char *s) {
    size_t l = strlen(s);
    if (l > 0 && s[l - 1] == '\n') 
        s[l - 1] = '\0';
}

int carregar_clientes(const char *filepath, Cliente clientes[], int *qtd) {
    FILE *f = fopen(filepath, "r");
    if (!f) {
        *qtd = 0;
        return 0;
    }

    char linha[1024];
    int count = 0;

    while (fgets(linha, sizeof(linha), f) && count < MAX_CLIENTES) {
        trim_newline(linha);

        char *saveptr = NULL;
        char *token = strtok_r(linha, ";", &saveptr);

        int field = 0;
        Cliente c;
        memset(&c, 0, sizeof(Cliente));

        while (token) {
            switch (field) {
                case 0: 
                    c.id = atoi(token); 
                    break;

                case 1: 
                    c.tipo = (TipoCliente) atoi(token); 
                    break;

                case 2:
                    if (c.tipo == TIPO_PF)
                        strncpy(c.dados.pf.nome, token, TAM_NOME - 1);
                    else
                        strncpy(c.dados.pj.razao_social, token, TAM_RAZAO - 1);
                    break;

                case 3:
                    if (c.tipo == TIPO_PF)
                        strncpy(c.dados.pf.cpf, token, TAM_CPF - 1);
                    else
                        strncpy(c.dados.pj.cnpj, token, TAM_CNPJ - 1);
                    break;

                case 4:
                    if (c.tipo == TIPO_PF)
                        strncpy(c.dados.pf.celular, token, TAM_TELEFONE - 1);
                    else
                        strncpy(c.dados.pj.nome_contato, token, TAM_NOME - 1);
                    break;

                case 5:
                    strncpy(c.endereco, token, TAM_ENDERECO - 1);
                    break;

                case 6:
                    strncpy(c.telefone, token, TAM_TELEFONE - 1);
                    break;

                case 7:
                    strncpy(c.email, token, TAM_EMAIL - 1);
                    break;
            }

            token = strtok_r(NULL, ";", &saveptr);
            field++;
        }

        if (c.tipo != TIPO_PF && c.tipo != TIPO_PJ)
            continue;

        clientes[count++] = c;
    }

    fclose(f);
    *qtd = count;
    return 1;
}

int salvar_clientes(const char *filepath, Cliente clientes[], int qtd) {
    FILE *f = fopen(filepath, "w");
    if (!f) return 0;

    for (int i = 0; i < qtd; i++) {
        Cliente *c = &clientes[i];

        if (c->tipo == TIPO_PF) {
            fprintf(f, "%d;%d;%s;%s;%s;%s;%s;%s\n",
                c->id,
                c->tipo,
                c->dados.pf.nome,
                c->dados.pf.cpf,
                c->dados.pf.celular,
                c->endereco,
                c->telefone,
                c->email
            );
        } else {
            fprintf(f, "%d;%d;%s;%s;%s;%s;%s;%s\n",
                c->id,
                c->tipo,
                c->dados.pj.razao_social,
                c->dados.pj.cnpj,
                c->dados.pj.nome_contato,
                c->endereco,
                c->telefone,
                c->email
            );
        }
    }

    fclose(f);
    return 1;
}
