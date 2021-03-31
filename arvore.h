#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
	int CPF;
	char Nome[50];
	char Profissao[30];
}Info;

typedef struct No_Est {
	Info *info;
	struct No_Est *esq;
	struct No_Est *dir;
}No;

// funções da árvore
No*	criar_arvore();
bool inserir_by_cpf(No **arvore, Info *funcionario);
bool inserir_by_nome(No **arvore, Info *funcionario);

Info* buscar_by_nome(No *arvore, char *nome);
Info* buscar_by_cpf(No *arvore, int cpf);

char* remover_by_cpf(No **arvore, int cpf);
int remover_by_nome(No **arvore, char *nome);

void post_order(No *arvore);

void vizualizar_arvore(No *arvore, int space);
void vizualizar_func(Info* funcionario);

bool free_arvore(No *arvore);

// funçoes de entrada e saida
int menu();
Info *criar_funcionario();
Info *func_cpy(Info *funcionario);
char *get_nome();
int get_cpf();
bool carregar_arquivo(No **arvore_cpf, No **arvore_nome, char *nome_arq);