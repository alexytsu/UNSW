#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <string.h>

#include "params.h"
#include "hunGraph.h"

RankList newRankList(int rank){
    RankList new = malloc(sizeof(struct rankRep));
    assert(rankListIntegrity(new));
    new->first=new->last=NULL;
    new->rank=rank;

}

Vertex newVertex(char *url){
    Vertex new = malloc(sizeof(struct vertex));
    assert(new);
    new->url=malloc(PNEUMONOULTRAMICROSCOPICSILICOVOLCANOCONIOSIS*sizeof(char));
    new->next=NULL;
    new->ratio=0;
    return new;
}

void addUrl(List l, char *url){
    Vertex new = newVertex

}



void addList(List l, char *page){ //adds page/url into end of list
    assert(ratioListIntegrity(l));
    Node new = newListNode(page);
    if(l->length==0){
        l->first=l->last=new;
        l->length++;
        return;
    }else{
        l->last->next=new;
        l->last=new;
        l->length++;
    }   
}

void insertOrder(List l, char *v){
    assert(ratioListIntegrity(l));
    Node new = newListNode(v);
    Node curr = l->first;
    Node prev = NULL;

    //if the list is empty
    if(curr == NULL){
        l->first = new;
        return;
    }

    while(curr!=NULL && ratioSortedWord(curr->url, new->url)){
        prev = curr;
        curr = curr -> next;		
    }
    
    if(prev == NULL){ //a new smallest element in the list    
        l->first = new;
        new->next = curr;
        l->last = new;
    }else if(curr == NULL){ //a new largest element in list
    
        prev->next=new;
        new->next=NULL;
        l->last=new;
        
    }else{
    
        prev->next = new;
        new->next = curr;
    }
    l->length++;
}

void ratioRemoveNext(List l, Node keep){
    Node tmp = keep->next;
    keep->next = keep->next->next;
    free(tmp->url);
    free(tmp);    
}

//filters out duplicates in list
void ratioFilterList(List l){
    assert(ratioListIntegrity(l));
    Node curr = l->first;
    while(curr->next!=NULL){
        if(strcmp(curr->url, curr->next->url)==0){
            while(strcmp(curr->url, curr->next->url)==0){
                ratioRemoveNext(l, curr);
                if (curr->next==NULL) return;
            }
        }
        curr=curr->next;
    }
}

void computeAvgRatio(List l){
    assert(ratioListIntegrity(l));
    Node curr = l->first;
    Node flag = NULL;
    int dupCount = 0;
    double ratio = curr->ratio;
    while(curr->next!=NULL){
        dupCount=0;
        if(strcmp(curr->url, curr->next->url)==0){
            flag = curr->next;
            while(strcmp(curr->url, flag->url)==0 && flag!=NULL){
                dupCount++;
                ratio += flag->ratio;
                flag = flag->next;
            }
            curr->ratio = ratio/dupCount;
          //  printf("Was here\n");
            
        }
       
        curr=curr->next;
        printf("%s\n", curr->url);
        if(curr->next==NULL) break;
        printf("avg ratio exited\n");
    }
   
}

void calculateRatio(List l, int rank){
    assert(ratioListIntegrity(l));
    int i = 0;
    Node curr = l->first;
    while(curr!=NULL){
        i++;
        curr->ratio = i/rank;   //this function is called for lists whose urls are already sorted by rank
        curr=curr->next;
    }
}

void combineLists(List dest, List src){ //merge src into dest with duplicates
    Node curr = src->first;
    while(curr!=NULL){
        addList(dest, curr->url);
        curr=curr->next;
    }
}

void copyList(List dest, List src){
    assert(ratioListIntegrity(dest) && ratioListIntegrity(src));
    Node curr = src->first;
    while(curr!=NULL){
        insertOrder(dest, curr->url);        
        curr=curr->next;
    }

}


int rankListIntegrity(List l){    
    if(l==NULL){
        fprintf(stderr, "list doesn't exist\n");
        return 0;
    }
    return 1;
}

 //sorts string in alphabetical order
int ratioSortedWord(char *name1, char *name2)
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
        return ratioSortedWord(name1+1, name2+1);
    }
}

void showRatioList(List l)
{
    for(node *curr = l->first; curr!=NULL; curr = curr->next){
        printf("%s -> ", curr->url);
    }
    printf("X\n");
}

