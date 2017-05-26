/*
@jeffvfa - Jefferson Viana Fonseca Abreu 130028959
@renanlr - Renan Lobato Rheinboldt 120077400
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define NV 150
#define DEBUG printf("aqui"); getchar();
#define DEBUGU printf("aquiu");

//elemento da lista de adjacência, aresta
typedef struct are {
    struct are *prox;
    struct ver *vertice;
    char *nome;
    int preenchido;
} aresta;

//vértice do grafo
typedef struct ver {
    int tipo;
    char *nome;
    char *habilitacao;
    aresta *arestas;
} vertice;

vertice grafo_materias[NV];

//protótipos de funções
int preencherGrafo();
void strip(char *);
void ligarArestas();
char **str_split(char *, const char);
void menu();
void printaGrafo();
vertice *buscaVertice(char *);

//invoca o menu
void menu() {
    int escape = 1, opt;

    do {
        system("clear||cls");
        printf("\t=====================================================\n");
        printf("\t======================= Menu ========================\n");
        printf("\t=====================================================\n");
        printf("\t========== Curso: CIÊNCIA DA COMPUTAÇÃO =============\n");
        printf("\t=====================================================\n");
        printf("\t================ 1) Imprimir Grafo ==================\n");
        printf("\t================ 2) Emparelhamento ==================\n");
        printf("\t================ 3) Sair           ==================\n");
        printf("\t=====================================================\n");
        printf("\t=====================================================\n");
        printf("\t=====================================================\n\t>>>");
        scanf("%d", &opt);
        switch (opt) {
            case 1:
                system("clear||cls");
                printaGrafo();
                break;
            case 2:
                system("clear||cls");
                break;
            case 3:
                system("clear||cls");
                escape = 0;
                break;
            default:
                break;
        }
    } while (escape);
}

int preencherGrafo() {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char **tokens;
    int i, j = 0, transforma;
    vertice *alvo;

    //abre-se o arquivo
    fp = fopen("input.txt", "r");
    if (fp == NULL) {
        return -1;
    }


    while ((read = getline(&line, &len, fp)) != -1) {
        printf("%s\n", line);
        strip(line);
        // Separando linha por virgulas
        tokens = str_split(line, ',');

        if (tokens) {

            //printf("%s  ,  %s  ,   %s   ,  %s ...\n", *(tokens + 1),*(tokens + 2),*(tokens + 3),*(tokens + 4));
            //inicializando a lista de amigos como uma lista vazia
            grafo_materias[j].arestas = NULL;
            //inserindo nome do aluno no grafo
            grafo_materias[j].nome = *(tokens);
            //inserindo matricula do aluno
            grafo_materias[j].habilitacao = *(tokens + 1);
            grafo_materias[j].tipo = 0;

            if(j<100){
              grafo_materias[j].tipo = 1;

              // inserindo arestas
              aresta *ultimoDaLista;

              grafo_materias[j].arestas = malloc(sizeof(aresta));
              ultimoDaLista = grafo_materias[j].arestas;

              for (i = 2; *(tokens + i); i++) {

                  ultimoDaLista->nome = *(tokens + i);
                  ultimoDaLista->preenchido = 1;
                  ultimoDaLista->prox = malloc(sizeof(aresta));
                  ultimoDaLista = (aresta *) ultimoDaLista->prox;

              }
            }
        }
        j++;
    }
    printf("Tchau While\n");
    fclose(fp);
    ligarArestas();
    return 0;
}

// Este método deve relacionar a lista de amigos com o seu respectivo nó
void ligarArestas() {
    int k;
    printf("Ligando Arestas\n");
    aresta *elementoAresta;
    for (k = 0; k < NV; k++) {
        elementoAresta = grafo_materias[k].arestas;
        if(elementoAresta != NULL){
            while ((elementoAresta->preenchido)==1) {
                elementoAresta->vertice = buscaVertice(elementoAresta->nome);
                printf("%s\n", (elementoAresta->vertice)->nome);
                elementoAresta = (aresta *)elementoAresta->prox;
            }
        }
    }
}
void strip(char *s) {
    char *p2 = s;
    while (*s != '\0') {
        if (*s != '\t' && *s != '\n') {
            *p2++ = *s++;
        } else {
            ++s;
        }
    }
    *p2 = '\0';
}

char **str_split(char *a_str, const char a_delim) {
    char **result = 0;
    size_t count = 0;
    char *tmp = a_str;
    char *last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp) {
        if (a_delim == *tmp) {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char *) * count);

    if (result) {
        size_t idx = 0;
        char *token = strtok(a_str, delim);

        while (token) {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}

//função que busca um vértice através de sua matrícula
vertice *buscaVertice(char *target) {
    vertice *retorno = NULL;
    //varre a lista
    int i;
    for (i = 0; i < NV; i++) {
        if (strcmp((grafo_materias[i].nome), target) == 0) {
            //se encontra o vértice retorna o endereço do vértice
            retorno = &grafo_materias[i];
            return retorno;
        }
    }
    //se não retorna um ponteiro nulo
    return retorno;
}

void printaGrafo() {
  int i;
  for(i=0; i<NV; i++){
      printf("\t%s ", grafo_materias[i].nome);
      aresta * aux = (grafo_materias[i].arestas);
      if(aux != NULL){
          while(aux->preenchido == 1){
            printf("%s ", (aux->vertice)->nome);
            aux = aux->prox;
          }
      }
      printf("\n");
  }
    printf("\n\n\t>>> Pressione uma tecla para voltar ao menu <<<\n\t");
    getchar();
    getchar();
}

int main() {
  preencherGrafo();
  menu();

  return 0;
}
