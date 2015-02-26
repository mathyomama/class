# Program to test if a palindrome function works properly or not
# Written by Xiuwen Liu for CDA 3100 - Homework #3, problem #2
# Register usage
# $s7 - save $ra
# $s2 - current address of the string to be tested
# $s3 - the next of the last string to be tested 
# $a0 - for function parameter / syscall parameter
# $v0 - syscall number / function return value
					
	.text
	.globl main
main:
	addu     $s7, $ra, $zero, # Save the ra
	la	$s2,  test_str    # Load the starting address of the array
	la	$s3, is_pali_msg, # the next of last address
pali_test_loop:	
	lw	$a0, 0($s2)	  # $a0 is the address of the string
	li      $v0, 4		  # system call to print a string
	syscall			  # print string
	li      $v0, 4		  # print a new line
        la      $a0, newline
	li      $v0, 4 
	syscall
	lw	$a0, 0($s2)	  # $a0 is the address of the string
	jal	palindrome	  # call palindrome
	beq	$v0, $zero, pali_no #if $v0 is 0, it is not a palindrome
	li      $v0, 4		#it is a palindrome
        la      $a0, is_pali_msg
	syscall
	j	pali_test_end
pali_no:			#it is not a palindrome
	li      $v0, 4 
        la      $a0, not_pali_msg	 
	syscall
pali_test_end:
	li      $v0, 4 
        la      $a0, newline
	syscall
	addiu	$s2, $s2, 4
	lw	$a0, 0($s2)
	beq	$a0, $s3, pali_done
	j	pali_test_loop

pali_done:
	li	$v0, 10
	syscall
	addu    $ra, $zero, $s7  #restore $ra since the function calles
		#another function
	jr      $ra
	add	$zero, $zero, $zero
	add	$zero, $zero, $zero
########## End of main function #########
	.data
#The following examples were copied from 
#	http://en.wikipedia.org/wiki/Palindrome
pali1:	
	.asciiz "Socorram me subi no on ibus em Marrocos" #Brazilian Portuguese
pali2:	
	.asciiz	"Ein Neger mit Gazelle zagtim Regen nie" #German
pali3:	
	.asciiz "stressed  desserts"
pali4:
	.asciiz	"palindromes"
pali5:	
	.asciiz "tattarrattat"
is_pali_msg: 
	.asciiz "    The string is a palindrome."
not_pali_msg: 
	.asciiz "    The string is not a palindrome."
newline:	
	.asciiz "\n"	
test_str:
	.word  pali1, pali2, pali3, pali4, pali5, is_pali_msg
	
