#pragma message("funcId_asm_inserted")
// Sleeping locks

#include "types.h"
#include "defs.h"
#include "param.h"
#include "x86.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "spinlock.h"
#include "sleeplock.h"

void
initsleeplock(struct sleeplock *lk, char *name)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $340000,%%edi \n\t"    "0: \n\t" : : ); /*filePath=sleeplock.c,line=15,column=1,abs_location_id=340000,funcName=initsleeplock,srcFileId=34,locationId=0*/
  initlock(&lk->lk, "sleep lock");
  lk->name = name;
  lk->locked = 0;
  lk->pid = 0;
}

void
acquiresleep(struct sleeplock *lk)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $340001,%%edi \n\t"    "0: \n\t" : : ); /*filePath=sleeplock.c,line=24,column=1,abs_location_id=340001,funcName=acquiresleep,srcFileId=34,locationId=1*/
  acquire(&lk->lk);
  while (lk->locked) {
    sleep(lk, &lk->lk);
  }
  lk->locked = 1;
  lk->pid = myproc()->pid;
  release(&lk->lk);
}

void
releasesleep(struct sleeplock *lk)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $340002,%%edi \n\t"    "0: \n\t" : : ); /*filePath=sleeplock.c,line=36,column=1,abs_location_id=340002,funcName=releasesleep,srcFileId=34,locationId=2*/
  acquire(&lk->lk);
  lk->locked = 0;
  lk->pid = 0;
  wakeup(lk);
  release(&lk->lk);
}

int
holdingsleep(struct sleeplock *lk)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $340003,%%edi \n\t"    "0: \n\t" : : ); /*filePath=sleeplock.c,line=46,column=1,abs_location_id=340003,funcName=holdingsleep,srcFileId=34,locationId=3*/
  int r;
  
  acquire(&lk->lk);
  r = lk->locked && (lk->pid == myproc()->pid);
  release(&lk->lk);
  return r;
}



