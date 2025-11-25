#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "avaliacao.h"

typedef struct {
    tpAvaliacao avaliacao;
    tpAluno aluno;
    tpProfessor professor;
} tpAvaliacaoRegistro;

static tpAvaliacaoRegistro *listaAvaliacoes = NULL;
static int qtdAvaliacoes = 0;
static const char *ARQ_AVALIACOES = "Avaliacao/dados.json";

static int validarCampos(tpAluno *aluno, tpProfessor *professor, tpAvaliacao *avaliacao);
static void gerarIdAleatorio(char *id, size_t tamanho);
static void gerarTimestamp(char *timestamp, size_t tamanho);

int create_avaliacao(tpAluno *aluno, tpProfessor *professor, tpAvaliacao *avaliacao) {
    if (!validarCampos(aluno, professor, avaliacao)) {
        return 2;
    }

    tpAluno alunoEncontrado;
    tpProfessor professorEncontrado;

    if (read_aluno(aluno->cpf, &alunoEncontrado) != 0) {
        return 1;
    }

    if (read_professor(professor->cpf, &professorEncontrado) != 0) {
        return 1;
    }

    // Verificar se já existe avaliação do mesmo aluno para o mesmo professor
    for (int i = 0; i < qtdAvaliacoes; i++) {
        if (strcmp(listaAvaliacoes[i].aluno.cpf, aluno->cpf) == 0 &&
            strcmp(listaAvaliacoes[i].professor.cpf, professor->cpf) == 0) {
            return 1; // Avaliação duplicada
        }
    }

    // Gerar ID aleatório automaticamente
    gerarIdAleatorio(avaliacao->id, sizeof(avaliacao->id));
    
    // Verificar se o ID gerado já existe (muito improvável, mas verificar mesmo assim)
    for (int i = 0; i < qtdAvaliacoes; i++) {
        if (strcmp(listaAvaliacoes[i].avaliacao.id, avaliacao->id) == 0) {
            // Se o ID já existe, gerar outro
            gerarIdAleatorio(avaliacao->id, sizeof(avaliacao->id));
            i = -1; // Reiniciar verificação
        }
    }
    
    // Gerar timestamp automaticamente
    gerarTimestamp(avaliacao->timestamp, sizeof(avaliacao->timestamp));

    tpAvaliacaoRegistro *novaLista = realloc(listaAvaliacoes, (qtdAvaliacoes + 1) * sizeof(tpAvaliacaoRegistro));
    if (novaLista == NULL) {
        return 99;
    }

    listaAvaliacoes = novaLista;
    listaAvaliacoes[qtdAvaliacoes].avaliacao = *avaliacao;
    listaAvaliacoes[qtdAvaliacoes].aluno = alunoEncontrado;
    listaAvaliacoes[qtdAvaliacoes].professor = professorEncontrado;
    qtdAvaliacoes++;

    return 0;
}

int get_avaliacoes_professor(tpProfessor *professor, tpAvaliacao **avaliacoes, int *quantidade) {
    if (professor == NULL || avaliacoes == NULL || quantidade == NULL || strlen(professor->cpf) == 0) {
        return 2;
    }

    int total = 0;
    for (int i = 0; i < qtdAvaliacoes; i++) {
        if (strcmp(listaAvaliacoes[i].professor.cpf, professor->cpf) == 0) {
            total++;
        }
    }

    if (total == 0) {
        *avaliacoes = NULL;
        *quantidade = 0;
        return 1;
    }

    tpAvaliacao *lista = malloc(total * sizeof(tpAvaliacao));
    if (lista == NULL) {
        return 99;
    }

    int indice = 0;
    for (int i = 0; i < qtdAvaliacoes; i++) {
        if (strcmp(listaAvaliacoes[i].professor.cpf, professor->cpf) == 0) {
            lista[indice++] = listaAvaliacoes[i].avaliacao;
        }
    }

    *avaliacoes = lista;
    *quantidade = total;
    return 0;
}

static int validarCampos(tpAluno *aluno, tpProfessor *professor, tpAvaliacao *avaliacao) {
    if (aluno == NULL || professor == NULL || avaliacao == NULL) {
        return 0;
    }

    if (strlen(aluno->cpf) == 0 || strlen(professor->cpf) == 0) {
        return 0;
    }

    // ID e timestamp são gerados automaticamente, não precisam ser validados aqui
    if (strlen(avaliacao->nota) == 0 || strlen(avaliacao->comentario) == 0) {
        return 0;
    }

    int nota = atoi(avaliacao->nota);
    if (nota < 1 || nota > 5) {
        return 0;
    }

    return 1;
}

static void gerarIdAleatorio(char *id, size_t tamanho) {
    // Gera um ID aleatório usando timestamp + número aleatório
    time_t t = time(NULL);
    unsigned int seed = (unsigned int)(t ^ (unsigned long)id);
    srand(seed);
    
    snprintf(id, tamanho, "AVAL_%ld_%d", t, rand() % 10000);
}

static void gerarTimestamp(char *timestamp, size_t tamanho) {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    
    // Formato: YYYY-MM-DD HH:MM:SS
    strftime(timestamp, tamanho, "%Y-%m-%d %H:%M:%S", tm_info);
}

void avaliacao_detach_state(void **estado, int *quantidade) {
    if (estado == NULL || quantidade == NULL) {
        return;
    }
    *estado = listaAvaliacoes;
    *quantidade = qtdAvaliacoes;
    listaAvaliacoes = NULL;
    qtdAvaliacoes = 0;
}

void avaliacao_attach_state(void *estado, int quantidade) {
    if (listaAvaliacoes != NULL) {
        free(listaAvaliacoes);
    }
    listaAvaliacoes = estado;
    qtdAvaliacoes = quantidade;
}

void avaliacao_free_state(void *estado) {
    free(estado);
}

void carregarAvaliacoes() {
    FILE *fp = fopen(ARQ_AVALIACOES, "r");
    if(!fp){
        return;
    }
    char linha[512];
    tpAvaliacaoRegistro r;
    int state = 0;
    if (listaAvaliacoes) { free(listaAvaliacoes); listaAvaliacoes = NULL; }
    qtdAvaliacoes = 0;
    memset(&r, 0, sizeof(r));
    while(fgets(linha, sizeof(linha), fp)){
        if(strstr(linha, "\"id\"")){
            sscanf(linha, " \"%*[^:\"]\" : \"%[^\"]\"", r.avaliacao.id);
            state = 1;
        } else if(strstr(linha, "\"nota\"")){
            sscanf(linha, " \"%*[^:\"]\" : \"%[^\"]\"", r.avaliacao.nota);
        } else if(strstr(linha, "\"comentario\"")){
            sscanf(linha, " \"%*[^:\"]\" : \"%[^\"]\"", r.avaliacao.comentario);
        } else if(strstr(linha, "\"timestamp\"")){
            sscanf(linha, " \"%*[^:\"]\" : \"%[^\"]\"", r.avaliacao.timestamp);
        } else if(strstr(linha, "\"aluno_cpf\"")){
            sscanf(linha, " \"%*[^:\"]\" : \"%[^\"]\"", r.aluno.cpf);
        } else if(strstr(linha, "\"professor_cpf\"")){
            sscanf(linha, " \"%*[^:\"]\" : \"%[^\"]\"", r.professor.cpf);
            if (state == 1) {
                listaAvaliacoes = realloc(listaAvaliacoes, (qtdAvaliacoes+1) * sizeof(tpAvaliacaoRegistro));
                listaAvaliacoes[qtdAvaliacoes++] = r;
                memset(&r, 0, sizeof(r));
                state = 0;
            }
        }
    }
    fclose(fp);
    printf("Carregadas %d avaliações do arquivo!\n", qtdAvaliacoes);
    if (qtdAvaliacoes == 0) {
        printf("Nenhuma avaliação cadastrada.\n");
    } else {
        printf("===== LISTA DE AVALIAÇÕES =====\n");
        for (int i = 0; i < qtdAvaliacoes; i++) {
            printf("[%d]\n", i + 1);
            printf("  ID: %s\n", listaAvaliacoes[i].avaliacao.id);
            printf("  Nota: %s\n", listaAvaliacoes[i].avaliacao.nota);
            printf("  Comentário: %s\n", listaAvaliacoes[i].avaliacao.comentario);
            printf("  Timestamp: %s\n", listaAvaliacoes[i].avaliacao.timestamp);
            printf("  Aluno CPF: %s\n", listaAvaliacoes[i].aluno.cpf);
            printf("  Professor CPF: %s\n", listaAvaliacoes[i].professor.cpf);
            printf("----------------------------------\n");
        }
    }
}

void salvarAvaliacoes() {
    FILE *fp = fopen(ARQ_AVALIACOES, "w");
    if(!fp){ return; }
    fprintf(fp, "[\n");
    for(int i = 0; i < qtdAvaliacoes; i++){
        fprintf(fp,
            "  {\n"
            "    \"id\": \"%s\",\n"
            "    \"nota\": \"%s\",\n"
            "    \"comentario\": \"%s\",\n"
            "    \"timestamp\": \"%s\",\n"
            "    \"aluno_cpf\": \"%s\",\n"
            "    \"professor_cpf\": \"%s\"\n"
            "  }%s\n",
            listaAvaliacoes[i].avaliacao.id,
            listaAvaliacoes[i].avaliacao.nota,
            listaAvaliacoes[i].avaliacao.comentario,
            listaAvaliacoes[i].avaliacao.timestamp,
            listaAvaliacoes[i].aluno.cpf,
            listaAvaliacoes[i].professor.cpf,
            (i == qtdAvaliacoes-1 ? "" : ",")
        );
    }
    fprintf(fp, "]\n");
    fclose(fp);
    printf("\n>> dados salvos em Avaliacao/dados.json <<\n");
}

tpAvaliacao create_instancia_avaliacao(const char *id, const char *nota) {
    tpAvaliacao avaliacao;
    memset(&avaliacao, 0, sizeof(tpAvaliacao));
    if (id != NULL) {
        snprintf(avaliacao.id, sizeof(avaliacao.id), "%s", id);
    }
    if (nota != NULL) {
        snprintf(avaliacao.nota, sizeof(avaliacao.nota), "%s", nota);
    }
    snprintf(avaliacao.comentario, sizeof(avaliacao.comentario), "%s", "Muito bom");
    snprintf(avaliacao.timestamp, sizeof(avaliacao.timestamp), "%s", "2025-11-15T10:00:00Z");
    return avaliacao;
}

int get_all_avaliacoes(tpAvaliacao **avaliacoes, int *quantidade) {
    if (avaliacoes == NULL || quantidade == NULL) {
        return 2;
    }

    if (qtdAvaliacoes == 0) {
        *avaliacoes = NULL;
        *quantidade = 0;
        return 1;
    }

    tpAvaliacao *lista = malloc(qtdAvaliacoes * sizeof(tpAvaliacao));
    if (lista == NULL) {
        return 99;
    }

    for (int i = 0; i < qtdAvaliacoes; i++) {
        lista[i] = listaAvaliacoes[i].avaliacao;
    }

    *avaliacoes = lista;
    *quantidade = qtdAvaliacoes;

    return 0;
}
