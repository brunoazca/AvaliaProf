#ifndef PROFESSOR_DISCIPLINA_H
#define PROFESSOR_DISCIPLINA_H

#include "../Professor/professor.h"
#include "../Disciplina/disciplina.h"

typedef struct {
    char disciplinaCodigo[50];
    char professorCpf[100];
} tpProfessorDisciplinaRel;

/**
 * @brief Cria um vínculo entre um professor e uma disciplina
 * @param disciplina Ponteiro para a estrutura da disciplina
 * @param professor Ponteiro para a estrutura do professor
 * @return 0 se o vínculo foi criado com sucesso ou já existe, 1 se disciplina ou professor não encontrados, 2 se parâmetro inválido, 99 se erro de memória
 * 
 * @pre disciplina != NULL && professor != NULL
 * @pre strlen(disciplina->codigo) > 0 && strlen(professor->cpf) > 0
 * @post Se retorno == 0: relação foi criada na lista de relações (ou já existia)
 * @post Se retorno == 1: lista de relações permanece inalterada (disciplina ou professor não encontrados)
 * @post Se retorno == 2: lista de relações permanece inalterada (parâmetro inválido)
 * @post Se retorno == 99: lista de relações permanece inalterada (erro de memória)
 */
int link_professor_disciplina(tpDisciplina *disciplina, tpProfessor *professor);

/**
 * @brief Obtém todos os professores associados a uma disciplina
 * @param disciplina Ponteiro para a estrutura da disciplina
 * @param professores Ponteiro para o ponteiro do array de professores (será alocado)
 * @param quantidade Ponteiro para a quantidade de professores encontrados
 * @return 0 se a operação foi bem-sucedida, 1 se nenhum professor encontrado, 2 se parâmetro inválido, 99 se erro de memória
 * 
 * @pre disciplina != NULL && professores != NULL && quantidade != NULL
 * @pre strlen(disciplina->codigo) > 0
 * @post Se retorno == 0: *professores aponta para array alocado com os professores e *quantidade contém o número de professores
 * @post Se retorno == 1: *professores == NULL e *quantidade == 0 (nenhum professor encontrado)
 * @post Se retorno == 2: *professores e *quantidade não foram modificados (parâmetro inválido)
 * @post Se retorno == 99: *professores e *quantidade não foram modificados (erro de memória)
 */
int get_professores_disciplina(tpDisciplina *disciplina, tpProfessor **professores, int *quantidade);

/**
 * @brief Desanexa o estado das relações professor-disciplina para uso em testes
 * @param relacoes Ponteiro para o ponteiro das relações
 * @param quantidade Ponteiro para a quantidade de relações
 * 
 * @pre relacoes != NULL && quantidade != NULL
 * @post *relacoes aponta para a lista anterior de relações
 * @post *quantidade contém a quantidade anterior de relações
 * @post Lista interna de relações foi resetada (NULL e quantidade 0)
 */
void professor_disciplina_detach_state(tpProfessorDisciplinaRel **relacoes, int *quantidade);

/**
 * @brief Anexa um estado das relações professor-disciplina para uso em testes
 * @param relacoes Ponteiro para as relações
 * @param quantidade Quantidade de relações
 * 
 * @pre relacoes pode ser NULL ou apontar para uma lista válida
 * @pre quantidade >= 0
 * @post Lista interna de relações aponta para relacoes (ou NULL se relacoes == NULL)
 * @post Quantidade interna == quantidade
 * @post Se lista anterior != NULL: memória foi liberada
 */
void professor_disciplina_attach_state(tpProfessorDisciplinaRel *relacoes, int quantidade);

/**
 * @brief Libera a memória alocada para as relações professor-disciplina
 * @param relacoes Ponteiro para as relações a serem liberadas
 * 
 * @pre relacoes pode ser NULL ou apontar para memória alocada dinamicamente
 * @post Se relacoes != NULL: memória foi liberada
 * @post Se relacoes == NULL: nenhuma operação realizada
 */
void professor_disciplina_free_state(tpProfessorDisciplinaRel *relacoes);

/**
 * @brief Carrega as relações professor-disciplina do arquivo de dados
 * 
 * @pre Arquivo "Professor_Disciplina/dados.json" pode existir ou não
 * @post Se arquivo existe: lista interna contém todas as relações do arquivo
 * @post Se arquivo não existe: lista interna = NULL e quantidade = 0
 */
void carregarProfessorDisciplina();

/**
 * @brief Salva as relações professor-disciplina no arquivo de dados
 * 
 * @pre Lista interna de relações pode estar vazia ou conter relações
 * @post Arquivo "Professor_Disciplina/dados.json" contém todas as relações da lista atual
 * @post Se lista vazia: arquivo será criado vazio ou sobrescrito
 */
void salvarProfessorDisciplina();

#endif

