typedef struct NO* ArvAVL;

int altura_NO(struct NO* no);
int balanceamento_NO(struct NO* no);
int maior(int x, int y);
void rotacaoLL(ArvAVL *raiz);
void rotacaoRR(ArvAVL *raiz);
void rotacaoLR(ArvAVL *raiz);
void rotacaoRL(ArvAVL *raiz);
int add_ArvAVL(ArvAVL *raiz, int valor);
struct NO* menorNO(struct NO* atual);
int rem_ArvAVL(ArvAVL *raiz, int valor);
ArvAVL* criar_ArvAVL();
void destruir_NO(struct NO* no);
void destruir_ArvAVL(ArvAVL* raiz);
void imprimir_AvrAVL(ArvAVL* raiz);
void imprimir_NO(struct NO* no);
void criar_Arvora_Manual();