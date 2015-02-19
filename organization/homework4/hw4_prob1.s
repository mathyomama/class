	.data
first_input:
	.asciiz	"Enter a base (between 2 and 36 decimal): "

second_input:
	.asciiz	"Enter a number in base %d: "

output:
	.asciiz "The value in decimal is: "

newline:
	.asciiz "\n"

not_valid_base:
	.asciiz "That is not a valid base."

not_valid_number:
	.asciiz "That is not a valid number for the given base."
