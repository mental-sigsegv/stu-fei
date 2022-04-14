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

struct Node* insert_node_index(struct Node* head_node, int index, int value) {
    struct Node* tmp = head_node;
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = value;

    if (index == 1) {
        new_node->next = head_node;
        return new_node;
    }

    for (int i = 0; i < index-2; i++) {
        tmp = tmp->next;
    }
    new_node->next = tmp->next;
    tmp->next = new_node;
    return head_node;
}

struct Node* remove_nth_node(struct Node* head_node, int index) {  // TODO free node
    struct Node* header;
    header = head_node;
    if (index == 1) {
        header = header->next;
        free(head_node);
        return header;
    }
    for (int i = 0; i < index - 2; i++) {
        header = header->next;
    }
    header->next = header->next->next ;
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
    // head = insert_node_index(head, 1, 111);
    // head = remove_nth_node(head, 2);

    print_node(head);
    freeList(head);
    return 0;
}
