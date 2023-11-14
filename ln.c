#pragma message("funcId_asm_inserted")
#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $90000,%%edi \n\t"    "0: \n\t" : : ); /*filePath=ln.c,line=7,column=1,abs_location_id=90000,funcName=main,srcFileId=9,locationId=0*/
  if(argc != 3){
    printf(2, "Usage: ln old new\n");
    exit();
  }
  if(link(argv[1], argv[2]) < 0)
    printf(2, "link %s %s: failed\n", argv[1], argv[2]);
  exit();
}
