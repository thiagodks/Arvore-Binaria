#include "arvore.h"

//apresenta o menu ao usuário, e retorna a opção escolhida
int menu(){

	char opt[50];
	
	printf("\n-> SISTEMA DE RH: \n");
	printf( "\n1. Cadastrar um funcionário\
			\n2. Remover um funcionário pelo nome\
			\n3. Remover um funcionário pelo CPF\
			\n4. Buscar e exibir os dados de um funcionário pelo nome\
			\n5. Buscar e exibir os dados de um funcionário pelo CPF\
			\n6. Exibir os dados de todos os funcionários ordenados pelo Nome\
			\n7. Remover todos os funcionários\
			\n8. Vizualizar Arvore\
			\n9. Sair\n\n");
	do{
		printf(">> ");
		scanf("%s", opt);
		if (atoi(opt) == 0) printf("\nOpção Inválida!\n");

	}while(atoi(opt) == 0);	
	return atoi(opt);
}

//pede os dados do funcionário que irá ser inserido nas árvore, e o retorna
Info *criar_funcionario(){

	Info *func = (Info*) malloc(sizeof(Info));
	char aux[50];

	system("clear");// system("cls");
	printf("\nCADASTRO - FUNCIONÁRIO\n\n");
	
	printf("-> Nome: ");
	scanf("%s", func->Nome);
	do{
		printf("-> CPF: ");
		scanf("%s", aux);
		if (atoi(aux) == 0) printf("\nCPF Inválido!\n");

	}while(atoi(aux) == 0);

	func->CPF = atoi(aux);
	printf("-> Profissão: ");
	scanf("%s", (func->Profissao));

	return func;
}

//pede ao usuário o nome do funcionário que ele deseja realizar alguma ação
char *get_nome(char str[10]){

	char *nome = (char*)malloc(50*sizeof(char));
	system("clear");// system("cls");
	printf("\n%s - FUNCIONÁRIO\n\n", str);
	printf("Digite o nome do usuário que deseja %s: ", str);
	scanf("%s", nome);

	return nome;
}

//pede ao usuário o cpf do funcionário que ele deseja realizar alguma ação
int get_cpf(char str[10]){

	int cpf;
	system("clear");// system("cls");
	printf("\n%s - FUNCIONÁRIO\n\n", str);
	printf("Digite o CPF do usuário que deseja %s: ", str);
	scanf("%d", &cpf);

	return cpf;
}

//carrega o arquivo de funcionários, e já os insere
bool carregar_arquivo(No **arvore_cpf, No **arvore_nome, char *nome_arq){

	FILE *arquivo = fopen(nome_arq, "r");
	if (arquivo == NULL) return false;

	while(!feof(arquivo)){
		Info *func = (Info*) malloc(sizeof(Info));
		fscanf(arquivo, "%s %d %s\n", func->Nome, &func->CPF, func->Profissao);
		inserir_by_cpf(&(*arvore_cpf), func);
		Info *func2 = func_cpy(func);
		inserir_by_nome(&(*arvore_nome), func2);
	}
	fclose(arquivo);
	return true;
}
