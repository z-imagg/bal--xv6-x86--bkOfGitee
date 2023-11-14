#pragma message("funcId_asm_inserted")
#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char **argv)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $80000,%%edi \n\t"    "0: \n\t" : : ); /*filePath=kill.c,line=7,column=1,abs_location_id=80000,funcName=main,srcFileId=8,locationId=0*/
  int i;

  if(argc < 2){
    printf(2, "usage: kill pid...\n");
    exit();
  }
  for(i=1; i<argc; i++)
    kill(atoi(argv[i]));
  exit();
}
