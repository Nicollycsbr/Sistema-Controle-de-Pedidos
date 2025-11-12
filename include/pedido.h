#ifndef PEDIDO_H
#define PEDIDO_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct {
    int id;
    int clienteId;
    char data[11];
    float total;
} Pedido;

typedef struct {
    int pedidoId;
    int produtoId;
    int quantidade;
    float subtotal;
} ItemPedido;

void cadastrarPedido();
void listarPedidos();
void consultarPedido();
void atualizarPedido();
void deletarPedido();

#endif
