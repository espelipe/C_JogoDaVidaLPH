/*
Projeto Jogo da Vida
JVida-LPH

Grupo: Mateus Neves Eredia, Felipe Casagrande Espel, Joao Marcos Ribeirete Garbelini, Murilo Bonventi Romani Pinto
*/

#include "JVida_LPH_model.h"
#include "JVida_LPH_controller.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// funcao para criacao do mundo
void gerarmundo()
{

	int i, j;

	for (i = 0; i < tamanho; i++)
		for (j = 0; j < tamanho; j++)
			mundo[i][j] = '.';
}

// opcoes de inicio do jogo
void menuInicio()
{

	int csm;

	do
	{

		csm = Menu();

		switch (csm)
		{

		case 1:
			apresentamundo();
			break;

		case 2:
			apresentamundo();
			primeiraGeracao();
			break;

		case 3:
		if(Iniciar == 1)
		{
			gerarmundo();
			Lista();
			Lista2();
			limpou();
			apresentamundo();
			Iniciar = 0;
		}
		else
		{
			Lista();
			apresentamundo();
		}	
			break;

		case 4:
			if(Iniciar == 1)
			{
			ListaVivos();
			ListaMortos();
			}
			else
			{
			Lista2();
			}
			break;
		case 5:
			espel();
			apresentamundo();
			marco();
			break;

		case 6:
			gravarCel();
			break;

		case 7:
			recuperaCel();
			break;

		case 0:
			caso0();
			break;

		default:
			opcInval();
			break;
		}
	} while (csm != 0);
}

void AddLista(int ii, int jj)
{
	TipoCel *aux = malloc(sizeof(TipoCel)); // aloca��o din�mica
	if (aux == NULL)
	{
		semespaco();
		return;
	}
	// carrega os dados da c�lula:  ii e jj
	aux->lin = ii;
	aux->col = jj;
	// sempre inclui no in�cio da listaporque neste caso a ordem n�o importa
	if (totvivo == 0) // se a lista est� vazia
	{
		pvivo = aux;
		pvivo->next = NULL;
	}
	else // lista n�o vazia
	{
		aux->next = pvivo;
		pvivo = aux; // o inicio da lista passa a ser a nova celula
	}
	totvivo++;
}

// A fun��o a seguir � destinada para que conforme o usu�rio interaja com a fun��o de alocar, o mesmo possa remover da lista os elementos que foram retirados
void excVivosLista(int ii, int jj)
{
	TipoCel *aux, *aux2;

	aux = pvivo;
	aux2 = aux;

	if (totvivo > 0)
	{
		while (aux->lin != ii || aux->col != jj)
		{
			aux2 = aux;
			aux = aux->next;
		}
		if (aux->lin == ii && aux->col == jj)
		{
			if (aux2 == aux) //� o primeiro da lista
				pvivo = aux->next;
			else
				aux2->next = aux->next;
			free(aux);
		}
		totvivo--;
	}
}

// funcao para remover alocacoes passadas
void Lista()
{
	TipoCel *aux;

	aux = pvivo;

	while (aux <= totvivo)
	{
		free(aux);
		aux = aux->next;
	}

	totvivo = 0;
	aux = aux->next;
	free(aux);

	printf("\n");
}

void Lista2()
{
	TipoCel *aux;

	aux = pmorto;

	if (totmorto > 0)
	{

		while (aux <= totmorto)
		{
			free(aux);
			aux = aux->next;
		}
		totmorto = 0;

		aux = aux->next;
		free(aux);

		printf("\n");
	}
}

void carrega1morto(int lin, int col)
{

	if ((lin >= 0 && lin < tamanho) && (col >= 0 && col < tamanho) && (mundo[lin][col] != 'O'))
	{
		if (comparacursor(lin, col) == 1)

			AddListaMortos(lin, col);
	}
}

// Carrega celulas vizinhas mortas
void CarregaMortosVizinhos(int ii, int jj)
{

	Lista2();

	TipoCel *aux = pvivo;

	while (aux->next != NULL)
	{

		carrega1morto(aux->lin + 1, aux->col + 1);
		carrega1morto(aux->lin + 1, aux->col - 1);
		carrega1morto(aux->lin - 1, aux->col + 1);
		carrega1morto(aux->lin + 1, aux->col);
		carrega1morto(aux->lin, aux->col + 1);
		carrega1morto(aux->lin - 1, aux->col);
		carrega1morto(aux->lin, aux->col - 1);
		carrega1morto(aux->lin - 1, aux->col - 1);

		aux = aux->next;
	}
	carrega1morto(aux->lin + 1, aux->col + 1);
	carrega1morto(aux->lin + 1, aux->col - 1);
	carrega1morto(aux->lin - 1, aux->col + 1);
	carrega1morto(aux->lin + 1, aux->col);
	carrega1morto(aux->lin, aux->col + 1);
	carrega1morto(aux->lin - 1, aux->col);
	carrega1morto(aux->lin, aux->col - 1);
	carrega1morto(aux->lin - 1, aux->col - 1);
}

// funcao para adicao de mortos a uma lista de celulas mortas
void AddListaMortos(int ii, int jj)
{

	TipoCel *aux = malloc(sizeof(TipoCel));
	if (aux == NULL)
	{
		semespaco();
		return;
	}

	aux->lin = ii;
	aux->col = jj;

	if (totmorto == 0)
	{
		pmorto = aux;
		pmorto->next = NULL;
	}
	else
	{
		aux->next = pmorto;
		pmorto = aux;
	}
	totmorto++;
}

// funcao para comparar espacos disponiveis da matriz e detectar se ha mortos em certas posicoes
int comparacursor(int lin, int col)
{

	TipoCel *aux = pmorto;

	if (totmorto == 0)
		return 1;

	else
	{

		while (aux->next != NULL)
		{
			if ((aux->col == col) && (aux->lin == lin))
				return 0;

			aux = aux->next;
		}
		if ((aux->col == col) && (aux->lin == lin))
			return 0;

		else
			return 1;
	}
}

void gravarCel()
{
	int i, j;

	FILE *fp;

	if ((fp = fopen("CONFIG_INIC", "w")) == NULL)
	{
		printf("Erro 1");
	}

	for (i = 0; i < tamanho; i++)
	{
		for (j = 0; j < tamanho; j++)
		{
			if (fwrite(&mundo[i][j], sizeof(mundo), 1, fp) != 1)
			{
				printf("Erro 2");
				break;
			}
		}
	}

	fclose(fp);

	if ((fp = fopen("Tamanho", "w")) == NULL)
	{
		printf("Erro 3");
	}

	if (fwrite(&tamanho, sizeof(tamanho), 1, fp) != 1)
	{
		printf("Erro 4");
		return 1;
	}
}

void recuperaCel()
{
	int i, j;

	if(Iniciar==1)
	{
	gerarmundo();
	Lista();
	Lista2();
	}

	FILE *fp;

	if ((fp = fopen("Tamanho", "r")) == NULL)
	{
		printf("Erro 5");
	}

	if (fread(&tamanho, sizeof(tamanho), 1, fp) != 1)
	{
		printf("Erro 6");
	}
	fclose(fp);

	if ((fp = fopen("CONFIG_INIC", "r")) == NULL)
	{
		printf("Erro 7");
	}

	for (i = 0; i < tamanho; i++)
	{
		for (j = 0; j < tamanho; j++)
		{
			if (fread(&mundo[i][j], sizeof(mundo), 1, fp) != 1)
			{
				printf("Erro 2");
				break;
			}
		}
	}

	fclose(fp);

	for (i = 0; i < tamanho; i++)
	{
		for (j = 0; j < tamanho; j++)
		{
			if (mundo[i][j] == "O")
			{
				AddLista(i, j);
				CarregaMortosVizinhos(i, j);
			}
		}
	}
}

