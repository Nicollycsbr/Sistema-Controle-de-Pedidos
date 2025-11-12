#nome do executável 
EXEC = build/cliente

#compilador 
CC = gcc

#diretórios 
SRC_DIR = src 
INC_DIR = include
BUILD_DIR = build 

# Arquivos-fonte e cabeçalhos 
SRC = $(SRC_DIR)/main.c $(SRC_DIR)/cliente.c
INCLUDES = -I$(INC_DIR)

#Flags de compilação 
CFLAGS = -Wall -Wextra -std=c11

#Regra padrão 
$(EXEC): $(SRC)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(SRC) $(INCLUDES) $(CFLAGS) -o $(EXEC)
	@echo "Compilação concluída! Executável gerado em $(EXEC)"

#Rodar o programa 
run: $(EXEC)
	./$(EXEC)

#Limpar arquivos compilados 
clean:
	rm -rf $(BUILD_DIR)
	@echo "Diretório 'build' limpo!" 

CFLAGS = -Iinclude
LDFLAGS = -lncurses

SRC = src/main.c src/interface.c src/cliente.c
OBJ = $(SRC:.c=.o)
EXEC = sistema

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LDFLAGS)

clean:
	rm -f $(OBJ) $(EXEC)
