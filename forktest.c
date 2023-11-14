#pragma message("funcId_asm_inserted")
// Test that fork fails gracefully.
// Tiny executable so that the limit can be filling the proc table.

#include "types.h"
#include "stat.h"
#include "user.h"

#define N  1000

void
printf(int fd, const char *s, ...)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $50000,%%edi \n\t"    "0: \n\t" : : ); /*filePath=forktest.c,line=12,column=1,abs_location_id=50000,funcName=printf,srcFileId=5,locationId=0*/
  write(fd, s, strlen(s));
}

void
forktest(void)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $50001,%%edi \n\t"    "0: \n\t" : : ); /*filePath=forktest.c,line=18,column=1,abs_location_id=50001,funcName=forktest,srcFileId=5,locationId=1*/
  int n, pid;

  printf(1, "fork test\n");

  for(n=0; n<N; n++){
    pid = fork();
    if(pid < 0)
      break;
    if(pid == 0)
      exit();
  }

  if(n == N){
    printf(1, "fork claimed to work N times!\n", N);
    exit();
  }

  for(; n > 0; n--){
    if(wait() < 0){
      printf(1, "wait stopped early\n");
      exit();
    }
  }

  if(wait() != -1){
    printf(1, "wait got too many\n");
    exit();
  }

  printf(1, "fork test OK\n");
}

int
main(void)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $50002,%%edi \n\t"    "0: \n\t" : : ); /*filePath=forktest.c,line=53,column=1,abs_location_id=50002,funcName=main,srcFileId=5,locationId=2*/
  forktest();
  exit();
}
