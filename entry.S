# The xv6 kernel starts executing in this file. This file is linked with
# the kernel C code, so it can refer to kernel symbols such as main().
# The boot block (bootasm.S and bootmain.c) jumps to entry below.
        
# Multiboot header, for multiboot boot loaders like GNU Grub.
# http://www.gnu.org/software/grub/manual/multiboot/multiboot.html
#
# Using GRUB 2, you can boot xv6 from a file stored in a
# Linux file system by copying kernel or kernelmemfs to /boot
# and then adding this menu entry:
#
# menuentry "xv6" {
# 	insmod ext2
# 	set root='(hd0,msdos1)'
# 	set kernel='/boot/kernel'
# 	echo "Loading ${kernel}..."
# 	multiboot ${kernel} ${kernel}
# 	boot
# }

#include "asm.h"
#include "memlayout.h"
#include "mmu.h"
#include "param.h"

# Multiboot header.  Data to direct multiboot loader.
.p2align 2
.text
.globl multiboot_header
multiboot_header:
  #define magic 0x1badb002
  #define flags 0
  .long magic
  .long flags
  .long (-magic-flags)

# By convention, the _start symbol specifies the ELF entry point.
# Since we haven't set up virtual memory yet, our entry point is
# the physical address of 'entry'.
.globl _start
_start = V2P_WO(entry)

# Entering xv6 on boot processor, with paging off.
.globl entry
entry:
  # Turn on page size extension for 4Mbyte pages
  movl    %cr4, %eax
  orl     $(CR4_PSE), %eax
  movl    %eax, %cr4
  # Set page directory
  movl    $(V2P_WO(entrypgdir)), %eax
  movl    %eax, %cr3
  # Turn on paging.
  movl    %cr0, %eax
  orl     $(CR0_PG|CR0_WP), %eax
  movl    %eax, %cr0

  # Set up the stack pointer.
  movl $(stack + KSTACKSIZE), %esp
  test $stack, %eax
  test $KSTACKSIZE, %eax
  test $(stack + KSTACKSIZE), %eax

/**
语法                 intel      AT&T(即GCC汇编)
通用寄存器           pusha      pushal
                    popa       popal  
eflags状态寄存器     pushfd     pushfl  
                    popfd      popfl  
*/

  nop  #空指令标记供人工观测
  pushal
  pushfl  #保存现场

  #开始处理
  pushl $stack #目标值进栈
  popl %edx    #目标值进edx
  TESTL 0x7b00, %ecx  #'0x7b00' 读内存断点(gdb rwatch) , 断点触发时打印edx值即目标值. (显然任选一个寄存器都可以，未必非要ecx)

  pushl $KSTACKSIZE #目标值进栈
  popl %edx    #目标值进edx
  TESTL 0x7a00, %ecx  #'0x7a00' 读内存断点(gdb rwatch) , 断点触发时打印edx值即目标值. (显然任选一个寄存器都可以，未必非要ecx)


  #结束处理


  popfl
  popal  #恢复现场
  nop  #空指令标记供人工观测


  # gdb单步打印此些指令如下:

	  
  # Jump to main(), and switch to executing at
  # high addresses. The indirect call is needed because
  # the assembler produces a PC-relative instruction
  # for a direct jump.
  mov $main, %eax
  jmp *%eax

.comm stack, KSTACKSIZE
