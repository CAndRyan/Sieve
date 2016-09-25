#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node * next;
	struct node * previous;
} node_t;

typedef struct int_array {
	int length;
	int * head;
} int_array_t;

// function prototypes
node_t * construct_node(int val);
node_t * construct_list(int_array_t * values);
void print_list(node_t * head);
int pop(node_t ** head);
int remove_last(node_t ** head);
int remove_by_index(node_t ** head, int n);
int remove_by_value(node_t ** head, int val);

int main() {

    //node_t * test_list = malloc(sizeof(node_t));
    //test_list->val = 1;
    //test_list->next = malloc(sizeof(node_t));
    //test_list->next->val = 2;
    //test_list->next->next = malloc(sizeof(node_t));
    //test_list->next->next->val = 3;
    //test_list->next->next->next = malloc(sizeof(node_t));
    //test_list->next->next->next->val = 4;
    //test_list->next->next->next->next = NULL;
    //
    //remove_by_value(&test_list, 3);
	//remove_last(&test_list);
	//remove_by_index(&test_list, 2);
	//pop(&test_list);

	int values[] = {1, 2, 3, 4, 5};
	int_array_t * val_array = malloc(sizeof(val_array));
	val_array->length = sizeof(values)/sizeof(values[0]);
	val_array->head = values;
	
	node_t * test_list = construct_list(val_array);
	
    print_list(test_list);
}

node_t * construct_node(int val){
	node_t * new_node = malloc(sizeof(node_t));
	new_node->val = val;
	new_node->next = NULL;
	new_node->previous= NULL;
	
	return new_node;
}

node_t * construct_list(int_array_t * values) {
	node_t * head = NULL;
	
	if (values->length > 0) {
		head = construct_node(*(values->head));
		
		int i = 1;
		node_t * current = head;
		for (i = 1; i < values->length; i++) {
			node_t * next_node = construct_node(*(values->head + i));
			current->next = next_node;
			next_node->previous = current;
			current = next_node;
		}
	}
	
	return head;
}

void print_list(node_t * head) {
    node_t * current = head;

    while (current != NULL) {
        printf("%d\n", current->val);
        current = current->next;
    }
}

// pop off the head element of the linked list
int pop(node_t ** head) {
    int retval = -1;
    node_t * next_node = NULL;

    if (*head == NULL) {
        return -1;
    }

    next_node = (*head)->next;
    retval = (*head)->val;
    free(*head);
    *head = next_node;
	
	if (*head != NULL) {
		(*head)->previous = NULL;
	}

    return retval;
}

int remove_last(node_t ** head) {
    int retval = 0;
    node_t * current = *head;
	
    /* if there is only one item in the list, remove it */
    if (current->next == NULL) {
        retval = current->val;
        free(current);
        current = NULL;
        return retval;
    }

    while (current->next->next != NULL) {
        current = current->next;
    }
	
	free(current->next);
	current->next = NULL;
}

int remove_by_index(node_t ** head, int n) {
    int i = 0;
    int retval = -1;
    node_t * current = *head;
    node_t * temp_node = NULL;

    if (n == 0) {
        return pop(head);
    }

    for (i = 0; i < n-1; i++) {
        if (current->next == NULL) {
            return -1;
        }
		
        current = current->next;
    }

    temp_node = current->next;
    retval = temp_node->val;
    current->next = temp_node->next;
    free(temp_node);
	
	if (current->next != NULL) {
		current->next->previous = current;
	}

    return retval;
}

int remove_by_value(node_t ** head, int val) {
    int retval = -1;
	int count = 0;
	node_t * current = *head;
    node_t * temp_node = NULL;
	
	if (current->val == val) {
		return pop(head);
	}
	
	while ((current->next != NULL) && (temp_node == NULL)) {
		if (current->next->val == val) {
			temp_node = current->next;
		}
		else {
			current = current->next;
		}
    }
	
	if (temp_node != NULL) {
		retval = temp_node->val;
		current->next = temp_node->next;
		free(temp_node);
		
		if (current->next != NULL) {
			current->next->previous = current;
		}
	}
	
	return retval;
}
