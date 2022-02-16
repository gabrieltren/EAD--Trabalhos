#include <stdio.h>
#include <stdlib.h>
#include "ArvoreAVL.h"

struct NO
{
    int valor;
    int alt;
    struct NO *esq;
    struct NO *dir;
};

ArvAVL *raiz;

int altura_NO(struct NO *no)
{
    if (no == NULL)
        return -1;
    else
        return no->alt;
}

int balanceamento_NO(struct NO *no)
{
    return labs(altura_NO(no->esq) - altura_NO(no->dir));
}

int maior(int x, int y)
{
    if (x > y)
        return x;
    else
        return y;
}

void rotacaoLL(ArvAVL *raiz)
{
    struct NO *no;
    no = (*raiz)->esq;
    (*raiz)->esq = no->dir;
    no->dir = *raiz;
    (*raiz)->alt = maior(altura_NO((*raiz)->esq), altura_NO((*raiz)->dir)) + 1;

    no->alt = maior(altura_NO(no->esq), altura_NO(no->dir)) + 1;

    *raiz = no;
}

void rotacaoRR(ArvAVL *raiz)
{
    struct NO *no;
    no = (*raiz)->dir;
    (*raiz)->dir = no->esq;
    no->esq = (*raiz);
    (*raiz)->alt = maior(altura_NO((*raiz)->esq), altura_NO((*raiz)->dir)) + 1;
    no->alt = maior(altura_NO(no->esq), altura_NO(no->dir)) + 1;

    (*raiz) = no;
}

void rotacaoLR(ArvAVL *raiz)
{
    rotacaoRR(&(*raiz)->esq);
    rotacaoLL(raiz);
}

void rotacaoRL(ArvAVL *raiz)
{
    rotacaoLL(&(*raiz)->dir);
    rotacaoRR(raiz);
}

int add_ArvAVL(ArvAVL *raiz, int valor)
{
    int resp;
    if (*raiz == NULL)
    {
        struct NO *novo;
        novo = (struct NO *)malloc(sizeof(struct NO));
        if (novo == NULL)
            return 0;
        novo->valor = valor;
        novo->alt = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }

    struct NO *atual = *raiz;
    if (valor < atual->valor)
    {
        if ((resp = add_ArvAVL(&(atual->esq), valor)) == 1)
        {
            if (balanceamento_NO(atual) >= 2)
            {
                if (valor < (*raiz)->esq->valor)
                {
                    rotacaoLL(raiz);
                }
                else
                {
                    rotacaoLR(raiz);
                }
            }
        }
    }
    else
    {
        if (valor > atual->valor)
        {
            if ((resp = add_ArvAVL(&(atual->dir), valor)) == 1)
            {
                if (balanceamento_NO(atual) >= 2)
                {
                    if ((*raiz)->dir->valor < valor)
                    {
                        rotacaoRR(raiz);
                    }
                    else
                    {
                        rotacaoRL(raiz);
                    }
                }
            }
        }
        else
        {
            printf("Valor ja existe!!\n");
            return 0;
        }
    }

    atual->alt = maior(altura_NO(atual->esq), altura_NO(atual->dir)) + 1;

    return resp;
}

struct NO *menorNO(struct NO *atual)
{
    struct NO *no1 = atual;
    struct NO *no2 = atual->esq;

    while (no2 != NULL)
    {
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

int rem_ArvAVL(ArvAVL *raiz, int valor)
{
    if (*raiz == NULL)
    {
        printf("Valor nao encontrado!!\n");
        return 0;
    }
    int resp;
    if (valor < (*raiz)->valor)
    {
        if ((resp = rem_ArvAVL(&(*raiz)->esq, valor)) == 1)
        {
            if (balanceamento_NO(*raiz) >= 2)
            {
                if (altura_NO((*raiz)->dir->esq) <= altura_NO((*raiz)->dir->dir))
                    rotacaoRR(raiz);
                else
                    rotacaoRL(raiz);
            }
        }
    }

    if (valor > (*raiz)->valor)
    {
        if ((resp = rem_ArvAVL(&(*raiz)->dir, valor)) == 1)
        {
            if (balanceamento_NO(*raiz) >= 2)
            {
                if (altura_NO((*raiz)->esq->dir) <= altura_NO((*raiz)->esq->esq))
                    rotacaoLL(raiz);
                else
                    rotacaoLR(raiz);
            }
        }
    }

    if (valor == (*raiz)->valor)
    {
        if (((*raiz)->esq == NULL) || ((*raiz)->dir == NULL)){
            struct NO *noRem = (*raiz);
            if ((*raiz)->esq != NULL)
                *raiz = (*raiz)->esq;
            else
                *raiz = (*raiz)->dir;
            free(noRem);
            return 1;
        }
        else{
            struct NO *temp = menorNO((*raiz)->dir);
            (*raiz)->valor = temp->valor;
            rem_ArvAVL(&(*raiz)->dir, (*raiz)->valor);
            if (balanceamento_NO(*raiz) >= 2){
                if (altura_NO((*raiz)->esq->esq))
                    rotacaoLL(raiz);
                else
                    rotacaoLR(raiz);
            }
        }
        return 1;
    }
    return resp;
}

ArvAVL *criar_ArvAVL(){
    ArvAVL *raiz = (ArvAVL *)malloc(sizeof(ArvAVL));
    if (raiz != NULL)
    {
        *raiz = NULL;
    }
    return raiz;
}

void destruir_NO(struct NO *no){
    if (no == NULL)
        return;
    destruir_NO(no->esq);
    destruir_NO(no->dir);
    free(no);
    no = NULL;
}

void destruir_ArvAVL(ArvAVL *raiz)
{
    if (raiz == NULL)
        return;
    destruir_NO((*raiz));
    free(raiz);
}

void imprimir_AvrAVL(ArvAVL *raiz){
    printf("%d\n", (*raiz)->valor);
    imprimir_NO((*raiz)->esq);
    imprimir_NO((*raiz)->dir);
}

void imprimir_NO(struct NO *no){
    printf("   %d\n", no->valor);
    imprimir_NO(no->esq);
    imprimir_NO(no->dir);
}
