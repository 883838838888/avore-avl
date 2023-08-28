#include<stdio.h>
#include<stdlib.h>

typedef struct No {
    int valor;
    struct No *dir, *esq;
    short altura;
} No;

No* novoNo(int x) {
    No* novo = (No* )malloc(sizeof(No));
    if (novo) {
        novo->valor = x;
        novo->esq = NULL;
        novo->dir = NULL;
        novo->altura = 0;
    } else {
        printf("Erro ao alocar um nó!!!!\n");
    }
    return novo; // Return novo even in the error case
}

short maior(short a, short b) {
    return (a > b) ? a : b;
}

short alturaNo(No *no) {
    if (no == NULL) {
        return -1;
    } else {
        return no->altura; // Return the height of the node
    }
}

short fatorDeBalanceamento(No *no) {
    if (no) {
        return alturaNo(no->esq) - alturaNo(no->dir); // Fix typo "alturaDoNo" to "alturaNo"
    }
    return 0;
}

No* rotacaoEsquerda(No *r) {
    No *y, *f;

    y = r->dir;
    f = y->esq; // Fix typo, should be y->esq instead of r->esq

    y->esq = r;
    r->dir = f; // Fix typo, should be r->dir instead of r->esq

    r->altura = maior(alturaNo(r->esq), alturaNo(r->dir)) + 1;
    y->altura = maior(alturaNo(y->esq), alturaNo(y->dir)) + 1;

    return y;
}

No* rotacaoDireita(No *r) {
    No *y, *f;

    y = r->esq; // Fix typo, should be r->esq instead of r->dir
    f = y->dir; // Fix typo, should be y->dir instead of y->esq

    y->dir = r;
    r->esq = f;

    r->altura = maior(alturaNo(r->esq), alturaNo(r->dir)) + 1;
    y->altura = maior(alturaNo(y->esq), alturaNo(y->dir)) + 1;

    return y;
}

No* rotacaoEsquerdaDireita(No *r) { // Correct the function name
    r->esq = rotacaoEsquerda(r->esq);
    return rotacaoDireita(r);
}

No* rotacaoDireitaEsquerda(No *r) { // Correct the function name
    r->dir = rotacaoDireita(r->dir);
    return rotacaoEsquerda(r);
}

No* balancear(No *raiz) {
    short fb = fatorDeBalanceamento(raiz);

    if (fb < -1) {
        if (fatorDeBalanceamento(raiz->dir) <= 0) {
            raiz = rotacaoEsquerda(raiz);
        } else {
            raiz = rotacaoDireitaEsquerda(raiz);
        }
    } else if (fb > 1) {
        if (fatorDeBalanceamento(raiz->esq) >= 0) {
            raiz = rotacaoDireita(raiz);
        } else {
            raiz = rotacaoEsquerdaDireita(raiz);
        }
    }

    return raiz;
}

No* inserir(No *raiz, int x) {
    if (raiz == NULL) {
        return novoNo(x);
    } else {
        if (x < raiz->valor) {
            raiz->esq = inserir(raiz->esq, x);
        } else if (x > raiz->valor) {
            raiz->dir = inserir(raiz->dir, x);
        } else {
            printf("Inserção não realizada, o elemento já existe.\n");
        }
    }

    raiz->altura = maior(alturaNo(raiz->esq), alturaNo(raiz->dir)) + 1;
    raiz = balancear(raiz);

    return raiz;
}

No* remover(No *raiz, int chave) {
    if (raiz == NULL) {
        printf("Valor não encontrado.\n");
        return NULL;
    } else {
        if (raiz->valor == chave) {
            if (raiz->esq != NULL && raiz->dir != NULL) {
                free(raiz);
                printf("Elemento da folha removido: %d !\n", chave);
                return NULL;
            } else {
                if (raiz->esq != NULL && raiz->dir == NULL) {
                    No *aux = raiz->esq;
                    free(raiz);
                    printf("Elemento com 1 filho removido: %d !\n", chave);
                    return aux;
                } else if (raiz->esq == NULL && raiz->dir != NULL) {
                    No *aux = raiz->dir;
                    free(raiz);
                    printf("Elemento com 1 filho removido: %d !\n", chave);
                    return aux;
                } else {
                    No *aux = raiz->esq;
                    while (aux->dir != NULL)
                        aux = aux->dir;
                    raiz->valor = aux->valor;
                    raiz->esq = remover(raiz->esq, aux->valor);
                    printf("Elemento trocado: %d !\n", chave);
                    return raiz;
                }
            }
        } else {
            if (chave < raiz->valor)
                raiz->esq = remover(raiz->esq, chave);
            else
                raiz->dir = remover(raiz->dir, chave);
        }
    }

    raiz->altura = maior(alturaNo(raiz->esq), alturaNo(raiz->dir)) + 1;
    raiz = balancear(raiz);

    return raiz;
}

void imprimir(No *raiz, int nivel) {
    int i;

    if (raiz) {
        imprimir(raiz->dir, nivel + 1);
        printf("\n");

        for (i = 0; i < nivel; i++) {
            printf("\t");
        }

        printf("%d", raiz->valor);
        imprimir(raiz->esq, nivel + 1);
    }
}

int main(){
		
	 int op, valor;
	 No *raiz = NULL;
	 	 
	 do{
	 	
	 	printf("\n\n sair - 1 enserir\n\t2   - 2 remover\n\t 3 imprimir\n\n");
	 	scanf("%d", &op);
	 	
	 	switch(op){
	 		case 0:
	 			printf("saindo");
	 		break;
	 			
	       case 1:
	 		printf("digite o valor a ser enserido: \n");
	 		scanf("%d", &valor);
	     	raiz = inserir(raiz,  valor);	
	 	break;
	 			
	 	case 2:
	 		printf("digite o valor a ser removido: \n");
	 		scanf("%d", &valor);
	     	raiz = remover(raiz,  valor);	
	 	break;
	 	
	    case 3:
	 			imprimir(raiz, 1);
	 		break;
	 		default:
	 			printf("nocao invalida");			
		 }
	 }while(op!= 0);
	
	return 0;
}
