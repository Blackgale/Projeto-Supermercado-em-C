#ifndef _MERCADORIA_H
#define _MERCADORIA_H

struct Mercadoria
{
	char nomemercadoria[100];
	int codigomercadoria;
	int qtdmercadoria;
	float precomercadoria;
};

void cadastromercadorias(struct Mercadoria*, int*, float); //cadastro de mercadorias
void pesquisamercadorias(struct Mercadoria*, int, float); //pesquisar entre mercadorias cadastradas
void listamercadorias(struct Mercadoria*, int, float); //lista de mercadorias cadastradas
void vender(struct Mercadoria*, int, float); //venda de um produto e atualiza��o do estoque e caixa ap�s a venda
void saldo(struct Mercadoria*, int, float); //mostra o quanto de dinheiro temos no caixa
void atualizacaodedados(struct Mercadoria*, int, float); //atualiza��o de pre�o e quantidade de qualquer produto
void excluirmercadoria(struct Mercadoria*, int, float); //remo��o de produtos

#endif
