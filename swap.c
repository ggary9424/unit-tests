#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef struct List_node {
    int value;
    struct List_node *next;
} List_node;

typedef struct List_node List;

List *swap(List *head, List *node_1, List *node_2)
{
    if (!head &&
        (node_1 == NULL) && (node_2 == NULL) &&
        (node_1 == node_2))
        return head;

    int num_pre_node_1_and_node_2 = 0;

    List *_head = head;
    List *pre_node_1,*pre_node_2,*tmp_node;

	if (head == node_1) {
        pre_node_1 = NULL;
        num_pre_node_1_and_node_2 = num_pre_node_1_and_node_2 + 1;
    }
	else if (head == node_2) {
        pre_node_2 = NULL;
        num_pre_node_1_and_node_2 = num_pre_node_1_and_node_2 + 1;
    }

    while (head && head->next) {
        if (head->next == node_1) {
            pre_node_1 = head;
            num_pre_node_1_and_node_2 = num_pre_node_1_and_node_2 + 1;
			if(num_pre_node_1_and_node_2 == 2){
				break;
			}
        }
        else if (head->next == node_2) {
            pre_node_2 = head;
            num_pre_node_1_and_node_2 = num_pre_node_1_and_node_2 + 1;
			if(num_pre_node_1_and_node_2 == 2){
				break;
			}
        }
        head = head->next;
    }

    head = _head;

    if (num_pre_node_1_and_node_2 != 2)
        return head;

    if (pre_node_1 == NULL) {
        pre_node_2->next = node_1;
        tmp_node = node_1->next;
        node_1->next = node_2->next;
        node_2->next = tmp_node;
        return node_2;
    }
    else if (pre_node_2 == NULL) {
        pre_node_1->next = node_2;
        tmp_node = node_2->next;
        node_2->next = node_1->next;
        node_1->next = tmp_node;
        return node_1;
    }

    pre_node_1->next = node_2;
    pre_node_2->next = node_1;
    tmp_node = node_2->next;
    node_2->next = node_1->next;
    node_1->next = tmp_node;
    return head;
}


void myswap(List **headref, List *a, List *b){
    assert(headref && "fuction swap argu headref is NULL\n");
    assert(*headref && "fuction swap link list is NULL\n");
    assert(a && "fuction swap argu a is NULL\n");
    assert(b && "fuction swap argu b is NULL\n");  	
	
	if(a == b){
		return;
	}
	
	bool is_a_headref = false; bool is_b_headref = false;
	bool is_a_found = false; bool is_b_found = false;
	bool is_circular_ll = false;
	List *head =  *headref;
	List *current, *prev, *prevA, *prevB;
	
	current = head;
	prev = NULL;
	prevA = NULL;
	prevB = NULL;

	if(a == head){
		is_a_headref = true;
		is_a_found = true;
	}
	else if(b == head){
		is_b_headref = true;
		is_b_found = true;
	}

	while((current != NULL) || (!is_a_found && !is_b_found)){
		prev = current;
		current = current->next;
		
		if(current == head){
			is_circular_ll = true;
			if(is_a_headref){
				prevA = prev;
			}
			else if(is_b_headref){
				prevB = prev;
			}
			break;
		}
		else if(current == a){
			is_a_found = true;
			prevA = prev;
		}
		else if(current == b){
			is_b_found = true;
			prevB = prev;
		}
	}

	assert(is_a_found && "swap argu a is not in link list.\n");
	assert(is_b_found && "swap argu b is not in link list.\n");
	
	if(is_a_headref){
		prevB->next = a;
		if(is_circular_ll){
			prevA->next = b;
		}
		*headref = b;
	}
	else if(is_b_headref){
		prevA->next = b;
		if(is_circular_ll){
			prevB->next = a;
		}
		*headref = a;
	}
	else{
		prevA->next = b;
		prevB->next = a;
	}
	
	List *tmp = a->next;
	a->next = b->next;
	b->next = tmp;
}

