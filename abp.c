#include <stdio.h>
#include <stdlib.h>
#include "abp.h"

NodoABP* inicializaABP(NodoABP *a)
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

void imprimeArvoreABP(NodoABP *a, int nivel)
{

    //int nivel_local = nivel;
  
    if (a != NULL)
    {
        for(int i = 0; i < nivel; i++)
            printf("=");
        printf("%d\n", a->nome);
        nivel++;
        imprimeArvoreABP(a->esq, nivel);
        imprimeArvoreABP(a->dir, nivel);
    }

}

int AchaNivel(NodoABP *a, char* nome, int nivel)
{
    
    if(a == NULL)
        return 0;

    else
    {


        if(strcmp(a->nome, nome) == 0)
            return nivel;

        nivel++;

        if(strcmp(a->nome, nome) < 0)
        {
            return AchaNivel(a->dir, nome, nivel);
        }

        else if(strcmp(a->nome, nome) > 0)
        {
            return AchaNivel(a->esq, nome, nivel);
        }  

    }

}

char* MenorAncestralComum(NodoABP *a, char *nomeA, char *nomeB)
{
    

    if(a!=NULL)
    {

        if((strcmp(nomeA, a->nome) > 0) && (strcmp(nomeB, a->nome) > 0))
        {
            return MenorAncestralComum(a->dir, nomeA, nomeB);
        }

        else if((strcmp(nomeA, a->nome) < 0) && (strcmp(nomeB, a->nome) < 0))
        {
            return MenorAncestralComum(a->esq, nomeA, nomeB);
        }  

        else
            return a->nome;

    }

}

NodoABP *InsereArvore(NodoABP *a, char *ch)
{
    if (a == NULL)
    {
        a = (NodoABP *)malloc(sizeof(NodoABP));
        a->nome = ch;
        a->esq = NULL;
        a->dir = NULL;
    }
    else if (strcmp(ch, a->nome) < 0)
        a->esq = InsereArvore(a->esq, ch);
    else
        a->dir = InsereArvore(a->dir, ch);
    return a;
}

