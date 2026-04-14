TARGET = grafos

ifeq ($(OS),Windows_NT)
    SEP = \\
else
    SEP = /
endif

BUILD_DIR = build
DOTS_DIR = $(BUILD_DIR)$(SEP)dots
ASSETS_DIR = $(BUILD_DIR)$(SEP)assets

CC = gcc
CFLAGS = -Wall -Wextra -g

SRC = grafos.c
OBJ = $(BUILD_DIR)$(SEP)grafos.o
EXEC = $(BUILD_DIR)$(SEP)$(TARGET).exe

all: $(EXEC) run graph

# -------------------------
# Diretórios
# -------------------------
$(BUILD_DIR):
	@if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)

$(DOTS_DIR): | $(BUILD_DIR)
	@if not exist $(DOTS_DIR) mkdir $(DOTS_DIR)

$(ASSETS_DIR): | $(BUILD_DIR)
	@if not exist $(ASSETS_DIR) mkdir $(ASSETS_DIR)

# -------------------------
# Compilação
# -------------------------
$(OBJ): $(SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(SRC) -o $(OBJ)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

# -------------------------
# Execução (gera .dot)
# -------------------------
run: $(EXEC) $(DOTS_DIR)
	./$(EXEC)

# -------------------------
# Conversão (SEM RECURSÃO)
# -------------------------
graph: $(ASSETS_DIR)
	@echo Gerando imagens...
	@$(eval DOTS := $(wildcard $(DOTS_DIR)$(SEP)*.dot))
	@$(eval PNGS := $(patsubst $(DOTS_DIR)$(SEP)%.dot,$(ASSETS_DIR)$(SEP)%.png,$(DOTS)))
	@echo $(DOTS)
	@echo $(PNGS)
	@for %%f in ($(DOTS_DIR)\*.dot) do dot -Tpng "%%f" -o "$(ASSETS_DIR)\%%~nf.png"

# -------------------------
# Limpeza
# -------------------------
clean:
	@if exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR)