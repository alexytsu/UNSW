#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <string.h>
#include "linkedList.h"
#include "params.h"

struct listRep;

typedef struct node{
    char *content;
    struct listRep *urlList;
    struct node *next;
}node;

typedef struct listRep{
    struct node *first;
    int length;
}listRep;

List newList(){
    List new = malloc(sizeof(struct listRep));
    assert(new);
    new->first=NULL;
    new->length=0;
    return new;
}

Node newNode(char *c){
    Node new = malloc(sizeof(struct node*));
    assert(new);
    new->content=malloc(PNEUMONOULTRAMICROSCOPICSILICOVOLCANOCONIOSIS*sizeof(char));
    strcpy(new->content, c);
    new->urlList=newList();
    new->next=NULL;
    return new;
}

Node newWordNode(char *word){
    Node new = malloc(sizeof(struct node*));
    assert(new);
    new->content=malloc(PNEUMONOULTRAMICROSCOPICSILICOVOLCANOCONIOSIS*sizeof(char));
    strcpy(new->content, word);
    new->urlList=NULL;
    new->next=NULL;
    return new;
}

int sortedWord(char *name1, char *name2)
{
    //  printf("String 1:%s and String 2: %s\n", name1, name2);
    if(*name1 == '\0'&& *name2 == '\0'){
        return 2;
    }

    if(*name1 == '\0'){
        return 1;
    } else if(*name2 == '\0'){
        return 0;
    }

    if(*name1 < *name2){
        return 1;
    } else if(*name1 > *name2){
        return 0;
    } else {
        return sortedWord(name1+1, name2+1);
    }
}

void insertWord(List l, char *w){    
    Node n = newNode(w);

    if(l==NULL){
        List newL = newList();
        l = newL;
    }

    Node curr = l->first;
    Node prev = NULL;

    //if the list is empty
    if(curr == NULL){
        l->first = n;
        return;
    }

    //move the pointers to the correct positions
    while(curr!=NULL && sortedWord(curr->content, w)){
        prev = curr;
        curr = curr -> next;

    }

    if(prev == NULL){ //a new smallest element in the list
        l->first = n;
        n->next = curr;
    }else{ //insert elsewhere in the list
        prev->next = n;
        n->next = curr;
        /*if(n->next == NULL){ //if it's the biggest element in the list
          l->last = n;
          }*/
    }
    l->length++;
    /*
       new->next = new->urlList=NULL;
       if(l->first==NULL){
       l->last=l->first=new;
       }else{
       l->last->next = l->last = new;
       }
       */
}

void insertWordsInPage(List l, char *word){
    Node new = newWordNode(word);

    if(l==NULL){    //but this is never gonna happen. new list malloced before this is called who cares
        List newL = newList();
        l = newL;
    }

    Node curr = l->first;
    Node prev = NULL;

    //if the list is empty
    if(curr == NULL){
        l->first = new;
        return;
    }

    while(curr!=NULL && sortedWord(curr->content, word)){
        prev = curr;
        curr = curr -> next;		
    }
    if(prev == NULL){ //a new smallest element in the list
        l->first = new;
        new->next = curr;
    }else{
        prev->next = new;
        new->next = curr;
    }
    l->length++;
}


Node fromList(List l){
    return l->first;
}

void insertUrl(List l, char *u, char urls[MAX_URLS]){
    Node curr=l->first;
    while(strcmp(curr->content, u)!=0){ //word definitely exists as urls are being added to all the words that reside in its content.
        curr=curr->next;
    }
    //if no urls have been inserted into word index yet
    insertWord(curr->urlList, urls);
    curr->urlList->length++;
}

//returns -1 if doesn't exist in list
int noUrls(List l, char *word){
    Node curr = l->first;
    while(curr!=NULL && strcmp(curr->content, word)!=0){
        curr=curr->next;        
    }
    if (curr==NULL) return -1;
    return curr->urlList->length;

}

int listIntegrity(List l){    
    if(l==NULL){
        fprintf(stderr, "list doesn't exist\n");
        return 0;
    }
    return 1;
}

void showList(List l){
    Node curr = l->first;
    assert(listIntegrity(l));
    if(l->length==0) printf("list is empty\n");
    printf("{");
    while(curr!=NULL){
        printf("%s ", curr->content);        
        curr=curr->next;
    }
    printf("}\n");
}

//filters out duplicates in list
void filterList(List l){
    assert(listIntegrity(l));
    Node curr = l->first;
    while(curr->next!=NULL){
        if(strcmp(curr->content, curr->next->content)==0){
            while(strcmp(curr->content, curr->next->content)==0){
                removeNext(l, curr);
                if (curr->next==NULL) return;
            }
        }
        curr=curr->next;
    }
}

void removeNext(List l, Node keep){
    Node tmp = keep->next;
    keep->next = keep->next->next;
    free(tmp->content);
    free(tmp);    
}

void printIndex(List l, FILE *fout){

    for(Node curr=l->first; curr!=NULL; curr=curr->next){
        fprintf(fout, "%s", curr->content);
        for(Node url=curr->urlList->first; url!=NULL; url=url->next){
            fprintf(fout, " %s", url->content);
        }
        fprintf(fout, "\n");
    }

}

int dupWordCount(List l, char *word){
    if(l==NULL || l->length==0) return 0;
    int count = 0;
    Node curr = l->first;
    while(curr!=NULL){
        if(strcmp(curr->content, word)==0) count++;
        curr = curr->next;
    }
    return count;
}  

int find(List l, char *word){
    Node curr = NULL;
    if(l==NULL || l->length==0) return 0;
    else curr = l->first;
    while(curr!=NULL){
        if(strcmp(curr->content, word)==0) return 1;
        curr = curr->next;
    }
    return 0;
}

int length(List l){
    assert(l!=NULL);
    return l->length;
}

void clearList(List l){
    assert(l!=NULL);
    Node curr = l->first;
    Node prev = NULL;
    Node tmp = NULL;
    while(curr!=NULL){
        tmp = prev;
        prev = curr;
        curr-curr->next;
        free(tmp);
    }
    free(prev);
}
