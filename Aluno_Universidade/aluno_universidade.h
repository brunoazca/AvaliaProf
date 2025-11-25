#ifndef ALUNO_UNIVERSIDADE_H
#define ALUNO_UNIVERSIDADE_H

#include "../Aluno/aluno.h"
#include "../Universidade/universidade.h"

/**
 * @brief Cria um vínculo entre um aluno e uma universidade
 * @param aluno Ponteiro para a estrutura do aluno
 * @param universidade Ponteiro para a estrutura da universidade
 * @return 0 se o vínculo foi criado/atualizado com sucesso, 1 se aluno ou universidade não encontrados, 2 se parâmetro inválido, 99 se erro de memória
 * 
 * @pre aluno != NULL && universidade != NULL
 * @pre strlen(aluno->cpf) > 0 && strlen(universidade->cnpj) > 0
 * @post Se retorno == 0: relação foi criada ou atualizada na lista de relações
 * @post Se retorno == 1: lista de relações permanece inalterada (aluno ou universidade não encontrados)
 * @post Se retorno == 2: lista de relações permanece inalterada (parâmetro inválido)
 * @post Se retorno == 99: lista de relações permanece inalterada (erro de memória)
 */
int link_aluno_universidade(tpAluno *aluno, tpUniversidade *universidade);

/**
 * @brief Obtém a universidade associada a um aluno
 * @param aluno Ponteiro para a estrutura do aluno
 * @param universidade Ponteiro para a estrutura onde a universidade será armazenada
 * @return 0 se a universidade foi encontrada, 1 se não encontrada, 2 se parâmetro inválido
 * 
 * @pre aluno != NULL && universidade != NULL && strlen(aluno->cpf) > 0
 * @post Se retorno == 0: universidade contém os dados da universidade associada ao aluno
 * @post Se retorno == 1: universidade não foi modificado (relação não encontrada)
 * @post Se retorno == 2: universidade não foi modificado (parâmetro inválido)
 */
int get_universidade_aluno(tpAluno *aluno, tpUniversidade *universidade);

/**
 * @brief Desanexa o estado das relações aluno-universidade para uso em testes
 * @param relacoes Ponteiro para o ponteiro das relações
 * @param quantidade Ponteiro para a quantidade de relações
 * 
 * @pre relacoes != NULL && quantidade != NULL
 * @post *relacoes aponta para a lista anterior de relações
 * @post *quantidade contém a quantidade anterior de relações
 * @post Lista interna de relações foi resetada (NULL e quantidade 0)
 */
void aluno_universidade_detach_state(void **relacoes, int *quantidade);

/**
 * @brief Anexa um estado das relações aluno-universidade para uso em testes
 * @param relacoes Ponteiro para as relações
 * @param quantidade Quantidade de relações
 * 
 * @pre relacoes pode ser NULL ou apontar para uma lista válida
 * @pre quantidade >= 0
 * @post Lista interna de relações aponta para relacoes (ou NULL se relacoes == NULL)
 * @post Quantidade interna == quantidade
 * @post Se lista anterior != NULL: memória foi liberada
 */
void aluno_universidade_attach_state(void *relacoes, int quantidade);

/**
 * @brief Libera a memória alocada para as relações aluno-universidade
 * @param relacoes Ponteiro para as relações a serem liberadas
 * 
 * @pre relacoes pode ser NULL ou apontar para memória alocada dinamicamente
 * @post Se relacoes != NULL: memória foi liberada
 * @post Se relacoes == NULL: nenhuma operação realizada
 */
void aluno_universidade_free_state(void *relacoes);

/**
 * @brief Carrega as relações aluno-universidade do arquivo de dados
 * 
 * @pre Arquivo "Aluno_Universidade/dados.json" pode existir ou não
 * @post Se arquivo existe: lista interna contém todas as relações do arquivo
 * @post Se arquivo não existe: lista interna = NULL e quantidade = 0
 */
void carregarAlunoUniversidade();

/**
 * @brief Salva as relações aluno-universidade no arquivo de dados
 * 
 * @pre Lista interna de relações pode estar vazia ou conter relações
 * @post Arquivo "Aluno_Universidade/dados.json" contém todas as relações da lista atual
 * @post Se lista vazia: arquivo será criado vazio ou sobrescrito
 */
void salvarAlunoUniversidade();

#endif

