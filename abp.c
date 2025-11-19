#include <stdio.h>
#include <stdlib.h>
#include "abp.h"

NodoABP* inicializa(NodoABP *a)
{
    return NULL;
}

int ContaNodos(NodoABP *a)
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

void imprimeArvore(NodoABP *a, int nivel)
{

    //int nivel_local = nivel;
  
    if (a != NULL)
    {
        for(int i = 0; i < nivel; i++)
            printf("=");
        printf("%d\n", a->nome);
        nivel++;
        imprimeArvore(a->esq, nivel);
        imprimeArvore(a->dir, nivel);
    }

}

int AchaNivel(NodoABP *a, int k, int nivel)
{
    
    if(a == NULL)
        return 0;

    else
    {


        if(a->nome == k)
            return nivel;

        nivel++;

        if(a->nome < k)
        {
            return AchaNivel(a->dir, k, nivel);
        }

        else if(a->nome > k)
        {
            return AchaNivel(a->esq, k, nivel);
        }  

    }

}

int MenorAncestralComum(NodoABP *a, int c1, int c2)
{
    

    if(a!=NULL)
    {

        if(c1 > a->nome && c2 > a->nome)
        {
            return MenorAncestralComum(a->dir, c1, c2);
        }

        else if(c1 < a->nome && c2 < a->nome)
        {
            return MenorAncestralComum(a->esq, c1, c2);
        }  

        else
            return a->nome;

    }

}

NodoABP *InsereArvore(NodoABP *a, int ch)
{
    if (a == NULL)
    {
        a = (NodoABP *)malloc(sizeof(NodoABP));
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

void PreFixado(NodoABP *a)
{
    if (a != NULL)
    {
        printf("%d\n", a->nome);
        PreFixado(a->esq);
        PreFixado(a->dir);
    }
}
