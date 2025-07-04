#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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

void ParaMinusculo(TIPOCHAVE nome)
{
    for(int i=0; nome[i]; i++)
    {
        nome[i] = tolower((unsigned char) nome[i]);
    }
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
    ParaMinusculo(ch);
    
    if(!raiz) return(CriaNo(ch));
    
    if(strcmp(ch,raiz->chave)<0)
    {
        raiz->esq = Inserir(raiz->esq, ch);
        if((altura(raiz->esq))-(altura(raiz->dir))==2)
        {
            if(strcmp(ch,raiz->esq->chave) < 0) raiz = RotacaoDireita(raiz);
            
            else raiz = EsquerdaDireita(raiz);
        }
    }
    
    else if(strcmp(ch,raiz->chave)>0)
    {
        raiz->dir = Inserir(raiz->dir, ch);
        if((altura(raiz->dir))-(altura(raiz->esq))==2)
        {
            if(strcmp(ch,raiz->dir->chave) > 0) raiz = RotacaoEsquerda(raiz);
            
            else raiz = DireitaEsquerda(raiz);
        }
    }
    
    else
    {
        printf("Já existe um aquivo com o mesmo nome: %s", ch);
        return raiz;
    }
    
    raiz->h = max(altura(raiz->esq), altura(raiz->dir)) + 1;
    
    return (raiz);
}

void desenhaArvoreBonita(PONT raiz, char *prefixo, int ehUltimo) {
    if (raiz == NULL) return;

    printf("%s", prefixo);
    printf("%s", ehUltimo ? "-- " : "|-- ");
    printf("%s\n", raiz->chave);

    char novoPrefixo[1000];
    strcpy(novoPrefixo, prefixo);
    strcat(novoPrefixo, ehUltimo ? "   " : "|  ");

    int temEsq = (raiz->esq != NULL);
    int temDir = (raiz->dir != NULL);

    if (temDir)
        desenhaArvoreBonita(raiz->dir, novoPrefixo, !temEsq && !temDir);

    if (temEsq)
        desenhaArvoreBonita(raiz->esq, novoPrefixo, 1);
}

PONT Buscar(PONT raiz, TIPOCHAVE nome)
{
    ParaMinusculo(nome);
    
    if(raiz==NULL) return NULL;
    
    int comp = strcmp(nome, raiz->chave);
    
    if(comp == 0) return raiz;
    else if(comp < 0) return Buscar(raiz->esq, nome);
    else return Buscar(raiz->dir, nome);
}

void LiberarArvore(PONT raiz)
{
    if(!raiz) return;
    LiberarArvore(raiz->esq);
    LiberarArvore(raiz->dir);
    free(raiz);
}

int main()
{
    PONT r = Inicializa();
    
    TIPOCHAVE temp;

    strcpy(temp, "feijao");
    r = Inserir(r, temp);
    strcpy(temp, "Arroz");
    r = Inserir(r, temp);
    strcpy(temp, "Arroz");
    r = Inserir(r, temp);
    strcpy(temp, "morango");
    r = Inserir(r, temp);
    strcpy(temp, "banana");
    r = Inserir(r, temp);
    strcpy(temp, "Melancia");
    r = Inserir(r, temp);
    strcpy(temp, "abacate");
    r = Inserir(r, temp);
    strcpy(temp, "laranja");
    r = Inserir(r, temp);
    strcpy(temp, "Uva");
    r = Inserir(r, temp);
    
    printf("\nÁrvore AVL (bonita):\n");
    desenhaArvoreBonita(r, "", 1);
    
    strcpy(temp, "laranja");
    PONT resultado = Buscar(r, temp);
    if(resultado) printf("\nBusca: %s\n", resultado->chave);
    else printf("Nao encontrado!\n");
    
    PONT t = Inicializa();
    
    char nomes[][256] = {
        "feijao",
        "Arroz",
        "Arroz",
        "morango",
        "banana",
        "Melancia",
        "abacate",
        "laranja",
        "Uva"
    };
    
    int total = sizeof(nomes) / sizeof(nomes[0]);

    for (int i = 0; i < total; i++) {
        strcpy(temp, nomes[i]);
        printf("\nInserindo: %s\n", temp);
        t = Inserir(t, temp);
        printf("Árvore após inserção:\n");
        desenhaArvoreBonita(t, "", 1);
    }
    
    LiberarArvore(r);
    LiberarArvore(t);
    
    return 0;
}
