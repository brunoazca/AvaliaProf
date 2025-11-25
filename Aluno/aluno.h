#ifndef ALUNO_H
#define ALUNO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tpAluno {
    char cpf[100];
    char nome[100];
    char email[100];
    char senha[100];
    char curso[100];
    char universidade[100];
} tpAluno;

// só declara as funções (não implementa aqui)

/**
 * @brief Lê os dados de um aluno pelo CPF
 * @param cpf CPF do aluno a ser buscado
 * @param aluno Ponteiro para estrutura onde os dados do aluno serão armazenados
 * @return 0 se o aluno foi encontrado, 1 se não encontrado, 2 se parâmetro inválido
 * 
 * @pre cpf != NULL && aluno != NULL && strlen(cpf) > 0
 * @post Se retorno == 0: aluno contém os dados do aluno encontrado
 * @post Se retorno == 1: aluno não foi modificado (aluno não encontrado)
 * @post Se retorno == 2: aluno não foi modificado (parâmetro inválido)
 */
int read_aluno(char *cpf, tpAluno *aluno);

/**
 * @brief Remove um aluno da lista pelo CPF
 * @param cpf CPF do aluno a ser removido
 * @return 0 se o aluno foi removido com sucesso, 1 se não encontrado ou lista vazia, 2 se parâmetro inválido, 99 se erro de memória
 * 
 * @pre cpf != NULL && strlen(cpf) > 0
 * @post Se retorno == 0: qtdAlunos foi decrementado em 1 e o aluno foi removido da lista
 * @post Se retorno == 1: lista permanece inalterada
 * @post Se retorno == 2: lista permanece inalterada (parâmetro inválido)
 * @post Se retorno == 99: estado da lista pode estar inconsistente
 */
int delete_aluno(char *cpf);

/**
 * @brief Registra um novo aluno no sistema
 * @param aluno Ponteiro para a estrutura com os dados do aluno a ser registrado
 * @return 0 se o registro foi realizado com sucesso, 1 se CPF já existe, 2 se parâmetro inválido, 99 se erro de memória
 * 
 * @pre aluno != NULL && strlen(aluno->cpf) > 0 && strlen(aluno->nome) > 0
 * @post Se retorno == 0: qtdAlunos foi incrementado em 1 e o aluno foi adicionado à lista
 * @post Se retorno == 1: lista permanece inalterada (CPF duplicado)
 * @post Se retorno == 2: lista permanece inalterada (parâmetro inválido)
 * @post Se retorno == 99: lista permanece inalterada (erro de memória)
 */
int registrar(tpAluno *aluno);

/**
 * @brief Realiza o login de um aluno no sistema
 * @param cpf CPF do aluno
 * @param senha Senha do aluno
 * @return 0 se o login foi bem-sucedido, 1 se CPF não encontrado ou senha incorreta, 2 se parâmetro inválido
 * 
 * @pre cpf != NULL && senha != NULL && strlen(cpf) > 0 && strlen(senha) > 0
 * @post Se retorno == 0: login bem-sucedido (nenhuma modificação na lista)
 * @post Se retorno == 1: login falhou (nenhuma modificação na lista)
 * @post Se retorno == 2: parâmetro inválido (nenhuma modificação na lista)
 */
int login(char *cpf, char *senha);

/**
 * @brief Salva a lista de alunos no arquivo de dados
 * 
 * @pre listaAlunos pode ser NULL ou apontar para uma lista válida
 * @post Arquivo "Aluno/dados.json" contém todos os alunos da lista atual
 * @post Se qtdAlunos == 0: arquivo será criado vazio ou sobrescrito
 */
void salvarAlunos();

/**
 * @brief Carrega a lista de alunos do arquivo de dados
 * 
 * @pre Arquivo "Aluno/dados.json" pode existir ou não
 * @post Se arquivo existe: listaAlunos contém todos os alunos do arquivo e qtdAlunos reflete a quantidade
 * @post Se arquivo não existe: listaAlunos = NULL e qtdAlunos = 0
 */
void carregarAlunos();

/**
 * @brief Desanexa o estado da lista de alunos para uso em testes
 * @param lista Ponteiro para o ponteiro da lista de alunos
 * @param quantidade Ponteiro para a quantidade de alunos
 * 
 * @pre lista != NULL && quantidade != NULL
 * @post *lista aponta para a lista anterior de alunos
 * @post *quantidade contém a quantidade anterior de alunos
 * @post listaAlunos == NULL && qtdAlunos == 0
 */
void aluno_detach_state(tpAluno **lista, int *quantidade);

/**
 * @brief Anexa um estado da lista de alunos para uso em testes
 * @param lista Ponteiro para a lista de alunos
 * @param quantidade Quantidade de alunos na lista
 * 
 * @pre lista pode ser NULL ou apontar para uma lista válida
 * @pre quantidade >= 0
 * @post listaAlunos aponta para lista (ou NULL se lista == NULL)
 * @post qtdAlunos == quantidade
 * @post Se listaAlunos anterior != NULL: memória foi liberada
 */
void aluno_attach_state(tpAluno *lista, int quantidade);

/**
 * @brief Libera a memória alocada para a lista de alunos
 * @param lista Ponteiro para a lista de alunos a ser liberada
 * 
 * @pre lista pode ser NULL ou apontar para memória alocada dinamicamente
 * @post Se lista != NULL: memória foi liberada
 * @post Se lista == NULL: nenhuma operação realizada
 */
void aluno_free_state(tpAluno *lista);
#endif
