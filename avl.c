#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "avl.h"

int comp2 = 0;

NodoAVL* inicializaAVL(NodoAVL *a)
{
    return NULL;
}

int ContaNodosAVL(NodoAVL *a)
{
    int dir, esq;

    if (a == NULL)
    {
        return 0;
    }

    else
    {
        return 1 + ContaNodosAVL(a->esq) + ContaNodosAVL(a->dir);

    }

}

void imprimeArvoreAVL(NodoAVL *a, int nivel)
{

    int nivel_local = nivel;
  
    if (a != NULL)
    {
        for(int i = 0; i < nivel; i++)
            printf("=");
        printf("%s\n", a->nome);
        nivel_local++;
        imprimeArvoreAVL(a->esq, nivel_local);
        imprimeArvoreAVL(a->dir, nivel_local);
    }

}

NodoAVL* rotacao_direita(NodoAVL* p) {

    NodoAVL *u;

    u = p->esq;
    p->esq = u->dir;
    u->dir = p;
    p->FB = 0;
    p = u;

    return p;
}

NodoAVL* rotacao_esquerda(NodoAVL *p) {

    NodoAVL *z;

    z = p->dir;
    p->dir = z->esq;
    z->esq = p;
    p->FB = 0;
    p = z;

    return p;
} 

NodoAVL* rotacao_dupla_direita (NodoAVL* p) {

    NodoAVL *u, *v;

    u = p->esq;
    v = u->dir;
    u->dir = v->esq;
    v->esq = u;
    p->esq = v->dir;
    v->dir = p;

    if (v->FB == 1) 
        p->FB = -1;

    else 
        p->FB = 0;

    if (v->FB == -1) 
        u->FB = 1;

    else 
        u->FB = 0;

    p = v;

    return p;
} 

NodoAVL* rotacao_dupla_esquerda (NodoAVL *p) {

    NodoAVL *z, *y;

    z = p->dir;
    y = z->esq;
    z->esq = y->dir;
    y->dir = z;
    p->dir = y->esq;
    y->esq = p;

    if (y->FB == -1) p->FB = 1;
        else p->FB = 0;
    if (y->FB == 1) z->FB = -1;
        else z->FB = 0;

    p = y;

    return p;
}

NodoAVL* InsereAVL (NodoAVL *a, char *x, float horas, int *ok, int *rot)
{

    
    /* Insere nodo em uma árvore AVL, onde A representa a raiz da árvore,
    x, a chave a ser inserida e h a altura da árvore */
    if (a == NULL) {
        
        a = (NodoAVL*) malloc(sizeof(NodoAVL));
        strcpy(a->nome,x);
        a->horas = horas;
        a->esq = NULL;
        a->dir = NULL;
        a->FB = 0;
        *ok = 1;

    }

    else if (strcmp(x, a->nome) < 0) {

        a->esq = InsereAVL(a->esq,x,horas,ok, rot);
        
        if (*ok) {

            switch (a->FB) 
            {
                case -1: a->FB = 0; *ok = 0; break;
                case 0: a->FB = 1; break;
                case 1: (*rot)++; a=Caso1(a,ok); break;
            }
        }
    }

    else 
    {
        a->dir = InsereAVL(a->dir,x,horas,ok, rot);

        if (*ok) 
        {
            switch (a->FB)
            {
                case 1: a->FB = 0; *ok = 0; break;
                case 0: a->FB = -1; break;
                case -1: (*rot)++; a = Caso2(a,ok); break;
            }
        }

    }

    return a;

}

NodoAVL* Caso1 (NodoAVL *a , int *ok)
{
    NodoAVL *z;

    z = a->esq;

    if (z->FB == 1)
        a = rotacao_direita(a);

    else
        a = rotacao_dupla_direita(a);

    a->FB = 0;

    *ok = 0;

    return a;
}

NodoAVL* Caso2 (NodoAVL *a , int *ok)
{
    NodoAVL *z;

    z = a->dir;

    if (z->FB == -1)
        a = rotacao_esquerda(a);

    else
        a = rotacao_dupla_esquerda(a);

    a->FB = 0;

    *ok = 0;

    return a;
}

NodoAVL* Maior( NodoAVL* r )
{
    if( r != NULL )
        while( r->dir != NULL )
            r = r->dir;

    return r;
}

int Altura (NodoAVL *a){

    int Alt_Esq, Alt_Dir;

    if (a == NULL)
        return 0;

    else
    {
        Alt_Esq = Altura (a->esq);
        Alt_Dir = Altura (a->dir);

        if (Alt_Esq > Alt_Dir)
            return (1 + Alt_Esq);

        else
            return (1 + Alt_Dir);
    }

}

int FBNodo(NodoAVL *a)
{

    return abs(Altura(a->esq) - Altura(a->dir));

}

void FBArvore(NodoAVL *a, int *maior)
{

    if (a != NULL)
    {
        int fbNodo = FBNodo(a);
        if(fbNodo > *maior)
            *maior = fbNodo;
        FBArvore(a->esq, maior);
        FBArvore(a->dir, maior);
    }

}

NodoAVL* consultaAVL(NodoAVL *a, char *chave){ 
    int i = 0;
    int j = 0;
    char chaveUpper[100] = {0}, nomeUpper[100] = {0};
    int cmp;


    while (a != NULL){ 

         while (chave[i] != '\0') {
            chaveUpper[i] = toupper(chave[i]); // Converte o caractere na posição i
            i++;
        }

        while (a->nome[j] != '\0') {
            nomeUpper[j] = toupper(a->nome[j]); // Converte o caractere na posição i
            j++;
        }

        cmp = strcmp(nomeUpper, chaveUpper);

        comp2++; 
        if (cmp == 0){ 
            return a;  
        } else { 
            if (cmp > 0) 
                a = a->esq; 
            else 
                a = a->dir; 
        } 
    } 
    return NULL;  
}

/*
NodoAVL* RemoveAVL (int X, NodoAVL* T )
{
    NodoAVL* TmpCell;

    if( T == NULL )
        printf( "Elemento nao encontrado.\n" );

    else if( X < T->nome ) // vai para a subarvore esquerda 
        T->esq = RemoveAVL( X, T->esq );

    else if( X > T->nome ) // vai para a subarvore direita 
        T->dir = RemoveAVL( X, T->dir );

    else  // achou o elemento a ser removido 

        if( T->esq && T->dir )  // o elemento tem as 2 subarvores 
        {
            // substitui pelo maior valor da sub�rvore esquerda 
            TmpCell = Maior( T->esq );
            T->nome = TmpCell->nome;
            T->esq = RemoveAVL( T->nome, T->esq );
        }

        else  // uma ou nenhuma sub-�rvore 
        {
            TmpCell = T;
            if( T->esq == NULL ) // substitui pelo filho dir -- se n�o tiver filhos, substitui por NULL
                T = T->dir;

            else if( T->dir == NULL )
                T = T->esq; //substitui pelo filho esq

            free( TmpCell );
        }

    return T;
}
*/