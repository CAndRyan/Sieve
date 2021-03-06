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
node_t * number_line(int start, int end);
void print_list(node_t * head);
int pop(node_t ** head);
int remove_last(node_t ** head);
int remove_by_index(node_t ** head, int n);
int remove_by_value(node_t ** head, int val);

node_t * construct_node(int val){
	node_t * new_node = malloc(sizeof(node_t));
	new_node->val = val;
	new_node->next = NULL;
	new_node->previous= NULL;
	
	return new_node;
}

//*** Build values int[] list this...
//int values[] = {1, 2, 3, 4, 5};
//int_array_t * val_array = malloc(sizeof(int_array_t));
//val_array->length = sizeof(values)/sizeof(values[0]);
//val_array->head = values;
//node_t * test_list = construct_list(val_array);
//***
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
	
	free(values);
	
	return head;
}

node_t * number_line(int start, int end) {
	int size = (end - start) + 1;
	int chunk[size];
	int i = 0;
	
	for (i = 0; i < size; i++) {
		chunk[i] = start + i;
	}
	
	int_array_t * val_array = malloc(sizeof(int_array_t));
	val_array->length = sizeof(chunk)/sizeof(chunk[0]);
	val_array->head = chunk;
	
	return construct_list(val_array);
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
