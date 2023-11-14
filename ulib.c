#pragma message("funcId_asm_inserted")
#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"
#include "x86.h"

char*
strcpy(char *s, const char *t)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $0,%%edi \n\t"    "0: \n\t" : : ); /*filePath=ulib.c,line=9,column=1,abs_location_id=0,funcName=strcpy,srcFileId=0,locationId=0*/
  char *os;

  os = s;
  while((*s++ = *t++) != 0)
    ;
  return os;
}

int
strcmp(const char *p, const char *q)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $1,%%edi \n\t"    "0: \n\t" : : ); /*filePath=ulib.c,line=20,column=1,abs_location_id=1,funcName=strcmp,srcFileId=0,locationId=1*/
  while(*p && *p == *q)
    p++, q++;
  return (uchar)*p - (uchar)*q;
}

uint
strlen(const char *s)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $2,%%edi \n\t"    "0: \n\t" : : ); /*filePath=ulib.c,line=28,column=1,abs_location_id=2,funcName=strlen,srcFileId=0,locationId=2*/
  int n;

  for(n = 0; s[n]; n++)
    ;
  return n;
}

void*
memset(void *dst, int c, uint n)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $3,%%edi \n\t"    "0: \n\t" : : ); /*filePath=ulib.c,line=38,column=1,abs_location_id=3,funcName=memset,srcFileId=0,locationId=3*/
  stosb(dst, c, n);
  return dst;
}

char*
strchr(const char *s, char c)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $4,%%edi \n\t"    "0: \n\t" : : ); /*filePath=ulib.c,line=45,column=1,abs_location_id=4,funcName=strchr,srcFileId=0,locationId=4*/
  for(; *s; s++)
    if(*s == c)
      return (char*)s;
  return 0;
}

char*
gets(char *buf, int max)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $5,%%edi \n\t"    "0: \n\t" : : ); /*filePath=ulib.c,line=54,column=1,abs_location_id=5,funcName=gets,srcFileId=0,locationId=5*/
  int i, cc;
  char c;

  for(i=0; i+1 < max; ){
    cc = read(0, &c, 1);
    if(cc < 1)
      break;
    buf[i++] = c;
    if(c == '\n' || c == '\r')
      break;
  }
  buf[i] = '\0';
  return buf;
}

int
stat(const char *n, struct stat *st)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $6,%%edi \n\t"    "0: \n\t" : : ); /*filePath=ulib.c,line=72,column=1,abs_location_id=6,funcName=stat,srcFileId=0,locationId=6*/
  int fd;
  int r;

  fd = open(n, O_RDONLY);
  if(fd < 0)
    return -1;
  r = fstat(fd, st);
  close(fd);
  return r;
}

int
atoi(const char *s)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $7,%%edi \n\t"    "0: \n\t" : : ); /*filePath=ulib.c,line=86,column=1,abs_location_id=7,funcName=atoi,srcFileId=0,locationId=7*/
  int n;

  n = 0;
  while('0' <= *s && *s <= '9')
    n = n*10 + *s++ - '0';
  return n;
}

void*
memmove(void *vdst, const void *vsrc, int n)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $8,%%edi \n\t"    "0: \n\t" : : ); /*filePath=ulib.c,line=97,column=1,abs_location_id=8,funcName=memmove,srcFileId=0,locationId=8*/
  char *dst;
  const char *src;

  dst = vdst;
  src = vsrc;
  while(n-- > 0)
    *dst++ = *src++;
  return vdst;
}
