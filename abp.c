#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "abp.h"

int comp1 = 0;

NodoABP* inicializaABP(NodoABP *a)
{
    return NULL;
}

int ContaNodosABP(NodoABP *a)
{
    int dir, esq;

    if (a == NULL)
    {
        return 0;
    }

    else
    {
        return 1 + ContaNodosABP(a->esq) + ContaNodosABP(a->dir);

    }

}

NodoABP *InsereArvore(NodoABP *a, char *ch, float horas)
{

    if (a == NULL)
    {
        a = (NodoABP *)malloc(sizeof(NodoABP));
        strcpy(a->nome, ch);
        a->horas = horas;
        a->esq = NULL;
        a->dir = NULL;
    }

    else if (strcmp(ch, a->nome) < 0)
        a->esq = InsereArvore(a->esq, ch, horas);

    else
        a->dir = InsereArvore(a->dir, ch, horas);

    return a;
}


NodoABP* consultaABP(NodoABP *a, char *chave)
{

    printf("---------------------------------ABP-------------------------------\n");

    while(a != NULL) {


        printf("%s\n", a->nome);
        printf("%s\n", chave);
        printf("%f\n", a->horas);

        comp1++;

        if(!strcmp(a->nome, chave)) {
            return a;
        } else {
            if(strcmp(a->nome, chave) > 0)
                a = a->esq;
            else
                a = a->dir;
        }
    }

    return NULL;
}

int AlturaABP (NodoABP *a){

    int Alt_Esq, Alt_Dir;

    if (a == NULL)
        return 0;

    else
    {
        Alt_Esq = AlturaABP (a->esq);
        Alt_Dir = AlturaABP (a->dir);

        if (Alt_Esq > Alt_Dir)
            return (1 + Alt_Esq);

        else
            return (1 + Alt_Dir);
    }   
}
 
