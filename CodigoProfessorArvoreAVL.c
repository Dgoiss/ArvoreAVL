#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0

typedef int bool;
typedef int TIPOCHAVE;

typedef struct aux
{
    TIPOCHAVE chave;
    struct aux* esq;
    struct aux* dir;
    int h;
}NO, *PONT;

PONT CriaNo(TIPOCHAVE ch)
{
    PONT novo_no = (PONT) malloc (sizeof(NO));
    novo_no->esq = novo_no->dir = NULL;
    novo_no->chave = ch;
    novo_no-> h = 0;
    
    return(novo_no);
}

PONT Inicializa(){
    return(NULL);
}

int altura(PONT raiz)
{
    if(!raiz) return(-1);
    return(raiz->h);
}

int max(int a, int b){
    return (a>b) ? a : b;
}

PONT RotacaoDireita(PONT r)
{
    PONT aux;
    aux = r->esq;
    r->esq = aux->dir;
    aux->dir = r;
    
    r->h = max(altura(r->dir), altura(r->esq)) + 1;
    aux->h = max(altura(aux->esq), r->h) + 1;
    
    return(aux);
}

PONT RotacaoEsquerda(PONT r)
{
    PONT aux;
    aux = r->dir;
    r->dir = aux->esq;
    aux->esq = r;
    
    r->h = max(altura(r->dir), altura(r->esq)) + 1;
    aux->h = max(altura(aux->dir), r->h) + 1;
    
    return(aux);
}

PONT EsquerdaDireita(PONT r)
{
    r->esq = RotacaoEsquerda(r->esq);
    return(RotacaoDireita(r));
}

PONT DireitaEsquerda(PONT r)
{
    r->dir = RotacaoDireita(r->dir);
    return(RotacaoEsquerda(r));
}

PONT Inserir(PONT raiz, TIPOCHAVE ch)
{
    if(!raiz) return(CriaNo(ch));
    if(ch < raiz->chave)
    {
        raiz->esq = Inserir(raiz->esq, ch);
        if((altura(raiz->esq))-(altura(raiz->dir))==2)
        {
            if(ch < raiz->esq->chave) raiz = RotacaoDireita(raiz);
            
            else raiz = EsquerdaDireita(raiz);
        }
    }
    
    else
    {
        if(ch > raiz->chave)
        {
            raiz->dir = Inserir(raiz->dir, ch);
            if((altura(raiz->dir))-(altura(raiz->esq))==2)
            {
                if(ch > raiz->dir->chave) raiz = RotacaoEsquerda(raiz);
                
                else raiz = DireitaEsquerda(raiz);
            }
        }
    }
    raiz->h = max(altura(raiz->esq), altura(raiz->dir)) + 1;
    
    return (raiz);
}

int main()
{
    PONT r = Inicializa();
    
    return 0;
}
