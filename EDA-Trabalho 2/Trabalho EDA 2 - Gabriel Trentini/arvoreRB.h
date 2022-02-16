/*
#############################################################################################################
#############################################################################################################
#############################################################################################################

##### Nome: Gabriel Silveira Trentini  ######################################################################
##### Matricula: 404497                ######################################################################

#############################################################################################################
#############################################################################################################
#############################################################################################################
*/

typedef struct NO* ArvRB;

ArvRB* criar_ArvRB();

void destruir_ArvRB(ArvRB *raiz);

void destruir_NO(struct NO* no);

int verificar_ArvRB_estaVazia(ArvRB *raiz);

int verificar_NO_estaVazia(struct NO* no);

struct NO* verificar_NO(int info, struct NO* no);

int cor(struct NO* no);

void troca_cor(struct NO* no);

struct NO* rotacao_esquerda(struct NO* no);

struct NO* rotacao_direita(struct NO* no);

void inserir_NO(struct NO* raiz, struct NO* no);

void inserir_NO_ArvRB(struct NO* no);

void insereRB(int info,struct NO* no);

void passo_Esq(struct NO* atual, struct NO* pai, struct NO* avo);

void passo_Dir(struct NO* atual, struct NO* pai, struct NO* avo);

struct NO* passoCER(struct NO* no, struct NO* raiz);

struct NO* passoCER_esq(struct NO* no, struct NO* raiz);

struct NO* passoCER_dir(struct NO* no, struct NO* raiz);

int revomeRB(ArvRB *raiz, int info);

struct NO* remove_NO(struct NO* no, int info);

struct NO* procurarMenor(struct NO* no);