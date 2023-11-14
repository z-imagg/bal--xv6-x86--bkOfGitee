#pragma message("funcId_asm_inserted")
#include "types.h"
#include "x86.h"

void*
memset(void *dst, int c, uint n)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $360000,%%edi \n\t"    "0: \n\t" : : ); /*filePath=string.c,line=6,column=1,abs_location_id=360000,funcName=memset,srcFileId=36,locationId=0*/
  if ((int)dst%4 == 0 && n%4 == 0){
    c &= 0xFF;
    stosl(dst, (c<<24)|(c<<16)|(c<<8)|c, n/4);
  } else
    stosb(dst, c, n);
  return dst;
}

int
memcmp(const void *v1, const void *v2, uint n)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $360001,%%edi \n\t"    "0: \n\t" : : ); /*filePath=string.c,line=17,column=1,abs_location_id=360001,funcName=memcmp,srcFileId=36,locationId=1*/
  const uchar *s1, *s2;

  s1 = v1;
  s2 = v2;
  while(n-- > 0){
    if(*s1 != *s2)
      return *s1 - *s2;
    s1++, s2++;
  }

  return 0;
}

void*
memmove(void *dst, const void *src, uint n)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $360002,%%edi \n\t"    "0: \n\t" : : ); /*filePath=string.c,line=33,column=1,abs_location_id=360002,funcName=memmove,srcFileId=36,locationId=2*/
  const char *s;
  char *d;

  s = src;
  d = dst;
  if(s < d && s + n > d){
    s += n;
    d += n;
    while(n-- > 0)
      *--d = *--s;
  } else
    while(n-- > 0)
      *d++ = *s++;

  return dst;
}

// memcpy exists to placate GCC.  Use memmove.
void*
memcpy(void *dst, const void *src, uint n)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $360003,%%edi \n\t"    "0: \n\t" : : ); /*filePath=string.c,line=54,column=1,abs_location_id=360003,funcName=memcpy,srcFileId=36,locationId=3*/
  return memmove(dst, src, n);
}

int
strncmp(const char *p, const char *q, uint n)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $360004,%%edi \n\t"    "0: \n\t" : : ); /*filePath=string.c,line=60,column=1,abs_location_id=360004,funcName=strncmp,srcFileId=36,locationId=4*/
  while(n > 0 && *p && *p == *q)
    n--, p++, q++;
  if(n == 0)
    return 0;
  return (uchar)*p - (uchar)*q;
}

char*
strncpy(char *s, const char *t, int n)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $360005,%%edi \n\t"    "0: \n\t" : : ); /*filePath=string.c,line=70,column=1,abs_location_id=360005,funcName=strncpy,srcFileId=36,locationId=5*/
  char *os;

  os = s;
  while(n-- > 0 && (*s++ = *t++) != 0)
    ;
  while(n-- > 0)
    *s++ = 0;
  return os;
}

// Like strncpy but guaranteed to NUL-terminate.
char*
safestrcpy(char *s, const char *t, int n)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $360006,%%edi \n\t"    "0: \n\t" : : ); /*filePath=string.c,line=84,column=1,abs_location_id=360006,funcName=safestrcpy,srcFileId=36,locationId=6*/
  char *os;

  os = s;
  if(n <= 0)
    return os;
  while(--n > 0 && (*s++ = *t++) != 0)
    ;
  *s = 0;
  return os;
}

int
strlen(const char *s)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $360007,%%edi \n\t"    "0: \n\t" : : ); /*filePath=string.c,line=98,column=1,abs_location_id=360007,funcName=strlen,srcFileId=36,locationId=7*/
  int n;

  for(n = 0; s[n]; n++)
    ;
  return n;
}

