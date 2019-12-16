#include <stdio.h>
#include <stdlib.h>

typedef struct node_t Node;

struct node_t{
    Node *next;
    int data;
};

Node *create_node(int data, Node *next){
    Node *n;
    n = malloc(sizeof(Node));
    if (n == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }
    n->data = data;
    n->next = next;
    return n;
}

Node *find_node(Node *head, int data){
    Node *n = head;
    while(n != NULL){
        if(n->data == data){
            return n;
        }
        n = n->next;
    }
    return NULL;
}

int sum(Node *head){
    int sum = 0;
    for(Node *n = head; n != NULL; n = n->next){
        sum += n->data;
    }
    return sum;
}

void print_node_data(Node *head){
    if(head == NULL){
        printf("No match found!\n");
    }else{
        printf("Found %d\n", head->data); 
    }
}

int main( int argc, char *argv[]){
    Node *head = create_node(5, NULL);
    for(int i = 1; i <= 100; i ++){
        if(i != 50) head = create_node(i, head);
    }
    printf("%d\n", sum(head));
    print_node_data(find_node(head, 50));
	return 0;
}
