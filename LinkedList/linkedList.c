#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

struct node{
	int element;
	struct node* ptr;
}node;

struct node* lastPtr;

void add(int element){

	struct node* n = (struct node *) malloc(sizeof(struct node));
	n->element = element;
	n->ptr = lastPtr;
	lastPtr = n;
	printf("[+] Adding element.... %d -> %p \n", n->element, n->ptr);
}


void clr_mem(){
	printf("\n[+] Clearing allocated memory. \n");
	struct node* currentPtr = lastPtr;
	while(currentPtr != NULL){
		struct node * tempPtr = currentPtr;
		currentPtr = currentPtr->ptr;
		free(tempPtr);
	}
}


void add_head(int element){
	struct node* n = (struct node *) malloc(sizeof(struct node));
	n->element = element;
	n->ptr = NULL;
	lastPtr = n;
	printf("[+] Adding head... %d -> %p \n", n->element, n->ptr);
}


void traverse_backwards(int element){
	struct node* currentPtr = lastPtr;
	if(element != -1){
		printf("[+] Recieved element %d \n", element);
		while(currentPtr->element != element){
			struct node * tempPtr = currentPtr;
			currentPtr = currentPtr->ptr;
		}
	}
	printf("\n[+] Traversing backwards... from %d \n", currentPtr->element);
	while(currentPtr != NULL){
		printf("%d -> %p \n", currentPtr->element, currentPtr->ptr);
		struct node * tempPtr = currentPtr;
		currentPtr = currentPtr->ptr;
		sleep(1);
	}
	printf("[+] Reached head! \n");
}


int main(){

	printf("\n Size of one node- %d bytes \n\n", sizeof(struct node));
	add_head(0);
	for(int i=1; i<10; i++){
		add(i);
		sleep(1);
	}
	system("clear");
	traverse_backwards(5);
	clr_mem();

  return 0;
}
