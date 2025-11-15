#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>  // Opcional para medir tempo, mas não usado aqui para simplicidade

// Definição da struct Item, que armazena informações essenciais de cada objeto coletado.
struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

// Definição da struct No para a lista encadeada, contendo um Item e um ponteiro para o próximo nó.
struct No {
    struct Item dados;
    struct No* proximo;
};

// Contadores globais para comparações em buscas.
int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

// Funções para o vetor (lista sequencial)

// Vetor de structs para armazenar até 10 itens.
struct Item itensVetor[10];
int numItensVetor = 0;

// Função para inserir um item no vetor.
void inserirItemVetor() {
    if (numItensVetor >= 10) {
        printf("Mochila cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }
    
    struct Item novoItem;
    printf("Digite o nome do item (sem espacos): ");
    scanf("%s", novoItem.nome);
    printf("Digite o tipo do item (ex: arma, municao, cura): ");
    scanf("%s", novoItem.tipo);
    printf("Digite a quantidade: ");
    scanf("%d", &novoItem.quantidade);
    
    itensVetor[numItensVetor] = novoItem;
    numItensVetor++;
    printf("Item cadastrado com sucesso!\n");
}

// Função para remover um item do vetor por nome.
void removerItemVetor() {
    char nomeRemover[30];
    printf("Digite o nome do item a remover: ");
    scanf("%s", nomeRemover);
    
    int encontrado = 0;
    for (int i = 0; i < numItensVetor; i++) {
        if (strcmp(itensVetor[i].nome, nomeRemover) == 0) {
            for (int j = i; j < numItensVetor - 1; j++) {
                itensVetor[j] = itensVetor[j + 1];
            }
            numItensVetor--;
            encontrado = 1;
            printf("Item removido com sucesso!\n");
            break;
        }
    }
    
    if (!encontrado) {
        printf("Item nao encontrado na mochila.\n");
    }
}

// Função para listar itens do vetor.
void listarItensVetor() {
    if (numItensVetor == 0) {
        printf("Mochila vazia.\n");
        return;
    }
    
    printf("\nItens na mochila (vetor):\n");
    for (int i = 0; i < numItensVetor; i++) {
        printf("Nome: %s, Tipo: %s, Quantidade: %d\n", itensVetor[i].nome, itensVetor[i].tipo, itensVetor[i].quantidade);
    }
    printf("\n");
}

// Função para ordenar o vetor por nome usando Bubble Sort.
void ordenarVetor() {
    for (int i = 0; i < numItensVetor - 1; i++) {
        for (int j = 0; j < numItensVetor - i - 1; j++) {
            if (strcmp(itensVetor[j].nome, itensVetor[j + 1].nome) > 0) {
                struct Item temp = itensVetor[j];
                itensVetor[j] = itensVetor[j + 1];
                itensVetor[j + 1] = temp;
            }
        }
    }
    printf("Vetor ordenado por nome.\n");
}

// Função para busca sequencial no vetor.
void buscarSequencialVetor() {
    char nomeBuscar[30];
    printf("Digite o nome do item a buscar: ");
    scanf("%s", nomeBuscar);
    
    comparacoesSequencial = 0;
    int encontrado = 0;
    for (int i = 0; i < numItensVetor; i++) {
        comparacoesSequencial++;
        if (strcmp(itensVetor[i].nome, nomeBuscar) == 0) {
            printf("Item encontrado:\n");
            printf("Nome: %s, Tipo: %s, Quantidade: %d\n", itensVetor[i].nome, itensVetor[i].tipo, itensVetor[i].quantidade);
            encontrado = 1;
            break;
        }
    }
    
    if (!encontrado) {
        printf("Item nao encontrado na mochila.\n");
    }
    printf("Comparacoes na busca sequencial: %d\n", comparacoesSequencial);
}

// Função para busca binária no vetor (após ordenação).
void buscarBinariaVetor() {
    char nomeBuscar[30];
    printf("Digite o nome do item a buscar: ");
    scanf("%s", nomeBuscar);
    
    comparacoesBinaria = 0;
    int esquerda = 0, direita = numItensVetor - 1;
    int encontrado = 0;
    while (esquerda <= direita) {
        comparacoesBinaria++;
        int meio = esquerda + (direita - esquerda) / 2;
        int cmp = strcmp(itensVetor[meio].nome, nomeBuscar);
        if (cmp == 0) {
            printf("Item encontrado:\n");
            printf("Nome: %s, Tipo: %s, Quantidade: %d\n", itensVetor[meio].nome, itensVetor[meio].tipo, itensVetor[meio].quantidade);
            encontrado = 1;
            break;
        } else if (cmp < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    
    if (!encontrado) {
        printf("Item nao encontrado na mochila.\n");
    }
    printf("Comparacoes na busca binaria: %d\n", comparacoesBinaria);
}

// Funções para a lista encadeada

// Ponteiro para o início da lista encadeada.
struct No* inicioLista = NULL;

// Função para inserir um item na lista encadeada.
void inserirItemLista() {
    struct Item novoItem;
    printf("Digite o nome do item (sem espacos): ");
    scanf("%s", novoItem.nome);
    printf("Digite o tipo do item (ex: arma, municao, cura): ");
    scanf("%s", novoItem.tipo);
    printf("Digite a quantidade: ");
    scanf("%d", &novoItem.quantidade);
    
    struct No* novoNo = (struct No*)malloc(sizeof(struct No));
    novoNo->dados = novoItem;
    novoNo->proximo = inicioLista;
    inicioLista = novoNo;
    printf("Item cadastrado com sucesso!\n");
}

// Função para remover um item da lista encadeada por nome.
void removerItemLista() {
    char nomeRemover[30];
    printf("Digite o nome do item a remover: ");
    scanf("%s", nomeRemover);
    
    struct No* atual = inicioLista;
    struct No* anterior = NULL;
    int encontrado = 0;
    
    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nomeRemover) == 0) {
            if (anterior == NULL) {
                inicioLista = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            encontrado = 1;
            printf("Item removido com sucesso!\n");
            break;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    
    if (!encontrado) {
        printf("Item nao encontrado na mochila.\n");
    }
}

// Função para listar itens da lista encadeada.
void listarItensLista() {
    if (inicioLista == NULL) {
        printf("Mochila vazia.\n");
        return;
    }
    
    printf("\nItens na mochila (lista encadeada):\n");
    struct No* atual = inicioLista;
    while (atual != NULL) {
        printf("Nome: %s, Tipo: %s, Quantidade: %d\n", atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
    printf("\n");
}

// Função para busca sequencial na lista encadeada.
void buscarSequencialLista() {
    char nomeBuscar[30];
    printf("Digite o nome do item a buscar: ");
    scanf("%s", nomeBuscar);
    
    comparacoesSequencial = 0;
    struct No* atual = inicioLista;
    int encontrado = 0;
    
    while (atual != NULL) {
        comparacoesSequencial++;
        if (strcmp(atual->dados.nome, nomeBuscar) == 0) {
            printf("Item encontrado:\n");
            printf("Nome: %s, Tipo: %s, Quantidade: %d\n", atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
            encontrado = 1;
            break;
        }
        atual = atual->proximo;
    }
    
    if (!encontrado) {
        printf("Item nao encontrado na mochila.\n");
    }
    printf("Comparacoes na busca sequencial: %d\n", comparacoesSequencial);
}

// Função principal com menu para escolher estrutura e operações.
int main() {
    int estrutura, opcao;
    
    printf("Bem-vindo ao comparador de estruturas de dados para mochila virtual!\n");
    printf("Escolha a estrutura de dados:\n");
    printf("1. Vetor (lista sequencial)\n");
    printf("2. Lista encadeada\n");
    printf("Estrutura: ");
    scanf("%d", &estrutura);
    
    if (estrutura == 1) {
        // Menu para vetor
        while (1) {
            printf("\nEscolha uma opcao para vetor:\n");
            printf("1. Inserir item\n");
            printf("2. Remover item\n");
            printf("3. Listar itens\n");
            printf("4. Ordenar vetor\n");
            printf("5. Buscar sequencial\n");
            printf("6. Buscar binaria (apos ordenacao)\n");
            printf("7. Sair\n");
            printf("Opcao: ");
            scanf("%d", &opcao);
            
            switch (opcao) {
                case 1: inserirItemVetor(); break;
                case 2: removerItemVetor(); break;
                case 3: listarItensVetor(); break;
                case 4: ordenarVetor(); break;
                case 5: buscarSequencialVetor(); break;
                case 6: buscarBinariaVetor(); break;
                case 7: printf("Saindo...\n"); exit(0);
                default: printf("Opcao invalida.\n");
            }
        }
    } else if (estrutura == 2) {
        // Menu para lista encadeada
        while (1) {
            printf("\nEscolha uma opcao para lista encadeada:\n");
            printf("1. Inserir item\n");
            printf("2. Remover item\n");
            printf("3. Listar itens\n");
            printf("4. Buscar sequencial\n");
            printf("5. Sair\n");
            printf("Opcao: ");
            scanf("%d", &opcao);
            
            switch (opcao) {
                case 1: inserirItemLista(); break;
                case 2: removerItemLista(); break;
                case 3: listarItensLista(); break;
                case 4: buscarSequencialLista(); break;
                case 5: printf("Saindo...\n"); exit(0);
                default: printf("Opcao invalida.\n");
            }
        }
    } else {
        printf("Estrutura invalida.\n");
    }
    
    return 0;
}
