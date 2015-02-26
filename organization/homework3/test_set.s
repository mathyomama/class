# Program to test if a set function works properly
# Written by Xiuwen Liu for CDA 3100 - Homework #3, problem #1
# Register usage
# $s7 - save $ra
# $s2 - current address of the string to be tested
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
	add	$a2, $v0,  $zero #save the value to a2
	add	$s6, $a2,  $zero
	la	$a0, array_a	 # the address of the array
	li	$a1, 1000	 # the size of the array of 1000
	jal	set
	la	$s2, array_a
	lw	$a0, 0($s2)	  # $a0 is the integer to be printed
	li      $v0, 1		  # system call to print an integer
	syscall			  # print int
	la	$a0, space_msg
	li      $v0, 4
	syscall
	lw	$a0, 4000($s2)	  # $a0 is the integer to be printed
	li      $v0, 1		  # system call to print an integer
	syscall			  # print int

	add	$s1, $zero, $zero
for_loop:
	slti	$s0, $s1, 1000
	beq	$s0, $zero, end_loop
	sll	$s4, $s1, 2
	addu	$s3, $s2, $s4	  #a[s1]
	lw	$s4, 0($s3)
	bne	$s6, $s4, no_good
	addi	$s1, $s1, 1
	j	for_loop	
end_loop:	
	li      $v0, 4		#it is working
        la      $a0, is_good_msg
	syscall
	j	end_main
no_good:			#it is not working
	li      $v0, 4 
        la      $a0, not_good_msg	 
	syscall
end_main:	
	addu    $ra, $zero, $s7  #restore $ra since the function calles
		#another function
	jr      $ra
	add	$zero, $zero, $zero
	add	$zero, $zero, $zero
########## End of main function #########
	.data
#Data segment starts here
is_good_msg: 
	.asciiz "\n The program is working properly.\n"
not_good_msg: 
	.asciiz "\n The program is not working properly.\n"
int_prompt:
	.asciiz "Please enter an integer: "
space_msg:	
	.asciiz " "	
array_a:
	.align 2
	.space	4000
	.word	-5, -4, -3, -2, -1
	
