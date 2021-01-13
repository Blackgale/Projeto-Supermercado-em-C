#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<locale.h>
#define MAX 50
#define N 5
#include "mercadoria.h" //biblioteca estática com as funções e definições que envolvem mercadoria
#include "cliente.h" //biblioteca estática com as funções e definições que envolvem cliente

int main(int argc, char *argv[]) 
{
	setlocale(LC_ALL, "Portuguese");
	
	FILE *dados_mercadoria; //ponteiro para o arquivo com os dados das mercadorias
	FILE *dados_cliente; //ponteiro para o arquivo com os dados dos clientes
	struct Cliente *cliente;
	struct Mercadoria *mercadoria;
	int opNum, num_mercadoria, num_cliente, memoria_mercadoria, memoria_cliente, n_merc, n_cliente;
	float caixa;
	
	mercadoria = (struct Mercadoria *)malloc(N * sizeof(struct Cliente)); //alocando memória para cliente
	cliente = (struct Cliente *)malloc(N * sizeof(struct Cliente)); //alocando memória para cliente
	
	/*leitura de dados das mercadorias em binario*/
	dados_mercadoria = fopen("dados_mercadoria.dat", "rb");
	if(dados_mercadoria != NULL)
	{
		fread(&n_merc, sizeof(int), 1, dados_mercadoria);
		fread(&caixa, sizeof(float), 1, dados_mercadoria);
		fread(mercadoria, sizeof(struct Mercadoria), n_merc, dados_mercadoria);
		fclose(dados_mercadoria);	
	}
	else
	{
		n_merc = 0;
		caixa = 100.0;
	}
		
	/*leitura de dados dos clientes em binario*/
	dados_cliente = fopen("dados_cliente.dat", "rb");
	if(dados_cliente != NULL)
	{
		fread(&n_cliente, sizeof(int), 1, dados_cliente);
		fread(cliente, sizeof(struct Cliente), n_cliente, dados_cliente);
		fclose(dados_cliente);	
	}
	else
		n_cliente = 0;	
	
	if(!mercadoria || !cliente)
		printf("\nMemória insuficiente");
	else
	{
		memoria_mercadoria = N;
		memoria_cliente = N;
		printf("%.2f", caixa);
		
		do{
			system("cls"); //windows
			//system("clear"); //linux
		    printf("\tMENU\n\n");
		    printf("[ 1 ] - Cadastrar mercadoria\n[ 2 ] - Cadastrar cliente\n[ 3 ] - Pesquisar mercadorias\n[ 4 ] - Pesquisar clientes\n[ 5 ] - Lista de mercadorias\n[ 6 ] - Lista de clientes\n[ 7 ] - Vender\n[ 8 ] - Saldo em caixa\n[ 9 ] - Atualizacao de dados\n[ 10 ] - Excluir mercadoria\n[ 11 ] - Excluir cliente\n[ 0 ] - Sair\n>");
		    
			fflush(stdout);
		    scanf("%d", &opNum);
		    fflush(stdin);
		    
			switch(opNum)
			{
		    	case 1:
		    		if(n_merc == memoria_mercadoria)
					{
						n_merc += N;	
						mercadoria = (struct Mercadoria *) realloc(mercadoria, memoria_mercadoria * sizeof(struct Mercadoria)); // realocação da memoria de mercadoria
						
						if(!mercadoria) //testando a realocação
							printf("\nMemória insuficiente");
						else
						{
							if(num_mercadoria == MAX)
								printf("\nNão é possível cadastrar mais mercadorias");
							else
								cadastromercadorias(mercadoria, &n_merc, caixa);	
						}
					}
					else
						cadastromercadorias(mercadoria, &n_merc, caixa);
		    	break;
		    	
		    	case 2:
		    		if(n_cliente == memoria_cliente)
					{
						n_cliente += N;	
						cliente = (struct Cliente *) realloc(cliente, memoria_cliente * sizeof(struct Cliente)); // realocação da memoria de cliente
						
						if(!cliente) //testando a realocação
							printf("\nMemória insuficiente");
						else
						{
							if(n_cliente == MAX)
								printf("\nNão é possível cadastrar mais mercadorias");
							else
								cadastrocliente(cliente, &n_cliente);
						}
					}
					else
						cadastrocliente(cliente, &n_cliente);
		    	break;
		    	
		    	case 3:
		    		pesquisamercadorias(mercadoria, n_merc, caixa);
		    		break;
		    	case 4:
		    		pesquisaclientes(cliente, n_cliente);
		    		break;
		    	case 5:
		    		listamercadorias(mercadoria, n_merc, caixa);
		    		break;
		    	case 6:
		    		listaclientes(cliente, n_cliente);
		    		break;
		    	case 7:
	                vender(mercadoria, n_merc, caixa);
		    		break;
		    	case 8:
	                saldo(mercadoria, n_merc, caixa);
		    		break;
		    	case 9: 
		    		atualizacaodedados(mercadoria, n_merc, caixa);
		    		break;
		    	case 10:
		    		excluirmercadoria(mercadoria, n_merc, caixa);
		    		break;
		    	case 11:
		    		excluircliente(cliente, n_cliente);
		    		break;
		    	case 0:
		    		system("exit");
		    	    break;
		    	default:
		    		printf("Opcao invalida. ");
		    		getchar();
		    		break;
			}
	    
		}while(opNum != 0);
	}	
	return 0;
}
