#include <stdio.h>
#include <stdlib.h>
#define NULL 0

typedef struct Node{
    int data;
    struct Node* next;
    struct Node* prev;
} Node;
Node* head;
Node* tail;
int length;

void init() {
    head = NULL;
    tail = NULL;
    length = 0;
}

void insert_first(int item) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = item;
    new_node->prev = NULL;
    new_node->next = head;
    if(head != NULL)
        head->prev = new_node;
    else
        tail = new_node;
    head = new_node;
    length++;
}

void insert_last(int item) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = item;
    new_node->next = NULL;
    new_node->prev = tail;
    if(tail != NULL)
        tail->next = new_node;
    else
        head = new_node;
    tail = new_node;
    length++;
}

void insert_at(int item, int pos) {
	// write your code here
	 if(pos<0){//position cant be negative
        return;
    }
    if(pos>length){//position cant be greater than length
        return;
    }
    if(pos==0){//incase pposition is 0;item will be inserted at first position
    insert_first(item);
    return;
    }
    if(pos==length){//if position is equal to length; item will be inserted at last position
        insert_last(item);
        return;
    }
    Node*temp=head;
    int i=0;//i as counter
    while(temp!=NULL){//lopp till temp is not equal to temp
        if(i==pos)//if i match position; break
            break;
        temp=temp->next;//temp will be temps next
        i++;
    }
    Node*new_node=(Node*)malloc(sizeof(Node));// Nwe Node
    new_node->data=item;//data stored
    new_node->next=temp;//
    temp->prev->next=new_node;//temp's previous next  point to new node
    new_node->prev=temp->prev;//new node's prev points to temps prev
    temp->prev=new_node;//temp's prev points to new node
    length++;
}

int search(int key) {
	// write your code here
	   int i=0;//i as counter
      Node*temp=head;
      while(temp!=NULL){//loop till temp is not equal to Null
        if(temp->data==key){//if temps data match to search key
            return i;
        }
        temp=temp->next;//temp will be temp next
        i++;
      }

}

void delete_first() {
	// write your code here
	if(head==NULL)//if head directly points to NULL
        return -1;
    if(head==tail){//when theres only single node
        tail=NULL;
    }
    else
        head->next->prev=NULL;// head's next's previous is equal to null
    Node*temp=head;//temp node point to head
    head=head->next;//current head will be heads next
    free(temp);
    return 1;
}

void delete_last() {
	// write your code here
	if(tail==NULL)//if tail directly points to null
        return -1;
    if(tail==head){//when there is only a single node
        head=NULL;
    }
    else
        tail->prev->next=NULL;////tail's previous's next is equal to null
    Node*temp=tail;//temp node point to tail
    tail=tail->prev;//current tail will be tails next
    free(temp);
    return 1;
}


void delete_at(int pos) {
	// write your code here
	if(pos<0)//pos cant be nagetive
        return;
    if (pos>=length)//pos cant be grater than or equal to length
        return;
    if(pos==0){//if pos equal to 0; first entry will be deleted
        delete_first();
        return;
    }
    if(pos==length-1){//if pos is equal to length -1; last entry will be deleted
        delete_last();
        return;
    }
     Node*temp=head;//to start loop
    int i=0;//i as counter
    while(temp!=NULL){//lopp till temp is not equal to temp
        if(i==pos)//if i match position; break
            break;
        temp=temp->next;//temp will be temps next
        i++;
    }
    temp->prev->next=temp->next;//temp-prev's next will point to temp-next
    temp->next->prev=temp->prev;//temp-next's prev will point to temp-prev
    free(temp);//free temp
    length--;
}

void delete_item(int item) {
	// write your code here
	    int i=search(item);//to locate the position of the entry specified by item

    if(i==-1)
        return;
    delete_at(i);//to delete the specified entry

}

void print() {
    Node* temp = head;
    while(temp!= NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void print_back() {
    Node* temp = tail;
    while(temp!= NULL) {
        printf("%d ", temp->data);
        temp = temp->prev;
    }
    printf("\n");
}

int main() {
    init();
    insert_first(5);
    print();
    insert_first(10);
    print();
    insert_first(15);
    print();
    insert_last(20);
    print();
    insert_at(16,2);
    print();
    printf("%d \n",search(10));
    //delete_first();
    //print();
    //delete_last();
    //print();

    delete_item(5);
    print();
    return 0;
}
