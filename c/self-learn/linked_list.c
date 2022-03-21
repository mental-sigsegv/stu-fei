#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
}; 

void freeList(struct Node* head) {
    struct Node* tmp;

    while (head != NULL) {
       tmp = head;
       head = head->next;
       free(tmp);
    }
}

struct Node* insert_node_head(struct Node *head_node, int num) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node)); 
    new_node->data = num;
    new_node->next = head_node;
    head_node = new_node;
    return head_node;
}

struct Node* insert_node_tail(struct Node *head_node, int num) {
    struct Node* tmp = head_node;
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = num;
    new_node->next = NULL;

    if (head_node == NULL) {
        return new_node;
    }

    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = new_node;
    return head_node;

}

void print_node(struct Node *node) {
    struct Node *tmp = node;
    while (tmp != NULL) {
        printf("%d ", tmp->data);
        tmp = tmp->next;
    }
}

int main() {
    int arr[] = {8, 92, 23, 6, 2, 93, 95, 20, 9, 83};
    struct Node *head;
    head = NULL;
    
    // 8 92 23 6 2 93 95 20 9 83

    for (int i = 0; i < 10; i++) {
        // head = insert_node_head(head, arr[i]);
        head = insert_node_tail(head, arr[i]);
    }

    print_node(head);
    freeList(head);
    return 0;
}

// For debug
// -exec x/32w 0x800029b80
// -exec w/128b 0x800029b80
// https://sourceware.org/gdb/onlinedocs/gdb/Memory.html