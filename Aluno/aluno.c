#include "aluno.h"
static tpAluno *listaAlunos = NULL; 
static int qtdAlunos = 0;           

void listarAlunos() {
    if(qtdAlunos == 0){
        printf("\nNenhum aluno cadastrado ainda.\n\n");
        return;
    }

    printf("\n===== LISTA DE TODOS OS ALUNOS =====\n");
    for(int i = 0; i < qtdAlunos; i++){
        printf("[%d]\n", i+1);
        printf("  Nome:         %s\n", listaAlunos[i].nome);
        printf("  CPF:          %s\n", listaAlunos[i].cpf);
        printf("  Email:        %s\n", listaAlunos[i].email);
        printf("  Curso:        %s\n", listaAlunos[i].curso);
        printf("-------------------------------------\n");
    }
    printf("\n");
}

void carregarAlunos() {
    FILE *fp = fopen("Aluno/dados.json", "r");
    if(!fp){
        printf("Nenhum arquivo de alunos encontrado, começando vazio.\n");
        return;
    }

    char linha[256];
    tpAluno aluno;
    qtdAlunos = 0;
    listaAlunos = NULL;

    while(fgets(linha, sizeof(linha), fp)){
        // pegar cada campo usando sscanf
        if(strstr(linha, "\"cpf\"")){
            sscanf(linha, " \"%*[^:\"]\" : \"%[^\"]\"", aluno.cpf);
        } else if(strstr(linha, "\"nome\"")){
            sscanf(linha, " \"%*[^:\"]\" : \"%[^\"]\"", aluno.nome);
        } else if(strstr(linha, "\"email\"")){
            sscanf(linha, " \"%*[^:\"]\" : \"%[^\"]\"", aluno.email);
        } else if(strstr(linha, "\"senha\"")){
            sscanf(linha, " \"%*[^:\"]\" : \"%[^\"]\"", aluno.senha);
        } else if(strstr(linha, "\"curso\"")){
            sscanf(linha, " \"%*[^:\"]\" : \"%[^\"]\"", aluno.curso);
            
            // depois que pegou curso, adiciona na lista
            listaAlunos = realloc(listaAlunos, (qtdAlunos+1) * sizeof(tpAluno));
            listaAlunos[qtdAlunos] = aluno;
            qtdAlunos++;
        }
    }

    fclose(fp);

    printf("Carregados %d alunos do arquivo!\n", qtdAlunos);
    listarAlunos();
}

int registrar(tpAluno *aluno) {
    // Caso 2: parâmetro inválido
    if(aluno == NULL || strlen(aluno->cpf) == 0 || strlen(aluno->nome) == 0){
        return 2;
    }

    // Caso 1: verificar se já existe CPF
    for(int i = 0; i < qtdAlunos; i++){
        if(strcmp(listaAlunos[i].cpf, aluno->cpf) == 0){
            return 1; // CPF já existe
        }
    }

    // Tentar adicionar na lista
    tpAluno *novo = realloc(listaAlunos, (qtdAlunos + 1) * sizeof(tpAluno));
    if(novo == NULL){
        return 99; // caso 99: falha de memória/exceção
    }

    listaAlunos = novo;
    listaAlunos[qtdAlunos] = *aluno;
    qtdAlunos++;

    // Impressão de confirmação
    printf("\n[REGISTRADO]\n");
    printf("Nome: %s | CPF: %s\n", aluno->nome, aluno->cpf);
    printf("Agora temos %d alunos cadastrados.\n\n", qtdAlunos);
    listarAlunos();

    return 0; // caso 0: ok
}

void salvarAlunos() {
    FILE *fp;
    printf("HORA DE SALVAR");
    listarAlunos() ;
    fp = fopen("Aluno/dados.json", "w");  // só abre e sobrescreve

    if(!fp){
        printf("Erro abrindo arquivo JSON\n");
        return;
    }

    fprintf(fp, "[\n");
    for(int i = 0; i < qtdAlunos; i++){
        fprintf(fp,
         "  {\n"
         "    \"cpf\": \"%s\",\n"
         "    \"nome\": \"%s\",\n"
         "    \"email\": \"%s\",\n"
         "    \"senha\": \"%s\",\n"
         "    \"curso\": \"%s\"\n"
         "  }%s\n",
         listaAlunos[i].cpf,
         listaAlunos[i].nome,
         listaAlunos[i].email,
         listaAlunos[i].senha,
         listaAlunos[i].curso,
         (i == qtdAlunos-1 ? "" : ",")
        );
    }
    fprintf(fp, "]\n");

    fclose(fp);

    printf("\n>> dados salvos em alunos/dados.json <<\n");
}

// apenas para evitar warnings
int read_aluno(char *cpf, tpAluno *aluno) {
    // Verifica parâmetros inválidos
    if(cpf == NULL || aluno == NULL || strlen(cpf) == 0) {
        return 2; // Parâmetro inválido -> caso de teste 3
    }

    // Busca na lista de alunos
    for(int i = 0; i < qtdAlunos; i++) {
        if(strcmp(listaAlunos[i].cpf, cpf) == 0) {
            *aluno = listaAlunos[i]; // copia os dados para o ponteiro
            return 0; // Ok (Aluno encontrado) -> caso de teste 1
        }
    }

    return 1; // Aluno não encontrado -> caso de teste 2
}


int delete_aluno(char *cpf) {
    if(cpf == NULL || strlen(cpf) == 0) {
        return 2; // Parâmetro inválido -> caso de teste 7
    }

    if(qtdAlunos == 0) {
        return 1; // Falha ao deletar (lista vazia) -> caso de teste 6
    }

    for(int i = 0; i < qtdAlunos; i++) {
        if(strcmp(listaAlunos[i].cpf, cpf) == 0) {
            // Encontrou o aluno, remover da lista
            for(int j = i; j < qtdAlunos - 1; j++) {
                listaAlunos[j] = listaAlunos[j+1];
            }
            qtdAlunos--;

            // Reduz o tamanho do array
            tpAluno *tmp = realloc(listaAlunos, qtdAlunos * sizeof(tpAluno));
            if(tmp != NULL || qtdAlunos == 0) {
                listaAlunos = tmp;
            } else {
                return 99; // Cancelamento por exceção -> caso de teste 8
            }
            listarAlunos();
            return 0; // Ok -> caso de teste 5
        }
    }

    return 1; // Aluno não encontrado -> caso de teste 6
}

int login(char *cpf, char *senha) {
    if(cpf == NULL || senha == NULL || strlen(cpf) == 0 || strlen(senha) == 0) {
        return 2; // Parâmetro inválido -> caso de teste 15
    }

    for(int i = 0; i < qtdAlunos; i++) {
        if(strcmp(listaAlunos[i].cpf, cpf) == 0) {
            if(strcmp(listaAlunos[i].senha, senha) == 0) {
                printf("Login bem-sucedido! Bem-vindo, %s.\n", listaAlunos[i].nome);
                return 0; // Ok -> caso de teste 13
            } else {
                return 1; // Falha no login (senha incorreta) -> caso de teste 14
            }
        }
    }

    return 1; // Falha no login (CPF não encontrado) -> caso de teste 14
}

void aluno_detach_state(tpAluno **lista, int *quantidade) {
    if (lista == NULL || quantidade == NULL) {
        return;
    }
    *lista = listaAlunos;
    *quantidade = qtdAlunos;
    listaAlunos = NULL;
    qtdAlunos = 0;
}

void aluno_attach_state(tpAluno *lista, int quantidade) {
    if (listaAlunos != NULL) {
        free(listaAlunos);
    }
    listaAlunos = lista;
    qtdAlunos = quantidade;
}

void aluno_free_state(tpAluno *lista) {
    free(lista);
}

tpAluno create_instancia_aluno(const char *cpf, const char *nome, const char *email) {
    tpAluno aluno;
    memset(&aluno, 0, sizeof(tpAluno));
    if (cpf != NULL) {
        snprintf(aluno.cpf, sizeof(aluno.cpf), "%s", cpf);
    }
    if (nome != NULL) {
        snprintf(aluno.nome, sizeof(aluno.nome), "%s", nome);
    }
    if (email != NULL) {
        snprintf(aluno.email, sizeof(aluno.email), "%s", email);
    }
    snprintf(aluno.senha, sizeof(aluno.senha), "%s", "123456");
    snprintf(aluno.curso, sizeof(aluno.curso), "%s", "Computação");
    return aluno;
}

int get_all_alunos(tpAluno **alunos, int *quantidade) {
    if (alunos == NULL || quantidade == NULL) {
        return 2;
    }

    if (qtdAlunos == 0) {
        *alunos = NULL;
        *quantidade = 0;
        return 1;
    }

    tpAluno *lista = malloc(qtdAlunos * sizeof(tpAluno));
    if (lista == NULL) {
        return 99;
    }

    memcpy(lista, listaAlunos, qtdAlunos * sizeof(tpAluno));
    *alunos = lista;
    *quantidade = qtdAlunos;

    return 0;
}
