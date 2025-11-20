#ifndef HEADERFILE_H
#define HEADERFILE_H

int comp1 = 0;

typedef struct NodoABP {
 char *nome;
 float horas;
 struct NodoABP *esq;
 struct NodoABP *dir;
} NodoABP;

NodoABP* inicializaABP(NodoABP *a);
NodoABP* InsereArvore(NodoABP *a, char *ch, float horas);
int ContaNodosABP(NodoABP *a);
void imprimeArvoreABP(NodoABP *a, int nivel);
int AchaNivel(NodoABP *a, char* nome, int nivel);
char* MenorAncestralComum(NodoABP *a, char *nomeA, char *nomeB);
NodoABP* consultaABP(NodoABP *a, char *chave);

#endif
