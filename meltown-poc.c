#include <stdint.h>
#include <stdlib.h>
#include <asm-generic/cachectl.h>
//#include <asm.h>
#include 
int main() {


    // uint*_t should be one byte big
    uint8_t* probe_array = malloc(256 * 4096 * sizeof(uint8_t));

    // make sure probe_array is not cached/clear cache

    uint8_t kernel_memory = *(uint8_t*)(0x00/* some kernel address */);
    uint64_t final_kernel_memory = kernel_memory * 4096; // 4096 is page size?
    uint8_t dummy = probe_array[final_kernel_memory];

    // catch page fault
    // determine which of 256 slots in probe_array is cached
    for (int i=0; i<256; i++) {
	// start timing
	// get it 
	// end timing
    }

    return 0;
}
