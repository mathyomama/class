	.text
	.globl	main
main:
	addiu	$t0, $0, -1
	la	$t1, num
	lw	$t1, 0($t1)
	sltu	$a0, $t0, $t1
	addi 	$v0, $0, 1
	syscall
	addi 	$v0, $0, 10
	syscall

	.data
num:
	.word	4294967294
