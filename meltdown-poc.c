#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

//if you read array much larger than the l3 cache it should clear everything except that array

int getCacheSize() {
    puts("1");

    FILE* fp = fopen("/sys/devices/system/cpu/cpu0/cache/index3/size", "r");

    if (fp == NULL) { fprintf(stderr, "Couldn't get cache size!"); }

    puts("2");
    size_t bufsize = 10;
    char *buffer = malloc(bufsize);
    puts("2.5");
    size_t num_chars = getline(&buffer, &bufsize, fp);
    buffer[num_chars-1] = 0;
    puts("3");
    int cache_size = atoi(buffer);

    return cache_size;
}

void clearCache() {

}



int main() {

    int first_thing_in_stack;

    // uint*_t should be one byte big
    uint8_t* probe_array = malloc(256 * 4096 * sizeof(uint8_t));

    
    // CLEAR CACHE
    void *clearer = calloc(8, 1024*1024); // 8 MB


    void * huh = ((void*)&first_thing_in_stack)-1024; 
    uint8_t kernel_memory = *(uint8_t*) huh;
    printf("First thing in stack: %p\n", &first_thing_in_stack);
    printf("kernel memory: %p\n", huh);
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

