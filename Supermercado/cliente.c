#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<locale.h>
#define MAX 50
#define N 5
#include "cliente.h"

FILE *dados_cliente;

void cadastrocliente(struct Cliente *cliente, int *num)
{	 
	int i, codigo, igual, num_cliente;
	char opChar;
	
	printf("\n\tRegistro de clientes\n\n");
	     
    do{
    	igual = 0;

		printf("\nC�digo: ");
		scanf("%d", &codigo);
		
		for (i = 0; (i < *num) && (!igual); i++) //verificando se o c�digo j� est� cadastrado
		{
			if (cliente[i].codigocliente == codigo) 
			{
				printf("\nC�digo j� cadastrado\n");
				igual = 1;
			}	
		}
		
		if(!igual)
		{
			cliente[*num].codigocliente = codigo;
			fflush(stdin);	
			
	   		printf("\nNome: ");
	    	fgets(cliente[*num].nome, sizeof(cliente[*num].nome), stdin);
		    
		    (*num)++;
		}

	    printf("\nDeseja cadastrar um novo cliente?(s/n)");
        scanf(" %c", &opChar);
        getchar();
    }while(opChar == 's' || opChar == 'S');
    
	num_cliente = *num;
	    
	/*gravando os dados na mem�ria*/    
	dados_cliente = fopen("dados_cliente.dat", "wb");
	if(dados_cliente == NULL)
		printf("\nN�o foi poss�vel salvar os registros");
	else
	{
		fwrite(&num_cliente, sizeof(int), 1, dados_cliente);
		fwrite(cliente, sizeof(struct Cliente), num_cliente, dados_cliente);
		fclose(dados_cliente);
	}
}

void pesquisaclientes(struct Cliente *cliente, int num)
{
	char opChar, verificarNome[50];
	int verificarCodigo;
	
	if (num == 0)
		printf("\nN�o existem clientes cadastrados");
	else
	{	
		do{
			int i, opNum, contador;
			
				printf("\nDigite 1 para pesquisar por NOME ou 2 para pesquisar por CODIGO: ");
				scanf("%d", &opNum);
				getchar();
				
				switch(opNum)
				{
					case 1:
						printf("\nDigite o NOME: "); //pesquisa por nome
						fgets(verificarNome, sizeof(verificarNome), stdin);
						
						for(i = 0; i < num; i++)
						{
							if(strcmp(cliente[i].nome, verificarNome) == 0 && cliente[i].codigocliente > 0)
							{
								printf("\nNome: %sCodigo: %.4d\n", cliente[i].nome, cliente[i].codigocliente);
								break;
							}
						}
						if(strcmp(cliente[i].nome, verificarNome) != 0)
							printf("\nCliente nao encontrado. ");
						break;
					
					case 2:
						printf("\nDigite o CODIGO: "); //pesquisa por c�digo
						scanf("%d", &verificarCodigo);
						
						for(i = 0, contador = 0; i < num; i++)
						{
							if(cliente[i].codigocliente == verificarCodigo)
							{
								printf("\nNome: %sCodigo: %.4d\n", cliente[i].nome, cliente[i].codigocliente);
								contador++;
								break;
							}
						}
					
						if(contador == 0)
							printf("\nCliente n�o encontrado. ");
						break;
					
					default:
						printf("\nEntrada invalida. ");
						break;
				}
				printf("Deseja pesquisar novamente?(s/n)");
				scanf(" %c", &opChar);
		        getchar();
			}while(opChar == 's' || opChar == 'S');	
		}
}

void listaclientes(struct Cliente *cliente, int num)
{ 
	int i;
	
	if (num == 0)
		printf("\nN�o existem clientes cadastrados.\n");
	else 
	{
		printf("\nClientes:");
		for(i = 0; i < num; i++)
		{
			if(cliente[i].codigocliente > 0)
				printf("\n\nCodigo: %d\nNome: %s", cliente[i].codigocliente, cliente[i].nome);
			printf("\n");
		}
	}
	printf("\nPressione enter para sair.");
	getchar();
}

void excluircliente(struct Cliente *cliente, int num)
{
	int codigo, igual, i;
	char opChar;
	
	do{		
		printf("\nClientes:");
		for(i = 0; i < num; i++)
		{
			if(cliente[i].codigocliente > 0)
				printf("\nCodigo: %d\nNome: %s", cliente[i].codigocliente, cliente[i].nome);
			printf("\n");
		}
		
		printf("\n\nDigite o c�digo do cliente que deseja excluir: ");
		scanf("%d", &codigo);
		fflush(stdin);
		
		//verificando se existe o c�digo da mercadoria
		igual = 0;
		for(i = 0; i < num; i++)
			if(cliente[i].codigocliente == codigo)
				igual++;	
		
		if(igual != 1)
			printf("\n\nN�o cadastrado, por favor digite um c�digo existente");
		else
		{	
			cliente[codigo-1].codigocliente = 0;
			
			/*gravando os dados na mem�ria*/    
			dados_cliente = fopen("dados_cliente.dat", "wb");
			if(dados_cliente == NULL)
				printf("\nN�o foi poss�vel salvar os registros");
			else
			{
				fwrite(&num, sizeof(int), 1, dados_cliente);
				fwrite(cliente, sizeof(struct Cliente), num, dados_cliente);
				fclose(dados_cliente);
			}
		}
		printf("\n\nDeseja excluir mais algo ?(s/n)");
		scanf(" %c", &opChar);
        getchar();
        
		system("cls"); //windows
		//system("clear"); //linux
	}while(opChar == 's' || opChar == 'S');	
}
