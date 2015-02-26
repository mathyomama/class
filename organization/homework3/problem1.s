	.text
	.globl 	set
set:
	addi	$sp, $sp, -4	# making room on the stack
	sw	$s0, 0($sp)	# saving callee-saved variable which will be used later
	add	$s0, $0, $0	# setting i to zero
loop:
	sll	$t0, $s0, 2	# multiply increment by 4 for number of bytes
	add 	$t0, $a0, $t0	# setting the address to the right value
	sw	$a2, 0($t0)	# saving value v in array
	addi	$s0, $s0, 1	# increment i by one
	slt	$t1, $s0, $a1	# checking if i < n
	bne	$t1, $0, loop	# branch if the comparison is true, i.e. $t1 is not zero
	add	$v0, $s0, $0	# put the return value in v0
	lw	$s0, 0($sp)	# restore the callee-saved value
	addi	$sp, $sp, 4	# restore the stack pointer position
	jr	$ra		# jump to the return address
