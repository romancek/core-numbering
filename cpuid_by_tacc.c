#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>

struct abcd{
  unsigned int a,b,c,d;
};

void cpuid(struct abcd* r, unsigned int eax, unsigned int ecx){
  __asm__ volatile ("cpuid"
                    :"=a"(r->a), "=b"(r->b), "=c"(r->c), "=d"(r->d)
                    : "a"(eax), "c"(ecx));
}

int main(){
  int cpu = sched_getcpu();
  struct abcd r;
  cpuid(&r, 0x1, 0x0);
  printf("%d\t%08x\t%02x\n", cpu, r.b, (r.b >> 25) & 0x1f);
}

