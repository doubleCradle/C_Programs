#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

struct Node {
	int element;
	struct Node* fd;
	struct Node* rd;
};

static struct Node* lastPtr;

static struct Node* ret_ptr(){
	struct Node* ptr = (struct Node *) malloc(sizeof(struct Node));
	return ptr;
}

void traverse_backwards(int element){
        struct Node* currentPtr = lastPtr;
        if(element != -1){
                printf("[+] Recieved element %d \n", element);
                while(currentPtr->element != element){
                        struct Node * tempPtr = currentPtr;
                        currentPtr = currentPtr->rd;
                }
        }
        printf("\n[+] Traversing backwards... from %d \n", currentPtr->element);
        while(currentPtr != NULL){
                printf("%d -> %p \n", currentPtr->element, currentPtr->rd);
                struct Node * tempPtr = currentPtr;
                currentPtr = currentPtr->rd;
        }
        printf("[+] Reached head! \n");
}


void make_head(int element) {
	struct Node* head=ret_ptr();
	head->element = element;
	head->fd = NULL;
	head->rd = NULL;
	printf("[+] Created head with element %d\n",head->element);
	lastPtr = head;
}

void clr_mem(){
	struct Node* current = lastPtr;
	while(current != NULL) {
		struct Node* temp = current;
		current = current->rd;
		free(temp);
	}
}

void del_node(int element) {
	struct Node* current = lastPtr;
	while(current->element != element) {
		current = current->rd;
		if(current->rd == NULL){
			printf("[!] Cannot delete HEAD\n");
			return;
		}
	}
	current->rd->fd = current->fd;
	current->fd->rd = current->rd;
	free(current);
	printf("[+] Deleted Node having element - %d\n", element);
}


void add_node(int element){
	struct Node* n = ret_ptr();
	n->element = element;
	n->fd = NULL;
	lastPtr->fd = n;
	n->rd = lastPtr;
	printf("[+] Added node with element %d <-- %d\n",n->element, lastPtr->element);
	lastPtr = n;
}

void add_in_bet(int e1, int e2, int e3){
	struct Node* current = lastPtr;
	while(current->element != e1) {
		struct Node* temp = current;
		current = current->rd;
	}
	struct Node* np = ret_ptr();
	if(np == NULL){
		printf("[-] Memory allocation failed [ret_ptr()->add_in_bet()]");
		return;
	}
	np->element = e3;
	np->rd = current;
	np->fd = current->fd;
	current->fd = np;
	np->fd->rd = np;
	printf("[+] Added element %d -> %d <- %d", current->element, np->element, np->fd->element);
}

int main() {
	make_head(0);
	for(int i=0; i<5; i++){
		add_node(i);
	}
	add_in_bet(1,2, 8);
	traverse_backwards(-1);
	del_node(8);
	traverse_backwards(-1);
	clr_mem();
}
