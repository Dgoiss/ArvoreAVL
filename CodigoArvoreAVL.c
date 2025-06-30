#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NoAVL
{
    char nome[100];
    struct NoAVL* esquerda;
    struct NoAVL* direita;
    int altura;
}

int Altura(NoAVL* no)
{
    return no ? no->altura : 0;
}

int Maximo(int a, int b)
{
    return (a>b) ? a : b;
}

NoAVL* CriarNo(const char* nome)
{
    NoAVL novo_no = (NoAVL*) malloc (sizeof(NoAVL));
    strcpy(novo_no->nome, nome);
    novo_no->esquerda = novo_no->direita=NULL;
    novo_no->altura = 1;
    
    return novo_no;
}

NoAVL* RotacaoDireita(NoAVL* y)
{
    NoAVL* x = y->esquerda;
    NoAVL* T2 = x->direita;
    
    x->direita = y;
    y->esquerda = T2;
    
    y->altura = Maximo(Altura(y->esquerda), Altura(y->direita)) + 1;
    x->altura = Maximo(Altura(x->esquerda), Altura(x->direita)) + 1;
}

NoAVL* RotacaoEsquerda(NoAVL* x)
{
    NoAVL* y = x->direita;
    NoAVL* T2 = x->esquerda;
    
    y->esquerda = x;
    x->direita = T2;
    
    x->altura = Maximo(Altura(x->esquerda), Altura(x->direita)) + 1;
    y->altura = Maximo(Altura(y->esquerda), Altura(y->direita)) + 1;
}

int FatorBalanceamento

int main()
{
    printf("https://www.youtube.com/watch?v=YkF76cOgtMQ");
    printf("https://www.youtube.com/watch?v=2tXA9-0z4iI");

    return 0;
}