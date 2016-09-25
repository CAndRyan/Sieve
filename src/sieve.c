#include <stdio.h>
#include <stdlib.h>
#include "sieve-list.h"

void remove_non_primes (node_t ** head);

int main(int argc, char * argv[]) {
	node_t * test_list = number_line(2, 30);
	
    print_list(test_list);
	
	return 0;
}

void remove_non_primes (node_t ** head) {
	//
}
