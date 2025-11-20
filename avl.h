#ifndef HEADERFILE_AVL_H
#define HEADERFILE_AVL_H

int comp2 = 0;

typedef struct NodoAVL {
    char *nome;
    float horas;
    int FB;
    struct NodoAVL *esq;
    struct NodoAVL *dir;
} NodoAVL;

NodoAVL* inicializaAVL(NodoAVL *a);
int ContaNodosAVL(NodoAVL *a);
void imprimeArvoreAVL(NodoAVL *a, int nivel);
NodoAVL* rotacao_direita(NodoAVL* p);
NodoAVL* rotacao_esquerda(NodoAVL *p);
NodoAVL* rotacao_dupla_direita (NodoAVL* p);
NodoAVL* rotacao_dupla_esquerda (NodoAVL *p);
NodoAVL* InsereAVL (NodoAVL *a, char *x, float horas, int *ok, int *rot);
NodoAVL* Caso1 (NodoAVL *a , int *ok);
NodoAVL* Caso2 (NodoAVL *a , int *ok);
NodoAVL* Maior( NodoAVL* r );
NodoAVL* RemoveAVL (int X, NodoAVL* T );
int Altura (NodoAVL *a);
void FBArvore(NodoAVL *a, int *maior);
int FBNodo(NodoAVL *a);
NodoAVL* consultaAVL(NodoAVL *a, char *chave);


#endif
