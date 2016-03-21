/* FIXME : introduce elegant ways to reuse */
#include <assert.h>
#include <stdbool.h>

#include "swap.c"

void bubble_sort(List **head)
{
    if (head == NULL || (*head == NULL))
        return;

    int num_list = 0;
    int i = 0;
    int sub_i;
    int sub_for_times;
    int sub_for_Max;
    List **pre_sub_head = head;
    List *sub_head;
	//List *current_node = *head;

    sub_head = *head;

    while(sub_head && sub_head->next) {
        if (sub_head->value < sub_head->next->value) {
            sub_head = swap(sub_head,sub_head,sub_head->next);
            *pre_sub_head = sub_head;
        }

        num_list = num_list + 1;
        pre_sub_head = &((*pre_sub_head)->next);
        sub_head = sub_head->next;
    }
/*
    while(current_node && current_node->next) {
        if (current_node->value < current_node->next->value) {
            sub_head = swap(sub_head,current_node,current_node->next);
        }
		else{
			current_node = current_node->next;
		}
        num_list = num_list + 1;
    }
*/
    sub_for_times = num_list - 1;

    for (i=0; i < sub_for_times; i++) {
        sub_head = *head;
        sub_for_Max = num_list - (i + 1);
        pre_sub_head = head;
        for (sub_i = 0; sub_head && sub_head->next && (sub_i < sub_for_Max);
             sub_i++) {
            if (sub_head->value < sub_head->next->value) {
                sub_head = swap(sub_head,sub_head,sub_head->next);
                *pre_sub_head = sub_head;
            }

            pre_sub_head = &((*pre_sub_head)->next);
            sub_head = sub_head->next;
        }
    }
/*	
    for (i=0; i < sub_for_times; i++) {
        sub_for_Max = num_list - (i + 1);
		current_node = sub_head;
        for (sub_i = 0; (sub_i < sub_for_Max); sub_i++) {
            if (current_node->value < current_node->next->value) {
                sub_head = swap(sub_head, current_node, current_node->next);
            }
			else{
				current_node = current_node->next;
			}
        }
    }
	*head = sub_head;
*/
    return;
}

