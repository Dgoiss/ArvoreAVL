#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define true 1
#define false 0

typedef int bool;
typedef char TIPOCHAVE[256];

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
    strcpy(novo_no->chave, ch);
    novo_no->esq = novo_no->dir = NULL;
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
    if(strcmp(ch,raiz->chave)<0)
    {
        raiz->esq = Inserir(raiz->esq, ch);
        if((altura(raiz->esq))-(altura(raiz->dir))==2)
        {
            if(strcmp(ch,raiz->esq->chave) < 0) raiz = RotacaoDireita(raiz);
            
            else EsquerdaDireita(raiz);
        }
    }
    
    else
    {
        if(strcmp(ch,raiz->chave)>0)
        {
            raiz->dir = Inserir(raiz->dir, ch);
            if((altura(raiz->dir))-(altura(raiz->esq))==2)
            {
                if(strcmp(ch,raiz->dir->chave) > 0) raiz = RotacaoEsquerda(raiz);
                
                else DireitaEsquerda(raiz);
            }
        }
    }
    raiz->h = max(altura(raiz->esq), altura(raiz->dir)) + 1;
    
    return (raiz);
}

void desenhaArvoreBonita(PONT raiz, char *prefixo, int ehUltimo) {
    if (raiz == NULL) return;

    printf("%s", prefixo);
    printf("%s", ehUltimo ? "└── " : "├── ");
    printf("%s\n", raiz->chave);

    char novoPrefixo[1000];
    strcpy(novoPrefixo, prefixo);
    strcat(novoPrefixo, ehUltimo ? "    " : "│   ");

    int temEsq = (raiz->esq != NULL);
    int temDir = (raiz->dir != NULL);

    if (temDir)
        desenhaArvoreBonita(raiz->dir, novoPrefixo, !temEsq && !temDir);

    if (temEsq)
        desenhaArvoreBonita(raiz->esq, novoPrefixo, 1);
}

int main()
{
    PONT r = Inicializa();
    
    r = Inserir(r, "feijao");
    r = Inserir(r, "morango");
    r = Inserir(r, "banana");
    r = Inserir(r, "abacate");
    r = Inserir(r, "laranja");
    
    printf("Árvore AVL (bonita):\n");
    desenhaArvoreBonita(r, "", 1);
    
    return 0;
}
