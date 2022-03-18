#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
}; 

struct Node* insert_node(struct Node *node, int num) {
    struct Node* tmp = (struct Node*)malloc(sizeof(struct Node)); 
    tmp->data = num;
    tmp->next = node;
    node = tmp;
    return node;
}

void print_node(struct Node *node) {
    struct Node *tmp = node;
    while (tmp != NULL) {
        printf("%d ", tmp->data);
        tmp = tmp->next;
    }
}

int main() {
    struct Node *head;
    head = NULL;
    int x;
    // 8 92 23 6 2 93 95 20 9 83

    for (int i = 0; i < 10; i++) {
        scanf("%d", &x);
        head = insert_node(head, x);
    }

    print_node(head);
    return 0;
}

// For debug
// -exec x/32w 0x800029b80
// -exec w/128b 0x800029b80
// https://sourceware.org/gdb/onlinedocs/gdb/Memory.html