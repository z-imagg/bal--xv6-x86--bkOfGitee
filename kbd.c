#pragma message("funcId_asm_inserted")
#include "types.h"
#include "x86.h"
#include "defs.h"
#include "kbd.h"

int
kbdgetc(void)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $260000,%%edi \n\t"    "0: \n\t" : : ); /*filePath=kbd.c,line=8,column=1,abs_location_id=260000,funcName=kbdgetc,srcFileId=26,locationId=0*/
  static uint shift;
  static uchar *charcode[4] = {
    normalmap, shiftmap, ctlmap, ctlmap
  };
  uint st, data, c;

  st = inb(KBSTATP);
  if((st & KBS_DIB) == 0)
    return -1;
  data = inb(KBDATAP);

  if(data == 0xE0){
    shift |= E0ESC;
    return 0;
  } else if(data & 0x80){
    // Key released
    data = (shift & E0ESC ? data : data & 0x7F);
    shift &= ~(shiftcode[data] | E0ESC);
    return 0;
  } else if(shift & E0ESC){
    // Last character was an E0 escape; or with 0x80
    data |= 0x80;
    shift &= ~E0ESC;
  }

  shift |= shiftcode[data];
  shift ^= togglecode[data];
  c = charcode[shift & (CTL | SHIFT)][data];
  if(shift & CAPSLOCK){
    if('a' <= c && c <= 'z')
      c += 'A' - 'a';
    else if('A' <= c && c <= 'Z')
      c += 'a' - 'A';
  }
  return c;
}

void
kbdintr(void)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $260001,%%edi \n\t"    "0: \n\t" : : ); /*filePath=kbd.c,line=48,column=1,abs_location_id=260001,funcName=kbdintr,srcFileId=26,locationId=1*/
  consoleintr(kbdgetc);
}
