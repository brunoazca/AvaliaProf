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
	Disciplina_Universidade/Disciplina_Universidade.c \
	tests/test_utils.c \
	tests/test_runner.c \
	Aluno/aluno_test.c \
	Universidade/universidade_test.c \
	Disciplina/disciplina_test.c \
	Professor/professor_test.c \
	Avaliacao/avaliacao_test.c \
	Aluno_Universidade/aluno_universidade_test.c \
	Professor_Disciplina/professor_disciplina_test.c \
	Disciplina_Universidade/disciplina_universidade_test.c

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

