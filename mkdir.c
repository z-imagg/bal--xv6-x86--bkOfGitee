#pragma message("funcId_asm_inserted")
#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $110000,%%edi \n\t"    "0: \n\t" : : ); /*filePath=mkdir.c,line=7,column=1,abs_location_id=110000,funcName=main,srcFileId=11,locationId=0*/
  int i;

  if(argc < 2){
    printf(2, "Usage: mkdir files...\n");
    exit();
  }

  for(i = 1; i < argc; i++){
    if(mkdir(argv[i]) < 0){
      printf(2, "mkdir: %s failed to create\n", argv[i]);
      break;
    }
  }

  exit();
}
