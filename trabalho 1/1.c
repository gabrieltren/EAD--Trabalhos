#include <stdio.h>
#include <stdlib.h>

int pai_(int x){
    if(x == 0){
        return -1;
    }else{
        return x/2;

    }
}

void heap_Ver(int vet[], int i, int quant){
    int esq, dir, maior, aux;
    maior = i;
    if (2*i+1 <= quant){
        esq = 2*i+1;
        dir = 2*i;
        if (vet[esq] >= vet[dir] && vet[esq] > vet[i]){
            maior = esq;
        }else if (vet[dir] > vet[esq] && vet[dir] > vet[i]){
            maior = dir;
        }
    }else if (2*i <= quant){
        dir = 2*i;
        if (vet[dir] > vet[i]){
            maior = dir;
        }
    }
    if (maior != i){
        aux = vet[i];
        vet[i] = vet[maior];
        vet[maior] = aux;
        heap_Ver(vet,maior,quant);
    }
}

void main(){
    int vet[11];
    int opcao = 0, tam=0, ind, num;

    while(opcao != 5){
        printf("\n LISTA DE PRIORIDADE - HEAP");
        printf("\n 1 - Inserir elemento");
        printf("\n 2 - Consutar elemento de maior prioridade");
        printf("\n 3 - Remover elemento");
        printf("\n 4 - Consultar toda a lista");
        printf("\n 5 - Sair");
        printf("\n Digite a opcao: ");
        
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                if (tam < 10){
                    tam++;
                    printf(" Digite um numero: ");
                    scanf("%d", &num);
                    while (ind > 1 && vet[pai_(ind)] < num){
                        vet[ind] = vet[pai_(ind)];
                        ind = pai_(ind);
                    }
                    vet[ind] =  num;
                    printf(" Numero inserido\n");
                }else{
                    printf("\n Lista cheia\n");
                }
            break;
            case 2:
                if (tam == 0){
                    printf("\n Lista vazia \n");
                }else{
                    printf(" Elemento de maior prioridade: %d", vet[1]);
                }
            break;
            case 3:
                if(tam == 0){
                    printf("\n Lista vazia \n");
                }else{
                    int remo_pri = vet[1];
                    vet[1]= vet[tam];
                    tam--;
                    heap_Ver(vet,1,tam);
                    printf("Removido o elemento: %d",remo_pri);
                }
            break;
            case 4:
                if(tam == 0){
                    printf("\n Lista vazia \n");
                }else{
                    printf("\n Elementos da lista de prioridade\n");
                    for(int i = 1; i<= tam; i++){
                        printf("%d ", vet[i]);
                    }
                    printf("\n");

                }
            break;
            case 5:
                printf(" Saindo....");
            break;
            default:
                printf("\n Opcao invalida\n");
            break; 
        }
    }
}