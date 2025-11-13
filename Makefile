CC := gcc
CFLAGS := -Wall -Wextra -std=c11

SRC := \
	principal.c \
	Aluno/aluno.c \
	Universidade/Universidade.c \
	Professor/professor.c \
	Disciplina/disciplina.c \
	Avaliacao/avaliacao.c \
	Aluno_Universidade/aluno_Universidade.c \
	Professor_Disciplina/professor_disciplina.c \
	Disciplina_Universidade/Disciplina_Universidade.c

OBJ := $(SRC:.c=.o)

BIN := programa

.PHONY: all clean run

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(BIN)
	./$(BIN)

clean:
	rm -f $(OBJ) $(BIN)

