#include <stdio.h>

typedef struct s_node{
    int data;
    struct s_node * next;
}Node;

Node create_node(int data){
    Node new_node;
    new_node.data = data;
    new_node.next = NULL;
    return new_node;
}

void print_list(Node * head, char *name){
    Node * print = head;
    printf("%s: ", name);
    int counter = 0;
    while(print!=NULL){
        printf("[%d](%d)->", counter, print->data);
    }
    printf("X\n");
}

Node * prepend(Node * head, Node * new){
    new->next = head;
    return new;
}

Node * append(Node * head, Node * new){
     
    return head;
}

int main(void){
    Node * list1 = NULL;
    for(int i = 0; i < 10; i ++){
        list1 = prepend(list1, create_node(i*10));
    }
    print_list(list1);
}
