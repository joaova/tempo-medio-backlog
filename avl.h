#ifndef HEADERFILE_H
#define HEADERFILE_H

typedef struct {
    int nome;
    float horas;
    int FB;
    struct NodoAVL *esq;
    struct NodoAVL *dir;
} NodoAVL;

NodoAVL* inicializa(NodoAVL *a);
void PreFixado(NodoAVL *a);
int ContaNodos(NodoAVL *a);
void imprimeArvore(NodoAVL *a, int nivel);
NodoAVL* rotacao_direita(NodoAVL* p);
NodoAVL* rotacao_esquerda(NodoAVL *p);
NodoAVL* rotacao_dupla_direita (NodoAVL* p);
NodoAVL* rotacao_dupla_esquerda (NodoAVL *p);
NodoAVL* InsereAVL (NodoAVL *a, int x, int *ok);
NodoAVL* Caso1 (NodoAVL *a , int *ok);
NodoAVL* Caso2 (NodoAVL *a , int *ok);
NodoAVL* Maior( NodoAVL* r );
NodoAVL* RemoveAVL (int X, NodoAVL* T );
int Altura (NodoAVL *a);
void FBArvore(NodoAVL *a, int *maior);
int FBNodo(NodoAVL *a);
void populaArvore(NodoAVL **a, int vec[], int n);
NodoAVL *InsereArvore(NodoAVL *a, int ch);


#endif
