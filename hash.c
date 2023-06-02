#include <stdio.h>
#include <stdlib.h>

// Struktur Node
struct Node {
    int data;
    struct Node* next;
};

// Fungsi untuk membuat node baru
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->next = NULL;
    return node;
}

// Fungsi untuk menambahkan node baru ke linked list
void push(struct Node** head_ref, int data) {
    struct Node* node = newNode(data);
    node->next = *head_ref;
    *head_ref = node;
}

// Fungsi untuk mencetak linked list
void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

// Fungsi untuk menampilkan data selain yang terdapat di linked list
void displayNonListData(struct Node* head, int start, int end) {
    int i;
    struct Node* current = head;
    int* hash = (int*)calloc((end - start + 1), sizeof(int));

    while (current != NULL) {
        if (current->data >= start && current->data <= end) {
            hash[current->data - start] = 1;
        }
        current = current->next;
    }

    printf("Data selain yang terdapat di linked list: ");
    for (i = 0; i <= (end - start); i++) {
        if (hash[i] == 0) {
            printf("%d ", start + i);
        }
    }
    printf("\n");

    free(hash);
}

// Program utama
int main() {
    struct Node* head = NULL;

    // Menambahkan elemen ke linked list
    push(&head, 6);
    push(&head, 3);
    push(&head, 8);
    push(&head, 1);
    push(&head, 9);

    printf("Linked list: ");
    printList(head);

    // Menampilkan data selain yang terdapat di linked list
    displayNonListData(head, 1, 10);

    return 0;
}

