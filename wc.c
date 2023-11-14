#pragma message("funcId_asm_inserted")
#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];

void
wc(int fd, char *name)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $160000,%%edi \n\t"    "0: \n\t" : : ); /*filePath=wc.c,line=9,column=1,abs_location_id=160000,funcName=wc,srcFileId=16,locationId=0*/
  int i, n;
  int l, w, c, inword;

  l = w = c = 0;
  inword = 0;
  while((n = read(fd, buf, sizeof(buf))) > 0){
    for(i=0; i<n; i++){
      c++;
      if(buf[i] == '\n')
        l++;
      if(strchr(" \r\t\n\v", buf[i]))
        inword = 0;
      else if(!inword){
        w++;
        inword = 1;
      }
    }
  }
  if(n < 0){
    printf(1, "wc: read error\n");
    exit();
  }
  printf(1, "%d %d %d %s\n", l, w, c, name);
}

int
main(int argc, char *argv[])
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $160001,%%edi \n\t"    "0: \n\t" : : ); /*filePath=wc.c,line=37,column=1,abs_location_id=160001,funcName=main,srcFileId=16,locationId=1*/
  int fd, i;

  if(argc <= 1){
    wc(0, "");
    exit();
  }

  for(i = 1; i < argc; i++){
    if((fd = open(argv[i], 0)) < 0){
      printf(1, "wc: cannot open %s\n", argv[i]);
      exit();
    }
    wc(fd, argv[i]);
    close(fd);
  }
  exit();
}
