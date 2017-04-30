void pop_direct_branch()
{
  __asm__ (  "popq %rbp\n\t"
	     "addq $8, %rsp\n\t"
	     "leave\n\t"
	     "movq (%rsp), %rax\n\t"
	     "addq $8, %rsp\n\t"
	     "jmp *%rax\n\t"
	   );
}
