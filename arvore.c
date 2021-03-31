#include "arvore.h"

//inicializa uma árvore
No*	criar_arvore(){
	No* arvore = NULL;
	return arvore;
}

//recebe um funcionário, cria um nó e insere o funcionário neste nó
No* criar_no(Info *info){
	No *no = (No*) malloc(sizeof(No));
	no->info = info;
	no->esq = NULL;
	no->dir = NULL;
	return no;
}

//insere na árvoreCPF
bool inserir_by_cpf(No **arvore, Info *funcionario){

	//chegamos em um nó folha, onde será inserido o funcionário
	if(*arvore == NULL){
		*arvore = criar_no(funcionario);
		return true;
	}

	// todos os valores da sub-árvore esquerda são menores do que o nó pai.
	// todos os valores da sub-árvore direita são maiores do que o nó pai.
	// seguindo essa regra, inicia-se uma busca recursiva pela posição correta para inserção
	if(funcionario->CPF < (*arvore)->info->CPF)
		return inserir_by_cpf(&((*arvore)->esq), funcionario);

	if(funcionario->CPF > (*arvore)->info->CPF)
		return inserir_by_cpf(&((*arvore)->dir), funcionario);

	//não foi possivel inserir
	return false;
}

//insere na árvoreNome
bool inserir_by_nome(No **arvore, Info *funcionario){

	//chegamos em um nó folha, onde será inserido o funcionário
	if(*arvore == NULL){
		*arvore = criar_no(funcionario);
		return true;
	}

	//funcionário já está cadastrado
	if(strcmp((*arvore)->info->Nome, funcionario->Nome) == 0)
		return false;

	// inicia-se uma busca recursiva pela posição correta para inserção, seguindo a mesma regra de uma inserção por CPF
	int max = 0;
	strlen((*arvore)->info->Nome) > strlen(funcionario->Nome) ? (max = strlen((*arvore)->info->Nome)) : (max = strlen(funcionario->Nome));
	for(int i=0; i < max; i++){
		if(funcionario->Nome[i] < (*arvore)->info->Nome[i])
			return inserir_by_nome(&((*arvore)->esq), funcionario);
		if(funcionario->Nome[i] > (*arvore)->info->Nome[i])
			return inserir_by_nome(&((*arvore)->dir), funcionario);
	}

	return false;
}

//busca pelo nó sucessor
void sucessor(No* remover, No** restante) {
	
	//busca pelo mínimo da sua sub-árvore direita do nó que será removido
	No* no_aux;
	if ((*restante)->esq != NULL) {
		sucessor (remover, &(*restante)->esq);
		return; 
	}
	//libera o funcionário que irá ser removido
	free(remover->info);
	//onde estava o funcionario removido, agora recebe o funcionário que está no nó sucessor
	remover->info = (*restante)->info;
	//salvo o no sucessor
	no_aux = *restante;
	//link com o resto da arvore (pra onde o sucessor aponta)
	*restante = (*restante)->dir;
	//libera o nó sucessor
	no_aux->info = NULL;
	free (no_aux);
}

//remoção na árvore CPF
char *remover_by_cpf(No **arvore, int cpf){

	No *no_aux;
	//variável que será retornada para remoção na outra arvore (arvoreNome)
	char *nome_retorno = (char*) malloc(50*sizeof(char));

	//não encontrou
	if(*arvore == NULL) {
		free(nome_retorno);
		return NULL;
	}
	//busca na sub-arvore a esqueda (menor)
	if(cpf < (*arvore)->info->CPF){
		free(nome_retorno);
		return remover_by_cpf(&((*arvore)->esq), cpf);
	}

	//busca na sub-arvore a direita (maior)
	if(cpf > (*arvore)->info->CPF){
		free(nome_retorno);
		return remover_by_cpf(&((*arvore)->dir), cpf);
	}

	//encontrou, então é salvo o nome que será retornado
	strcpy(nome_retorno, (*arvore)->info->Nome);
	//crio um nó auxiliar que será o nó removido
	no_aux = *arvore;
	
	//sobre poe o vértice que será removido, pelo seus filhos
	if ((*arvore)->dir == NULL) {
		*arvore = (*arvore)->esq;
		free(no_aux->info);
		free(no_aux);
		return nome_retorno; 
	}

	if ((*arvore)->esq == NULL) {
		*arvore = (*arvore)->dir;
		free(no_aux->info);
		free(no_aux);
		return nome_retorno;
	}

	//dois filhos
	sucessor(*arvore, &(*arvore)->dir);
	return nome_retorno;
}

//função que verifica se um nome está em outro nome: thia está em thiago, por exemplo
bool nome_in(char* nome1, char* nome2){
	int in = 0;
	char *menor_nome = (char*)malloc(50*sizeof(char));

	int min = 0;
	strlen(nome1) < strlen(nome2) ? (min = strlen(nome1)) : (min = strlen(nome2));

	for(int i = 0; i < min; i++)
		if(nome1[i] == nome2[i]) in++;

	free(menor_nome);
	return in == min;
}

//remoção na árvore CPF
int remover_by_nome(No **arvore, char *nome){

	No *no_aux;
	//variável que será retornada para remoção na outra arvore (arvoreCPF)
	int cpf_retorno;
	//não encontrou
	if(*arvore == NULL) return -1;

	for(int i=0; i < strlen(nome); i++){
		//busca na sub-arvore a esqueda (menor)
		if(nome[i] < (*arvore)->info->Nome[i])
			return remover_by_nome(&((*arvore)->esq), nome);
		//busca na sub-arvore a direita (maior)
		if(nome[i] > (*arvore)->info->Nome[i])
			return remover_by_nome(&((*arvore)->dir), nome);
	}

	if(strcmp((*arvore)->info->Nome, nome) == 0){
		//encontrou, então é salvo o cpf que será retornado
		cpf_retorno = (*arvore)->info->CPF;
		//crio um nó auxiliar que será o nó removido
		no_aux = *arvore;

		//sobre poe o vértice que será removido, pelo seus filhos
		if ((*arvore)->dir == NULL) {
			*arvore = (*arvore)->esq;
			free(no_aux->info);
			free(no_aux);
			return cpf_retorno; 
		}

		if ((*arvore)->esq == NULL) {
			*arvore = (*arvore)->dir;
			free(no_aux->info);
			free(no_aux);
			return cpf_retorno;
		}

		//dois filhos
		sucessor(*arvore, &(*arvore)->dir);
		return cpf_retorno;
	}

	// if((*arvore)->dir != NULL && nome_in((*arvore)->dir->info->Nome, nome))
	// 	return remover_by_nome(&((*arvore)->dir), nome, free_info);
	// if((*arvore)->esq != NULL && nome_in((*arvore)->esq->info->Nome, nome))
	// 	return remover_by_nome(&((*arvore)->esq), nome, free_info);

	return -1;
}

//busca pelo nome fornecido
Info* buscar_by_nome(No *arvore, char *nome){

	//não encontrou
	if(arvore == NULL) return NULL;

	//encontrou, logo, retorna o funcionário
	if(strcmp(arvore->info->Nome, nome) == 0)
		return arvore->info;


	for(int i=0; i < strlen(nome); i++){
		//busca na sub-arvore a esqueda (menor)
		if(nome[i] < arvore->info->Nome[i])
			return buscar_by_nome(arvore->esq, nome);
		//busca na sub-arvore a direita (maior)
		if(nome[i] > arvore->info->Nome[i])
			return buscar_by_nome(arvore->dir, nome);
	}
	// if(arvore->dir != NULL && nome_in(arvore->dir->info->Nome, nome)) return buscar_by_nome(arvore->dir, nome);
	// if(arvore->esq != NULL && nome_in(arvore->esq->info->Nome, nome)) return buscar_by_nome(arvore->esq, nome);
	return NULL;
}





//busca pelo cpf fornecido
Info* buscar_by_cpf(No *arvore, int cpf){

	//não encontrou
	if(arvore == NULL) return NULL;

	//encontrou, logo, retorna o funcionário
	if (arvore->info->CPF == cpf)
		return arvore->info;

	//busca na sub-arvore a esqueda (menor)
	if(cpf < arvore->info->CPF)
		return buscar_by_cpf(arvore->esq, cpf);

	//busca na sub-arvore a direita (maior)
	if(cpf > arvore->info->CPF)
		return buscar_by_cpf(arvore->dir, cpf);

	return NULL;
}

//libera todos os funcionários e nós da árvore
bool free_arvore(No *arvore){

	if(arvore != NULL) {
		free_arvore(arvore->esq);
		free_arvore(arvore->dir);
		free(arvore->info);
		free(arvore);
	}
	return true;
}

//apresenta a árvore de forma 2D
void vizualizar_arvore(No *arvore, int space){
    
    if (arvore == NULL) return;
    space += 15;
    
    vizualizar_arvore(arvore->dir, space);
    
    printf("\n");
    for (int i = 15; i < space; i++) printf(" ");
    printf("(%s - %d)\n", arvore->info->Nome, arvore->info->CPF);
    vizualizar_arvore(arvore->esq, space);
}

//apresenta a árvore de forma ordenada
void post_order(No *arvore){
	
	if(arvore != NULL){
		post_order(arvore->esq);
		vizualizar_func(arvore->info);
		post_order(arvore->dir);
	}
}

//apresenta o funcionário
void vizualizar_func(Info* funcionario){
	printf("\nFuncionario: \n\tNome: %s\n\tCPF: %d\n\tProfissão: %s\n", funcionario->Nome, funcionario->CPF, funcionario->Profissao);
}

//realiza a copia de um funcionário
Info *func_cpy(Info *funcionario){
	Info *funcionario_cpy = (Info*)malloc(sizeof(Info));
	memcpy(funcionario_cpy, funcionario, sizeof(Info));
	return funcionario_cpy;
}
