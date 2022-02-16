/*
#############################################################################################################
#############################################################################################################
#############################################################################################################

##### Nome: Gabriel Silveira Trentini  ######################################################################
##### Matricula: 404497                ######################################################################

##### Link :https://youtu.be/Il0d7vdFsEI

#############################################################################################################
#############################################################################################################
#############################################################################################################
*/


#include <stdio.h>
#include <stdlib.h>
#include "arvoreRB.h"

// Definindo as cores
#define RED 1
#define BLACK 0

struct NO{
    int info;
    struct NO *pai; 
    struct NO *esq;
    struct NO *dir;
    int cor;
};

ArvRB* raiz;

ArvRB* criar_ArvRB(){
    ArvRB* raiz = (ArvRB*)malloc(sizeof(ArvRB));
    if(raiz!=NULL){
        *raiz = NULL;
    }
    return raiz;
}

void destruir_ArvRB(ArvRB *raiz){
    if(raiz==NULL){
        return;
    }
    destruir_NO(*raiz);
    free(raiz);
}

void destruir_NO(struct NO* no){
    if(no==NULL){
        return;
    }
    destruir_NO(no->esq);
    destruir_NO(no->dir);
    destruir_NO(no->pai);
    free(no);
    no = NULL;
}

/*Verifica se a Arvore ja tem Elementos*/
int verificar_ArvRB_estaVazia(ArvRB *raiz){
    if(raiz == NULL){
        return 1;
    }
    if(*raiz == NULL){
        return 1;
    }

    return 0;

}

/*Verifica se o No que eu recebir e nullo ou nao */
int verificar_NO_estaVazia(struct NO* no){
    if(no == NULL){
        return 1;
    }

    return 0;
}

struct NO* verificar_NO(int info, struct NO* no){
    if(no->info == info){
        return no;
    }else{
        if(no->info > info){
            verificar_NO(info,no->esq);
        }else{
            verificar_NO(info,no->dir);
        }
    }
    return NULL;
}


/* Verifica qual a cor do no, se estiver apontando para nulo retorna Negro*/
int cor(struct NO* no){
    if(no==NULL){
        return BLACK;
    }else{
        return no->cor;
    }
}

void troca_cor(struct NO* no){
    no->cor = !no->cor;
    if(no->esq != NULL){
        no->esq->cor = !no->esq->cor;
    }
    if(no->dir != NULL){
        no->dir->cor = !no->dir->cor;
    }
}

struct NO* rotacao_esquerda(struct NO* no){
    
    int lado; /* so para verificar o lado do pai do no*/
    int esq = 1; /* Valorações para os lados referente*/
    int dir = 0;

    struct NO* pai = no->pai; /* NO auxiliar pai para receber pai do no que vou rota*/
    
    if(pai->esq == no){ /* Verificação de qual lado o filho é*/
        lado = esq;
    }else{
        lado = dir;
    }
    /* Rotação e ajuste do pai*/
    struct NO* no2 = no->dir;
    no2->pai = pai;
    no->dir = no2->esq;
    no->dir->pai = no;
    no2->esq = no;
    no->esq->pai = no2;

    /*Ajustar pai*/
    if (lado == esq){
        pai->esq = no2;
    }else{
        pai->dir = no2;
    }
    
    
    return no2;
}

struct NO* rotacao_direita(struct NO* no){
    
    int lado; /* so para verificar o lado do pai do no*/
    int esq = 1; /* Valorações para os lados referente*/
    int dir = 0;

    struct NO* pai = no->pai; /* NO auxiliar pai para receber pai do no que vou rota*/
    
    if(pai->esq == no){ /* Verificação de qual lado o filho é*/
        lado = esq;
    }else{
        lado = dir;
    }

    /* Rotação e ajuste do pai*/
    struct NO* no2 = no->esq;
    no2->pai = pai;
    no->esq = no2->dir;
    no->esq->pai = no;
    no2->dir = no;
    no->dir->pai = no2;

    /*Ajustar pai*/
    if (lado == esq){
        pai->esq = no2;
    }else{
        pai->dir = no2;
    }


    return no2;
}

/*Insere um NO*/
void inserir_NO(struct NO* raiz, struct NO* no){
    if( verificar_NO_estaVazia(raiz) ){
        no->cor = RED;
        raiz = no;
    }else{
        if(raiz->info > no->info){
            no->pai = raiz;
            inserir_NO(raiz->esq,no);
        }else{
            no->pai = raiz;
            inserir_NO(raiz->esq,no);
        }
    }
}

/*Insere um NO na arvoreRB*/
void inserir_NO_ArvRB(struct NO* no){
    if( verificar_ArvRB_estaVazia(*raiz) ){
        no->cor = BLACK;
        (*raiz) = no;
    }else{
        if((*raiz)->info > no->info){
            inserir_NO((*raiz)->esq,no);
        }else{
            inserir_NO((*raiz)->esq,no);
        }

}

/*Inserir no No na Arvore RB*/
void insereRB(int info, struct NO* no){
    if( verificar_ArvRB_estaVazia((*raiz)) ){
        no->info = info;
        inserir_NO_ArvRB(no);
    }else{
        struct NO *pai,*avo,*atual;
        no->info = info;
        inserir_NO_ArvRB(no);

        atual = no;
        while(atual != raiz && atual->pai->cor == RED){
            pai->pai = atual->pai;
            avo = pai->pai;

            if(avo->esq == pai){
                /*Passo Esquerda*/
                passo_Esq(atual,pai,avo)
            }else{
                /*Passo Direita*/
                passo_Dir(atual,pai,avo)
            }

        }
        (*raiz)->cor = BLACK;
    }
}

/*Implemantação do passo Esquerdo*/
void passo_Esq(struct NO* atual, struct NO* pai, struct NO* avo){
    struct NO *tio;

    tio = avo->dir;

    if(tio->cor == RED){ /* caso 1*/
        pai->cor = BLACK;
        avo->cor = RED;
        tio->cor = BLACK;
        atual = avo;         /* Sobe dois niveis*/
    }else{
        if(pai->dir == atual){ /* caso 2*/
            rotacao_esquerda(pai);
            atual = atual->esq; /* Resetando o atual*/
        }
        pai->cor = BLACK;  /* Caso 3*/
        avo->cor = RED;
        rotacao_direita(avo)
    }

}

/*Implemantação do passo Direito*/
void passo_Dir(struct NO* atual, struct NO* pai, struct NO* avo){
    struct NO *tio;

    tio = avo->esq;

    if(tio->cor == RED){ /* caso 1*/
        pai->cor = BLACK;
        avo->cor = RED;
        tio->cor = BLACK;
        atual = avo;         /* Sobe dois niveis*/
    }else{
        if(pai->esq == atual){ /* caso 2*/
            rotacao_direita(pai);
            atual = atual->dir; /* Resetando o atual*/
        }
        pai->cor = BLACK;  /* Caso 3*/
        avo->cor = RED;
        rotacao_esquerda(avo)
    }
}

/*Correção e elevação da Remoção*/
struct NO* passoCER(struct NO* no, struct NO* raiz){
    while(no != raiz){
        if(no == no->pai->esq){
            no = passoCER_esq(no,raiz); /* Esquerda */
        }else{
            no = passoCER_dir(no,raiz); /* Direita */
        }
    }
    return no;

}


struct NO* passoCER_esq(struct NO* no, struct NO* raiz){
    struct NO *aux;
    aux = no->pai->dir; /* Aux recebe o irmao da Direita*/

    if(aux->cor == RED){ /* Caso 1*/
        aux->cor = BLACK;
        no->pai->cor = RED;
        rotacao_esquerda(no->pai);
        aux= no->pai->dir  /*Resete Caso 1*/
    }
    if(aux->esq->cor == BLACK && aux->dir->cor == BLACK){   /* Caso 2*/
        aux->cor = RED;
        no = no->pai;                                      /*Sobe caso 2*/
    }else{
        if(aux->dir->cor == BLACK){     /* Caso 3 */
            aux->esq->cor = BLACK;
            aux->cor = RED;
            rotacao_direita(aux);
            aux = no->pai->dir;
        }
        aux->cor = no->pai->cor; /* Caso 4*/
        no->pai->cor = BLACK;
        aux->dir->cor = BLACK;
        rotacao_esquerda(no->pai);
        no= raiz;
    }
    return no;
}

struct NO* passoCER_dir(struct NO* no, struct NO* raiz){
    struct NO *aux;
    aux = no->pai->esq; /* Aux recebe o irmao da Esquerda*/

    if(aux->cor == RED){ /* Caso 1*/
        aux->cor = BLACK;
        no->pai->cor = RED;
        rotacao_esquerda(no->pai);
        aux= no->pai->esq  /*Resete Caso 1*/
    }
    if(aux->dir->cor == BLACK && aux->esq->cor == BLACK){   /* Caso 2*/
        aux->cor = RED;
        no = no->pai;                                      /*Sobe caso 2*/
    }else{
        if(aux->esq->cor == BLACK){     /* Caso 3 */
            aux->dir->cor = BLACK;
            aux->cor = RED;
            rotacao_esquerda(aux);
            aux = no->pai->esq;
        }
        aux->cor = no->pai->cor; /* Caso 4*/
        no->pai->cor = BLACK;
        aux->esq->cor = BLACK;
        rotacao_direita(no->pai);
        no= raiz;
    }
    return no;
}

int revomeRB(ArvRB *raiz, int info){
    struct NO* no = verificar_NO(info, raiz);
    if(no != NULL){
        struct NO* h = *raiz;

         ac = revome_NO(h,info);
        if(ac != NULL){
            free(ac);
            return 1
        }
    }else{
        return 0;
    }
}

struct NO* revome_NO(struct NO* no, int info){ 
        struct NO* re = verificar_NO(info,(*raiz));
        struct NO* remo = passoCER(re, (*raiz))
        if(remo->info == info){
            no = procurarMenor(raiz){
            raiz->info = no->info; 
            return remo;
            }
        }else{
            return NULL;
        }
}
struct NO* procurarMenor(struct NO* no){
    if(no->esq == NULL){
        if(no->dir != NULL){
            struct NO* guard = no;
            no->pai->esq = no->dir;
            return guard;
        }else{
            struct NO* guard = no;
            no = no->pai;
            no->esq = NULL;
            if(no->pai->cor == RED && no->cor == RED){
                no->cor = BLACK;
            }
            return guard;
        }
    }else{
        procurarMenor(no);
    }

}