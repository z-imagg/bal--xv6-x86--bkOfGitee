void f(){
	int pa;
    __asm__  __volatile__ ( 
 
      "movl %0, %%eax \n\t"    
      "nop \n\t"     
      :  
      : "m"(pa) 
       );
}

