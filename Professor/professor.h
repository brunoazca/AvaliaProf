#ifndef PROFESSOR_H
#define PROFESSOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char cpf[100];
    char nome[150];
    char area_de_atuacao[150];
} tpProfessor;

/**
 * @brief Lê os dados de um professor pelo CPF
 * @param cpf CPF do professor a ser buscado
 * @param professor Ponteiro para estrutura onde os dados do professor serão armazenados
 * @return 0 se o professor foi encontrado, 1 se não encontrado, 2 se parâmetro inválido
 * 
 * @pre cpf != NULL && professor != NULL && strlen(cpf) > 0
 * @post Se retorno == 0: professor contém os dados do professor encontrado
 * @post Se retorno == 1: professor não foi modificado (professor não encontrado)
 * @post Se retorno == 2: professor não foi modificado (parâmetro inválido)
 */
int read_professor(char *cpf, tpProfessor *professor);

/**
 * @brief Remove um professor da lista pelo CPF
 * @param cpf CPF do professor a ser removido
 * @return 0 se o professor foi removido com sucesso, 1 se não encontrado ou lista vazia, 2 se parâmetro inválido, 99 se erro de memória
 * 
 * @pre cpf != NULL && strlen(cpf) > 0
 * @post Se retorno == 0: qtdProfessores foi decrementado em 1 e o professor foi removido da lista
 * @post Se retorno == 1: lista permanece inalterada
 * @post Se retorno == 2: lista permanece inalterada (parâmetro inválido)
 * @post Se retorno == 99: estado da lista pode estar inconsistente
 */
int delete_professor(char *cpf);

/**
 * @brief Cria um novo professor no sistema
 * @param professor Ponteiro para a estrutura com os dados do professor a ser criado
 * @return 0 se o professor foi criado com sucesso, 1 se CPF já existe, 2 se parâmetro inválido, 99 se erro de memória
 * 
 * @pre professor != NULL && strlen(professor->cpf) > 0 && strlen(professor->nome) > 0
 * @post Se retorno == 0: qtdProfessores foi incrementado em 1 e o professor foi adicionado à lista
 * @post Se retorno == 1: lista permanece inalterada (CPF duplicado)
 * @post Se retorno == 2: lista permanece inalterada (parâmetro inválido)
 * @post Se retorno == 99: lista permanece inalterada (erro de memória)
 */
int create_professor(tpProfessor *professor);

/**
 * @brief Atualiza os dados de um professor existente
 * @param cpf CPF do professor a ser atualizado
 * @param professor Ponteiro para a estrutura com os novos dados do professor
 * @return 0 se o professor foi atualizado com sucesso, 1 se não encontrado, 2 se parâmetro inválido
 * 
 * @pre cpf != NULL && professor != NULL && strlen(cpf) > 0
 * @post Se retorno == 0: dados do professor na lista foram atualizados (nome e/ou área de atuação)
 * @post Se retorno == 1: lista permanece inalterada (professor não encontrado)
 * @post Se retorno == 2: lista permanece inalterada (parâmetro inválido)
 */
int update_professor(char *cpf, tpProfessor *professor);

/**
 * @brief Desanexa o estado da lista de professores para uso em testes
 * @param lista Ponteiro para o ponteiro da lista de professores
 * @param quantidade Ponteiro para a quantidade de professores
 * 
 * @pre lista != NULL && quantidade != NULL
 * @post *lista aponta para a lista anterior de professores
 * @post *quantidade contém a quantidade anterior de professores
 * @post listaProfessores == NULL && qtdProfessores == 0
 */
void professor_detach_state(tpProfessor **lista, int *quantidade);

/**
 * @brief Anexa um estado da lista de professores para uso em testes
 * @param lista Ponteiro para a lista de professores
 * @param quantidade Quantidade de professores na lista
 * 
 * @pre lista pode ser NULL ou apontar para uma lista válida
 * @pre quantidade >= 0
 * @post listaProfessores aponta para lista (ou NULL se lista == NULL)
 * @post qtdProfessores == quantidade
 * @post Se listaProfessores anterior != NULL: memória foi liberada
 */
void professor_attach_state(tpProfessor *lista, int quantidade);

/**
 * @brief Libera a memória alocada para a lista de professores
 * @param lista Ponteiro para a lista de professores a ser liberada
 * 
 * @pre lista pode ser NULL ou apontar para memória alocada dinamicamente
 * @post Se lista != NULL: memória foi liberada
 * @post Se lista == NULL: nenhuma operação realizada
 */
void professor_free_state(tpProfessor *lista);

/**
 * @brief Carrega a lista de professores do arquivo de dados
 * 
 * @pre Arquivo "Professor/dados.json" pode existir ou não
 * @post Se arquivo existe: listaProfessores contém todos os professores do arquivo e qtdProfessores reflete a quantidade
 * @post Se arquivo não existe: listaProfessores = NULL e qtdProfessores = 0
 */
void carregarProfessores();

/**
 * @brief Salva a lista de professores no arquivo de dados
 * 
 * @pre listaProfessores pode ser NULL ou apontar para uma lista válida
 * @post Arquivo "Professor/dados.json" contém todos os professores da lista atual
 * @post Se qtdProfessores == 0: arquivo será criado vazio ou sobrescrito
 */
void salvarProfessores();

#endif

