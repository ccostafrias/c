# compilador
CC = gcc
# flags de compilação (ativam warnings e padrão C)
CFLAGS = -Wall -Wextra -std=c11

# Diretório dos objetos
OBJDIR = build

# nome do executável
TARGET = main

# pega todos os arquivos .c no diretório atual
SRC = $(wildcard *.c)

# itera sobre SRC e transforma arquivo *.c em build/*.o
OBJ = $(SRC:%.c=$(OBJDIR)/%.o)

# regra padrão: compilar tudo
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(OBJDIR)/$(TARGET)

# Regra para compilar cada .c em .o (colocando os .o dentro de build/)
$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Cria a pasta build se não existir
$(OBJDIR):
	mkdir $(OBJDIR)