
typedef struct fruta {
    int codigo;
    char nome[50];
    int quantidade;
    float preco;
} Fruta;

typedef struct lista {
    Fruta **listaDeFrutas;
    int numElementos;
    int capacidade;
    int* codigosExcluidos;
    int tamanhoExcluidos;
    int proximoCodigo;
} Lista;

Lista* criarLista() {
    Lista *lista = (Lista *)malloc(sizeof(Lista));
    lista->capacidade = 2;
    lista->numElementos = 0;
    lista->listaDeFrutas = (Fruta **)malloc(lista->capacidade * sizeof(Fruta *));

    lista->codigosExcluidos = (int *)malloc(100 * sizeof(int));
    lista->tamanhoExcluidos = 0;
    lista->proximoCodigo = 1;

    return lista;
}

Fruta* cadastrarFruta(Lista *lista) {
    Fruta *novaFruta = (Fruta *)malloc(sizeof(Fruta));

    if (lista->tamanhoExcluidos > 0) {
        novaFruta->codigo = lista->codigosExcluidos[--lista->tamanhoExcluidos];
        lista->tamanhoExcluidos--;
    } else {
        novaFruta->codigo = lista->proximoCodigo++;
    }

    printf("Código gerado: %d\n", novaFruta->codigo);
    printf("Digite o nome da fruta: ");
    fgets(novaFruta->nome, sizeof(novaFruta->nome), stdin);
    novaFruta->nome[strcspn(novaFruta->nome, "\n")] = 0;
    printf("Digite a quantidade: ");
    scanf("%d", &novaFruta->quantidade);
    printf("Digite o preço: ");
    scanf("%f", &novaFruta->preco);
    getchar();
    return novaFruta;
}

void adicionarFruta(Lista *lista, Fruta *fruta) {
    if (lista->numElementos >= lista->capacidade) {
        lista->capacidade *= 2;
        lista->listaDeFrutas = (Fruta **)realloc(lista->listaDeFrutas, lista->capacidade * sizeof(Fruta *));
        if (lista->listaDeFrutas == NULL) {
            printf("Erro ao realocar memoria\n");
            exit(EXIT_FAILURE);
        }
    }
    lista->listaDeFrutas[lista->numElementos] = fruta;
    lista->numElementos++;
}

void listarFrutas(Lista *lista) {
    if (lista->numElementos == 0) {
        printf("Nenhuma fruta cadastrada.\n");
        return;
    }
    printf("Lista de frutas:\n");
    for (int i = 0; i < lista->numElementos; i++) {
        Fruta *fruta = lista->listaDeFrutas[i];
        printf("Código: %d, Nome: %s, Quantidade: %d, Preço: %.2f\n",
               fruta->codigo, fruta->nome, fruta->quantidade, fruta->preco);
    }
}

Fruta* buscarFruta(Lista *lista, int codigo) {
    for (int i = 0; i < lista->numElementos; i++) {
        if (lista->listaDeFrutas[i]->codigo == codigo) {
            return lista->listaDeFrutas[i];
        }
    }
    return NULL;
}

void alterarFruta(Lista *lista, int codigo) {
    Fruta *fruta = buscarFruta(lista, codigo);
    if (fruta) {
        printf("Digite o novo nome da fruta: ");
        scanf("%s", fruta->nome);
        printf("Digite a nova quantidade: ");
        scanf("%d", &fruta->quantidade);
        printf("Digite o novo preço: ");
        scanf("%f", &fruta->preco);
        printf("Fruta alterada com sucesso!\n");
    } else {
        printf("Fruta não encontrada.\n");
    }
}

void excluirFruta(Lista *lista, int codigo) {
    Fruta *fruta = buscarFruta(lista, codigo);
    if (fruta) {
        if (fruta->quantidade > 0) {
            printf("Não é possível excluir a fruta, pois ainda há estoque.\n");
            return;
        }

        for (int i = 0; i < lista->numElementos; i++) {
            if (lista->listaDeFrutas[i]->codigo == codigo) {
                free(lista->listaDeFrutas[i]);
                for (int j = i; j < lista->numElementos - 1; j++) {
                    lista->listaDeFrutas[j] = lista->listaDeFrutas[j + 1];
                }
                lista->numElementos--;
                lista->codigosExcluidos[lista->tamanhoExcluidos++] = codigo;
                printf("Fruta excluída com sucesso!\n");
                return;
            }
        }
    } else {
        printf("Fruta não encontrada.\n");
    }
}

void venderFruta(Lista *lista, int codigo, int quantidade) {
    Fruta *fruta = buscarFruta(lista, codigo);
    if (fruta) {
        if (quantidade > fruta->quantidade) {
            printf("Quantidade em estoque insuficiente para a venda.\n");
            return;
        }
        fruta->quantidade -= quantidade;

        FILE *file = fopen("vendas.txt", "a");
        if (file) {
            fprintf(file, "Venda: Código: %d, Nome: %s, Quantidade: %d, Preço: %.2f\n",
                    fruta->codigo, fruta->nome, quantidade, fruta->preco);
            fclose(file);
            printf("Venda registrada com sucesso!\n");
        } else {
            printf("Erro ao abrir o arquivo de vendas.\n");
        }
    } else {
        printf("Fruta não encontrada.\n");
    }
}

void liberarLista(Lista *lista) {
    for (int i = 0; i < lista->numElementos; i++) {
        free(lista->listaDeFrutas[i]);
    }
    free(lista->listaDeFrutas);
    free(lista);
}