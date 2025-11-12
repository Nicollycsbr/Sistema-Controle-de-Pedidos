# Nome do executável
EXEC = build/produto

# Compilador
CC = gcc

# Diretórios
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

# Arquivos-fonte e cabeçalhos
SRC = $(SRC_DIR)/main.c $(SRC_DIR)/produto.c
INCLUDES = -I$(INC_DIR)

# Flags de compilação
CFLAGS = -Wall -Wextra -std=c11

# Regra padrão (gera o executável)
$(EXEC): $(SRC)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(SRC) $(INCLUDES) $(CFLAGS) -o $(EXEC)
	@echo "✅ Compilação concluída! Executável gerado em $(EXEC)"

# Rodar o programa
run: $(EXEC)
	./$(EXEC)

# Limpar arquivos compilados
clean:
	rm -rf $(BUILD_DIR)
	@echo "🧹 Diretório 'build' limpo!"