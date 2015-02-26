	.text
	.globl	palindrome
palindrome:
	addi	$sp, $sp, -8	# making room on the stack
	sw	$s0, 0($sp)	# s0 will be the index
	sw	$s1, 4($sp)	# s1 will be the second index
	add	$s0, $0, $0	# make s0 0
LOOP1:
	add	$t0, $s0, $a0	# put address of the next character in t0
	lb	$t1, 0($t0)	# put character in t1
	beq	$t1, $0, EXIT1	# check if character is null
	addi	$sp, $sp, -4	# make room on stack for character
	sb	$t1, 0($sp)	# put character on the stack
	addi	$s0, $s0, 1	# increment the index by 1
	j	LOOP1		# go back to the beginning of the loop
EXIT1:
	add	$s1, $0, $0	# set the second index to 0
LOOP2:
	beq	$s0, $0, GOOD	# use the index to go back down the stack, when the index is zero the string is confirmed a palindrome
	lb	$t1, 0($sp)	# load the characters in reverse, t1 holds char from stack
	addi	$sp, $sp, 4	# push stack pointer back by one character
	add	$t0, $s1, $a0	# address into t0
	lb	$t2, 0($t0)	# t2 will hold the char from given array
	addi	$sp, $sp, -24	# put caller-saved variables on the stack
	sw	$ra, 0($sp)	# store return address
	sw	$a0, 4($sp)	# store first argument
	sw	$a1, 8($sp)	# store second argument
	sw	$t0, 12($sp)	# store t0
	sb	$t1, 16($sp)	# store t1
	sb	$t2, 20($sp)	# store t2
	add	$a0, $t1, $0	# put first character in the first argument
	add	$a1, $t2, $0	# put second character in the second argument
	jal	compare		# use compare function to compare to characters
	lbu	$t2, 20($sp)	# load t2
	lbu	$t1, 16($sp)	# load t1
	lw	$t0, 12($sp)	# load t0
	lw	$a1, 8($sp)	# restore second argument
	lw	$a0, 4($sp)	# restore first argument
	lw	$ra, 0($sp)	# restore return address
	addi	$sp, $sp, 24	# restore the stack pointer to position before call
	beq	$v0, $0, EXITP	# if the returned value is zero, break the loop and return zero
	addi	$s0, $s0, -1	# decrement the index by one
	addi	$s1, $s1, 1	# increment the second index by one
	j	LOOP2		# loop
EXITP:
	add	$v0, $0, $0	# set return value to zero
	j	EXIT
GOOD:
	addi	$v0, $0, 1	# set the return value to one
EXIT:
	lw	$s1, 4($sp)	# restore the value in s1
	lw	$s0, 0($sp)	# restore the value in s0
	addi	$sp, $sp, 8	# push stack pointer back up
	jr	$ra		# return to the caller

# Compare function used to determine if the two characters are equivalent
compare:
	add	$v0, $0, $0	# set the return value to 0, not equal until proven otherwise
	beq	$a0, $a1, EQUAL	# branch if the two characters are equal
	slti	$t0, $a0, 64	# t0 is 0 if a0 >= 65, ascii value of 'A'
	slti	$t1, $a0, 90	# t1 is 1 if a0 < 90, ascii value of 'Z'
	bne	$t0, $0, LOWER	# branch if a0 < 63
	beq	$t1, $0, LOWER	# branch if a0 >= 91
	addi	$t2, $a0, 32	# first character is upper case, add 32 for comparison
	bne	$t2, $a1, EXITC	# skip over EQUAL and LOWER if not equal
	j	EQUAL		# go to EQUAL and finish function
LOWER:
	slti	$t0, $a0, 96	# 97 is the ascii value for 'a'
	slti	$t1, $a0, 122	# 122 is the ascii value for 'z'
	bne	$t0, $0, EXITC	# the first character is not A-Z or a-z
	beq	$t1, $0, EXITC	# the first character is not A-Z or a-z
	addi	$t2, $a0, -32	# first character is lower case, add -32 for comparison to second character
	bne	$t2, $a1, EXITC	# skip over EQUAL if not equal
EQUAL:
	addi	$v0, $0, 1	# set the return value to 1, meaning the characters are equivalent
EXITC:
	jr	$ra		# jump to return address
