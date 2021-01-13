#ifndef _CLIENTE_H
#define _CLIENTE_H

struct Cliente
{
	char nome[100];
	int codigocliente;	
};

void cadastrocliente(struct Cliente*, int*); //cadastro de clientes
void pesquisaclientes(struct Cliente*, int); //pesquisar entre clientes cadastrados
void listaclientes(struct Cliente*, int); //lista de clientes cadastrados
void excluircliente(struct Cliente*, int); //remoção de clientes

#endif
