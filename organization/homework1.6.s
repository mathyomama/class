	.file	"homework1.6.c"
	.section	.rodata
.LC0:
	.string	""
	.string	"\377"
.LC5:
	.string	"HEX: %X\nDECIMAL: %E\n\n"
	.text
	.globl	show_number
	.type	show_number, @function
show_number:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$72, %esp
	movl	$.LC0, %eax
	movzwl	(%eax), %eax
	cmpw	$255, %ax
	ja	.L2
	movl	8(%ebp), %eax
	shrl	$9, %eax
	movl	%eax, -12(%ebp)
	movzwl	8(%ebp), %eax
	shrw	%ax
	andb	$255, %ah
	movzbl	%al, %eax
	movl	%eax, -16(%ebp)
	movzbl	8(%ebp), %eax
	andl	$1, %eax
	movzbl	%al, %eax
	movl	%eax, -20(%ebp)
	jmp	.L3
.L2:
	movl	8(%ebp), %eax
	andl	$8388607, %eax
	movl	%eax, -12(%ebp)
	movzwl	10(%ebp), %eax
	shrw	$7, %ax
	andb	$255, %ah
	movzbl	%al, %eax
	movl	%eax, -16(%ebp)
	movzbl	11(%ebp), %eax
	shrb	$7, %al
	movzbl	%al, %eax
	movl	%eax, -20(%ebp)
.L3:
	movl	-20(%ebp), %eax
	movl	$0, %edx
	movl	%eax, -56(%ebp)
	movl	%edx, -52(%ebp)
	fildq	-56(%ebp)
	fstpl	-48(%ebp)
	fldl	-48(%ebp)
	leal	-8(%esp), %esp
	fstpl	(%esp)
	fld1
	fchs
	leal	-8(%esp), %esp
	fstpl	(%esp)
	call	pow
	addl	$16, %esp
	movl	-12(%ebp), %eax
	movl	$0, %edx
	movl	%eax, -56(%ebp)
	movl	%edx, -52(%ebp)
	fildq	-56(%ebp)
	fstpl	-48(%ebp)
	fldl	-48(%ebp)
	fldl	.LC2
	fmulp	%st, %st(1)
	fld1
	faddp	%st, %st(1)
	fmulp	%st, %st(1)
	fstpl	-56(%ebp)
	movl	-16(%ebp), %eax
	subl	$127, %eax
	movl	%eax, -64(%ebp)
	movl	$0, -60(%ebp)
	fildq	-64(%ebp)
	fstpl	-48(%ebp)
	fldl	-48(%ebp)
	leal	-8(%esp), %esp
	fstpl	(%esp)
	fldl	.LC4
	leal	-8(%esp), %esp
	fstpl	(%esp)
	call	pow
	addl	$16, %esp
	fmull	-56(%ebp)
	fstpl	-32(%ebp)
	movl	8(%ebp), %eax
	pushl	-28(%ebp)
	pushl	-32(%ebp)
	pushl	%eax
	pushl	$.LC5
	call	printf
	addl	$16, %esp
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	show_number, .-show_number
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	leal	4(%esp), %ecx
	.cfi_def_cfa 1, 0
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	.cfi_escape 0x10,0x5,0x2,0x75,0
	movl	%esp, %ebp
	pushl	%ecx
	.cfi_escape 0xf,0x3,0x75,0x7c,0x6
	subl	$20, %esp
	movl	$-23, -24(%ebp)
	movl	$-161, -20(%ebp)
	movl	$2147483487, -16(%ebp)
	movl	$0, -12(%ebp)
	jmp	.L5
.L6:
	movl	-12(%ebp), %eax
	movl	-24(%ebp,%eax,4), %eax
	subl	$12, %esp
	pushl	%eax
	call	show_number
	addl	$16, %esp
	addl	$1, -12(%ebp)
.L5:
	movl	-12(%ebp), %eax
	cmpl	$2, %eax
	jbe	.L6
	movl	$0, %eax
	movl	-4(%ebp), %ecx
	.cfi_def_cfa 1, 0
	leave
	.cfi_restore 5
	leal	-4(%ecx), %esp
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.section	.rodata
	.align 8
.LC2:
	.long	0
	.long	1048576000
	.align 8
.LC4:
	.long	0
	.long	1073741824
	.ident	"GCC: (GNU) 4.9.1 20140903 (prerelease)"
	.section	.note.GNU-stack,"",@progbits
