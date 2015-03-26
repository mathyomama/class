# ***********************
# BASE CONVERSION PROGRAM
# ***********************
# This program converts a number in a certain base to a
# number in decimal. The program will prompt for a base
# followed by a prompt for a value. The base will be an
# int and the value will be read as a string. The value
# will be converted to a string with only lowercase chars
# for convenience. The base and value will be checked to
# make sure they are valid. The conversion will then be
# printed.
# ***********************
# The first part is the the main function
# ***********************

	.text
	.globl	main
main:
	addi	$sp, $sp, -12		# make room on the stack
	sw	$ra, 0($sp)		# put the return address on the stack
	sw	$s0, 4($sp)		# put value of $s0 on the stack
	sw	$s1, 8($sp)
	addi	$v0, $0, 4
	la	$a0, first_prompt
	syscall				# $v0 == 4, print first prompt
	addi	$v0, $0, 5
	syscall				# $v0 == 5, read integer
	add	$s0, $v0, $0		# put result into $s0
	add	$a0, $s0, $0		# put base into argument
	jal	check_base		# check if base is correct
	beq	$v0, $0, BAD_BASE	# goto BAD_BASE if $v0 == 0
	addi	$v0, $0, 4
	la	$a0, second_prompt
	syscall				# print second prompt
	addi	$v0, $0, 1
	add	$a0, $s0, $0
	syscall				# $v0 == 1, print integer
	addi	$v0, $0, 4
	la	$a0, colon
	syscall				# print colon
	addi	$v0, $0, 9
	addi	$a0, $0, 33		# need at most 32 bytes for base 2, need extra byte for null byte
	syscall				# $v0 == 9, make space on heap
	add	$s1, $v0, $0		# put address of new block of memory into $s1
	addi	$v0, $0, 8		# 8 for read string
	add	$a0, $s1, $0
	addi	$a1, $0, 32		# 32 bytes
	syscall				# $v0 == 8, read string into starting addr $a0 for $a1 bytes

	jal	to_lower		# $a0 holds addr of string, convert characters to lowercase

	add	$s1, $v0, $0		# save address into $s1
	add	$a0, $s0, $0		# put base into first argument
	add	$a1, $s1, $0		# put address of value into second argument
	jal	check_value		# check if the value is valid
	beq	$v0, $0, BAD_VALUE	# goto BAD_VALUE if $v0 == 0

	add	$a0, $s0, $0
	add	$a1, $s1, $0
	jal	convert_to_decimal
	add	$t0, $v0, $0		# put the result into $t0

	addi	$v0, $0, 4
	la	$a0, output
	syscall				# print output
	addi	$v0, $0, 1
	add	$a0, $t0, $0		# put integer into $a0
	syscall				# print answer
	addi	$v0, $0, 4
	la	$a0, newline
	syscall				# print newline
	j	EXIT_MAIN
BAD_BASE:
	addi	$v0, $0, 4
	la	$a0, not_valid_base
	syscall
	j	EXIT_MAIN
BAD_VALUE:
	addi	$v0, $0, 4
	la	$a0, not_valid_number
	syscall
EXIT_MAIN:
	lw	$s1, 8($sp)
	lw	$s0, 4($sp)
	lw	$ra, 0($sp)
	addi	$sp, $sp, 12
	jr	$ra
	add	$0, $0, $0		# not sure what this is for
	add	$0, $0, $0


# ***********************
# The next part is the data associated with the main function
# ***********************

	.data
first_prompt:
	.asciiz	"Enter a base (between 2 and 36 decimal): "

second_prompt:
	.asciiz	"Enter a number in base "

output:
	.asciiz "The value in decimal is: "

colon:
	.asciiz ": "

newline:
	.asciiz "\n"

not_valid_base:
	.asciiz "That is not a valid base.\n"

not_valid_number:
	.asciiz "That is not a valid number for the given base.\n"


# ***********************
# The third part is the collection of functions used in main
# ***********************

	.text
# this function converts a string value to the lowercase form.
# the address of the string is in $a0 and assumes it is null
# terminated. the returned value is the address of the string
to_lower:
	add	$t0, $0, $0		# set $t0 to 0
TO_LOWER_LOOP:
	add	$t1, $t0, $a0		# simply add the increment since char is one byte long
	lbu	$t3, 0($t1)		# put the char into $t1
	addi	$t5, $0, 10		# 10 == '\n', what is placed at the end of the input string
	beq	$t3, $t5, TO_LOWER_EXIT	# check if $t3 is a newline character (will also check if it's a null byte below)
	beq	$t3, $0, TO_LOWER_EXIT	# check if it's the end of the string
	addi	$t0, $t0, 1		# increment $t0
	slti	$t2, $t3, 65		# 65 is the ascii value of 'A'
	bne	$t2, $0, TO_LOWER_LOOP	# branch back to LOWER_LOOP
	slti	$t2, $t3, 91		# 91 is the ascii value of '[', the char before 'Z'
	beq	$t2, $0, TO_LOWER_LOOP
	addi	$t3, $t3, 32		# 32 is the distance between the 'A' and 'a'
	sb	$t3, 0($t1)		# store the changed byte
	j	TO_LOWER_LOOP
TO_LOWER_EXIT:
	add	$v0, $a0, $0
	jr	$ra

# this function takes in a base between 2 and 36 put in $a0
# and the address of the value which is a string in $a1. It
# doesn't check for if the base is between 2 and 36 and if
# the value is valid for the given base, the main function
# will do that.
convert_to_decimal:
	addi	$sp, $sp, -4		# make room for $s0
	sw	$s0, 0($sp)		# store $s0
	add	$s0, $0, $0		# set the accumulator, $s0, to 0
	add	$t0, $0, $0		# set $t0 to 0
CONVERT_LOOP:
	add	$t1, $a1, $t0		# set $t1 to the address of the first char
	lbu	$t2, 0($t1)		# load the char from the string into $t2
	addi	$t5, $0, 10		# 10 == '\n', what is placed at the end of the input string
	beq	$t2, $t5, CONVERT_EXIT	# check if $t2 is a newline character (will also check if it's a null byte below)
	beq	$t2, $0, CONVERT_EXIT	# branch if the string has reached the null byte
	addi	$t0, $t0, 1		# increment before the loop back
	mul	$s0, $s0, $a0		# multiply the accumulator by the base, like a shift
	slti	$t3, $t2, 58		# check if $t2 < ':', we already checked if the characters were valid
	beq	$t3, $0, ABC_BRANCH	# branch if $t2 > '9', character should then be 'a', 'b',...
	addi	$t5, $t2, -48		# get the digit value of the char in $t2
	add	$s0, $s0, $t5		# add the digit to the accumulator
	j	CONVERT_LOOP		# loop back to beginning
ABC_BRANCH:
	addi	$t5, $t2, -87		# get the digit value of the char, 87 == 'W' but 10 below 97 == 'a'
	add	$s0, $s0, $t5		# add the digit to the accumulator
	j	CONVERT_LOOP		# loop back to beginning
CONVERT_EXIT:
	add	$v0, $s0, $0		# put result into $v0
	lw	$s0, 0($sp)		# put value back into $s0 register
	addi	$sp, $sp, 4		# restore the stack
	jr	$ra			# jump back to caller

# this function checks if the base is between 2 and 36,
# the base is put in $a0. 0 is returned for false and 1
# is returned for true
check_base:
	slti	$t0, $a0, 2
	bne	$t0, $0, BASE_FALSE
	slti	$t0, $a0, 37
	beq	$t0, $0, BASE_FALSE
	add	$v0, $t0, $0		# $t0 should be set to 1 from slti at this point
	j	BASE_EXIT
BASE_FALSE:
	add	$v0, $0, $0		# set the return value to 0
BASE_EXIT:
	jr	$ra			# jump back to caller

# this function checks if the value, an ascii string null
# terminated is valid. The base is in $a0 and the value is
# in $a1. 0 is returned for false and 1 is returned for true.
# The part before the loop sets up how the loop will be run.
check_value:
	add	$t0, $0, $0		# set $t0 to 0 for the index
	slti	$t3, $a0, 11		# $t3 will be 1 if the base is 10 or less
	beq	$t3, $0, UPPER_BRANCH	# branch if the base is greater than 10
	addi	$t4, $a0, 48		# 48 == '0' and $t4 holds the least char not in character set
LOWER_LOOP:
	add	$t1, $t0, $a1		# put the address of the current char into t1
	lbu	$t2, 0($t1)		# load the char into $t2
	addi	$t5, $0, 10		# 10 == '\n', the character placed at the end of the input string
	beq	$t2, $t5, VALUE_TRUE	# check if $t2 is a newline character (will also check if it's a null byte below)
	beq	$t2, $0, VALUE_TRUE	# char == null byte, string is a good, all characters have been looked at, not sure if this is possible to reach
	slti	$t5, $t2, 48		# check if char $t2 is less than '0'
	bne	$t5, $0, VALUE_FALSE	# if char < '0' branch to false
	slt	$t5, $t2, $t4		# check if char $t2 is less than $t4
	beq	$t5, $0, VALUE_FALSE	# if char >= number branch to false
	addi	$t0, $t0, 1		# increment index by 1
	j	LOWER_LOOP		# loop back
UPPER_BRANCH:
	addi	$t4, $a0, 87		# 97 == 'a', 87 accounts for first ten digits and $t4 holds the least char not in character set
UPPER_LOOP:
	add	$t1, $t0, $a1		# put the address of the current char into t1
	lbu	$t2, 0($t1)		# load the char into $t2
	addi	$t5, $0, 10		# same routine as LOWER_LOOP
	beq	$t2, $t5, VALUE_TRUE
	beq	$t2, $0, VALUE_TRUE
	slti	$t5, $t2, 48
	bne	$t5, $0, VALUE_FALSE
	addi	$t0, $t0, 1		# increment index by 1, do it here before the jump back to UPPER_LOOP
	slti	$t5, $t2, 58		# check if char $t2 is less than ':', one above '9'
	bne	$t5, $0, UPPER_LOOP	# if char >= number branch to false
	slti	$t5, $t2, 97		# check if char $t2 is less than 'a'
	bne	$t5, $0, VALUE_FALSE	# branch if ':' >= $t2 > 'a' to VALUE_FALSE
	slt	$t5, $t2, $t4		# check if char $t2 is less than $t4
	beq	$t5, $0, VALUE_FALSE	# branch if $t2 >= $t4
	j	UPPER_LOOP		# loop back
VALUE_FALSE:
	add	$v0, $0, $0		# return value is false
	j	VALUE_EXIT
VALUE_TRUE:
	addi	$v0, $0, 1		# return value is true
VALUE_EXIT:
	jr	$ra			# jump back to caller
	
