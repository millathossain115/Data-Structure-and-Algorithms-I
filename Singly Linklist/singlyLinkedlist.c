#include <stdio.h>
#include <stdlib.h>
#define NULL 0

struct Node {
    int data;
    struct Node* next;
};

struct Node* head;
int length;

void init() {
    head = NULL;
    length = 0;
}

void insert_first(int item) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = item;
    // linking
    newNode->next = head;
    head = newNode;
    length++;
}

void insert_last(int item) {
    if(head == NULL) {
        insert_first(item);
        return;
    }
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = item;
    // linking
    struct Node* temp = head;
    while(temp->next != NULL) {
        temp = temp->next;
    }
    newNode->next = NULL;
    temp->next = newNode;
    length++;
}

void insert_at(int item, int pos) {
    if(pos<0 || pos>length) {
        return;
    }
    if(pos == 0) {
        insert_first(item);
        return;
    }
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = item;
    // linking
    struct Node* temp = head;
    int i=0;
    while(i < pos-1) {
        temp = temp->next;
        i++;
    }
    newNode->next = temp->next;
    temp->next = newNode;
    length++;
}

int search(int key) {
    // Write your code here
    int count=0;//counter
   struct Node*temp=head;
   while(temp!=NULL){//using a loop to find out if temp's data equals to search key
    if(temp->data==key){
        return count;
    }
    count++;
    temp=temp->next;
   }
   return NULL;
};

void delete_first() {
    // Write your code here
    if(head==NULL)
        return -1;
    struct Node*temp=head;//temp will point head
    head=head->next;//head assigned as temp next's
    free(temp);
    return 1;
}

void delete_last() {
    // Write your code here
    struct Node*temp=head;
    struct Node*prev;

    while(temp->next!=NULL){//as temp points to head, we check temps next is equal to null or not ,If yes it will move to statement
        prev=temp;
        temp=temp->next;
    }
    if(temp==head){
        head=NULL;
    }
    else prev->next=NULL;
    free(temp);
    return 1;
}

void delete_at(int pos) {
    // Write your code here
    struct Node* temp=head;
	struct Node* prev;
	int count=0;//counter

	while(temp->next!=NULL){//using loop to end of the linked list
		if(count==pos){//count will represent as position
			break;
		}
		prev=temp;
		temp=temp->next;
		count++;
	}

	prev->next= temp->next;
	free(temp);

}

void delete_item(int item) {
    // Write your code here
    struct Node* temp=head;
	struct Node* prev;

        while(temp!=NULL){//using loop till the end to match temp's data to item
		if(temp->data==item){
			break;
		}
		prev=temp;
		temp=temp->next;
	}

	prev->next = temp->next;
	free(temp);
}

void insert_before(int oldItem, int newItem) {
    // Write your code here
    struct Node* temp=head;
	struct Node* prev;
    while(temp!=NULL){//using loop to check till the end
		if(temp->data==oldItem){
			break;
		}
		oldItem=temp;
		temp=temp->next;
	}

	struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));//newnode
	newNode->data=newItem;
	newNode->next=prev->next;
	prev->next=newNode;
}

void insert_after(int oldItem, int newItem) {
    // Write your code here
    struct Node* temp=search(oldItem);
    if(temp==NULL){// condition to check till end
        return-1;
    }
    struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));//creating new node
    newNode->data=newItem;//
    newNode->next=temp->next;
    temp->next=newNode;
    return 1;

}

void print() {
    struct Node* temp = head;
    while(temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
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
    insert_first(20);
    print();
    //printf("%d ",search(5));
    //delete_first();
    //print();
    //delete_last();
    //print();
     //delete_at(2);
     //print();
     //delete_item(10);
     //print();
     insert_after(15,18);
     print();
    return 0;
}
