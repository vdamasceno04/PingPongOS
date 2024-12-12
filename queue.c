#include "queue.h"
#include <stdio.h>


void queue_append(queue_t **queue, queue_t *elem) {
    if (elem == NULL) {
        return;
    }

    if (*queue == NULL) {
        // Fila vazia, inicializa o único elemento
        *queue = elem;
        elem->next = NULL;
        elem->prev = NULL;
        return;
    }

    // Encontra o último elemento da fila
    queue_t *aux = *queue;
    while (aux->next != NULL) {
        aux = aux->next;
    }

    // Conecta o novo elemento ao final da fila
    aux->next = elem;
    elem->prev = aux;
    elem->next = NULL;  // O próximo do novo elemento é NULL (fim da fila)
}

queue_t *queue_remove(queue_t **queue, queue_t *elem) {
    if (elem == NULL || *queue == NULL) {
        return NULL;
    }

    queue_t *aux = *queue;
    // Busca pelo elemento na fila
    while (aux != elem && aux->next != NULL) {
        aux = aux->next;
    }

    // Se o elemento não foi encontrado, retorna NULL
    if (aux != elem) {
        return NULL;
    }

    // Se o elemento a ser removido é o único da fila
    if (aux == *queue && aux->next == NULL) {
        *queue = NULL;  // A fila fica vazia
    } else if (aux == *queue) {
        // Se o elemento a ser removido é o primeiro, atualiza o ponteiro da cabeça
        *queue = aux->next;
        (*queue)->prev = NULL;  // O novo primeiro elemento não tem elemento anterior
    } else if (aux->next == NULL) {
        // Se o elemento a ser removido é o último
        aux->prev->next = NULL;  // O penúltimo aponta para NULL
    } else {
        // Caso geral: o elemento está no meio da fila
        aux->prev->next = aux->next;
        aux->next->prev = aux->prev;
    }

    // Desconecta o elemento removido
    aux->next = NULL;
    aux->prev = NULL;

    return aux;
}

int queue_size(queue_t *queue) {
    if (queue == NULL) {
        return 0;
    }

    int size = 0;
    queue_t *aux = queue;
    while (aux != NULL) {
        size++;
        aux = aux->next;
    }

    return size;
}

void print_elem(void *ptr) {
    if (ptr == NULL) {
        printf("NULL");
        return;
    }

    // Converte o ponteiro genérico para o tipo específico da estrutura
    queue_t *elem = (queue_t *)ptr;

    // Imprime o identificador do elemento
    printf("ELEMENTO");
}


void queue_print(char *name, queue_t *queue, void print_elem(void *)) {
    // Exibe o nome da fila
    printf("%s: [", name);

    // Verifica se a fila está vazia
    if (queue == NULL) {
        printf("]\n"); // Fecha a lista e termina
        return;
    }

    // Percorre a fila e chama a função de impressão para cada elemento
    queue_t *aux = queue;
    while (aux != NULL) {
        print_elem(aux); // Usa a função de callback para exibir o elemento
        aux = aux->next; // Move para o próximo elemento
        if (aux != NULL) {
            printf(", "); // Adiciona uma vírgula entre os elementos
        }
    }

    printf("]\n"); // Fecha a lista e termina
}

// Testa a biblioteca de filas
int main(int argc, char const *argv[]) {
    // Declaração da fila
    queue_t *queue = NULL;

    // Criação dos elementos
    queue_t elem1 = {NULL, NULL};
    queue_t elem2 = {NULL, NULL};
    queue_t elem3 = {NULL, NULL};
    queue_t elem4 = {NULL, NULL};

    // Teste: Adicionando elementos à fila
    queue_append(&queue, (queue_t *)&elem1);
    queue_append(&queue, (queue_t *)&elem2);
    queue_append(&queue, (queue_t *)&elem3);
    queue_append(&queue, (queue_t *)&elem4);

    // Imprimindo a fila após adicionar elementos
    printf("Fila após adicionar elementos:\n");
    queue_print("Fila", queue, print_elem);

    // Teste: Removendo o primeiro elemento
    queue_t *removed = queue_remove(&queue, (queue_t *)&elem1);
    printf("Elemento removido: ");
    print_elem(removed);
    printf("\n");
    printf("Fila após remover o primeiro elemento:\n");
    queue_print("Fila", queue, print_elem);

    // Teste: Removendo o último elemento
    removed = queue_remove(&queue, (queue_t *)&elem4);
    printf("Elemento removido: ");
    print_elem(removed);
    printf("\n");
    printf("Fila após remover o último elemento:\n");
    queue_print("Fila", queue, print_elem);

    // Teste: Removendo um elemento do meio
    removed = queue_remove(&queue, (queue_t *)&elem2);
    printf("Elemento removido: ");
    print_elem(removed);
    printf("\n");
    printf("Fila após remover um elemento do meio:\n");
    queue_print("Fila", queue, print_elem);

    // Teste: Tamanho da fila
    printf("Tamanho da fila: %d\n", queue_size(queue));

    return 0;
}

