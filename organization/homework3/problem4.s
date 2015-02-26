	.text
	.globl	fib
fib:
	addi	$sp, $sp, -12	# saving callee saved variables
	sw	$ra, 0($sp)
	sw	$s0, 4($sp)
	sw	$s1, 8($sp)
	beq	$a0, $0, EXIT0	# check if argument is 0
	addi	$t0, $0, 1
	beq	$a0, $t0, EXIT1	# check if argument is 1
	addi	$sp, $sp, -8	# saving caller saved variables
	sw	$a0, 0($sp)
	sw	$t0, 4($sp)
	addi	$a0, $a0, -1	# subtract 1 for the first call
	jal	fib		# first jump to fib
	lw	$a0, 0($sp)	# load the argument back
	add	$s0, $v0, $0	# put the returned value into s0
	addi	$a0, $a0, -2	# subtract two for the next call
	jal	fib		# second jump to fib
	lw	$t0, 4($sp)
	lw	$a0, 0($sp)
	addi	$sp, $sp, 8	# restoring the caller saved variables
	add	$s1, $v0, $0	# put the second value into s1
	add	$v0, $s1, $s2	# add the two values and put it into v0
	lw	$s1, 8($sp)
	lw	$s0, 4($sp)
	lw	$ra, 0($sp)
	addi	$sp, $sp, 12	# restore the point to it's place before the call
	jr	$ra		# jump to next instruction
EXIT0:
	add 	$v0, $0, $0
	lw	$s1, 8($sp)
	lw	$s0, 4($sp)
	lw	$ra, 0($sp)
	addi	$sp, $sp, 12	# restore the point to it's place before the call
	jr	$ra
EXIT1:
	addi	$v0, $0, 1
	lw	$s1, 8($sp)
	lw	$s0, 4($sp)
	lw	$ra, 0($sp)
	addi	$sp, $sp, 12	# restore the point to it's place before the call
	jr	$ra
