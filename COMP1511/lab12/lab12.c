struct student *insert(struct student* node, struct student *head){
    struct student *previous = NULL;
    struct student *n = head;
    

    ///THIS CONDITION HERE SHOULD CHANGE BASED ON SORTING TYPE
    while(n!=NULL && unsorted(node, n)){
    //while(n!=NULL && node->zid>n->zid){
        previous = n;
        n = n->next;
    }

    if(previous == NULL){
        head = node;
    }else {
        previous->next = node;
    }

    node->next = n;
    return head;
}
