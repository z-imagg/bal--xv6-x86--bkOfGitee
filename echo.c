#pragma message("funcId_asm_inserted")
#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $40000,%%edi \n\t"    "0: \n\t" : : ); /*filePath=echo.c,line=7,column=1,abs_location_id=40000,funcName=main,srcFileId=4,locationId=0*/
  int i;

  for(i = 1; i < argc; i++)
    printf(1, "%s%s", argv[i], i+1 < argc ? " " : "\n");
  exit();
}
