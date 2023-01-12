/*
Projeto Jogo da Vida
JVida-LPH

Grupo: Mateus Neves Eredia, Felipe Casagrande Espel, Joao Marcos Ribeirete Garbelini, Murilo Bonventi Romani Pinto
*/

// salvamento da matriz e alocamento do espaco utilizado pela matriz

char mundo[60][60];
int Iniciar;
int tamanho;

typedef struct cel
{
    int lin, col;
    struct cel *next;
    
} TipoCel;

TipoCel *pvivo, *pmorto, *pvivoprox;
int totvivo, totmorto, totvivoprox;
