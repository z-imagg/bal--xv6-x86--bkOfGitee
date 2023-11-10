void f(){
	int pa;
    __asm__  __volatile__ (  "movl %%eax, 0x7b00 \n\t"  
      "movl %0, %%eax \n\t"    
      "nop \n\t"     
      :  
      : "m"(pa) 
       );
}

