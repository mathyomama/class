# After much deliberating, I decided to go with a sort and search algorithm.
# The sort will be an easy one, bubble sort, which is at-worst big-O(n^2).
# The search will be big-O(n). I thought about using the median of medians
# algorithm, but I was worried that there would be a lot of little things
# which would be a nightmare to implement. I will try it out another day.

	.text
	.globl	median
median:
	addi	$sp, $sp, -8	# make space on the stack
	sw	$ra, 0($sp)	# save the return address on the stack
	sw	$s0, 4($sp)	# save s0
	addi	$sp, $sp, -16	# make room for t0-t3
	sw	$t0, 0($sp)
	sw	$t1, 4($sp)
	sw	$t2, 8($sp)
	sw	$t3, 12($sp)
	jal	bubble_sort	# go to function bubble_sort, same arguments as compute_median
	lw	$t3, 12($sp)
	lw	$t2, 8($sp)
	lw	$t1, 4($sp)
	lw	$t0, 0($sp)
	addi	$sp, $sp, 16	# restore stack pointer
	add	$s0, $v0, $0	# put the return value in s0
	srl	$t1, $a1, 1	# divide by two to get the offset
	sll	$t1, $t1, 2	# multiply by 2
	add	$t1, $t1, $a0	# get address of median or half of the medians
	andi	$t0, $a1, 1	# check if the size is even or odd by extracting the least signif. bit
	beq	$t0, $0, EVEN	# branch to the even if t0 is zero
	lw	$v0, 0($t1)	# get value of median
	j	EXITMED		# go to the end of the function
EVEN:
	lw	$t2, 0($t1)	# load arr[size/2]
	lw	$t3, -4($t1)	# load arr[size/2 - 1]
	add	$t0, $t2, $t3	# take the average
	srl	$v0, $t0, 1	# integer division by 2
EXITMED:
	lw	$s0, 4($sp)	# restore s0
	lw	$ra, 0($sp)	# restore the return address
	addi	$sp, $sp, 8	# restore the stack
	jr	$ra		# return to the caller

bubble_sort:
LOOP1:
	add	$t0, $0, $0	# make t0 the number of swaps
	addi	$t1, $0, 1	# make t1 the index of the second loop, set to 1 for size - 1 iterations
LOOP2:
	slt	$t2, $t1, $a1	# check if t1 < size
	beq	$t2, $0, EXIT2	# branch to EXIT2 if ^^^^ false
	sll	$t7, $t1, 2	# multiply by 2 to get number of bytes
	add	$t3, $t7, $a0	# put the address in t3
	lw	$t4, -4($t3)	# arr[i - 1]
	lw	$t5, 0($t3)	# arr[i]
	slt	$t2, $t4, $t5	# check if arr[i - 1] < arr[i]
	bne	$t2, $0, NOSWAP	# branch if ^^^^ is true
	add	$t6, $t4, $0	# swapping with temp as t6
	add	$t4, $t5, $0	# put t5 into t4
	add	$t5, $t6, $0	# put t6 into t5
	sw	$t4, -4($t3)	# store back in arr[i - 1]
	sw	$t5, 0($t3)	# store back in arr[i]
	addi	$t0, $t0, 1	# add one to the swap counter
NOSWAP:
	addi	$t1, $t1, 1	# increment the index by one
	j	LOOP2		# loop
EXIT2:
	bne	$t0, $0, LOOP1	# branch if swaps > 0, in order to move on, need one pass with no swaps
	add	$v0, $a0, $0	# it's like returning a pointer
	jr	$ra		# jump to the return address
