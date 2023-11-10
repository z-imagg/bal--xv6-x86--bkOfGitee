void f(){
	int pa;
    __asm__  __volatile__ ( 
      "movw $0XBB77, 0x7c00-16 \n\t"  //写内存标记 供gdb条件断点使用 
 
      "movl %eax, 0x7c00-48 \n\t"   //备份eax 
 
      "movl %0, %%eax \n\t"    
      "movl %eax, 0x7c00-32 \n\t"   //记录变量pa值 
 
      "movl 0x7c00-48,%eax  \n\t"   //恢复eax 
      "nop \n\t"     
      :  
      : "m"(pa) 
       );
}

