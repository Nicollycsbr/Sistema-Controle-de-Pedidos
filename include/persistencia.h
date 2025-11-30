#ifndef PERSISTENCIA_H
#define PERSISTENCIA_H

#include "cliente.h"
#define CLIENTES_CSV "data/Clientes.csv"

int carregar_clientes(const char *filepath, Cliente clientes[], int *qtd);
int salvar_clientes(const char *filepath, Cliente clientes[], int qtd);

#endif 
