#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <strings.h>

#include "Aluno/aluno.h"
#include "Professor/professor.h"
#include "Universidade/universidade.h"
#include "Disciplina/disciplina.h"
#include "Avaliacao/avaliacao.h"
#include "Aluno_Universidade/aluno_universidade.h"
#include "Professor_Disciplina/professor_disciplina.h"
#include "Disciplina_Universidade/disciplina_universidade.h"
#include "tests/test_runner.h"

static void lerLinha(const char *mensagem, char *dest, size_t tamanho);
static void imprimirStatusGenerico(const char *acao, int status);
static void menuAluno(bool *alunoLogado, tpAluno *alunoSessao);
static void menuProfessor(void);
static void menuUniversidade(void);
static void menuDisciplina(void);
static void menuAvaliacao(bool alunoLogado, tpAluno *alunoSessao);
static void menuRelacionamentos(void);
static void menuAlunoUniversidade(void);
static void menuProfessorDisciplina(void);
static void menuDisciplinaUniversidade(void);

int main(void) {
    atexit(salvarJSON);
    carregarAlunos();

    bool executando = true;
    bool alunoLogado = false;
    tpAluno alunoSessao;
    memset(&alunoSessao, 0, sizeof(tpAluno));

    printf("=== Sistema de Gestão Acadêmica ===\n");

    while (executando) {
        char escolha[32];

        printf("\nMódulos disponíveis:\n");
        printf("1 - Aluno\n");
        printf("2 - Professor\n");
        printf("3 - Universidade\n");
        printf("4 - Disciplina\n");
        printf("5 - Avaliação\n");
        printf("6 - Relacionamentos\n");
        printf("7 - Testes automatizados\n");
        printf("0 - Sair\n");
        if (alunoLogado) {
            printf("\nAluno logado: %s\n", alunoSessao.nome[0] ? alunoSessao.nome : alunoSessao.email);
        }
        lerLinha("Escolha um módulo: ", escolha, sizeof(escolha));

        if (strcmp(escolha, "0") == 0 || strcasecmp(escolha, "sair") == 0) {
            executando = false;
        } else if (strcmp(escolha, "1") == 0 || strcasecmp(escolha, "aluno") == 0) {
            menuAluno(&alunoLogado, &alunoSessao);
        } else if (strcmp(escolha, "2") == 0 || strcasecmp(escolha, "professor") == 0) {
            menuProfessor();
        } else if (strcmp(escolha, "3") == 0 || strcasecmp(escolha, "universidade") == 0) {
            menuUniversidade();
        } else if (strcmp(escolha, "4") == 0 || strcasecmp(escolha, "disciplina") == 0) {
            menuDisciplina();
        } else if (strcmp(escolha, "5") == 0 || strcasecmp(escolha, "avaliacao") == 0 || strcasecmp(escolha, "avaliação") == 0) {
            menuAvaliacao(alunoLogado, &alunoSessao);
        } else if (strcmp(escolha, "6") == 0 || strcasecmp(escolha, "relacionamentos") == 0) {
            menuRelacionamentos();
        } else if (strcmp(escolha, "7") == 0 || strcasecmp(escolha, "testes") == 0) {
            printf("\nExecutando suíte completa de testes...\n");
            run_all_tests();
        } else {
            printf("Opção inválida, tente novamente.\n");
        }
    }

    printf("Finalizando...\n");
    return 0;
}

static void lerLinha(const char *mensagem, char *dest, size_t tamanho) {
    if (mensagem != NULL) {
        printf("%s", mensagem);
        fflush(stdout);
    }

    if (fgets(dest, (int)tamanho, stdin) == NULL) {
        dest[0] = '\0';
        clearerr(stdin);
        return;
    }

    dest[strcspn(dest, "\n")] = '\0';
}

static void imprimirStatusGenerico(const char *acao, int status) {
    switch (status) {
        case 0:
            printf("%s realizada com sucesso!\n", acao);
            break;
        case 1:
            printf("Falha ao %s.\n", acao);
            break;
        case 2:
            printf("Parâmetro inválido ao %s.\n", acao);
            break;
        case 99:
            printf("Cancelamento por exceção ao %s.\n", acao);
            break;
        default:
            printf("Retorno inesperado (%d) ao %s.\n", status, acao);
            break;
    }
}

static void menuAluno(bool *alunoLogado, tpAluno *alunoSessao) {
    bool voltar = false;

    while (!voltar) {
        char opcao[32];
        printf("\n=== Módulo Aluno ===\n");
        printf("Opções: registrar, login, logout, ler, deletar, avaliar, voltar\n");
        if (*alunoLogado) {
            printf("Aluno logado: %s\n", alunoSessao->nome[0] ? alunoSessao->nome : alunoSessao->email);
        }
        lerLinha("> ", opcao, sizeof(opcao));

        if (strcasecmp(opcao, "voltar") == 0 || strcmp(opcao, "0") == 0) {
            voltar = true;
        } else if (strcasecmp(opcao, "registrar") == 0 || strcasecmp(opcao, "adda") == 0) {
            char buffer[150];

            lerLinha("CPF: ", buffer, sizeof(buffer));
            snprintf(tipoAluno.cpf, sizeof(tipoAluno.cpf), "%s", buffer);

            lerLinha("Nome: ", buffer, sizeof(buffer));
            snprintf(tipoAluno.nome, sizeof(tipoAluno.nome), "%s", buffer);

            lerLinha("Email: ", buffer, sizeof(buffer));
            snprintf(tipoAluno.email, sizeof(tipoAluno.email), "%s", buffer);

            lerLinha("Senha: ", buffer, sizeof(buffer));
            snprintf(tipoAluno.senha, sizeof(tipoAluno.senha), "%s", buffer);

            lerLinha("Curso: ", buffer, sizeof(buffer));
            snprintf(tipoAluno.curso, sizeof(tipoAluno.curso), "%s", buffer);

            lerLinha("Universidade: ", buffer, sizeof(buffer));
            snprintf(tipoAluno.universidade, sizeof(tipoAluno.universidade), "%s", buffer);

            int status = registrar(&tipoAluno);
            switch (status) {
                case 0:  printf("\nAluno cadastrado com sucesso!\n\n"); break;
                case 1:  printf("\nFalha ao registrar: já existe um aluno com este CPF.\n\n"); break;
                case 2:  printf("\nParâmetro inválido.\n\n"); break;
                case 99: printf("\nCancelamento por exceção.\n\n"); break;
                default: printf("\nErro desconhecido ao registrar.\n\n"); break;
            }
        } else if (strcasecmp(opcao, "login") == 0) {
            char email[100];
            char senha[100];

            lerLinha("Email: ", email, sizeof(email));
            lerLinha("Senha: ", senha, sizeof(senha));

            int status = login(email, senha);
            switch (status) {
                case 0:
                    printf("Login bem-sucedido!\n");
                    *alunoLogado = true;
                    memset(alunoSessao, 0, sizeof(tpAluno));
                    snprintf(alunoSessao->email, sizeof(alunoSessao->email), "%s", email);
                    snprintf(alunoSessao->senha, sizeof(alunoSessao->senha), "%s", senha);

                    char cpf[100];
                    lerLinha("CPF (opcional para carregar dados completos): ", cpf, sizeof(cpf));
                    if (strlen(cpf) > 0) {
                        tpAluno alunoLido;
                        if (read_aluno(cpf, &alunoLido) == 0) {
                            *alunoSessao = alunoLido;
                            printf("Dados do aluno carregados.\n");
                        } else {
                            printf("Não foi possível carregar os dados completos com o CPF informado.\n");
                        }
                    }
                    break;
                case 1:
                    printf("Falha no login: credenciais inválidas.\n");
                    break;
                case 2:
                    printf("Parâmetro inválido.\n");
                    break;
                case 99:
                    printf("Cancelamento por exceção.\n");
                    break;
                default:
                    printf("Erro desconhecido.\n");
                    break;
            }
        } else if (strcasecmp(opcao, "logout") == 0) {
            if (*alunoLogado) {
                *alunoLogado = false;
                memset(alunoSessao, 0, sizeof(tpAluno));
                printf("Logout realizado.\n");
            } else {
                printf("Nenhum aluno está logado.\n");
            }
        } else if (strcasecmp(opcao, "ler") == 0 || strcasecmp(opcao, "reada") == 0) {
            char cpf[100];
            tpAluno alunoLido;

            lerLinha("CPF do aluno: ", cpf, sizeof(cpf));
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
                case 1:
                    printf("\nAluno não encontrado.\n");
                    break;
                case 2:
                    printf("\nParâmetro inválido.\n");
                    break;
                case 99:
                    printf("\nCancelamento por exceção.\n");
                    break;
                default:
                    printf("\nErro desconhecido.\n");
                    break;
            }
        } else if (strcasecmp(opcao, "deletar") == 0 || strcasecmp(opcao, "dela") == 0) {
            char cpf[100];
            lerLinha("CPF do aluno a remover: ", cpf, sizeof(cpf));

            int status = delete_aluno(cpf);
            switch (status) {
                case 0:
                    printf("Aluno removido com sucesso!\n");
                    break;
                case 1:
                    printf("Falha ao deletar aluno: CPF não encontrado ou lista vazia.\n");
                    break;
                case 2:
                    printf("Parâmetro inválido.\n");
                    break;
                case 99:
                    printf("Cancelamento por exceção.\n");
                    break;
                default:
                    printf("Erro desconhecido.\n");
                    break;
            }
        } else if (strcasecmp(opcao, "avaliar") == 0) {
            if (!*alunoLogado) {
                printf("Faça login como aluno para avaliar um professor.\n");
                continue;
            }

            tpProfessor professor;
            tpAvaliacao avaliacao;
            memset(&professor, 0, sizeof(tpProfessor));
            memset(&avaliacao, 0, sizeof(tpAvaliacao));

            char buffer[255];
            lerLinha("CPF do professor: ", buffer, sizeof(buffer));
            snprintf(professor.cpf, sizeof(professor.cpf), "%s", buffer);

            lerLinha("Nome do professor: ", buffer, sizeof(buffer));
            snprintf(professor.nome, sizeof(professor.nome), "%s", buffer);

            lerLinha("Área de atuação: ", buffer, sizeof(buffer));
            snprintf(professor.area_de_atuacao, sizeof(professor.area_de_atuacao), "%s", buffer);

            lerLinha("ID da avaliação: ", buffer, sizeof(buffer));
            snprintf(avaliacao.id, sizeof(avaliacao.id), "%s", buffer);

            lerLinha("Nota: ", buffer, sizeof(buffer));
            snprintf(avaliacao.nota, sizeof(avaliacao.nota), "%s", buffer);

            lerLinha("Comentário: ", buffer, sizeof(buffer));
            snprintf(avaliacao.comentario, sizeof(avaliacao.comentario), "%s", buffer);

            lerLinha("Timestamp: ", buffer, sizeof(buffer));
            snprintf(avaliacao.timestamp, sizeof(avaliacao.timestamp), "%s", buffer);

            int status = create_avaliacao(alunoSessao, &professor, &avaliacao);
            imprimirStatusGenerico("avaliar professor", status);
        } else {
            printf("Opção inválida, tente novamente.\n");
        }
    }
}

static void menuProfessor(void) {
    bool voltar = false;

    while (!voltar) {
        char opcao[32];
        printf("\n=== Módulo Professor ===\n");
        printf("Opções: criar, ler, atualizar, deletar, voltar\n");
        lerLinha("> ", opcao, sizeof(opcao));

        if (strcasecmp(opcao, "voltar") == 0 || strcmp(opcao, "0") == 0) {
            voltar = true;
        } else if (strcasecmp(opcao, "criar") == 0) {
            tpProfessor professor;
            memset(&professor, 0, sizeof(tpProfessor));
            char buffer[150];

            lerLinha("CPF: ", buffer, sizeof(buffer));
            snprintf(professor.cpf, sizeof(professor.cpf), "%s", buffer);
            lerLinha("Nome: ", buffer, sizeof(buffer));
            snprintf(professor.nome, sizeof(professor.nome), "%s", buffer);
            lerLinha("Área de atuação: ", buffer, sizeof(buffer));
            snprintf(professor.area_de_atuacao, sizeof(professor.area_de_atuacao), "%s", buffer);

            int status = create_professor(&professor);
            imprimirStatusGenerico("criar professor", status);
        } else if (strcasecmp(opcao, "ler") == 0) {
            char cpf[100];
            tpProfessor professor;
            memset(&professor, 0, sizeof(tpProfessor));

            lerLinha("CPF do professor: ", cpf, sizeof(cpf));
            int status = read_professor(cpf, &professor);
            if (status == 0) {
                printf("Professor encontrado:\n");
                printf("Nome: %s\n", professor.nome);
                printf("CPF: %s\n", professor.cpf);
                printf("Área de atuação: %s\n", professor.area_de_atuacao);
            } else {
                imprimirStatusGenerico("ler professor", status);
            }
        } else if (strcasecmp(opcao, "atualizar") == 0) {
            char cpf[100];
            tpProfessor professor;
            memset(&professor, 0, sizeof(tpProfessor));

            lerLinha("CPF do professor a atualizar: ", cpf, sizeof(cpf));

            lerLinha("Novo nome: ", professor.nome, sizeof(professor.nome));
            lerLinha("Nova área de atuação: ", professor.area_de_atuacao, sizeof(professor.area_de_atuacao));

            int status = update_professor(cpf, &professor);
            imprimirStatusGenerico("atualizar professor", status);
        } else if (strcasecmp(opcao, "deletar") == 0) {
            char cpf[100];
            lerLinha("CPF do professor a deletar: ", cpf, sizeof(cpf));

            int status = delete_professor(cpf);
            imprimirStatusGenerico("deletar professor", status);
        } else {
            printf("Opção inválida.\n");
        }
    }
}

static void menuUniversidade(void) {
    bool voltar = false;

    while (!voltar) {
        char opcao[32];
        printf("\n=== Módulo Universidade ===\n");
        printf("Opções: criar, ler, deletar, listar, voltar\n");
        lerLinha("> ", opcao, sizeof(opcao));

        if (strcasecmp(opcao, "voltar") == 0 || strcmp(opcao, "0") == 0) {
            voltar = true;
        } else if (strcasecmp(opcao, "criar") == 0) {
            tpUniversidade universidade;
            memset(&universidade, 0, sizeof(tpUniversidade));
            char buffer[255];

            lerLinha("CNPJ: ", buffer, sizeof(buffer));
            snprintf(universidade.cnpj, sizeof(universidade.cnpj), "%s", buffer);
            lerLinha("Nome: ", buffer, sizeof(buffer));
            snprintf(universidade.nome, sizeof(universidade.nome), "%s", buffer);
            lerLinha("Descrição: ", buffer, sizeof(buffer));
            snprintf(universidade.descricao, sizeof(universidade.descricao), "%s", buffer);

            int status = create_universidade(&universidade);
            imprimirStatusGenerico("criar universidade", status);
        } else if (strcasecmp(opcao, "ler") == 0) {
            char cnpj[100];
            tpUniversidade universidade;
            memset(&universidade, 0, sizeof(tpUniversidade));

            lerLinha("CNPJ da universidade: ", cnpj, sizeof(cnpj));
            int status = read_universidade(cnpj, &universidade);
            if (status == 0) {
                printf("Universidade encontrada:\n");
                printf("Nome: %s\n", universidade.nome);
                printf("CNPJ: %s\n", universidade.cnpj);
                printf("Descrição: %s\n", universidade.descricao);
            } else {
                imprimirStatusGenerico("ler universidade", status);
            }
        } else if (strcasecmp(opcao, "deletar") == 0) {
            char cnpj[100];
            lerLinha("CNPJ da universidade: ", cnpj, sizeof(cnpj));

            int status = delete_universidade(cnpj);
            imprimirStatusGenerico("deletar universidade", status);
        } else if (strcasecmp(opcao, "listar") == 0) {
            tpUniversidade *universidades = NULL;
            int quantidade = 0;
            int status = get_universidades(&universidades, &quantidade);
            if (status == 0) {
                printf("\nUniversidades cadastradas:\n");
                for (int i = 0; i < quantidade; i++) {
                    printf("[%d] %s (CNPJ: %s)\n", i + 1, universidades[i].nome, universidades[i].cnpj);
                    printf("    Descrição: %s\n", universidades[i].descricao);
                }
            }
            imprimirStatusGenerico("listar universidades", status);
            free(universidades);
        } else {
            printf("Opção inválida.\n");
        }
    }
}

static void menuDisciplina(void) {
    bool voltar = false;

    while (!voltar) {
        char opcao[32];
        printf("\n=== Módulo Disciplina ===\n");
        printf("Opções: criar, ler, atualizar, deletar, voltar\n");
        lerLinha("> ", opcao, sizeof(opcao));

        if (strcasecmp(opcao, "voltar") == 0 || strcmp(opcao, "0") == 0) {
            voltar = true;
        } else if (strcasecmp(opcao, "criar") == 0) {
            tpDisciplina disciplina;
            memset(&disciplina, 0, sizeof(tpDisciplina));

            lerLinha("Código: ", disciplina.codigo, sizeof(disciplina.codigo));
            lerLinha("Nome: ", disciplina.nome, sizeof(disciplina.nome));

            int status = create_disciplina(&disciplina);
            imprimirStatusGenerico("criar disciplina", status);
        } else if (strcasecmp(opcao, "ler") == 0) {
            char codigo[50];
            tpDisciplina disciplina;
            memset(&disciplina, 0, sizeof(tpDisciplina));

            lerLinha("Código da disciplina: ", codigo, sizeof(codigo));
            int status = read_disciplina(codigo, &disciplina);
            if (status == 0) {
                printf("Disciplina encontrada:\n");
                printf("Código: %s\n", disciplina.codigo);
                printf("Nome: %s\n", disciplina.nome);
            } else {
                imprimirStatusGenerico("ler disciplina", status);
            }
        } else if (strcasecmp(opcao, "atualizar") == 0) {
            char codigo[50];
            tpDisciplina disciplina;
            memset(&disciplina, 0, sizeof(tpDisciplina));

            lerLinha("Código da disciplina: ", codigo, sizeof(codigo));
            lerLinha("Novo nome: ", disciplina.nome, sizeof(disciplina.nome));

            int status = update_disciplina(codigo, &disciplina);
            imprimirStatusGenerico("atualizar disciplina", status);
        } else if (strcasecmp(opcao, "deletar") == 0) {
            char codigo[50];
            lerLinha("Código da disciplina: ", codigo, sizeof(codigo));

            int status = delete_disciplina(codigo);
            imprimirStatusGenerico("deletar disciplina", status);
        } else {
            printf("Opção inválida.\n");
        }
    }
}

static void menuAvaliacao(bool alunoLogado, tpAluno *alunoSessao) {
    bool voltar = false;

    while (!voltar) {
        char opcao[32];
        printf("\n=== Módulo Avaliação ===\n");
        printf("Opções: listar, criar, voltar\n");
        lerLinha("> ", opcao, sizeof(opcao));

        if (strcasecmp(opcao, "voltar") == 0 || strcmp(opcao, "0") == 0) {
            voltar = true;
        } else if (strcasecmp(opcao, "listar") == 0) {
            tpProfessor professor;
            tpAvaliacao *avaliacoes = NULL;
            int quantidade = 0;
            memset(&professor, 0, sizeof(tpProfessor));

            lerLinha("CPF do professor: ", professor.cpf, sizeof(professor.cpf));
            int status = get_avaliacoes_professor(&professor, &avaliacoes, &quantidade);
            if (status == 0) {
                printf("\nAvaliações encontradas:\n");
                for (int i = 0; i < quantidade; i++) {
                    printf("[%d]\n", i + 1);
                    printf("  ID: %s\n", avaliacoes[i].id);
                    printf("  Nota: %s\n", avaliacoes[i].nota);
                    printf("  Comentário: %s\n", avaliacoes[i].comentario);
                    printf("  Timestamp: %s\n", avaliacoes[i].timestamp);
                }
            }
            imprimirStatusGenerico("listar avaliações", status);
            free(avaliacoes);
        } else if (strcasecmp(opcao, "criar") == 0) {
            if (!alunoLogado) {
                printf("É necessário estar logado como aluno para criar uma avaliação.\n");
                continue;
            }

            tpProfessor professor;
            tpAvaliacao avaliacao;
            memset(&professor, 0, sizeof(tpProfessor));
            memset(&avaliacao, 0, sizeof(tpAvaliacao));
            char buffer[255];

            lerLinha("CPF do professor: ", buffer, sizeof(buffer));
            snprintf(professor.cpf, sizeof(professor.cpf), "%s", buffer);
            lerLinha("Nome do professor: ", buffer, sizeof(buffer));
            snprintf(professor.nome, sizeof(professor.nome), "%s", buffer);
            lerLinha("Área de atuação: ", buffer, sizeof(buffer));
            snprintf(professor.area_de_atuacao, sizeof(professor.area_de_atuacao), "%s", buffer);

            lerLinha("ID da avaliação: ", buffer, sizeof(buffer));
            snprintf(avaliacao.id, sizeof(avaliacao.id), "%s", buffer);
            lerLinha("Nota: ", buffer, sizeof(buffer));
            snprintf(avaliacao.nota, sizeof(avaliacao.nota), "%s", buffer);
            lerLinha("Comentário: ", buffer, sizeof(buffer));
            snprintf(avaliacao.comentario, sizeof(avaliacao.comentario), "%s", buffer);
            lerLinha("Timestamp: ", buffer, sizeof(buffer));
            snprintf(avaliacao.timestamp, sizeof(avaliacao.timestamp), "%s", buffer);

            int status = create_avaliacao(alunoSessao, &professor, &avaliacao);
            imprimirStatusGenerico("criar avaliação", status);
        } else {
            printf("Opção inválida.\n");
        }
    }
}

static void menuRelacionamentos(void) {
    bool voltar = false;

    while (!voltar) {
        char opcao[32];
        printf("\n=== Relacionamentos ===\n");
        printf("Opções: aluno_universidade, professor_disciplina, disciplina_universidade, voltar\n");
        lerLinha("> ", opcao, sizeof(opcao));

        if (strcasecmp(opcao, "voltar") == 0 || strcmp(opcao, "0") == 0) {
            voltar = true;
        } else if (strcasecmp(opcao, "aluno_universidade") == 0) {
            menuAlunoUniversidade();
        } else if (strcasecmp(opcao, "professor_disciplina") == 0) {
            menuProfessorDisciplina();
        } else if (strcasecmp(opcao, "disciplina_universidade") == 0) {
            menuDisciplinaUniversidade();
        } else {
            printf("Opção inválida.\n");
        }
    }
}

static void menuAlunoUniversidade(void) {
    bool voltar = false;

    while (!voltar) {
        char opcao[32];
        printf("\n--- Relacionamento Aluno x Universidade ---\n");
        printf("Opções: vincular, consultar, voltar\n");
        lerLinha("> ", opcao, sizeof(opcao));

        if (strcasecmp(opcao, "voltar") == 0 || strcmp(opcao, "0") == 0) {
            voltar = true;
        } else if (strcasecmp(opcao, "vincular") == 0 || strcasecmp(opcao, "link") == 0) {
            tpAluno aluno;
            tpUniversidade universidade;
            memset(&aluno, 0, sizeof(tpAluno));
            memset(&universidade, 0, sizeof(tpUniversidade));

            lerLinha("CPF do aluno: ", aluno.cpf, sizeof(aluno.cpf));
            lerLinha("Nome do aluno: ", aluno.nome, sizeof(aluno.nome));

            lerLinha("CNPJ da universidade: ", universidade.cnpj, sizeof(universidade.cnpj));
            lerLinha("Nome da universidade: ", universidade.nome, sizeof(universidade.nome));

            int status = link_aluno_universidade(&aluno, &universidade);
            imprimirStatusGenerico("vincular aluno à universidade", status);
        } else if (strcasecmp(opcao, "consultar") == 0) {
            tpAluno aluno;
            tpUniversidade universidade;
            memset(&aluno, 0, sizeof(tpAluno));
            memset(&universidade, 0, sizeof(tpUniversidade));

            lerLinha("CPF do aluno: ", aluno.cpf, sizeof(aluno.cpf));
            int status = get_universidade_aluno(&aluno, &universidade);
            if (status == 0) {
                printf("\nUniversidade vinculada:\n");
                printf("Nome: %s\n", universidade.nome);
                printf("CNPJ: %s\n", universidade.cnpj);
                printf("Descrição: %s\n", universidade.descricao);
            }
            imprimirStatusGenerico("consultar universidade do aluno", status);
        } else {
            printf("Opção inválida.\n");
        }
    }
}

static void menuProfessorDisciplina(void) {
    bool voltar = false;

    while (!voltar) {
        char opcao[32];
        printf("\n--- Relacionamento Professor x Disciplina ---\n");
        printf("Opções: vincular, consultar, voltar\n");
        lerLinha("> ", opcao, sizeof(opcao));

        if (strcasecmp(opcao, "voltar") == 0 || strcmp(opcao, "0") == 0) {
            voltar = true;
        } else if (strcasecmp(opcao, "vincular") == 0 || strcasecmp(opcao, "link") == 0) {
            tpDisciplina disciplina;
            tpProfessor professor;
            memset(&disciplina, 0, sizeof(tpDisciplina));
            memset(&professor, 0, sizeof(tpProfessor));

            lerLinha("Código da disciplina: ", disciplina.codigo, sizeof(disciplina.codigo));
            lerLinha("Nome da disciplina: ", disciplina.nome, sizeof(disciplina.nome));

            lerLinha("CPF do professor: ", professor.cpf, sizeof(professor.cpf));
            lerLinha("Nome do professor: ", professor.nome, sizeof(professor.nome));
            lerLinha("Área de atuação: ", professor.area_de_atuacao, sizeof(professor.area_de_atuacao));

            int status = link_professor_disciplina(&disciplina, &professor);
            imprimirStatusGenerico("vincular professor à disciplina", status);
        } else if (strcasecmp(opcao, "consultar") == 0) {
            tpDisciplina disciplina;
            tpProfessor *professores = NULL;
            int quantidade = 0;
            memset(&disciplina, 0, sizeof(tpDisciplina));

            lerLinha("Código da disciplina: ", disciplina.codigo, sizeof(disciplina.codigo));
            int status = get_professores_disciplina(&disciplina, &professores, &quantidade);
            if (status == 0) {
                printf("\nProfessores vinculados:\n");
                for (int i = 0; i < quantidade; i++) {
                    printf("[%d] %s (CPF: %s)\n", i + 1, professores[i].nome, professores[i].cpf);
                    printf("    Área: %s\n", professores[i].area_de_atuacao);
                }
            }
            imprimirStatusGenerico("consultar professores da disciplina", status);
            free(professores);
        } else {
            printf("Opção inválida.\n");
        }
    }
}

static void menuDisciplinaUniversidade(void) {
    bool voltar = false;

    while (!voltar) {
        char opcao[32];
        printf("\n--- Relacionamento Disciplina x Universidade ---\n");
        printf("Opções: vincular, consultar, voltar\n");
        lerLinha("> ", opcao, sizeof(opcao));

        if (strcasecmp(opcao, "voltar") == 0 || strcmp(opcao, "0") == 0) {
            voltar = true;
        } else if (strcasecmp(opcao, "vincular") == 0 || strcasecmp(opcao, "link") == 0) {
            tpDisciplina disciplina;
            tpUniversidade universidade;
            memset(&disciplina, 0, sizeof(tpDisciplina));
            memset(&universidade, 0, sizeof(tpUniversidade));

            lerLinha("Código da disciplina: ", disciplina.codigo, sizeof(disciplina.codigo));
            lerLinha("Nome da disciplina: ", disciplina.nome, sizeof(disciplina.nome));

            lerLinha("CNPJ da universidade: ", universidade.cnpj, sizeof(universidade.cnpj));
            lerLinha("Nome da universidade: ", universidade.nome, sizeof(universidade.nome));

            int status = link_disciplina_universidade(&disciplina, &universidade);
            imprimirStatusGenerico("vincular disciplina à universidade", status);
        } else if (strcasecmp(opcao, "consultar") == 0) {
            tpUniversidade universidade;
            tpDisciplina *disciplinas = NULL;
            int quantidade = 0;
            memset(&universidade, 0, sizeof(tpUniversidade));

            lerLinha("CNPJ da universidade: ", universidade.cnpj, sizeof(universidade.cnpj));
            int status = get_disciplinas_universidade(&universidade, &disciplinas, &quantidade);
            if (status == 0) {
                printf("\nDisciplinas vinculadas:\n");
                for (int i = 0; i < quantidade; i++) {
                    printf("[%d] %s (%s)\n", i + 1, disciplinas[i].nome, disciplinas[i].codigo);
                }
            }
            imprimirStatusGenerico("consultar disciplinas da universidade", status);
            free(disciplinas);
        } else {
            printf("Opção inválida.\n");
        }
    }
}
