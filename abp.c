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

void imprimeArvoreABP(NodoABP *a, int nivel)
{

    //int nivel_local = nivel;
  
    if (a != NULL)
    {
        for(int i = 0; i < nivel; i++)
            printf("=");
        printf("%s\n", a->nome);
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

NodoABP *InsereArvore(NodoABP *a, char *ch, float horas)
{
    if (a == NULL)
    {
        a = (NodoABP *)malloc(sizeof(NodoABP));
        a->nome = ch;
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

    int i = 0;

    char auxNome[100];

    printf("---------------------------------ABP-------------------------------\n");

    while(a != NULL) {

        strcpy(auxNome, a->nome);

        while (auxNome[i] != '\0') {
            auxNome[i] = toupper(auxNome[i]); // Converte o caractere na posição i
            i++;
        }

        printf("%s\n", auxNome);
        printf("%s\n", chave);

        comp1++;

        if(!strcmp(auxNome, chave)) {
            return a;
        } else {
            if(strcmp(auxNome, chave) > 0)
                a = a->esq;
            else
                a = a->dir;
        }
    }

    return NULL;
   
}