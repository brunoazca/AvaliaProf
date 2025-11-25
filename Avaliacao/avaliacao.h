#ifndef AVALIACAO_H
#define AVALIACAO_H

#include "../Aluno/aluno.h"
#include "../Professor/professor.h"

typedef struct {
    char id[50];
    char nota[10];
    char comentario[255];
    char timestamp[50];
} tpAvaliacao;

/**
 * @brief Cria uma nova avaliação de um professor feita por um aluno
 * @param aluno Ponteiro para a estrutura do aluno que está avaliando
 * @param professor Ponteiro para a estrutura do professor sendo avaliado
 * @param avaliacao Ponteiro para a estrutura com os dados da avaliação
 * @return 0 se a avaliação foi criada com sucesso, 1 se aluno/professor não encontrado ou avaliação duplicada, 2 se parâmetro inválido, 99 se erro de memória
 * 
 * @pre aluno != NULL && professor != NULL && avaliacao != NULL
 * @pre strlen(aluno->cpf) > 0 && strlen(professor->cpf) > 0
 * @pre strlen(avaliacao->nota) > 0 && strlen(avaliacao->comentario) > 0
 * @pre nota deve ser um número entre 1 e 5
 * @post Se retorno == 0: avaliação foi adicionada à lista, avaliacao->id e avaliacao->timestamp foram preenchidos automaticamente
 * @post Se retorno == 1: lista permanece inalterada (aluno/professor não encontrado ou avaliação duplicada)
 * @post Se retorno == 2: lista permanece inalterada (parâmetro inválido)
 * @post Se retorno == 99: lista permanece inalterada (erro de memória)
 */
int create_avaliacao(tpAluno *aluno, tpProfessor *professor, tpAvaliacao *avaliacao);

/**
 * @brief Obtém todas as avaliações de um professor
 * @param professor Ponteiro para a estrutura do professor
 * @param avaliacoes Ponteiro para o ponteiro do array de avaliações (será alocado)
 * @param quantidade Ponteiro para a quantidade de avaliações encontradas
 * @return 0 se a operação foi bem-sucedida, 1 se nenhuma avaliação encontrada, 2 se parâmetro inválido, 99 se erro de memória
 * 
 * @pre professor != NULL && avaliacoes != NULL && quantidade != NULL
 * @pre strlen(professor->cpf) > 0
 * @post Se retorno == 0: *avaliacoes aponta para array alocado com as avaliações e *quantidade contém o número de avaliações
 * @post Se retorno == 1: *avaliacoes == NULL e *quantidade == 0 (nenhuma avaliação encontrada)
 * @post Se retorno == 2: *avaliacoes e *quantidade não foram modificados (parâmetro inválido)
 * @post Se retorno == 99: *avaliacoes e *quantidade não foram modificados (erro de memória)
 */
int get_avaliacoes_professor(tpProfessor *professor, tpAvaliacao **avaliacoes, int *quantidade);

/**
 * @brief Desanexa o estado das avaliações para uso em testes
 * @param estado Ponteiro para o ponteiro do estado das avaliações
 * @param quantidade Ponteiro para a quantidade de avaliações
 * 
 * @pre estado != NULL && quantidade != NULL
 * @post *estado aponta para a lista anterior de avaliações
 * @post *quantidade contém a quantidade anterior de avaliações
 * @post Lista interna de avaliações foi resetada (NULL e quantidade 0)
 */
void avaliacao_detach_state(void **estado, int *quantidade);

/**
 * @brief Anexa um estado das avaliações para uso em testes
 * @param estado Ponteiro para o estado das avaliações
 * @param quantidade Quantidade de avaliações
 * 
 * @pre estado pode ser NULL ou apontar para uma lista válida
 * @pre quantidade >= 0
 * @post Lista interna de avaliações aponta para estado (ou NULL se estado == NULL)
 * @post Quantidade interna == quantidade
 * @post Se lista anterior != NULL: memória foi liberada
 */
void avaliacao_attach_state(void *estado, int quantidade);

/**
 * @brief Libera a memória alocada para o estado das avaliações
 * @param estado Ponteiro para o estado das avaliações a ser liberado
 * 
 * @pre estado pode ser NULL ou apontar para memória alocada dinamicamente
 * @post Se estado != NULL: memória foi liberada
 * @post Se estado == NULL: nenhuma operação realizada
 */
void avaliacao_free_state(void *estado);

/**
 * @brief Carrega as avaliações do arquivo de dados
 * 
 * @pre Arquivo "Avaliacao/dados.json" pode existir ou não
 * @post Se arquivo existe: lista interna contém todas as avaliações do arquivo
 * @post Se arquivo não existe: lista interna = NULL e quantidade = 0
 */
void carregarAvaliacoes();

/**
 * @brief Salva as avaliações no arquivo de dados
 * 
 * @pre Lista interna de avaliações pode estar vazia ou conter avaliações
 * @post Arquivo "Avaliacao/dados.json" contém todas as avaliações da lista atual
 * @post Se lista vazia: arquivo será criado vazio ou sobrescrito
 */
void salvarAvaliacoes();

#endif

