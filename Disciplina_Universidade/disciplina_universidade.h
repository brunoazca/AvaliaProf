#ifndef DISCIPLINA_UNIVERSIDADE_H
#define DISCIPLINA_UNIVERSIDADE_H

#include "../Disciplina/disciplina.h"
#include "../Universidade/universidade.h"

/**
 * @brief Cria um vínculo entre uma disciplina e uma universidade
 * @param disciplina Ponteiro para a estrutura da disciplina
 * @param universidade Ponteiro para a estrutura da universidade
 * @return 0 se o vínculo foi criado/atualizado com sucesso, 1 se disciplina ou universidade não encontradas, 2 se parâmetro inválido, 99 se erro de memória
 * 
 * @pre disciplina != NULL && universidade != NULL
 * @pre strlen(disciplina->codigo) > 0 && strlen(universidade->cnpj) > 0
 * @post Se retorno == 0: relação foi criada ou atualizada na lista de relações
 * @post Se retorno == 1: lista de relações permanece inalterada (disciplina ou universidade não encontradas)
 * @post Se retorno == 2: lista de relações permanece inalterada (parâmetro inválido)
 * @post Se retorno == 99: lista de relações permanece inalterada (erro de memória)
 */
int link_disciplina_universidade(tpDisciplina *disciplina, tpUniversidade *universidade);

/**
 * @brief Obtém todas as disciplinas associadas a uma universidade
 * @param universidade Ponteiro para a estrutura da universidade
 * @param disciplinas Ponteiro para o ponteiro do array de disciplinas (será alocado)
 * @param quantidade Ponteiro para a quantidade de disciplinas encontradas
 * @return 0 se a operação foi bem-sucedida, 1 se nenhuma disciplina encontrada, 2 se parâmetro inválido, 99 se erro de memória
 * 
 * @pre universidade != NULL && disciplinas != NULL && quantidade != NULL
 * @pre strlen(universidade->cnpj) > 0
 * @post Se retorno == 0: *disciplinas aponta para array alocado com as disciplinas e *quantidade contém o número de disciplinas
 * @post Se retorno == 1: *disciplinas == NULL e *quantidade == 0 (nenhuma disciplina encontrada)
 * @post Se retorno == 2: *disciplinas e *quantidade não foram modificados (parâmetro inválido)
 * @post Se retorno == 99: *disciplinas e *quantidade não foram modificados (erro de memória)
 */
int get_disciplinas_universidade(tpUniversidade *universidade, tpDisciplina **disciplinas, int *quantidade);

/**
 * @brief Desanexa o estado das relações disciplina-universidade para uso em testes
 * @param relacoes Ponteiro para o ponteiro das relações
 * @param quantidade Ponteiro para a quantidade de relações
 * 
 * @pre relacoes != NULL && quantidade != NULL
 * @post *relacoes aponta para a lista anterior de relações
 * @post *quantidade contém a quantidade anterior de relações
 * @post Lista interna de relações foi resetada (NULL e quantidade 0)
 */
void disciplina_universidade_detach_state(void **relacoes, int *quantidade);

/**
 * @brief Anexa um estado das relações disciplina-universidade para uso em testes
 * @param relacoes Ponteiro para as relações
 * @param quantidade Quantidade de relações
 * 
 * @pre relacoes pode ser NULL ou apontar para uma lista válida
 * @pre quantidade >= 0
 * @post Lista interna de relações aponta para relacoes (ou NULL se relacoes == NULL)
 * @post Quantidade interna == quantidade
 * @post Se lista anterior != NULL: memória foi liberada
 */
void disciplina_universidade_attach_state(void *relacoes, int quantidade);

/**
 * @brief Libera a memória alocada para as relações disciplina-universidade
 * @param relacoes Ponteiro para as relações a serem liberadas
 * 
 * @pre relacoes pode ser NULL ou apontar para memória alocada dinamicamente
 * @post Se relacoes != NULL: memória foi liberada
 * @post Se relacoes == NULL: nenhuma operação realizada
 */
void disciplina_universidade_free_state(void *relacoes);

/**
 * @brief Carrega as relações disciplina-universidade do arquivo de dados
 * 
 * @pre Arquivo "Disciplina_Universidade/dados.json" pode existir ou não
 * @post Se arquivo existe: lista interna contém todas as relações do arquivo
 * @post Se arquivo não existe: lista interna = NULL e quantidade = 0
 */
void carregarDisciplinaUniversidade();

/**
 * @brief Salva as relações disciplina-universidade no arquivo de dados
 * 
 * @pre Lista interna de relações pode estar vazia ou conter relações
 * @post Arquivo "Disciplina_Universidade/dados.json" contém todas as relações da lista atual
 * @post Se lista vazia: arquivo será criado vazio ou sobrescrito
 */
void salvarDisciplinaUniversidade();

#endif

