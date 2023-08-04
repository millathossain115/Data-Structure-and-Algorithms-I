 #include <stdio.h>

int arr[100];
int size = 100;
int length;



void init() {
    length = 0;
}



void print() {
    for(int i=0; i<length; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}



int is_full() {

    if( length==size ){//Length and array size are same ..so length is full;
       return 1;

    }
    else {
     	return 0;
    }
}



int is_empty() {

    if( length==0 ){
      return 1;// if the length is 0 ;the array has no element;

    }
    else{
     return 0;

    }
}



int insert_first(int item) {
    int i=0;
    arr[i] = item;//1st element insert at 0 index.

    length++; //length is increasing by 1;
    return 1;
}




int insert_last(int item) {



    arr[length] = item; //insert item to the end of the array
    length++; //increase length by 1
    return 1;
}



int insert_at(int item, int pos) {
    if( is_full()==1 ){
    	return 0;//if array is full we cann't insert any element;

    }



    for( int i=length;i>pos;i++ ) {//all the element of the array makes a space for pos ;
        arr[i]=arr[i-1];//makes a position for pos variable;
    }
    arr[pos] = item; //item is filling the position ;
    length++; //increase length by 1
    return 1;
}



int search(int item) {
    int look = -1;
    for( int x=0; x<length; x++ ){ //find the item in the array
        if( arr[x]==item ){
           look=x;	//search found and saved;

        }
    }
    return look; //reutrning the value of look;
}



int remove_first() {
    if( is_empty()==1 ) {
	   return 0;//if there are no element return 0;

	}

    for(int x=0;x<length;x++){ //all the value shifted and 0 index replaced;
        arr[x]=arr[x+1];
    }
    length--; //length decreased;
    return 1;
}



int remove_last() {
    if( is_empty()==1 ){

		return 0;//if there is nothing in the array return 0;

    }
    length--; // last item is removed;
    return 1;
}



int remove_at(int pos) {

    if( pos>=length){
    	 return 0; //index is not present ;
    }


    for(int i=pos;i<length;i++){ // all the element of the array makes a space for pos ;
        arr[i]=arr[i+1];
    }

    length--; // item removed
    return 1;
}



int remove_item_first(int item) {
    if( is_empty()==1 ) {
	  return 0; // nothing to remove in an empty array
    }
    int index = -1;
    for( int i=0; i<length; i++ ){ //find the first item in the array
        if( arr[i]==item ) {//search the first item;
            index=i;//if matched store in index;
            break;
        };
    }
    if( index==-1 ){
    	return 0;// index not found return 0;

    }
    remove_at(index); //remove_at function will be called;
    return 1;
}



int remove_item_last(int item) {
    if( is_empty()==1 ){

    	return 0; // nothing to remove in an empty array

    }

    int index = -1;
    for( int i=0; i<length; i++ ){ //find the last item in the array
        if( arr[i]==item ) {//search the item if found store in index;
            index=i;
            break;
        }
    }
    if( index==-1 ) {
	  return 0;
	} // item not found
    remove_at(index); //remove_at function will be called;
    return 1;
}



int remove_item_all(int item) {
    if( is_empty()==1 ){
      return 0;//if the array has no element; return 0;

    }

    int index = -1;
    for( int i=0; i<length; i++ ){ //find the items in the array
        if( arr[i]==item ) {
            index=i;
            remove_at(index); //item will be removed at found index;
        };
    }
    if( index==-1 ){
    	return 0; // item not found

    }
    return 1; //if index is not -1 then the items were removed
}

int replace(int old_item, int new_item) {
    int flag =0;

    for( int i=0; i<length; i++ ){ //find the items in the array
        if( arr[i]==old_item ) {
            arr[i]=new_item; //replace the old with the new
            flag = 1;
			break;
        }
    }
    return flag; //flag will return o ; otherwise return 1;
}

void clear() {
    length=0; // now all items are inaccessible
}

int main() {
    init(); // initializes the arraylist first
    // test your functions here



insert_first(6);
insert_last(13);
insert_at(2,25);




    return 0;
}
