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

PONT Minimo(PONT raiz)
{
    while (raiz->esq != NULL) raiz = raiz->esq;
    return raiz;
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
        printf("Ja existe um aquivo com o mesmo nome: %s\n", ch);
        return raiz;
    }
    
    raiz->h = max(altura(raiz->esq), altura(raiz->dir)) + 1;
    
    return (raiz);
}

PONT Remover(PONT raiz, TIPOCHAVE ch) {
    if (raiz == NULL) return NULL;

    ParaMinusculo(ch);  // Garante consistência na comparação

    int comp = strcmp(ch, raiz->chave);

    if (comp < 0)
    {
        raiz->esq = Remover(raiz->esq, ch);
    }
    else if (comp > 0)
    {
        raiz->dir = Remover(raiz->dir, ch);
    }
    else
    {
        // Encontrou o nó
        //Caso o tenha 0 ou 1 filho:
        if (raiz->esq == NULL || raiz->dir == NULL)
        {
            PONT temp = raiz->esq ? raiz->esq : raiz->dir;
            free(raiz);
            return temp;
        }
        
        //Caso haja dois:
        else
        {
            PONT sucessor = Minimo(raiz->dir);
            strcpy(raiz->chave, sucessor->chave);
            raiz->dir = Remover(raiz->dir, sucessor->chave);
        }
    }

    // Atualiza altura
    raiz->h = max(altura(raiz->esq), altura(raiz->dir)) + 1;

    // Verifica desbalanceamento
    int fb = altura(raiz->esq) - altura(raiz->dir);

    if (fb > 1)
    {
        if (altura(raiz->esq->esq) >= altura(raiz->esq->dir)) raiz = RotacaoDireita(raiz);
        else raiz = EsquerdaDireita(raiz);
    }
        
    else if (fb < -1)
    {
        if (altura(raiz->dir->dir) >= altura(raiz->dir->esq)) raiz = RotacaoEsquerda(raiz);
        else raiz = DireitaEsquerda(raiz);
    }

    return raiz;
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

void desenhaArvore(PONT raiz, char *prefixo, int ehUltimo) {
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
        desenhaArvore(raiz->dir, novoPrefixo, !temEsq && !temDir);

    if (temEsq)
        desenhaArvore(raiz->esq, novoPrefixo, 1);
}

void ExibirEmOrdem(PONT raiz)
{
    if(!raiz) return;
    
    ExibirEmOrdem(raiz->esq);
    printf("%s ", raiz->chave);
    ExibirEmOrdem(raiz->dir);
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
    PONT t = Inicializa();
    
    TIPOCHAVE temp;
    TIPOCHAVE deletar;

    //Povoando arvore r:
    strcpy(temp, "Feijao.css");
    r = Inserir(r, temp);
    strcpy(temp, "morango.bat");
    r = Inserir(r, temp);
    strcpy(temp, "uva.txt");
    r = Inserir(r, temp);
    strcpy(temp, "banana.js");
    r = Inserir(r, temp);
    strcpy(temp, "abacate.c");
    r = Inserir(r, temp);
    strcpy(temp, "Arroz.html");
    r = Inserir(r, temp);
    strcpy(temp, "Melancia.py");
    r = Inserir(r, temp);
    strcpy(temp, "Feijao.css");
    r = Inserir(r, temp);
    strcpy(temp, "laranja.exe");
    r = Inserir(r, temp);
    
    printf("\nArvore AVL:\n");
    desenhaArvore(r, "", 1);
    
    printf("\nExibicao em ordem alfabetica:\nr: ");
    ExibirEmOrdem(r);
    
    strcpy(temp, "laranja.exe");
    PONT resultado = Buscar(r, temp);
    if(resultado) printf("\n\nBusca: %s\n", resultado->chave);
    else printf("\nNao encontrado!\n");
    
    strcpy(deletar, "morango.bat");
    r = Remover(r, deletar);
    
    printf("\nArvore apos remocao de %s :\n", deletar);
    desenhaArvore(r, "", 1);
    
    printf("\nExibicao em ordem alfabetica:\nr: ");
    ExibirEmOrdem(r);
    
    printf("\n\n--------------------------------------------------\n");
    
    //Povoando arvore t:
    printf("\nArvore t:\n");
    char nomes[][256] = {
        "Feijao.css",
        "morango.bat",
        "uva.txt",
        "banana.js",
        "abacate.c",
        "Arroz.html",
        "Melancia.py",
        "feijao.css",
        "laranja.exe"
    };
    
    int total = sizeof(nomes) / sizeof(nomes[0]);
    for (int i = 0; i < total; i++)
    {
        strcpy(temp, nomes[i]);
        printf("\nInserindo: %s\n", temp);
        t = Inserir(t, temp);
        desenhaArvore(t, "", 1);
    }
    
    printf("\nExibicao em ordem alfabetica:\nt: ");
    ExibirEmOrdem(t);
    
    strcpy(temp, "uva.txt");
    resultado = Buscar(r, temp);
    if(resultado) printf("\n\nBusca: %s\n", resultado->chave);
    else printf("\nNao encontrado!\n");
    
    strcpy(deletar, "morango.bat");
    t = Remover(t, deletar);
    
    printf("\nArvore apos remocao de %s :\n", deletar);
    desenhaArvore(t, "", 1);
    
    printf("\nExibicao em ordem alfabetica:\nt: ");
    ExibirEmOrdem(t);
    
    LiberarArvore(r);
    LiberarArvore(t);
    
    return 0;
}
