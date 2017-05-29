/*
@jeffvfa - Jefferson Viana Fonseca Abreu 130028959
@renanlr - Renan Lobato Rheinboldt 120077400
*/
#include <list>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

using namespace std;

typedef struct esc {
    char *nome;
    std::list<struct prof> professores;
    char *habilitacao;
} escola;

typedef struct prof {
    char *nome;
    std::list<escola> preferencias;
    char *habilitacao;
} professor;

std::list<professor> professores;
std::list<escola> escolas;

//protótipos de funções
int preencherGrafo();
void strip(char *);
char **str_split(char *, const char);
void menu();
void imprimir();
void emparelhar();
int escolasComVaga();

int preencherGrafo() {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char **tokens;
    int i, j = 0, transforma;

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

            if(j<100){
              professor novoProfessor;
              novoProfessor.nome = *(tokens);
              novoProfessor.habilitacao = *(tokens + 1);
              for (i = 2; *(tokens + i); i++) {
                  escola escolaPreferida;
                  escolaPreferida.nome = *(tokens + i);
                  novoProfessor.preferencias.push_back(escolaPreferida);
              }
              professores.push_back(novoProfessor);
            }else{
              escola novaEscola;
              novaEscola.nome = *(tokens);
              novaEscola.habilitacao = *(tokens + 1);
              escolas.push_back(novaEscola);
            }
        }
        j++;
    }
    fclose(fp);
    return 0;
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

    result = (char **) malloc(sizeof(char *) * count);

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

void emparelhar(){
	while(escolasComVaga()){
		std::list<struct esc>::iterator auxEscola;
		for (std::list<struct esc>::iterator it2=escolas.begin(); it2 != escolas.end(); ++it2){
	    	if(it2->professores.size()<2){
	    		auxEscola = it2;
	    		break;
	    	}
	    }
	    //printf("While - %s\n", auxEscola->nome);
	    int i,sair=0;
	    for (i=0;i<100;i++){
	    	if (professores.empty()){
	    		break;
	    	} else {
		    	professor prof = professores.front();
		    	for (std::list<escola>::iterator preferencia=prof.preferencias.begin(); preferencia != prof.preferencias.end(); ++preferencia){
					if (strcmp(auxEscola->nome,preferencia->nome)==0){
						//printf("Escola %s contratou %s\n",auxEscola->nome, prof.nome );
						auxEscola->professores.push_back(prof);
						sair = 1;
						break;
					}
				}
				professores.push_back(prof);
				professores.pop_front();
	    	}
	    	if(sair){
	    		break;
	    	}
		}
	}
	printf("\tEmparelhamento concluído, pressione uma tecla para voltar ao menu\n");
	getchar();
	getchar();
}

int escolasComVaga(){
	for (std::list<struct esc>::iterator it2=escolas.begin(); it2 != escolas.end(); ++it2){
    	if(it2->professores.size()<2){
    		return 1;
    	}
    }
    return 0;
}

void imprimir(){
    for (std::list<struct esc>::iterator it2=escolas.begin(); it2 != escolas.end(); ++it2){
    	printf("\tEscola %s\n", it2->nome);
    	printf("\t\tProfessores\n\t\t%s\n\t\t%s\n",it2->professores.front().nome,it2->professores.back().nome);
    }
    getchar();
    getchar();
}

void imprimirSteps(){
	for (std::list<struct esc>::iterator it2=escolas.begin(); it2 != escolas.end(); ++it2){
    	printf("\tEscola %s\n", it2->nome);
    	printf("\t\tProfessores\n\t\t%s\n\t\t%s\n\tPressione uma tecla para continuar.\n",it2->professores.front().nome,it2->professores.back().nome);
    	getchar();
    	getchar();
    }
}

void menu() {
    int escape = 1, opt;

    do {
        system("clear||cls");
        printf("\t=====================================================\n");
        printf("\t======================= Menu ========================\n");
        printf("\t=====================================================\n");
        printf("\t========== Curso: CIÊNCIA DA COMPUTAÇÃO =============\n");
        printf("\t=====================================================\n");
        printf("\t============= 1) Emparelhamento         =============\n");
        printf("\t============= 2) imprimir Grafo         =============\n");
        printf("\t============= 3) imprimir Passo a Passo =============\n");
        printf("\t============= 4) Sair                   =============\n");
        printf("\t=====================================================\n");
        printf("\t=====================================================\n");
        printf("\t=====================================================\n\t>>>");
        scanf("%d", &opt);
        switch (opt) {
            case 1:
                system("clear||cls");
                emparelhar();
                break;
            case 2:
                system("clear||cls");
                imprimir();
                break;
            case 3:
                system("clear||cls");
                imprimirSteps();
                break;
            case 4:
                system("clear||cls");
                escape = 0;
                break;
            default:
                break;
        }
    } while (escape);
}

int main() {
  preencherGrafo();
  menu();

  return 0;
}