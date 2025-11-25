#ifndef UNIVERSIDADE_H
#define UNIVERSIDADE_H

typedef struct {
    char cnpj[100];
    char nome[150];
    char descricao[255];
} tpUniversidade;

/**
 * @brief Lê os dados de uma universidade pelo CNPJ
 * @param cnpj CNPJ da universidade a ser buscada
 * @param universidade Ponteiro para estrutura onde os dados da universidade serão armazenados
 * @return 0 se a universidade foi encontrada, 1 se não encontrada, 2 se parâmetro inválido
 * 
 * @pre cnpj != NULL && universidade != NULL && strlen(cnpj) > 0
 * @post Se retorno == 0: universidade contém os dados da universidade encontrada
 * @post Se retorno == 1: universidade não foi modificado (universidade não encontrada)
 * @post Se retorno == 2: universidade não foi modificado (parâmetro inválido)
 */
int read_universidade(char *cnpj, tpUniversidade *universidade);

/**
 * @brief Remove uma universidade da lista pelo CNPJ
 * @param cnpj CNPJ da universidade a ser removida
 * @return 0 se a universidade foi removida com sucesso, 1 se não encontrada ou lista vazia, 2 se parâmetro inválido, 99 se erro de memória
 * 
 * @pre cnpj != NULL && strlen(cnpj) > 0
 * @post Se retorno == 0: quantidade de universidades foi decrementado em 1 e a universidade foi removida da lista
 * @post Se retorno == 1: lista permanece inalterada
 * @post Se retorno == 2: lista permanece inalterada (parâmetro inválido)
 * @post Se retorno == 99: estado da lista pode estar inconsistente
 */
int delete_universidade(char *cnpj);

/**
 * @brief Cria uma nova universidade no sistema
 * @param universidade Ponteiro para a estrutura com os dados da universidade a ser criada
 * @return 0 se a universidade foi criada com sucesso, 1 se CNPJ já existe, 2 se parâmetro inválido, 99 se erro de memória
 * 
 * @pre universidade != NULL && strlen(universidade->cnpj) > 0 && strlen(universidade->nome) > 0 && strlen(universidade->descricao) > 0
 * @post Se retorno == 0: quantidade de universidades foi incrementado em 1 e a universidade foi adicionada à lista
 * @post Se retorno == 1: lista permanece inalterada (CNPJ duplicado)
 * @post Se retorno == 2: lista permanece inalterada (parâmetro inválido)
 * @post Se retorno == 99: lista permanece inalterada (erro de memória)
 */
int create_universidade(tpUniversidade *universidade);

/**
 * @brief Obtém todas as universidades cadastradas no sistema
 * @param universidades Ponteiro para o ponteiro do array de universidades (será alocado)
 * @param quantidade Ponteiro para a quantidade de universidades encontradas
 * @return 0 se a operação foi bem-sucedida, 1 se nenhuma universidade encontrada, 2 se parâmetro inválido, 99 se erro de memória
 * 
 * @pre universidades != NULL && quantidade != NULL
 * @post Se retorno == 0: *universidades aponta para array alocado com todas as universidades e *quantidade contém o número de universidades
 * @post Se retorno == 1: *universidades == NULL e *quantidade == 0 (nenhuma universidade encontrada)
 * @post Se retorno == 2: *universidades e *quantidade não foram modificados (parâmetro inválido)
 * @post Se retorno == 99: *universidades e *quantidade não foram modificados (erro de memória)
 */
int get_universidades(tpUniversidade **universidades, int *quantidade);

/**
 * @brief Desanexa o estado da lista de universidades para uso em testes
 * @param lista Ponteiro para o ponteiro da lista de universidades
 * @param quantidade Ponteiro para a quantidade de universidades
 * 
 * @pre lista != NULL && quantidade != NULL
 * @post *lista aponta para a lista anterior de universidades
 * @post *quantidade contém a quantidade anterior de universidades
 * @post Lista interna de universidades foi resetada (NULL e quantidade 0)
 */
void universidade_detach_state(tpUniversidade **lista, int *quantidade);

/**
 * @brief Anexa um estado da lista de universidades para uso em testes
 * @param lista Ponteiro para a lista de universidades
 * @param quantidade Quantidade de universidades na lista
 * 
 * @pre lista pode ser NULL ou apontar para uma lista válida
 * @pre quantidade >= 0
 * @post Lista interna de universidades aponta para lista (ou NULL se lista == NULL)
 * @post Quantidade interna == quantidade
 * @post Se lista anterior != NULL: memória foi liberada
 */
void universidade_attach_state(tpUniversidade *lista, int quantidade);

/**
 * @brief Libera a memória alocada para a lista de universidades
 * @param lista Ponteiro para a lista de universidades a ser liberada
 * 
 * @pre lista pode ser NULL ou apontar para memória alocada dinamicamente
 * @post Se lista != NULL: memória foi liberada
 * @post Se lista == NULL: nenhuma operação realizada
 */
void universidade_free_state(tpUniversidade *lista);

/**
 * @brief Carrega a lista de universidades do arquivo de dados
 * 
 * @pre Arquivo "Universidade/dados.json" pode existir ou não
 * @post Se arquivo existe: lista interna contém todas as universidades do arquivo e quantidade reflete o número de universidades
 * @post Se arquivo não existe: lista interna = NULL e quantidade = 0
 */
void carregarUniversidades();

/**
 * @brief Salva a lista de universidades no arquivo de dados
 * 
 * @pre Lista interna de universidades pode estar vazia ou conter universidades
 * @post Arquivo "Universidade/dados.json" contém todas as universidades da lista atual
 * @post Se lista vazia: arquivo será criado vazio ou sobrescrito
 */
void salvarUniversidades();

/**
 * @brief Cria uma instância de universidade com valores padrão para testes
 * @param cnpj CNPJ da universidade
 * @param nome Nome da universidade
 * @return Estrutura tpUniversidade preenchida com os valores fornecidos e valores padrão para os demais campos
 * 
 * @pre cnpj != NULL && nome != NULL
 * @post Retorna uma estrutura tpUniversidade válida com descrição padrão "Descrição de teste"
 */
tpUniversidade create_instancia_universidade(const char *cnpj, const char *nome);

#endif

