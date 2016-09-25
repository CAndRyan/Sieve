#include <stdio.h>
#include <stdlib.h>
#include "sieve-list.h"

int main() {
	int values[] = {1, 2, 3, 4, 5};
	int_array_t * val_array = malloc(sizeof(val_array));
	val_array->length = sizeof(values)/sizeof(values[0]);
	val_array->head = values;
	
	node_t * test_list = construct_list(val_array);
	
    print_list(test_list);
}
