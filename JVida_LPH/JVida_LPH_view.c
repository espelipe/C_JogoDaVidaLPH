/*
Projeto Jogo da Vida
JVida-LPH

Grupo: Mateus Neves Eredia, Felipe Casagrande Espel, Joao Marcos Ribeirete Garbelini, Murilo Bonventi Romani Pinto
*/

#include "JVida_LPH_model.h"
#include "JVida_LPH_controller.h"
#include <stdio.h>

int Menu()
{

	int opc;

	printf("\n ----Jogo da Vida LPH----\n");
	printf("\n 1 - Apresentar mundo");
	printf("\n 2 - Definir os seres vivos da primeira geracao");
	printf("\n 3 - Limpar a matriz do mundo");
	printf("\n 4 - Mostrar listas");
	printf("\n 5 - Mostrar/esconde as celulas mortas-vizinhas");
	printf("\n 6 - Gravar Celulas");
	printf("\n 7 - Recuperar Celulas");
	printf("\n 0 - Sair\n");
	scanf("%d", &opc);

	return (opc);
}

void tamanhoMundo()
{
	Iniciar = 0;
	do
	{

		printf("digite o tamanho desejado do mundo (min:10, max:60 )\n");
		scanf("%d", &tamanho);

		if (tamanho < 10 || tamanho > 60)
		{
			printf("O tamanho de mundo exigido esta fora dos parametros pre-requisitados\n");
			continue;
		}
		else
			gerarmundo();

	} while (tamanho < 10 || tamanho > 60);
}

void primeiraGeracao()
{

	int i, j;
	int homemdoC;
	Iniciar = 1;
	do
	{

		printf("\nDigite a coordenada desejada, separado por virgula (-1,-1 para sair): ");
		scanf("%d,%d", &i, &j);

		if (i != -1 && j != -1)
		{

			if (i < 0 || i >= tamanho || j < 0 || j >= tamanho)
			{
				printf("A posicao especificada nao existe no mundo \n");
				continue;
			}
		}
		else
			break;

		// condicao criada caso haja a escolha de uma opcao invalida
		if (mundo[i][j] == 'O')
		{
			printf("Ja ha uma celula nesta posicao, deseja exclui-la? (0 nao, 1 sim) \n");
			scanf("%d", &homemdoC);

			if (homemdoC == 1)
			{
				mundo[i][j] = '.';
				excVivosLista(i, j);
				apresentamundo();
			}
		}
		else
		{
			mundo[i][j] = 'O';
			printf("Celula posicionada com sucesso!\n");
			AddLista(i, j);
			apresentamundo();
			CarregaMortosVizinhos(i, j);
		}

	} while (i != -1 || j != -1);
}

// impressao da matriz
void apresentamundo()
{

	int i, j;

	printf("        ");
	for (j = 0; j < tamanho; j++)
		printf("%2d ", j);
	printf("\n\n");

	for (i = 0; i < tamanho; i++)
	{
		printf("%2d :\t", i);
		for (j = 0; j < tamanho; j++)
			printf(" %c ", mundo[i][j]);
		printf("\n");
	}
}

void caso0()
{

	printf("Obrigado por jogar!\n");
}

void limpou()
{
	printf("Mundo limpo! \n");
}

void opcInval()
{
	printf("Opcao invalida \n");
}

void semespaco()
{
	printf("Sem espa�o na memoria para inclusao de celula viva\n");
}

void ListaVivos()
{
	TipoCel *aux; // cria e inicializa um ponteiro auxiliar
	aux = pvivo;
	if (totvivo > 0)
	{
		printf("Lista dos vivos:");
		NovaLinha();

		while (aux->next != NULL)
		{
			printf("%d,%d   ", aux->lin, aux->col);
			aux = aux->next;
		}
		printf("%d,%d   ", aux->lin, aux->col);
	}

	printf("\n");
}

void ListaMortos()
{

	TipoCel *aux; // cria e inicializa um ponteiro auxiliar
	aux = pmorto;
	if (totmorto > 0)
	{
		printf("Lista dos mortos:");
		NovaLinha();

		while (aux->next != NULL)
		{
			printf("%d,%d   ", aux->lin, aux->col);
			aux = aux->next;
		}
		printf("%d,%d   ", aux->lin, aux->col);
	}

	printf("\n");
}

void espel()
{

	TipoCel *aux; // cria e inicializa um ponteiro auxiliar
	aux = pmorto;
	if (totmorto > 0)
	{
		while (aux->next != NULL)
		{
			mundo[aux->lin][aux->col] = '+';
			aux = aux->next;
		}
		mundo[aux->lin][aux->col] = '+';
	}

	printf("\n");
}

void marco()
{

	TipoCel *aux; // cria e inicializa um ponteiro auxiliar
	aux = pmorto;
	if (totmorto > 0)
	{
		while (aux->next != NULL)
		{
			mundo[aux->lin][aux->col] = '.';
			aux = aux->next;
		}
		mundo[aux->lin][aux->col] = '.';
	}

	printf("\n");
}

void NovaLinha()
{
	printf("\n");
}

