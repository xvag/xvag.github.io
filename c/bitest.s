	.file	"bitest.c"
	.section	.rodata
.LC0:
	.string	"%d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$255, -4(%rbp)
	movl	$0, -8(%rbp)
	jmp	.L2
.L4:
	movl	-4(%rbp), %eax
	andl	$1, %eax
	testl	%eax, %eax
	je	.L3
	addl	$1, -8(%rbp)
.L3:
	sarl	-4(%rbp)
.L2:
	cmpl	$0, -4(%rbp)
	jne	.L4
	movl	-8(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 7.2.0"
	.section	.note.GNU-stack,"",@progbits
