#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int dado;
    struct no *esq, *dir;
} no;

typedef struct celula {
    no *dado;
    struct celula *prox;
} celula;


celula *cria_pilha(){
    celula *topo = malloc(sizeof(celula));
    topo->prox = NULL;
    return topo;
}

int isPilhaVazia(celula *pilha){
    if(pilha->prox == NULL)
        return 0;
    else
        return 1;
}

void empilha (celula *p, no *x){
    celula *ponteiro = malloc(sizeof(celula));
    ponteiro->dado = x;
    ponteiro->prox = p->prox;
    p->prox = ponteiro;
}

no* desempilha (celula *p){
    no* numero;
    celula *lixo = p->prox;
    numero = lixo->dado;
    p->prox = lixo->prox;
    free(lixo);
    return numero;
}

void em_ordem (no *raiz){
    if(raiz == NULL)
        return;

    celula *pilha = cria_pilha();
    
    while(1){
        if(raiz!=NULL) {
            empilha(pilha, raiz);
            raiz = raiz->esq;
        }else{
            if(isPilhaVazia(pilha)==0)
                break;

        raiz = desempilha(pilha);
        printf("%d ", raiz->dado);
        raiz = raiz->dir;
        }
    }
}

no *criar_arvore (int x, no *esq, no *dir) {
    no *raiz = malloc (sizeof (no));
    raiz->dado = x;
    raiz->esq = esq;
    raiz->dir = dir;
    return raiz;
}

    no *procurar (no *raiz, int x) {
    if (raiz == NULL || raiz->dado == x) return raiz;
    no *esq = procurar (raiz->esq, x);
    if (esq != NULL) return esq;
    return procurar (raiz->dir, x);
    }

    void inserir (no *raiz, int x, int y, char L) {
    // inserir x do lado L de y
    no *procurado = procurar (raiz, y);
    if (L == 'E') {
        no *novo = criar_arvore (x, procurado->esq, NULL);
        procurado->esq = novo;
    }
    else {
        no *novo = criar_arvore (x, NULL, procurado->dir);
        procurado->dir = novo;
    }
    }

int main () {
    int elem, novo;
    char lado;
    //printf ("Digite a raiz: ");
    scanf ("%d", &novo);
    no *raiz = criar_arvore (novo, NULL, NULL);
    //printf ("Digite NOVO LADO EXISTENTE: ");
    while (scanf ("%d %c %d", &novo, &lado, &elem) != EOF) {
        inserir (raiz, novo, elem, lado);
        //printf ("Digite NOVO LADO EXISTENTE: ");
    }
    
    printf ("Em-ordem: ");
    em_ordem (raiz);
    printf ("\n");

    return 0;
}
