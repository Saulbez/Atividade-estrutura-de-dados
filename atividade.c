#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int indice;
    int dado;
} No;

typedef struct lista {
    No *listaDeNos[99];
    int numElementos;
} Lista;

Lista* criarLista() {
    Lista *lista = (Lista*)malloc(sizeof(Lista));
    if (lista != NULL) {
        lista->numElementos = 0;
    }
    return lista;
}

int inserirLista(Lista *lista, No *no) {
    if (lista->numElementos == 99) {
        printf("Lista cheia\n");
        return 0;
    } else {
        lista->listaDeNos[lista->numElementos] = no;
        lista->numElementos++;
        printf("Elemento inserido\n");
        return 1;
    }
}

void exibirLista(Lista *lista) {
    int i;
    printf("Lista: \" ");
    for (i = 0; i < lista->numElementos; i++) {
        printf("%i - %i | ", lista->listaDeNos[i]->indice, lista->listaDeNos[i]->dado);
    }
    printf("\"\n");
}

int verificarVazia(Lista *lista) {
    return lista->numElementos == 0;
}

No *buscarElemento(Lista *lista, int indice) {
    int i;
    if (lista->numElementos == 0) {
        printf("Lista Vazia\n");
        return NULL;
    }
    for (i = 0; i < lista->numElementos; i++) {
        if (lista->listaDeNos[i]->indice == indice) {
            return lista->listaDeNos[i];
        }
    }
    return NULL;
}

void excluirElemento(Lista *lista, int indice) {
    int i, pos = -1;
    for (i = 0; i < lista->numElementos; i++) {
        if (lista->listaDeNos[i]->indice == indice) {
            free(lista->listaDeNos[i]);
            pos = i;
            break;
        }
    }
    if (pos == -1) {
        printf("Elemento não encontrado\n");
        return;
    }

    for (i = pos; i < lista->numElementos - 1; i++) {
        lista->listaDeNos[i] = lista->listaDeNos[i + 1];
    }
    lista->numElementos--;
}

void liberarLista(Lista *lista) {
    for (int i = 0; i < lista->numElementos; i++) {
        free(lista->listaDeNos[i]);
    }
    free(lista);
}

int inserirListaOrdenada(Lista *lista, No *no) {
    if (lista->numElementos == 99) {
        printf("Lista cheia\n");
        return 0;
    }

    int i;

    for (i = 0; i < lista->numElementos; i++) {
        if (lista->listaDeNos[i]->dado > no->dado) {
            break;
        }
    }

    for (int j = lista->numElementos; j > i; j--) {
        lista->listaDeNos[j] = lista->listaDeNos[j - 1];
    }

    lista->listaDeNos[i] = no;
    lista->numElementos++;
    printf("Elemento inserido na ordem correta\n");
    return 1;
}

int main() {
    Lista *minhaLista = criarLista();
    
    No *no1 = (No*)malloc(sizeof(No));
    no1->indice = 1;
    no1->dado = 10;
    inserirLista(minhaLista, no1);

    No *no2 = (No*)malloc(sizeof(No));
    no2->indice = 2;
    no2->dado = 5;
    inserirLista(minhaLista, no2);

    exibirLista(minhaLista);
    
    if (verificarVazia(minhaLista)) {
        printf("A lista está vazia!\n");
    } else {
        printf("A lista não está vazia!\n");
    }

    No *buscado = buscarElemento(minhaLista, 1);
    if (buscado != NULL) {
        printf("Elemento encontrado: %i - %i\n", buscado->indice, buscado->dado);
    } else {
        printf("Elemento não encontrado\n");
    }

    excluirElemento(minhaLista, 1);
    exibirLista(minhaLista);

    liberarLista(minhaLista);

    Lista *minhaLista2 = criarLista();

    No *novoNo1 = (No*)malloc(sizeof(No));
    novoNo1->indice = 1;
    novoNo1->dado = 30;
    inserirListaOrdenada(minhaLista2, novoNo1);

    No *novoNo2 = (No*)malloc(sizeof(No));
    novoNo2->indice = 2;
    novoNo2->dado = 20;
    inserirListaOrdenada(minhaLista2, novoNo2);

    No *novoNo3 = (No*)malloc(sizeof(No));
    novoNo3->indice = 3;
    novoNo3->dado = 10;
    inserirListaOrdenada(minhaLista2, novoNo3);

    exibirLista(minhaLista2);

    return 0;
}