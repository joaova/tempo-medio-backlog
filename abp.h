#ifndef HEADERFILE_H
#define HEADERFILE_H

typedef struct {
 int nome;
 float horas;
 struct NodoABP *esq;
 struct NodoABP *dir;
} NodoABP;

NodoABP* inicializa(NodoABP *a);
NodoABP* InsereArvore(NodoABP *a, int ch);
void PreFixado(NodoABP *a);
int ContaNodos(NodoABP *a);
void imprimeArvore(NodoABP *a, int nivel);
int AchaNivel(NodoABP *a, int k, int nivel);
int MenorAncestralComum(NodoABP *a, int c1, int c2);

#endif
