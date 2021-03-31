#include "arvore.h"

int main(){

	system("clear"); //system("cls");
	
	//Inicialização das Variáveis
	No *arvoreCPF = criar_arvore();
	No *arvoreNome = criar_arvore();
	Info *funcionario = NULL, *funcionario_cpy = NULL;
	int opcao = -1, cpf = -1, cpf_retorno = -1; 
	char *nome = NULL, *nome_retorno = NULL;

	//Carrega o arquivo com os funcionários e já insere nas duas árvores
	if(!carregar_arquivo(&arvoreCPF, &arvoreNome, "funcionarios.txt")){
		printf("\nFalha ao carregar arquivo de funcionarios!\n\n");
		return 0;
	}

	do{
		//apresenta o menu com as opções para o usuário, e retorna a opção escolhida
		opcao = menu();
		switch(opcao){
			
			case 1:
				//pede ao usuário os dados do funcionário que ele pretende cadastrar
				funcionario = criar_funcionario();

				//verifica se o funcionário já não está cadastrado em nenhuma das duas árvores
				if((buscar_by_nome(arvoreNome, funcionario->Nome) == NULL) && (buscar_by_cpf(arvoreCPF, funcionario->CPF) == NULL)){
					//caso não esteja, cria uma copia do funcionário para poder cadastrar nas duas árvores
					funcionario_cpy = func_cpy(funcionario);
					inserir_by_cpf(&arvoreCPF, funcionario);
					inserir_by_nome(&arvoreNome, funcionario_cpy);
					printf("\nCadastro efetuado com sucesso!\n");
				}else{
					printf("\nO funcionario %s já está cadastrado!\n", funcionario->Nome);
					free(funcionario);
				}
				break;

			case 2: 
				//pede ao usuário o nome do funcionário que ele pretende remover
				nome = get_nome("REMOVER");
				//busca na árvore ordenada pelo nome. Caso remova com sucesso, retorna o cpf do funcionário removido, para então remover
				// na árvore ordenada por cpf. Caso contrário, retorna -1
				cpf_retorno = remover_by_nome(&arvoreNome, nome);
				if(cpf_retorno != -1){
					nome_retorno = remover_by_cpf(&arvoreCPF, cpf_retorno);
					printf("\nO funcionario %s foi removido com sucesso!\n", nome_retorno);
					free(nome_retorno);
				}else
					printf("\nO Nome: '%s' não corresponde a nenhum funcionario cadastrado!\n", nome);
				free(nome);
				break;

			case 3: 
				//pede ao usuário o cpf do funcionário que ele pretende remover
				cpf = get_cpf("REMOVER");
				//busca na árvore ordenada pelo cpf. Caso remova com sucesso, retorna o nome do funcionário removido, para então remover
				// na árvore ordenada por nome. Caso contrário, retorna NULL
				nome_retorno = remover_by_cpf(&arvoreCPF, cpf);
				
				if(nome_retorno != NULL){
					cpf_retorno = remover_by_nome(&arvoreNome, nome_retorno);
					printf("\nO funcionario %s foi removido com sucesso!\n", nome_retorno);
					free(nome_retorno);
				}else
					printf("\nO CPF: '%d' não corresponde a nenhum funcionario cadastrado!\n", cpf);
				break;
			
			case 4:
				//pede ao usuário o nome do funcionário que ele pretende buscar
				nome = get_nome("BUSCAR");
				//realiza uma busca na arvoreNome, caso encontre, retorna o funcionário, caso contrário, retorna NULL
				funcionario = buscar_by_nome(arvoreNome, nome);
				if (funcionario != NULL) vizualizar_func(funcionario);
				else printf("\n->Usuário não encontrado!\n");
				free(nome);
				break;
			
			case 5:
				//pede ao usuário o cpf do funcionário que ele pretende buscar
				cpf = get_cpf("BUSCAR");
				//realiza uma busca na arvoreCPF, caso encontre, retorna o funcionário, caso contrário, retorna NULL
				funcionario = buscar_by_cpf(arvoreCPF, cpf);
				if (funcionario != NULL) vizualizar_func(funcionario);
				else printf("\n->Usuário não encontrado!\n");
				break;
			
			case 6:
				system("clear");//system("cls");
				printf("\nFuncionários ordenados pelo Nome:\n");
				//realiza uma busca "post_order", dessa forma são apresentados os funcionários em ordem crescente pelo nome
				post_order(arvoreNome);
				break;
			
			case 7: 
				//libera as duas árvores e as inicializa com  NULL novamente
				free_arvore(arvoreCPF);
				free_arvore(arvoreNome);
				arvoreCPF = criar_arvore();
				arvoreNome = criar_arvore();
				system("clear");//system("cls");
				printf("\nTodos os usuários foram removidos com sucesso!\n");
				break;

			case 8:
				//Apresenta ambas as árvores de uma maneira 2D, para que seja possivel uma melhor vizualização das arvores binárias
				system("clear");//system("cls");
				printf("\n----------------> ARVORE ORDENADA POR CPF <----------------\n");
				vizualizar_arvore(arvoreCPF, 0);
				printf("\n----------------> ARVORE ORDENADA POR NOME <----------------\n");
				vizualizar_arvore(arvoreNome, 0);
				getchar();
				getchar();
				system("clear");//system("cls");
				break;
			
			case 9: break;
			default: printf("\nOpção Inválida!\n");
		}	
	
	}while(opcao != 9);

	//antes de finalizar, são liberadas ambas as árvores binárias
	free_arvore(arvoreCPF);
	free_arvore(arvoreNome);

	return 0;
}