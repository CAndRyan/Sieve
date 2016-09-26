#include <stdio.h>
#include "sieve-primes.h"

int main(int argc, char * argv[]) {
	int max_val = 166;
	
	if (argc > 1) {
		max_val = atoi(argv[1]);
	}
	
	node_t * test_list = number_line(2, max_val);
	
	remove_non_primes(&test_list);
	
    print_list(test_list);
	
	return 0;
}
