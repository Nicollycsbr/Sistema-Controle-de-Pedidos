# Nome do executável 
EXEC = build/cliente

# Compilador
CC = gcc

# Diretórios
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

# Arquivos-fonte (todos .c do src)
SRC = $(SRC_DIR)/main.c $(SRC_DIR)/cliente.c $(SRC_DIR)/interface.c $(SRC_DIR)/persistencia.c

# Flags de compilação
CFLAGS = -Wall -Wextra -std=c11 -I$(INC_DIR)

# Flags de biblioteca
LDFLAGS = -lncurses

# Regra padrão (gera o executável)
$(EXEC): $(SRC)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(SRC) $(CFLAGS) -o $(EXEC) $(LDFLAGS)
	@echo "Compilação concluída! Executável gerado em $(EXEC)"

# Rodar o programa
run: $(EXEC)
	./$(EXEC)

# Limpar arquivos compilados
clean:
	rm -rf $(BUILD_DIR)
	@echo "Diretório 'build' limpo!"
