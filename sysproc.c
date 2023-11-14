#pragma message("funcId_asm_inserted")
#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $390000,%%edi \n\t"    "0: \n\t" : : ); /*filePath=sysproc.c,line=12,column=1,abs_location_id=390000,funcName=sys_fork,srcFileId=39,locationId=0*/
  return fork();
}

int
sys_exit(void)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $390001,%%edi \n\t"    "0: \n\t" : : ); /*filePath=sysproc.c,line=18,column=1,abs_location_id=390001,funcName=sys_exit,srcFileId=39,locationId=1*/
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $390002,%%edi \n\t"    "0: \n\t" : : ); /*filePath=sysproc.c,line=25,column=1,abs_location_id=390002,funcName=sys_wait,srcFileId=39,locationId=2*/
  return wait();
}

int
sys_kill(void)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $390003,%%edi \n\t"    "0: \n\t" : : ); /*filePath=sysproc.c,line=31,column=1,abs_location_id=390003,funcName=sys_kill,srcFileId=39,locationId=3*/
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $390004,%%edi \n\t"    "0: \n\t" : : ); /*filePath=sysproc.c,line=41,column=1,abs_location_id=390004,funcName=sys_getpid,srcFileId=39,locationId=4*/
  return myproc()->pid;
}

int
sys_sbrk(void)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $390005,%%edi \n\t"    "0: \n\t" : : ); /*filePath=sysproc.c,line=47,column=1,abs_location_id=390005,funcName=sys_sbrk,srcFileId=39,locationId=5*/
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $390006,%%edi \n\t"    "0: \n\t" : : ); /*filePath=sysproc.c,line=61,column=1,abs_location_id=390006,funcName=sys_sleep,srcFileId=39,locationId=6*/
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $390007,%%edi \n\t"    "0: \n\t" : : ); /*filePath=sysproc.c,line=84,column=1,abs_location_id=390007,funcName=sys_uptime,srcFileId=39,locationId=7*/
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
