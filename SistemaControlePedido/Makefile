EXEC = build/sistema

CC = gcc

SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

SRC = \
$(SRC_DIR)/main.c \
$(SRC_DIR)/ui.c \
$(SRC_DIR)/produto.c \
$(SRC_DIR)/cliente.c \
$(SRC_DIR)/interface.c \
$(SRC_DIR)/persistencia.c

INCLUDES = -I$(INC_DIR)

CFLAGS = -Wall -Wextra -std=c11
LIBS = -lncurses

$(EXEC): $(SRC)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(SRC) $(INCLUDES) $(CFLAGS) $(LIBS) -o $(EXEC)
	@echo "✅ Sistema compilado com sucesso!"

run: $(EXEC)
	./$(EXEC)

clean:
	rm -rf $(BUILD_DIR)
	@echo "🧹 Build limpo!"