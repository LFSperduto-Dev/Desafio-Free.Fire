#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da struct Componente, que armazena informações de cada componente da torre.
struct Componente {
    char nome[30];
    char tipo[20];
    int prioridade;
};

// Vetor de structs para armazenar até 20 componentes.
struct Componente componentes[20];
int numComponentes = 0;

// Contadores globais para comparações em cada ordenação.
int comparacoesBubble = 0;
int comparacoesInsertion = 0;
int comparacoesSelection = 0;

// Função para medir tempo de execução de um algoritmo.
// Recebe um ponteiro para função e parâmetros, executa e retorna tempo em segundos.
double medirTempo(void (*algoritmo)(struct Componente[], int), struct Componente arr[], int n) {
    clock_t inicio = clock();
    algoritmo(arr, n);
    clock_t fim = clock();
    return ((double)(fim - inicio)) / CLOCKS_PER_SEC;
}

// Função para mostrar todos os componentes formatados.
void mostrarComponentes(struct Componente arr[], int n) {
    if (n == 0) {
        printf("Nenhum componente cadastrado.\n");
        return;
    }
    
    printf("\nComponentes da torre:\n");
    for (int i = 0; i < n; i++) {
        printf("Nome: %s, Tipo: %s, Prioridade: %d\n", arr[i].nome, arr[i].tipo, arr[i].prioridade);
    }
    printf("\n");
}

// Bubble Sort para ordenar por nome (string).
void bubbleSortNome(struct Componente arr[], int n) {
    comparacoesBubble = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoesBubble++;
            if (strcmp(arr[j].nome, arr[j + 1].nome) > 0) {
                struct Componente temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Insertion Sort para ordenar por tipo (string).
void insertionSortTipo(struct Componente arr[], int n) {
    comparacoesInsertion = 0;
    for (int i = 1; i < n; i++) {
        struct Componente chave = arr[i];
        int j = i - 1;
        while (j >= 0 && strcmp(arr[j].tipo, chave.tipo) > 0) {
            comparacoesInsertion++;
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = chave;
    }
}

// Selection Sort para ordenar por prioridade (int).
void selectionSortPrioridade(struct Componente arr[], int n) {
    comparacoesSelection = 0;
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            comparacoesSelection++;
            if (arr[j].prioridade < arr[minIdx].prioridade) {
                minIdx = j;
            }
        }
        struct Componente temp = arr[minIdx];
        arr[minIdx] = arr[i];
        arr[i] = temp;
    }
}

// Busca binária por nome, assumindo que o array está ordenado por nome.
void buscaBinariaPorNome(struct Componente arr[], int n, char chave[]) {
    int esquerda = 0, direita = n - 1;
    int comparacoes = 0;
    int encontrado = 0;
    
    while (esquerda <= direita) {
        comparacoes++;
        int meio = esquerda + (direita - esquerda) / 2;
        int cmp = strcmp(arr[meio].nome, chave);
        if (cmp == 0) {
            printf("Componente-chave encontrado para iniciar a montagem:\n");
            printf("Nome: %s, Tipo: %s, Prioridade: %d\n", arr[meio].nome, arr[meio].tipo, arr[meio].prioridade);
            encontrado = 1;
            break;
        } else if (cmp < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    
    if (!encontrado) {
        printf("Componente-chave nao encontrado.\n");
    }
    printf("Comparacoes na busca binaria: %d\n", comparacoes);
}

// Função para cadastrar componentes.
void cadastrarComponente() {
    if (numComponentes >= 20) {
        printf("Limite de 20 componentes atingido.\n");
        return;
    }
    
    struct Componente novo;
    printf("Digite o nome do componente: ");
    fgets(novo.nome, 30, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = 0;  // Remove newline
    
    printf("Digite o tipo do componente: ");
    fgets(novo.tipo, 20, stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = 0;
    
    printf("Digite a prioridade (1-10): ");
    scanf("%d", &novo.prioridade);
    getchar();  // Consome newline
    
    componentes[numComponentes] = novo;
    numComponentes++;
    printf("Componente cadastrado!\n");
}

// Função principal com menu interativo.
int main() {
    int opcao;
    int ordenadoPorNome = 0;  // Flag para verificar se foi ordenado por nome
    
    printf("Bem-vindo ao sistema de montagem da torre de fuga!\n");
    printf("Cadastre componentes e escolha estrategias de ordenacao para escapar.\n\n");
    
    while (1) {
        printf("Menu:\n");
        printf("1. Cadastrar componente\n");
        printf("2. Ordenar por nome (Bubble Sort)\n");
        printf("3. Ordenar por tipo (Insertion Sort)\n");
        printf("4. Ordenar por prioridade (Selection Sort)\n");
        printf("5. Buscar componente-chave (Busca Binaria, apos ordenacao por nome)\n");
        printf("6. Mostrar componentes\n");
        printf("7. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        getchar();  // Consome newline
        
        switch (opcao) {
            case 1:
                cadastrarComponente();
                ordenadoPorNome = 0;  // Reseta flag se novo componente for adicionado
                break;
            case 2: {
                double tempo = medirTempo(bubbleSortNome, componentes, numComponentes);
                printf("Ordenacao por nome concluida.\n");
                printf("Comparacoes: %d, Tempo: %.6f segundos\n", comparacoesBubble, tempo);
                mostrarComponentes(componentes, numComponentes);
                ordenadoPorNome = 1;
                break;
            }
            case 3: {
                double tempo = medirTempo(insertionSortTipo, componentes, numComponentes);
                printf("Ordenacao por tipo concluida.\n");
                printf("Comparacoes: %d, Tempo: %.6f segundos\n", comparacoesInsertion, tempo);
                mostrarComponentes(componentes, numComponentes);
                ordenadoPorNome = 0;
                break;
            }
            case 4: {
                double tempo = medirTempo(selectionSortPrioridade, componentes, numComponentes);
                printf("Ordenacao por prioridade concluida.\n");
                printf("Comparacoes: %d, Tempo: %.6f segundos\n", comparacoesSelection, tempo);
                mostrarComponentes(componentes, numComponentes);
                ordenadoPorNome = 0;
                break;
            }
            case 5: {
                if (!ordenadoPorNome) {
                    printf("Primeiro ordene por nome para usar busca binaria.\n");
                    break;
                }
                char chave[30];
                printf("Digite o nome do componente-chave: ");
                fgets(chave, 30, stdin);
                chave[strcspn(chave, "\n")] = 0;
                buscaBinariaPorNome(componentes, numComponentes, chave);
                break;
            }
            case 6:
                mostrarComponentes(componentes, numComponentes);
                break;
            case 7:
                printf("Fuga bem-sucedida! Ate a proxima.\n");
                exit(0);
            default:
                printf("Opcao invalida.\n");
        }
    }
    
    return 0;
}
