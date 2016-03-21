#include <stdlib.h>
#include <stdbool.h>

typedef struct List_node {
    int value;
    struct List_node *next;
} List;

void mergesort(List ** headref);
List *merge(List *a, List *b);
void splitLinkList(List *head, List **a_ref, List **b_ref);

void mergesort(List ** headref){
	if( headref == NULL){
		return;	
	}
	List *head = * headref;
	List *a, *b;

	if(head == NULL || head->next == NULL){
		return;
	}
	
	splitLinkList(head, &a, &b);

	mergesort(&a);
	mergesort(&b);
	* headref = merge(a, b);
}

List *merge(List *a, List *b){
	List *result;

	if(a == NULL){
		return b;
	}
	else if(b == NULL){
		return a;
	}

	if(a->value > b->value){
		result = b;
		result->next = merge(a, b->next);
	}
	else{
		result = a;
		result->next = merge(a->next, b);
	}
	
	return result;	
}

void splitLinkList(List *head, List **a_ref, List **b_ref){
	List *slow = head;
	List *fast = head->next;

	while(fast != NULL){
		fast = fast->next;
		if(fast != NULL){
			fast = fast->next;
			slow = slow->next;
		}
	}

	*a_ref = head;
	*b_ref = slow->next;
	slow->next = NULL;

	return;
}
