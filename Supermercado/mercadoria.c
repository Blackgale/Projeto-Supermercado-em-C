#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<locale.h>
#define MAX 50
#define N 5
#include "mercadoria.h"

FILE *dados_mercadoria;

void cadastromercadorias(struct Mercadoria *produto, int *qtde, float caixa)
{
	
	int i, codigo, igual, num_mercadoria;
	char opChar;
		
	printf("\n\tRegistro de mercadorias\n\n");
	     
    do{
    	igual = 0;
    	
    	printf("\nNome: ");
		fgets(produto[*qtde].nomemercadoria, sizeof(produto[*qtde].nomemercadoria), stdin);

		for (i = 0; i < *qtde; i++) //verificando se o código já está cadastrado
		{
			if(strcmp(produto[i].nomemercadoria, produto[*qtde].nomemercadoria) == 0) 
			{
				printf("\nMercadoria já cadastrada\n");
				igual = 1;
				break;
			}
		}	
		
		if(!igual)
		{
			produto[*qtde].codigomercadoria = *qtde;
			fflush(stdin);	
						
			printf("\nQuantidade: ");
		    scanf("%d", &produto[*qtde].qtdmercadoria);
		
		    printf("\nPreço: ");
		    scanf("%f", &produto[*qtde].precomercadoria);
		    
		    (*qtde)++;
		}

	    printf("\nDeseja cadastrar um novo produto?(s/n)");
        scanf(" %c", &opChar);
        getchar();
    }while(opChar == 's' || opChar == 'S');
    
	num_mercadoria = *qtde;

	/*gravando os dados na memória*/    
	dados_mercadoria = fopen("dados_mercadoria.dat", "wb");
	if(dados_mercadoria == NULL)
		printf("\nNão foi possível salvar os registros");
	else
	{
		fwrite(&num_mercadoria, sizeof(int), 1, dados_mercadoria);
		fwrite(&caixa, sizeof(float), 1, dados_mercadoria);
		fwrite(produto, sizeof(struct Mercadoria), num_mercadoria, dados_mercadoria);
		fclose(dados_mercadoria);
	}
}

void pesquisamercadorias(struct Mercadoria *produto, int qtde, float caixa)
{
	char opChar, verificarNomeMercadoria[50];
	int verificarCodigoMercadoria, contador;
	
	if (qtde == 0)
		printf("\nNão existem mercadorias cadastradas");
	else
	{
		do{
			int i, opNum;
			
			printf("\nDigite 1 para pesquisar por NOME ou 2 para pesquisar por CODIGO: ");
			scanf("%d", &opNum);
			getchar();
	
			switch(opNum)
			{
				case 1:
					printf("\nDigite o NOME: "); //pesquisa por nome
					fgets(verificarNomeMercadoria, sizeof(verificarNomeMercadoria), stdin);
					for(i = 0; i < qtde; i++)
					{
						if(strcmp(produto[i].nomemercadoria, verificarNomeMercadoria) == 0 && produto[i].qtdmercadoria > 0)
						{
							printf("\nCodigo: %.4d\nNome: %sQuantidade: %d\nPreco: %.2f\n", produto[i].codigomercadoria, produto[i].nomemercadoria, produto[i].qtdmercadoria, produto[i].precomercadoria);
							break;
						}
					}
					if(strcmp(produto[i].nomemercadoria, verificarNomeMercadoria) != 0)
						printf("\nProduto nao encontrado.");
					break;
				
				case 2:
					printf("\nDigite o CODIGO: "); //pesquisa por código
					scanf("%d", &verificarCodigoMercadoria);
					
					for(i = 0, contador = 0; i < qtde; i++)
					{
						if((produto[i].codigomercadoria == verificarCodigoMercadoria) && produto[i].qtdmercadoria > 0)
						{
							printf("\nCodigo: %.4d\nNome: %sQuantidade: %d\nPreco: %.2f\n", produto[i].codigomercadoria, produto[i].nomemercadoria, produto[i].qtdmercadoria, produto[i].precomercadoria);
							contador++;
							break;
						}
					}
			
					if(contador == 0)
						printf("\nProduto não encontrado");
					break;
				
				default:
					printf("\nEntrada invalida.");
					break;
			}
			printf("\nDeseja pesquisar novamente?(s/n)");
			scanf(" %c", &opChar);
	        getchar();	
		}while(opChar == 's' || opChar == 'S');
	}
}

void listamercadorias(struct Mercadoria *produto, int qtde, float caixa)
{ 	
	int i;
	
	if (qtde == 0)
		printf("\nNão existem mercadorias cadastradas.\n");
	else 
	{
		printf("\nMercadorias:");
		for(i = 0; i < qtde; i++)
		{
			if(produto[i].qtdmercadoria > 0)
				printf("\n\nCodigo: %d\nNome: %sQuantidade: %d\nPreço: %.2f", produto[i].codigomercadoria, produto[i].nomemercadoria, produto[i].qtdmercadoria, produto[i].precomercadoria);
			printf("\n");
		}	
	}
	printf("\nPressione enter para sair.");
	getchar();	
}

void vender(struct Mercadoria *produto, int qtde, float caixa)
{
	int codeprod, qtdprodcompra, i, igual;
	char clientecadastrado, opChar;
	float valor_venda;
	
	valor_venda = 0.0;
	
	do{
		/*leitura de dados das mercadorias em binario*/
		dados_mercadoria = fopen("dados_mercadoria.dat", "rb");
		if(dados_mercadoria != NULL)
		{
			fread(&qtde, sizeof(int), 1, dados_mercadoria); //tá lendo  qtde 2 vezes
			fread(&caixa, sizeof(float), 1, dados_mercadoria);
			fread(produto, sizeof(struct Mercadoria), qtde, dados_mercadoria);
			fclose(dados_mercadoria);
		}
	else
		printf("\nErro ao abrir o arquivo");

		for(i = 0; i < qtde; i++)
		{
			if(produto[i].qtdmercadoria > 0)
				printf("\nCodigo: %.4d\nNome: %sQuantidade em estoque: %d\nPreco: %.2f\t\n\n", produto[i].codigomercadoria, produto[i].nomemercadoria, produto[i].qtdmercadoria, produto[i].precomercadoria);
		}
			
		printf("\nDigite o codigo da mercadoria a ser comprada: ");
		scanf("%d", &codeprod);
		fflush(stdin);
		
		//verificando se existe o código da mercadoria
		igual = 0;
		for(i = 0; i < qtde; i++)
			if(produto[i].codigomercadoria == codeprod)
				igual++;	
		
		if(igual != 1)
			printf("\n\nNão cadastrado, por favor digite um código existente");
		else
		{
			if(produto[codeprod].qtdmercadoria == 0)
				printf("\n\nSem mercadoria no estoque");
			else
			{
				printf("\nQuantidade desejada: ");
				scanf("%d", &qtdprodcompra);
				
				if(produto[codeprod].qtdmercadoria < qtdprodcompra)
					printf("\n\nNão possuimos a quantidade desejada em estoque\nO nosso estoque, atualmente, possui %d unidade(s) de %s\n\n", produto[codeprod].qtdmercadoria, produto[codeprod].nomemercadoria);
				else
				{
					printf("\n\n !! Clientes cadastrados tem 10%%, de deconto !!\n\nO cliente e cadastrado ?(s/n)");
					scanf(" %c", &clientecadastrado);
					fflush(stdout);
					getchar();
				
					if(clientecadastrado == 's' || clientecadastrado == 'S')
					{
						printf("\n\nNome: %sQuantidade desejada: %d - Preco: %.2f\t\n\nDesconto = %.2f\nSubtotal: %.2f\n\n", produto[codeprod].nomemercadoria, qtdprodcompra, produto[codeprod].precomercadoria, produto[codeprod].precomercadoria * qtdprodcompra * 0.1, produto[codeprod].precomercadoria * qtdprodcompra - produto[codeprod].precomercadoria * qtdprodcompra * 0.1);	
						valor_venda += produto[codeprod].precomercadoria  * qtdprodcompra * 0.9;
					}
					else
					{
						printf("\n\nNome: %sQuantidade desejada: %d - Preco: %.2f\t\n\nSubtotal: %.2f\n\n", produto[codeprod].nomemercadoria, qtdprodcompra, produto[codeprod].precomercadoria, (produto[codeprod].precomercadoria * qtdprodcompra));	
						valor_venda += produto[codeprod].precomercadoria  * qtdprodcompra;
					}
					produto[codeprod].qtdmercadoria = produto[codeprod].qtdmercadoria - qtdprodcompra; //atualização da qtde de mercadoria
				
					/*gravando os dados na memória (atualização do estoque)*/    
					dados_mercadoria = fopen("dados_mercadoria.dat", "wb");
					if(dados_mercadoria == NULL)
						printf("\nNão foi possível salvar os registros");
					else
					{
						fwrite(&qtde, sizeof(int), 1, dados_mercadoria);
						fwrite(&caixa, sizeof(float), 1, dados_mercadoria);
						fwrite(produto, sizeof(struct Mercadoria), qtde, dados_mercadoria);
						fclose(dados_mercadoria);
					}
				}
			}	
		}
		printf("\nDeseja continuar comprando?(s/n)");
		scanf(" %c", &opChar);
        getchar();
        
		system("cls"); //windows
		//system("clear"); //linux
	}while(opChar == 's' || opChar == 'S');
	
	caixa += valor_venda; //atualização do dinheiro contido no caixa
	
	/*gravando os dados na memória (atualização do caixa)*/    
	dados_mercadoria = fopen("dados_mercadoria.dat", "wb");
	if(dados_mercadoria == NULL)
		printf("\nNão foi possível salvar os registros");
	else
	{
		fwrite(&qtde, sizeof(int), 1, dados_mercadoria);
		fwrite(&caixa, sizeof(float), 1, dados_mercadoria);
		fwrite(produto, sizeof(struct Mercadoria), qtde, dados_mercadoria);
		fclose(dados_mercadoria);
	}
	
	printf("Valor total compra: %.2f", valor_venda);
	fflush(stdout);
	printf("\nPressione enter para sair.");
	getchar();
}

void saldo(struct Mercadoria *produto, int qtde, float caixa)
{		
	/*leitura de dados das mercadorias em binario (atualização do saldo)*/
	dados_mercadoria = fopen("dados_mercadoria.dat", "rb");
	if(dados_mercadoria != NULL)
	{
		fread(&qtde, sizeof(int), 1, dados_mercadoria); //tá lendo  qtde 2 vezes
		fread(&caixa, sizeof(float), 1, dados_mercadoria);
		fread(produto, sizeof(struct Mercadoria), qtde, dados_mercadoria);
		fclose(dados_mercadoria);
	}
	else
		printf("\nErro ao abrir o arquivo");
    
	printf("Saldo = %.2f\n", caixa);
	printf("Pressione enter para continuar para o MENU.");
	getchar();
}

void atualizacaodedados(struct Mercadoria *produto, int qtde, float caixa)
{
	int codigoparaalterar, alterarqtd, i, contador;
    float alterarpreco;
    char opChar;
    
	do{
		for(i = 0; i < qtde; i++)
		{
			if(produto[i].qtdmercadoria > 0)
				printf("\nCodigo: %.4d\nNome: %sQuantidade em estoque: %d\nPreco: %.2f\n\t", produto[i].codigomercadoria, produto[i].nomemercadoria, produto[i].qtdmercadoria, produto[i].precomercadoria);
		}
	
		fflush(stdin);
		printf("\n\nDigite o codigo da mercadoria a ser alterada: ");
		scanf("%d", &codigoparaalterar);
		fflush(stdin);
	
		for(i = 0, contador = 0; i < qtde; i++)
		{
			if(produto[i].codigomercadoria == codigoparaalterar && produto[i].qtdmercadoria > 0)
			{
				printf("\nAlteração:\nCodigo: %.4d\nNome: %sQuantidade: %d\nPreco: %.2f", produto[i].codigomercadoria, produto[i].nomemercadoria, produto[i].qtdmercadoria, produto[i].precomercadoria);
				contador++;
				break;
			}
		}
	
		if(contador == 0)
			printf("\nNão cadastrado, por favor digite um código existente");
		else
		{
			printf("\n\nNova quantidade: ");
			scanf("%d", &alterarqtd);
			produto[i].qtdmercadoria = alterarqtd;
	
			printf("\nNovo preço: ");
			scanf("%f", &alterarpreco);
			produto[i].precomercadoria = alterarpreco;	
		}
		
		/*gravando os dados na memória*/    
		dados_mercadoria = fopen("dados_mercadoria.dat", "wb");
		if(dados_mercadoria == NULL)
			printf("\nNão foi possível salvar os registros");
		else
		{
			fwrite(&qtde, sizeof(int), 1, dados_mercadoria);
			fwrite(&caixa, sizeof(float), 1, dados_mercadoria);
			fwrite(produto, sizeof(struct Mercadoria), qtde, dados_mercadoria);
			fclose(dados_mercadoria);
		}
		
		printf("\n\nDeseja atualizar mais algo ?(s/n)");
		scanf(" %c", &opChar);
        getchar();
        
		system("cls"); //windows
		//system("clear"); //linux
	}while(opChar == 's' || opChar == 'S');		
}

void excluirmercadoria(struct Mercadoria *produto, int qtde, float caixa)
{
	int codigo, igual, i;
	char opChar;
	
	do{		
		printf("\nMercadorias\n");
		for(i = 0; i < qtde; i++)
		{
			if(produto[i].qtdmercadoria > 0)
				printf("\nCodigo: %d\nNome: %sQuantidade: %d\nPreço: %.2f", produto[i].codigomercadoria, produto[i].nomemercadoria, produto[i].qtdmercadoria, produto[i].precomercadoria);
			printf("\n");
		}
		
		printf("\n\nDigite o código da mercadoria que deseja excluir: ");
		scanf("%d", &codigo);
		fflush(stdin);
		
		//verificando se existe o código da mercadoria
		igual = 0;
		for(i = 0; i < qtde; i++)
			if(produto[i].codigomercadoria == codigo)
				igual++;	
		
		if(igual != 1)
			printf("\n\nNão cadastrado, por favor digite um código existente");
		else
		{	
			produto[codigo].qtdmercadoria = 0;
			
			/*gravando os dados na memória*/    
			dados_mercadoria = fopen("dados_mercadoria.dat", "wb");
			if(dados_mercadoria == NULL)
				printf("\nNão foi possível salvar os registros");
			else
			{
				fwrite(&qtde, sizeof(int), 1, dados_mercadoria);
				fwrite(&caixa, sizeof(float), 1, dados_mercadoria);
				fwrite(produto, sizeof(struct Mercadoria), qtde, dados_mercadoria);
				fclose(dados_mercadoria);
			}
		}
		printf("\n\nDeseja excluir mais algo ?(s/n)");
		scanf(" %c", &opChar);
        getchar();
        
		system("cls"); //windows
		//system("clear"); //linux
	}while(opChar == 's' || opChar == 'S');	
}
