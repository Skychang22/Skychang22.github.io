#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

void push(Node** head_ref, int new_data) {

    Node* new_head = (Node*)malloc(sizeof(Node));//为新的节点申请内存

    new_head->data = new_data;//为新节点的数据域赋值

    new_head->next = *head_ref;//*head_ref的值就是head中储存的值，这个值就是head指向的节点的地址，就是相当于让新节点指向旧节点，

    *head_ref = new_head;     //将新节点的地址赋值给head


         //整个过程中，head_ref始终指向head，head_ref只是作为中间变量，改变head的值

}                                

void print(Node* head) {
    while (head) {
        printf("%d->", head->data);
        head = head->next;
    }

    puts("NULL");
}

void free_list(Node* head) {
    while (head) {
        Node* tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main3() {
    Node* head = (Node*)malloc(sizeof(Node));
    head->next = NULL;
    head->data = 1;
    printf("Before push:\n");
    print(head);
    push(&head, 2);
    printf("\nAfter push:\n");
    print(head);
    free_list(head);
    return 0;
}