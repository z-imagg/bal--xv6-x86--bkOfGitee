#pragma message("funcId_asm_inserted")
#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];

void
cat(int fd)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $30000,%%edi \n\t"    "0: \n\t" : : ); /*filePath=cat.c,line=9,column=1,abs_location_id=30000,funcName=cat,srcFileId=3,locationId=0*/
  int n;

  while((n = read(fd, buf, sizeof(buf))) > 0) {
    if (write(1, buf, n) != n) {
      printf(1, "cat: write error\n");
      exit();
    }
  }
  if(n < 0){
    printf(1, "cat: read error\n");
    exit();
  }
}

int
main(int argc, char *argv[])
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $30001,%%edi \n\t"    "0: \n\t" : : ); /*filePath=cat.c,line=26,column=1,abs_location_id=30001,funcName=main,srcFileId=3,locationId=1*/
  int fd, i;

  if(argc <= 1){
    cat(0);
    exit();
  }

  for(i = 1; i < argc; i++){
    if((fd = open(argv[i], 0)) < 0){
      printf(1, "cat: cannot open %s\n", argv[i]);
      exit();
    }
    cat(fd);
    close(fd);
  }
  exit();
}
