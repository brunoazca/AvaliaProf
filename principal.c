#include <stdio.h>
#include <stdbool.h>   // necessário para usar true/false
#include <string.h>
#include <ctype.h>
#include "Aluno/aluno.h"

int main(void) {
    atexit(salvarJSON);   // salva os dados ao finalizar o programa
    carregarAlunos();      // carrega dados existentes no início

    printf("Iniciando Programa!\n");

    while (true) {
        char tipo[50];
        printf("\nDigite o que pretende fazer \nExemplos: exit, adda, dela, login, reada \n> ");
        scanf(" %49s", tipo);

        // transforma em minúsculo
        for (int i = 0; tipo[i]; i++) {
            tipo[i] = tolower((unsigned char) tipo[i]);
        }

        if (strcmp(tipo, "exit") == 0) {
            printf("Finalizando...\n");
            break;

        } else if (strcmp(tipo, "adda") == 0) {
            printf("CPF: ");
            scanf(" %99[^\n]", tipoAluno.cpf);

            printf("Nome: ");
            scanf(" %99[^\n]", tipoAluno.nome);

            printf("Email: ");
            scanf(" %99[^\n]", tipoAluno.email);

            printf("Senha: ");
            scanf(" %99[^\n]", tipoAluno.senha);

            printf("Curso: ");
            scanf(" %99[^\n]", tipoAluno.curso);

            printf("Universidade: ");
            scanf(" %99[^\n]", tipoAluno.universidade);

            int status = registrar(&tipoAluno);
            switch (status) {
                case 0:  printf("\nAluno cadastrado com sucesso!\n\n"); break;
                case 1:  printf("\nFalha ao registrar: já existe um aluno com este CPF.\n\n"); break;
                case 2:  printf("\nParâmetro inválido.\n\n"); break;
                case 99: printf("\nCancelamento por exceção.\n\n"); break;
                default: printf("\nErro desconhecido ao registrar.\n\n");
            }

        } else if (strcmp(tipo, "dela") == 0) {
            char cpf[100];
            printf("Digite o CPF do aluno que deseja remover: ");
            scanf(" %99[^\n]", cpf);

            int res = delete_Aluno(cpf);
            switch (res) {
                case 0:  printf("Aluno removido com sucesso!\n"); break;
                case 1:  printf("Falha ao deletar aluno: CPF não encontrado ou lista vazia.\n"); break;
                case 2:  printf("Parâmetro inválido.\n"); break;
                case 99: printf("Cancelamento por exceção.\n"); break;
                default: printf("Erro desconhecido.\n");
            }

        } else if (strcmp(tipo, "login") == 0) {
            char email[100];
            char senha[100];

            printf("Digite seu email: ");
            scanf(" %99[^\n]", email);

            printf("Digite sua senha: ");
            scanf(" %99[^\n]", senha);

            int status = login(email, senha);
            switch (status) {
                case 0:  printf("Login bem-sucedido!\n\n"); break;
                case 1:  printf("Falha no login: credenciais inválidas.\n\n"); break;
                case 2:  printf("Parâmetro inválido.\n\n"); break;
                case 99: printf("Cancelamento por exceção.\n\n"); break;
                default: printf("Erro desconhecido.\n\n");
            }

        } else if (strcmp(tipo, "reada") == 0) {
            char cpf[100];
            tpAluno alunoLido;

            printf("Digite o CPF do aluno a buscar: ");
            scanf(" %99[^\n]", cpf);

            int status = read_aluno(cpf, &alunoLido);
            switch (status) {
                case 0:
                    printf("\nAluno encontrado:\n");
                    printf("Nome: %s\n", alunoLido.nome);
                    printf("CPF: %s\n", alunoLido.cpf);
                    printf("Email: %s\n", alunoLido.email);
                    printf("Curso: %s\n", alunoLido.curso);
                    printf("Universidade: %s\n", alunoLido.universidade);
                    break;
                case 1:  printf("\nAluno não encontrado.\n"); break;
                case 2:  printf("\nParâmetro inválido.\n"); break;
                case 99: printf("\nCancelamento por exceção.\n"); break;
                default: printf("\nErro desconhecido.\n");
            }

        } else {
            printf("Não existe este comando, tente novamente!\n");
        }
    }

    return 0;
}
