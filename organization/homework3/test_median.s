# Program to test if a median function works properly
# Written by Xiuwen Liu for CDA 3100 - Homework #3, problem #3
# Register usage
# $s7 - save $ra
# $s1 - used as a temporary register
# $s3 - the next of the last string to be tested 
# $a0 - for function parameter / syscall parameter
# $v0 - syscall number / function return value
					
	.text
	.globl main
main:
	addu    $s7, $ra, $zero, # Save the ra
	la	$a0, int_prompt
	li	$v0, 4
	syscall
	li	$v0,  5
	syscall
	slti	$s1, $v0, 100	# is $v0 < 100
	bne	$s1, $zero, within_limit
	li	$v0, 100
within_limit:		
	add	$a1, $v0,  $zero #save the value to a2
	la	$a0, array_a	 # the address of the array
	jal	median
	add	$s1, $v0, $zero   # We save the result first
	
	la	$a0, median_msg
	li      $v0, 4
	syscall
	add	$a0, $s1, $zero	  # $a0 is the integer to be printed
	li      $v0, 1		  # system call to print an integer
	syscall			  # print int
	la	$a0, newline
	li	$v0, 4
	syscall
	
	addu    $ra, $zero, $s7  #restore $ra since the function calles
		#another function
	jr      $ra
	add	$zero, $zero, $zero
	add	$zero, $zero, $zero
########## End of main function #########
	.data
#Data segment starts here
median_msg:
	.asciiz "The median is "
newline:
	.asciiz ".\n"
int_prompt:
	.asciiz "Please enter an integer: "
array_a:
	.align 2
	.word 7, 16, 291, 272, 287, 113, 372, 378, 159, 259
	.word 380, 190, 137, 236, 390, 200, 239, 14, 25, 32
	.word 396, 338, 194, 143, 142, 11, 88, 284, 256, 76
	.word 46, 181, 63, 247, 393, 36, 342, 51, 250, 126
	.word 343, 261, 75, 244, 39, 241, 320, 180, 265, 215
	.word 102, 17, 343, 134, 189, 5, 273, 217, 135, 186
	.word 356, 45, 54, 148, 253, 337, 20, 154, 68, 315
	.word 359, 80, 72, 161, 201, 103, 209, 122, 3, 266
	.word 262, 28, 251, 149, 131, 66, 147, 123, 338, 71
	.word 256, 17, 235, 3, 152, 60, 394, 128, 73, 193 
	.word -5, -4, -3, -2, -1
