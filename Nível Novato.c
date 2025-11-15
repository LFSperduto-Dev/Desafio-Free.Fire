#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Definição da struct Item, que armazena informações essenciais de cada objeto coletado.
// Campos: nome (string de até 30 caracteres), tipo (string de até 20 caracteres, ex: arma, municao, cura), quantidade (inteiro).
struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

// Vetor de structs para armazenar até 10 itens, simulando a mochila virtual.
struct Item itens[10];

// Variável para controlar o número de itens cadastrados na mochila.
int numItens = 0;

// Função para inserir um novo item na mochila.
// Verifica se há espaço (até 10 itens), solicita os dados do item e o adiciona ao vetor.
// Após a inserção, lista todos os itens.
void inserirItem() {
    if (numItens >= 10) {
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
    
    // Adiciona o item ao vetor e incrementa o contador.
    itens[numItens] = novoItem;
    numItens++;
    
    printf("Item cadastrado com sucesso!\n");
    listarItens();  // Lista os itens após a operação.
}

// Função para remover um item da mochila pelo nome.
// Percorre o vetor sequencialmente, encontra o item e o remove (shiftando os elementos restantes).
// Se não encontrar, informa o usuário.
// Após a remoção, lista todos os itens.
void removerItem() {
    char nomeRemover[30];
    printf("Digite o nome do item a remover: ");
    scanf("%s", nomeRemover);
    
    int encontrado = 0;
    for (int i = 0; i < numItens; i++) {
        if (strcmp(itens[i].nome, nomeRemover) == 0) {
            // Remove o item shiftando os elementos para frente.
            for (int j = i; j < numItens - 1; j++) {
                itens[j] = itens[j + 1];
            }
            numItens--;
            encontrado = 1;
            printf("Item removido com sucesso!\n");
            break;
        }
    }
    
    if (!encontrado) {
        printf("Item nao encontrado na mochila.\n");
    }
    
    listarItens();  // Lista os itens após a operação.
}

// Função para listar todos os itens cadastrados na mochila.
// Percorre o vetor e exibe os dados de cada item.
void listarItens() {
    if (numItens == 0) {
        printf("Mochila vazia.\n");
        return;
    }
    
    printf("\nItens na mochila:\n");
    for (int i = 0; i < numItens; i++) {
        printf("Nome: %s, Tipo: %s, Quantidade: %d\n", itens[i].nome, itens[i].tipo, itens[i].quantidade);
    }
    printf("\n");
}

// Função para buscar um item na mochila pelo nome usando busca sequencial.
// Percorre o vetor, compara os nomes e exibe os dados se encontrado.
// Após a busca, lista todos os itens.
void buscarItem() {
    char nomeBuscar[30];
    printf("Digite o nome do item a buscar: ");
    scanf("%s", nomeBuscar);
    
    int encontrado = 0;
    for (int i = 0; i < numItens; i++) {
        if (strcmp(itens[i].nome, nomeBuscar) == 0) {
            printf("Item encontrado:\n");
            printf("Nome: %s, Tipo: %s, Quantidade: %d\n", itens[i].nome, itens[i].tipo, itens[i].quantidade);
            encontrado = 1;
            break;
        }
    }
    
    if (!encontrado) {
        printf("Item nao encontrado na mochila.\n");
    }
    
    listarItens();  // Lista os itens após a operação.
}

// Função principal: exibe um menu interativo para o jogador.
// Permite escolher operações até que o jogador decida sair.
// Usa um loop while para manter o menu ativo.
int main() {
    int opcao;
    
    printf("Bem-vindo ao sistema de inventario da mochila virtual!\n");
    printf("Colete recursos essenciais e organize sua mochila para sobreviver.\n\n");
    
    while (1) {
        printf("Escolha uma opcao:\n");
        printf("1. Cadastrar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("5. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 5:
                printf("Saindo do sistema. Boa sorte na sobrevivencia!\n");
                exit(0);
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    }
    
    return 0;
}
