#  __execve.S
#  executes the syscall
#  (c) 2019 MIT License
#  Marcel Bobolz
#  <ergotamin.source@gmail.com>

        .globl __asm_execve

        .text
__asm_execve:
        push           %rdi	        # argv[0]
        push           %rsi	        # argv
        push	       %rdx	        # envp
        mov            $59,     %rax	# sys_exexve
        syscall	                        # call execve
        ret	                        # should not return