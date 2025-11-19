#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

NodoAVL* inicializa(NodoAVL *a)
{
    return NULL;
}

int ContaNodos(NodoAVL *a)
{
    int dir, esq;

    if (a == NULL)
    {
        return 0;
    }

    else
    {
        return 1 + ContaNodos(a->esq) + ContaNodos(a->dir);

    }

}

NodoAVL *InsereArvore(NodoAVL *a, int ch)
{
    if (a == NULL)
    {
        a = (NodoAVL *)malloc(sizeof(NodoAVL));
        a->nome = ch;
        a->esq = NULL;
        a->dir = NULL;
    }
    else if (ch < a->nome)
        a->esq = InsereArvore(a->esq, ch);
    else
        a->dir = InsereArvore(a->dir, ch);
    return a;
}

void imprimeArvore(NodoAVL *a, int nivel)
{

    int nivel_local = nivel;
  
    if (a != NULL)
    {
        for(int i = 0; i < nivel; i++)
            printf("=");
        printf("%d\n", a->nome);
        nivel_local++;
        imprimeArvore(a->esq, nivel_local);
        imprimeArvore(a->dir, nivel_local);
    }

}

void PreFixado(NodoAVL *a)
{
    if (a != NULL)
    {
        printf("%d\n", a->nome);
        PreFixado(a->esq);
        PreFixado(a->dir);
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

NodoAVL* InsereAVL (NodoAVL *a, int x, int *ok)
{
    /* Insere nodo em uma árvore AVL, onde A representa a raiz da árvore,
    x, a chave a ser inserida e h a altura da árvore */
    if (a == NULL) {
        a = (NodoAVL*) malloc(sizeof(NodoAVL));
        a->nome = x;
        a->esq = NULL;
        a->dir = NULL;
        a->FB = 0;
        *ok = 1;
    }

    else if (x < a->nome) {

        a->esq = InsereAVL(a->esq,x,ok);
        
        if (*ok) {

            switch (a->FB) 
            {
                case -1: a->FB = 0; *ok = 0; break;
                case 0: a->FB = 1; break;
                case 1: a=Caso1(a,ok); break;
            }
        }
    }

    else 
    {
        a->dir = InsereAVL(a->dir,x,ok);

        if (*ok) 
        {
            switch (a->FB)
            {
                case 1: a->FB = 0; *ok = 0; break;
                case 0: a->FB = -1; break;
                case -1: a = Caso2(a,ok); break;
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

void populaArvore(NodoAVL **a, int vec[], int n)
{

    for(int i = 0; i < n; i++)
    {
        *a = InsereArvore(*a, vec[i]);
    }
}

// TODO
NodoAVL* RemoveAVL (int X, NodoAVL* T )
{
    NodoAVL* TmpCell;

    if( T == NULL )
        printf( "Elemento nao encontrado.\n" );

    else if( X < T->nome ) /* vai para a subarvore esquerda */
        T->esq = RemoveAVL( X, T->esq );

    else if( X > T->nome ) /* vai para a subarvore direita */
        T->dir = RemoveAVL( X, T->dir );

    else  /* achou o elemento a ser removido */

        if( T->esq && T->dir )  /* o elemento tem as 2 subarvores */
        {
            /* substitui pelo maior valor da sub�rvore esquerda */
            TmpCell = Maior( T->esq );
            T->nome = TmpCell->nome;
            T->esq = RemoveAVL( T->nome, T->esq );
        }

        else  /* uma ou nenhuma sub-�rvore */
        {
            TmpCell = T;
            if( T->esq == NULL ) /* substitui pelo filho dir -- se n�o tiver filhos, substitui por NULL*/
                T = T->dir;

            else if( T->dir == NULL )
                T = T->esq; /*substitui pelo filho esq*/

            free( TmpCell );
        }

    return T;
}


