#ifndef DISCIPLINA_H
#define DISCIPLINA_H

typedef struct {
    char codigo[50];
    char nome[150];
    char universidade[150];
    char professor[150];
} tpDisciplina;

/**
 * @brief Lê os dados de uma disciplina pelo código
 * @param codigo Código da disciplina a ser buscada
 * @param disciplina Ponteiro para estrutura onde os dados da disciplina serão armazenados
 * @return 0 se a disciplina foi encontrada, 1 se não encontrada, 2 se parâmetro inválido
 * 
 * @pre codigo != NULL && disciplina != NULL && strlen(codigo) > 0
 * @post Se retorno == 0: disciplina contém os dados da disciplina encontrada
 * @post Se retorno == 1: disciplina não foi modificado (disciplina não encontrada)
 * @post Se retorno == 2: disciplina não foi modificado (parâmetro inválido)
 */
int read_disciplina(char *codigo, tpDisciplina *disciplina);

/**
 * @brief Remove uma disciplina da lista pelo código
 * @param codigo Código da disciplina a ser removida
 * @return 0 se a disciplina foi removida com sucesso, 1 se não encontrada ou lista vazia, 2 se parâmetro inválido, 99 se erro de memória
 * 
 * @pre codigo != NULL && strlen(codigo) > 0
 * @post Se retorno == 0: qtdDisciplinas foi decrementado em 1 e a disciplina foi removida da lista
 * @post Se retorno == 1: lista permanece inalterada
 * @post Se retorno == 2: lista permanece inalterada (parâmetro inválido)
 * @post Se retorno == 99: estado da lista pode estar inconsistente
 */
int delete_disciplina(char *codigo);

/**
 * @brief Cria uma nova disciplina no sistema
 * @param disciplina Ponteiro para a estrutura com os dados da disciplina a ser criada
 * @return 0 se a disciplina foi criada com sucesso, 1 se código já existe, 2 se parâmetro inválido, 99 se erro de memória
 * 
 * @pre disciplina != NULL && strlen(disciplina->codigo) > 0 && strlen(disciplina->nome) > 0
 * @post Se retorno == 0: qtdDisciplinas foi incrementado em 1 e a disciplina foi adicionada à lista
 * @post Se retorno == 1: lista permanece inalterada (código duplicado)
 * @post Se retorno == 2: lista permanece inalterada (parâmetro inválido)
 * @post Se retorno == 99: lista permanece inalterada (erro de memória)
 */
int create_disciplina(tpDisciplina *disciplina);

/**
 * @brief Atualiza os dados de uma disciplina existente
 * @param codigo Código da disciplina a ser atualizada
 * @param disciplina Ponteiro para a estrutura com os novos dados da disciplina
 * @return 0 se a disciplina foi atualizada com sucesso, 1 se não encontrada, 2 se parâmetro inválido
 * 
 * @pre codigo != NULL && disciplina != NULL && strlen(codigo) > 0
 * @post Se retorno == 0: dados da disciplina na lista foram atualizados (nome)
 * @post Se retorno == 1: lista permanece inalterada (disciplina não encontrada)
 * @post Se retorno == 2: lista permanece inalterada (parâmetro inválido)
 */
int update_disciplina(char *codigo, tpDisciplina *disciplina);

/**
 * @brief Desanexa o estado da lista de disciplinas para uso em testes
 * @param lista Ponteiro para o ponteiro da lista de disciplinas
 * @param quantidade Ponteiro para a quantidade de disciplinas
 * 
 * @pre lista != NULL && quantidade != NULL
 * @post *lista aponta para a lista anterior de disciplinas
 * @post *quantidade contém a quantidade anterior de disciplinas
 * @post listaDisciplinas == NULL && qtdDisciplinas == 0
 */
void disciplina_detach_state(tpDisciplina **lista, int *quantidade);

/**
 * @brief Anexa um estado da lista de disciplinas para uso em testes
 * @param lista Ponteiro para a lista de disciplinas
 * @param quantidade Quantidade de disciplinas na lista
 * 
 * @pre lista pode ser NULL ou apontar para uma lista válida
 * @pre quantidade >= 0
 * @post listaDisciplinas aponta para lista (ou NULL se lista == NULL)
 * @post qtdDisciplinas == quantidade
 * @post Se listaDisciplinas anterior != NULL: memória foi liberada
 */
void disciplina_attach_state(tpDisciplina *lista, int quantidade);

/**
 * @brief Libera a memória alocada para a lista de disciplinas
 * @param lista Ponteiro para a lista de disciplinas a ser liberada
 * 
 * @pre lista pode ser NULL ou apontar para memória alocada dinamicamente
 * @post Se lista != NULL: memória foi liberada
 * @post Se lista == NULL: nenhuma operação realizada
 */
void disciplina_free_state(tpDisciplina *lista);

/**
 * @brief Carrega a lista de disciplinas do arquivo de dados
 * 
 * @pre Arquivo "Disciplina/dados.json" pode existir ou não
 * @post Se arquivo existe: listaDisciplinas contém todas as disciplinas do arquivo e qtdDisciplinas reflete a quantidade
 * @post Se arquivo não existe: listaDisciplinas = NULL e qtdDisciplinas = 0
 */
void carregarDisciplinas();

/**
 * @brief Salva a lista de disciplinas no arquivo de dados
 * 
 * @pre listaDisciplinas pode ser NULL ou apontar para uma lista válida
 * @post Arquivo "Disciplina/dados.json" contém todas as disciplinas da lista atual
 * @post Se qtdDisciplinas == 0: arquivo será criado vazio ou sobrescrito
 */
void salvarDisciplinas();

#endif

