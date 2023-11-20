#pragma message("funcId_asm_inserted")
// init: The initial user-level program

#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

char *argv[] = { "sh", 0 };

int
main(void)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $70000,%%edi \n\t"    "0: \n\t" : : ); /*filePath=init.c,line=12,column=1,abs_location_id=70000,funcName=main,srcFileId=7,locationId=0*/
  int pid, wpid;

  if(open("console", O_RDWR) < 0){
    mknod("console", 1, 1);
    open("console", O_RDWR);
  }
  dup(0);  // stdout
  dup(0);  // stderr

  for(;;){
    printf(1, "init: starting sh\n");
    pid = fork();
    if(pid < 0){
      printf(1, "init: fork failed\n");
      exit();
    }
    if(pid == 0){
      exec("sh", argv);
      printf(1, "init: exec sh failed\n");
      exit();
    }
    while((wpid=wait()) >= 0 && wpid != pid)
      printf(1, "zombie!\n");
  }
}
