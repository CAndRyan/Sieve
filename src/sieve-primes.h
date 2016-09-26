#include "sieve-list.h"

// function prototypes
void remove_multiples (node_t ** ptr, int val);
void remove_non_primes (node_t ** head);

void remove_multiples (node_t ** ptr, int val) {
	int count = 0;
	node_t * current = *ptr;
	
	while (current != NULL) {
		if (current->val % val == 0) {
			if (current->previous != NULL) {
				current->previous->next = current->next;
			}
			
			if (current->next != NULL) {
				current->next->previous = current->previous;
			}
			
			node_t * temp_node = current;
			current = current->next;
			free(temp_node);
		}
		else {
			current = current->next;
		}
    }
	
	return;
}

//fails after 166...works up to 43 and then ends with 0
//only breaks for the Notepad++ console actually...
void remove_non_primes (node_t ** head) {
	node_t * current = *head;
	
	while (current != NULL) {
		remove_multiples(&current, current->val);
		current = current->next;
	}
	
	return;
}
