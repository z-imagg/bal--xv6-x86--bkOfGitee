#pragma message("funcId_asm_inserted")
// Create a zombie process that
// must be reparented at exit.

#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $170000,%%edi \n\t"    "0: \n\t" : : ); /*filePath=zombie.c,line=10,column=1,abs_location_id=170000,funcName=main,srcFileId=17,locationId=0*/
  if(fork() > 0)
    sleep(5);  // Let child exit before parent.
  exit();
}
