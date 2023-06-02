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

// Fungsi untuk mencari node dengan nilai minimum dari linked list
struct Node* findMinNode(struct Node* head) {
    struct Node* minNode = head;
    struct Node* curr = head->next;

    while (curr != NULL) {
        if (curr->data < minNode->data)
            minNode = curr;
        curr = curr->next;
    }

    return minNode;
}

// Fungsi untuk mengurutkan linked list menggunakan selection sort
void selectionSort(struct Node** head_ref) {
    struct Node* sorted = NULL;
    struct Node* curr = *head_ref;

    while (curr != NULL) {
        struct Node* minNode = findMinNode(curr);
        // Menghapus minNode dari daftar asli
        if (minNode == curr) {
            curr = curr->next;
            *head_ref = curr; // Perbarui head_ref jika minNode adalah head
        } else {
            struct Node* prev = curr;
            while (prev->next != minNode)
                prev = prev->next;
            prev->next = minNode->next;
        }

        // Menambahkan minNode ke daftar terurut
        minNode->next = NULL;
        if (sorted == NULL)
            sorted = minNode;
        else {
            struct Node* last = sorted;
            while (last->next != NULL)
                last = last->next;
            last->next = minNode;
        }
    }

    *head_ref = sorted;
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

    printf("Linked list sebelum sorting: ");
    printList(head);

    // Melakukan selection sort
    selectionSort(&head);

    printf("Linked list setelah sorting: ");
    printList(head);

    return 0;
}
