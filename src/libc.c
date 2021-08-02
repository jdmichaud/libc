// https://stackoverflow.com/questions/2548486/compiling-without-libc
// https://en.wikipedia.org/wiki/Exit_(system_call)
// https://github.com/0xAX/linux-insides/blob/master/Theory/linux-theory-3.md

// compile with: rm libc.a && cc -nostdlib -c libc.c && ar rcs libc.a libc.o

#include "sys/syscall.h"

#define DEREF(X) #X
#define USE_MACRO(X) DEREF(X)

// Forward declare main which will be define in the consuming code.
int main(int, char *[]);

// Starting point in linux is _start added by libc.
// If no libc linked, then create _start.
void _start() {
  int res = main(0, 0) & 0xFF;

  // gcc uses asm AT&T syntax by default.
  // . register are prefixed with %
  // . values by $
  // . destination register at the end
  __asm__ volatile( // asm is gnu, __asm__ is more portable.
      "movl $"USE_MACRO(SYS_exit)", %%eax;" // Set eax to the sys_exit syscall number
      "movl %0, %%edi;" // set exit status to res
      "syscall;"
      : /* no output */
      : "m" (res)
  );
}

