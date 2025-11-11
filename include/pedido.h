#ifndef PEDIDO_H
#define PEDIDO_H

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
