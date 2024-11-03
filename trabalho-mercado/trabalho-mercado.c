#include <stdio.h>
#include <stdlib.h>
#include "./cadastrar.h"

Lista* criarLista();
void adicionarFruta(Lista *lista, Fruta *fruta);
void listarFrutas(Lista *lista);
Fruta* buscarFruta(Lista *lista, int codigo);
void alterarFruta(Lista *lista, int codigo);
void excluirFruta(Lista *lista, int codigo);
void venderFruta(Lista *lista, int codigo, int quantidade);
void liberarLista(Lista *lista);

int main() {
    Lista *minhaLista = criarLista();
    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1. Cadastrar fruta\n");
        printf("2. Listar frutas\n");
        printf("3. Buscar fruta\n");
        printf("4. Alterar fruta\n");
        printf("5. Excluir fruta\n");
        printf("6. Vender fruta\n");
        printf("7. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: {
                Fruta *novaFruta = cadastrarFruta(minhaLista);

                adicionarFruta(minhaLista, novaFruta);
                printf("Fruta cadastrada com sucesso!\n");
                break;
            }
            case 2:
                listarFrutas(minhaLista);
                break;
            case 3: {
                int codigo;
                printf("Digite o código da fruta a buscar: ");
                scanf("%d", &codigo);
                getchar();
                Fruta *fruta = buscarFruta(minhaLista, codigo);
                if (fruta) {
                    printf("Fruta encontrada: Código: %d, Nome: %s, Quantidade: %d, Preço: %.2f\n",
                           fruta->codigo, fruta->nome, fruta->quantidade, fruta->preco);
                } else {
                    printf("Fruta não encontrada.\n");
                }
                break;
            }
            case 4: {
                int codigo;
                printf("Digite o código da fruta a alterar: ");
                scanf("%d", &codigo);
                getchar();
                alterarFruta(minhaLista, codigo);
                break;
            }
            case 5: {
                int codigo;
                printf("Digite o código da fruta a excluir: ");
                scanf("%d", &codigo);
                getchar();
                excluirFruta(minhaLista, codigo);
                break;
            }
            case 6: {
                int codigo, quantidade;
                printf("Digite o código da fruta a vender: ");
                scanf("%d", &codigo);
                printf("Digite a quantidade a vender: ");
                scanf("%d", &quantidade);
                getchar();
                venderFruta(minhaLista, codigo, quantidade);
                break;
            }
            case 7:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (opcao != 7);

    liberarLista(minhaLista);
    return 0;
}