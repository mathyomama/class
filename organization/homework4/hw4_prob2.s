# *********************
# PGM HISTOGRAM PROGRAM
# *********************
# This will examine a pgm file and print out a histogram of the different
# values. The program will prompt for a pgm file name. The file will first be
# read into memory using the "read_pgm" function and then the array of values
# will be looked at and a histogram of values will be recorded.
# ********************* 
# First part: MAIN
# *********************

	.text
	.globl	main
main:
	addi	$sp, $sp, -20
	sw	$ra, 0($sp)		# store $ra on the stack
	sw	$s0, 4($sp)
	sw	$s1, 8($sp)
	sw	$s2, 12($sp)
	sw	$s3, 16($sp)

	addi	$v0, $0, 4
	la	$a0, prompt
	syscall				# print prompt

	addi	$v0, $0, 8
	la	$a0, file_name
	addi	$a1, $0, 255
	syscall				# read file name from stdin

	add	$t0, $0, $0		# make sure file name is null terminated
	addi	$t2, $0, 10		# 10 == '\n'
FILE_NAME_LOOP:
	add	$t1, $t0, $a0
	lbu	$t3, 0($t1)
	beq	$t3, $t2, FOUND_NEWLINE
	addi	$t0, $t0, 1
	j	FILE_NAME_LOOP
FOUND_NEWLINE:
	add	$t3, $0, $0
	sb	$t3, 0($t1)

	la	$a0, file_name
	la	$a1, rows		# put the address of rows into $a1
	la	$a2, cols		# similar for cols
	jal	read_pgm
	beq	$v0, $0, EXIT_MAIN	# branch if the function returned false
	add	$s0, $v0, $0
	lw	$s1, 0($a1)
	lw	$s2, 0($a2)

	addi	$v0, $0, 4
	la	$a0, row_msg
	syscall				# print row_msg

	addi	$v0, $0, 1
	add	$a0, $s1, $0
	syscall				# print number of rows
	
	addi	$v0, $0, 4
	la	$a0, newline
	syscall				# print newline
	
	addi	$v0, $0, 4
	la	$a0, col_msg
	syscall				# print col_msg

	addi	$v0, $0, 1
	add	$a0, $s2, $0
	syscall				# print number of columns
	
	addi	$v0, $0, 4
	la	$a0, newline
	syscall				# print newline

	addi	$v0, $0, 9
	addi	$t0, $0, 256
	sll	$t0, $t0, 2
	add	$a0, $t0, $0
	syscall				# make room on heap for histogram

	add	$a0, $s0, $0
	add	$a1, $s1, $0
	add	$a2, $s2, $0
	add	$a3, $v0, $0
	jal	histogram
	add	$t3, $a3, $0		# put the address of histogram into $t3

	addi	$v0, $0, 4
	la	$a0, output
	syscall
	add	$t0, $0, $0
HISTO_LOOP:
	slti	$t4, $t0, 256
	beq	$t4, $0, EXIT_MAIN	# once the loop is done, end of program
	sll	$t1, $t0, 2		# multiply by four
	add	$t1, $t1, $t3		# address of current element
	lw	$t2, 0($t1)
	addi	$v0, $0, 1
	add	$a0, $t0, $0
	syscall				# first print the ascii value
	addi	$v0, $0, 4
	la	$a0, colon
	syscall				# print colon
	addi	$v0, $0, 1
	add	$a0, $t2, $0
	syscall				# print value in histogram
	addi	$t0, $t0, 1
	addi	$v0, $0, 4
	la	$a0, newline
	syscall				# print newline
	j	HISTO_LOOP

EXIT_MAIN:
	lw	$s3, 16($sp)
	lw	$s2, 12($sp)
	lw	$s1, 8($sp)
	lw	$s0, 4($sp)
	lw	$ra, 0($sp)		# restore $ra on the stack
	addi	$sp, $sp, 20
	jr	$ra


# *********************
# Second part: data used in main
# *********************

	.data
prompt:
	.asciiz	"Please enter a valid pgm file name: "

row_msg:
	.asciiz	"Number of rows: "

col_msg:
	.asciiz "Number of columns: "

output:
	.asciiz "Histogram of the values in the file:\n"

colon:
	.asciiz	": "

newline:
	.asciiz	"\n"

file_name:
	.space	256

rows:
	.word	0

cols:
	.word	0


# *********************
# Third part: set of functions used in main
# *********************

	.text
# "read_pgm"
# inputs
# $a0 = file name [the pgm file name, should be NULL terminated]
# $a1 = memory address for number of rows [space will be modified in function]
# $a2 = memory address for number of columns [space will be modified in function]
# output
# $v0 = address of array of ascii values/bytes
# This function will allocate memory on the heap for the data from the pgm file.
# the return value is a pointer to that memory.
read_pgm:
	addi	$sp, $sp, -20		# make room on the callee saved registers
	sw	$ra, 0($sp)
	sw	$s0, 4($sp)
	sw	$s1, 8($sp)
	sw	$s2, 12($sp)
	sw	$s3, 16($sp)
	add	$s0, $a0, $0		# put the arguments onto saved registers
	add	$s1, $a1, $0		# this will save multiple loads/stores
	add	$s2, $a2, $0

	addi	$v0, $0, 13		# 13 for opening file
	add	$a1, $0, $0		# $a1 == 0 for read
	add	$a2, $0, $0		# set that to 0, ignore mode
	syscall				# $a0 is already set to the file name
	add	$s3, $v0, $0		# put file descriptor into a $s3
	slt	$t0, $s3, $0		# check if fd < 0
	bne	$t0, $0, BAD_FD		# branch if fd < 0 to BAD_FD

	add	$a0, $s3, $0		# fd in $a0
	jal	check_pgm_id		# checking if the pgm_id is correct, not storing $t0 since it is not important
	beq	$v0, $0, BAD_PGM	# branch if the function returned false/0

	add	$a0, $s3, $0
	add	$a1, $s1, $0		# rows
	add	$a2, $s2, $0		# cols
	jal	grab_row_col
	beq	$v0, $0, BAD_PGM	# branch if the function returned false/0
	add	$t8, $a1, $0
	add	$t9, $a2, $0
	lw	$t0, 0($a1)		# $t0 = row value
	lw	$t1, 0($a2)		# $t1 = col value
	mul	$t2, $t0, $t1		# $t2 = row*col the amount of bytes needed to store the file
	addi	$v0, $0, 9
	add	$a0, $t2, $0
	syscall
	add	$t3, $v0, $0		# put result into $t3

	addi	$v0, $0, 14
	add	$a0, $s3, $0
	add	$a1, $t3, $0
	add	$a2, $t2, $0
	syscall				# read row*col data from the file
	addi	$v0, $0, 16
	add	$a0, $s3, $0
	syscall				# close the file
	add	$v0, $a1, $0		# set the return value to the address of the array
	add	$a1, $t8, $0
	add	$a2, $t9, $0
	j	EXIT_READ_PGM		# more test could be done to make sure that reading of the file was correct and complete
BAD_FD:
	addi	$v0, $0, 4
	la	$a0, invalid_file
	syscall
	add	$a0, $0, $0
	add	$a1, $0, $0
	add	$v0, $0, $0		# address 0x0 is returned
	j	EXIT_READ_PGM
BAD_PGM:
	addi	$v0, $0, 4
	la	$a0, invalid_pgm_id
	syscall
	addi	$v0, $0, 16
	add	$a0, $s3, $0
	syscall				# close file
	add	$a0, $0, $0
	add	$a1, $0, $0
	add	$v0, $0, $0
EXIT_READ_PGM:
	lw	$s3, 16($sp)
	lw	$s2, 12($sp)
	lw	$s1, 8($sp)
	lw	$s0, 4($sp)
	lw	$ra, 0($sp)
	addi	$sp, $sp, 20
	jr	$ra


# "histogram"
# inputs
# $a0 = address of array of bytes/ascii values
# $a1 = number of rows
# $a2 = number of columns
# $a3 = address of where the histogram will be stored
# output
# $v0 = number of bytes viewed (should be number of rows * number of columns)
# This condenses the data into a histogram and return a pointer to histogram
histogram:
	add	$t0, $0, $0		# set index of CLEAR_MEM_LOOP to 0
CLEAR_MEM_LOOP:
	slti	$t2, $t0, 256
	beq	$t2, $0, CLEAR_MEM_EXIT	# branch if $t0 > 255
	add	$t3, $t0, $a3
	sb	$0, 0($t3)
	addi	$t0, $t0, 1		# increment
	j	CLEAR_MEM_LOOP
CLEAR_MEM_EXIT:
	add	$t0, $0, $0		# set index of outer loop to 0
	add	$t2, $0, $0		# index for array
	add	$t3, $a1, $0		# rows
	add	$t4, $a2, $0		# cols
OUTER_LOOP:
	slt	$t5, $t0, $t3
	beq	$t5, $0, OUTER_EXIT	# branch if $t0 > rows - 1
	add	$t1, $0, $0		# set index of inner loop to 0
INNER_LOOP:
	slt	$t5, $t1, $t4
	beq	$t5, $0, INNER_EXIT	# branch if $t1 > cols - 1
	add	$t6, $t2, $a0		# address of current element in array
	lbu	$t7, 0($t6)
	sll	$t7, $t7, 2
	add	$t8, $t7, $a3		# use value from array*4 as offset
	lw	$t9, 0($t8)
	addi	$t9, $t9, 1		# Used all nine temporary registers!
	sw	$t9, 0($t8)
	addi	$t2, $t2, 1
	addi	$t1, $t1, 1
	j	INNER_LOOP
INNER_EXIT:
	addi	$t0, $t0, 1
	j	OUTER_LOOP
OUTER_EXIT:
	add	$v0, $t2, $0		# set the return value to $t2, the number of data in the histogram
	jr	$ra


# "check_pgm_id"
# inputs:
# $a0 = file descriptor
# output:
# $v0 = boolean, 1 for true, 0 for false/bad
# This function will check if the file headings are fit for a pgm
check_pgm_id:
	addi	$v0, $0, 14		# 14 is for reading a file
	la	$a1, pgm_id		# put the input buffer address in $a1
	addi	$a2, $0, 3		# read three bytes
	syscall
	bne	$a2, $v0, BAD_PGM_ID	# branch if the number of characters read isn't equal to 3
	add	$t0, $0, $0
PGM_ID_LOOP:
	slti	$t6, $t0, 3		# loop only three time
	beq	$t6, $0, GOOD_PGM_ID	# looped three times and all characters are good
	la	$t1, P5_msg		# the comparison string
	add	$t2, $t0, $t1		# address of current character in comparison string
	lbu	$t4, 0($t2)
	add	$t3, $t0, $a1		# address of current character in testing string
	lbu	$t5, 0($t3)
	bne	$t4, $t5, BAD_PGM_ID	# branch if the characters aren't the same
	addi	$t0, $t0, 1		# increment
	j	PGM_ID_LOOP
BAD_PGM_ID:
	add	$v0, $0, $0		# set return value to 0
	j	PGM_ID_EXIT
GOOD_PGM_ID:
	addi	$v0, $0, 1		# set return value to 1
PGM_ID_EXIT:
	jr	$ra


# "grab_row_col"
# inputs:
# $a0 = file descriptor of pgm file
# $a1 = pointer to int type (rows)
# $a2 = pointer to int type (columns)
# output:
# $v0 = bool (1 for success, 0 for bad read)
# This function will read the second line, hopefully, of a pgm file which will
# contain three numbers separated by spaces: the number of rows, the number of 
# columns, and the resolution. The resolution for our problem will be set to 255
# (meaning the values can only be from 0 to 255). The function will read each
# byte one at a time until a single number is constructed and then do it again
# until all three number are constructed.
grab_row_col:
	addi	$sp, $sp, -20		# store the arguments before making syscalls
	sw	$ra, 0($sp)
	sw	$a0, 4($sp)		# arguments are saved once instead of three times
	sw	$a1, 8($sp)
	sw	$a2, 12($sp)
	sw	$s0, 16($sp)
	lw	$a0, 4($sp)
	jal	grab_number		# grab the first number
	lw	$s0, 8($sp)		# this value in the stack holds a memory address
	sw	$v0, 0($s0)		# put result into memory pointed at by $s0

	lw	$a0, 4($sp)
	jal	grab_number		# grab the second number
	lw	$s0, 12($sp)
	sw	$v0, 0($s0)

	lw	$a0, 4($sp)
	jal	grab_number		# grab the third number
	addi	$t0, $0, 255
	bne	$v0, $t0, BAD_255

	addi	$v0, $0, 1		# return 1
	j	GRAB_ROW_COL_EXIT
BAD_255:
	add	$v0, $0, $0		# return 0
GRAB_ROW_COL_EXIT:
	lw	$s0, 16($sp)
	lw	$a2, 12($sp)		# restore is important since arguments are pointers
	lw	$a1, 8($sp)
	lw	$a0, 4($sp)
	lw	$ra, 0($sp)
	addi	$sp, $sp, 20		# restore stack
	jr	$ra


# "grab_number"
# input:
# $a0 = file descriptor
# output:
# $v0 = integer, the number retrieved
# this function reads each character until there isn't a digit and then returns
# the number as an integer
grab_number:
	add	$t2, $0, $0		# set accumulator to 0
GRAB_NUMBER_LOOP:
	addi	$v0, $0, 14
	la	$a1, one_char		# set the input buffer to one_char
	addi	$a2, $0, 1
	syscall
	lbu	$t0, 0($a1)		# $t0 is the ascii value
	slti	$t1, $t0, 48
	bne	$t1, $0, GRAB_EXIT	# branch if $t0 < '0'
	slti	$t1, $t0, 58
	beq	$t1, $0, GRAB_EXIT	# branch if $t0 > '9'
	sll	$t3, $t2, 3		# fancy way to multiply by 10, 8 + 2
	sll	$t4, $t2, 1
	add	$t2, $t3, $t4
	addi	$t0, $t0, -48		# subtract '0' from ascii value
	add	$t2, $t2, $t0		# add the digit
	j	GRAB_NUMBER_LOOP
GRAB_EXIT:
	add	$v0, $t2, $0
	jr	$ra



# *********************
# Fourth Part: data for function
# *********************

	.data
invalid_file:
	.asciiz "Could not find that file. Exiting.\n"

invalid_pgm_id:
	.asciiz	"The pgm_id was not correct. Exiting.\n"

P5_msg:
	.asciiz	"P5\n"

pgm_id:
	.byte	0, 0, 0, 0, 0, 0	# only need three bytes, next byte should be set to 0

one_char:
	.byte	0, 0			# for reading the characters on the second line
