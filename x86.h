#pragma message("funcId_asm_inserted")
#include "types.h"
// Routines to let C code use special x86 instructions.

static inline uchar
inb(ushort port)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $430000,%%edi \n\t"    "0: \n\t" : : ); /*filePath=x86.h,line=6,column=1,abs_location_id=430000,funcName=inb,srcFileId=43,locationId=0*/
  uchar data;

  asm volatile("in %1,%0" : "=a" (data) : "d" (port));
  return data;
}

static inline void
insl(int port, void *addr, int cnt)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $430001,%%edi \n\t"    "0: \n\t" : : ); /*filePath=x86.h,line=15,column=1,abs_location_id=430001,funcName=insl,srcFileId=43,locationId=1*/
  asm volatile("cld; rep insl" :
               "=D" (addr), "=c" (cnt) :
               "d" (port), "0" (addr), "1" (cnt) :
               "memory", "cc");
}

static inline void
outb(ushort port, uchar data)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $430002,%%edi \n\t"    "0: \n\t" : : ); /*filePath=x86.h,line=24,column=1,abs_location_id=430002,funcName=outb,srcFileId=43,locationId=2*/
  asm volatile("out %0,%1" : : "a" (data), "d" (port));
}

static inline void
outw(ushort port, ushort data)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $430003,%%edi \n\t"    "0: \n\t" : : ); /*filePath=x86.h,line=30,column=1,abs_location_id=430003,funcName=outw,srcFileId=43,locationId=3*/
  asm volatile("out %0,%1" : : "a" (data), "d" (port));
}

static inline void
outsl(int port, const void *addr, int cnt)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $430004,%%edi \n\t"    "0: \n\t" : : ); /*filePath=x86.h,line=36,column=1,abs_location_id=430004,funcName=outsl,srcFileId=43,locationId=4*/
  asm volatile("cld; rep outsl" :
               "=S" (addr), "=c" (cnt) :
               "d" (port), "0" (addr), "1" (cnt) :
               "cc");
}

static inline void
stosb(void *addr, int data, int cnt)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $430005,%%edi \n\t"    "0: \n\t" : : ); /*filePath=x86.h,line=45,column=1,abs_location_id=430005,funcName=stosb,srcFileId=43,locationId=5*/
  asm volatile("cld; rep stosb" :
               "=D" (addr), "=c" (cnt) :
               "0" (addr), "1" (cnt), "a" (data) :
               "memory", "cc");
}

static inline void
stosl(void *addr, int data, int cnt)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $430006,%%edi \n\t"    "0: \n\t" : : ); /*filePath=x86.h,line=54,column=1,abs_location_id=430006,funcName=stosl,srcFileId=43,locationId=6*/
  asm volatile("cld; rep stosl" :
               "=D" (addr), "=c" (cnt) :
               "0" (addr), "1" (cnt), "a" (data) :
               "memory", "cc");
}

struct segdesc;

static inline void
lgdt(struct segdesc *p, int size)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $430007,%%edi \n\t"    "0: \n\t" : : ); /*filePath=x86.h,line=65,column=1,abs_location_id=430007,funcName=lgdt,srcFileId=43,locationId=7*/
  volatile ushort pd[3];

  pd[0] = size-1;
  pd[1] = (uint)p;
  pd[2] = (uint)p >> 16;

  asm volatile("lgdt (%0)" : : "r" (pd));
}

struct gatedesc;

static inline void
lidt(struct gatedesc *p, int size)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $430008,%%edi \n\t"    "0: \n\t" : : ); /*filePath=x86.h,line=79,column=1,abs_location_id=430008,funcName=lidt,srcFileId=43,locationId=8*/
  volatile ushort pd[3];

  pd[0] = size-1;
  pd[1] = (uint)p;
  pd[2] = (uint)p >> 16;

  asm volatile("lidt (%0)" : : "r" (pd));
}

static inline void
ltr(ushort sel)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $430009,%%edi \n\t"    "0: \n\t" : : ); /*filePath=x86.h,line=91,column=1,abs_location_id=430009,funcName=ltr,srcFileId=43,locationId=9*/
  asm volatile("ltr %0" : : "r" (sel));
}

static inline uint
readeflags(void)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $430010,%%edi \n\t"    "0: \n\t" : : ); /*filePath=x86.h,line=97,column=1,abs_location_id=430010,funcName=readeflags,srcFileId=43,locationId=10*/
  uint eflags;
  asm volatile("pushfl; popl %0" : "=r" (eflags));
  return eflags;
}

static inline void
loadgs(ushort v)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $430011,%%edi \n\t"    "0: \n\t" : : ); /*filePath=x86.h,line=105,column=1,abs_location_id=430011,funcName=loadgs,srcFileId=43,locationId=11*/
  asm volatile("movw %0, %%gs" : : "r" (v));
}

static inline void
cli(void)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $430012,%%edi \n\t"    "0: \n\t" : : ); /*filePath=x86.h,line=111,column=1,abs_location_id=430012,funcName=cli,srcFileId=43,locationId=12*/
  asm volatile("cli");
}

static inline void
sti(void)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $430013,%%edi \n\t"    "0: \n\t" : : ); /*filePath=x86.h,line=117,column=1,abs_location_id=430013,funcName=sti,srcFileId=43,locationId=13*/
  asm volatile("sti");
}

static inline uint
xchg(volatile uint *addr, uint newval)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $430014,%%edi \n\t"    "0: \n\t" : : ); /*filePath=x86.h,line=123,column=1,abs_location_id=430014,funcName=xchg,srcFileId=43,locationId=14*/
  uint result;

  // The + in "+m" denotes a read-modify-write operand.
  asm volatile("lock; xchgl %0, %1" :
               "+m" (*addr), "=a" (result) :
               "1" (newval) :
               "cc");
  return result;
}

static inline uint
rcr2(void)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $430015,%%edi \n\t"    "0: \n\t" : : ); /*filePath=x86.h,line=136,column=1,abs_location_id=430015,funcName=rcr2,srcFileId=43,locationId=15*/
  uint val;
  asm volatile("movl %%cr2,%0" : "=r" (val));
  return val;
}

static inline void
lcr3(uint val)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $430016,%%edi \n\t"    "0: \n\t" : : ); /*filePath=x86.h,line=144,column=1,abs_location_id=430016,funcName=lcr3,srcFileId=43,locationId=16*/
  asm volatile("movl %0,%%cr3" : : "r" (val));
}

//PAGEBREAK: 36
// Layout of the trap frame built on the stack by the
// hardware and by trapasm.S, and passed to trap().
struct trapframe {
  // registers as pushed by pusha
  uint edi;
  uint esi;
  uint ebp;
  uint oesp;      // useless & ignored
  uint ebx;
  uint edx;
  uint ecx;
  uint eax;

  // rest of trap frame
  ushort gs;
  ushort padding1;
  ushort fs;
  ushort padding2;
  ushort es;
  ushort padding3;
  ushort ds;
  ushort padding4;
  uint trapno;

  // below here defined by x86 hardware
  uint err;
  uint eip;
  ushort cs;
  ushort padding5;
  uint eflags;

  // below here only when crossing rings, such as from user to kernel
  uint esp;
  ushort ss;
  ushort padding6;
};
