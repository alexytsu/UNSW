#
# COMP1521 18s1 -- Assignment 1 -- Worm on a Plane!
#
# Base code by Jashank Jeremy and Wael Alghamdi
# Tweaked (severely) by John Shepherd
#
# Set your tabstop to 8 to make the formatting decent

# Requires:
#  - [no external symbols]

# Provides:
	.globl	wormCol
	.globl	wormRow
	.globl	grid
	.globl	randSeed

	.globl	main
	.globl	clearGrid
	.globl	drawGrid
	.globl	initWorm
	.globl	onGrid
	.globl	overlaps
	.globl	moveWorm
	.globl	addWormToGrid
	.globl	giveUp
	.globl	intValue
	.globl	delay
	.globl	seedRand
	.globl	randValue

	# Let me use $at, please.
	.set	noat

# The following notation is used to suggest places in
# the program, where you might like to add debugging code
#
# If you see e.g. putc('a'), replace by the three lines
# below, with each x replaced by 'a'
#
# print out a single character
# define putc(x)
# 	addi	$a0, $0, x
# 	addiu	$v0, $0, 11
# 	syscall
# 
# print out a word-sized int
# define putw(x)
# 	add 	$a0, $0, x
# 	addiu	$v0, $0, 1
# 	syscall

####################################
# .DATA
	.data

	.align 4
wormCol:	.space	40 * 4
	.align 4
wormRow:	.space	40 * 4
	.align 4
grid:		.space	20 * 40 * 1

randSeed:	.word	0

main__0:	.asciiz "Invalid Length (4..20)"
main__1:	.asciiz "Invalid # Moves (0..99)"
main__2:	.asciiz "Invalid Rand Seed (0..Big)"
main__3:	.asciiz "Iteration "
main__4:	.asciiz "Blocked!\n"

	# ANSI escape sequence for 'clear-screen'
main__clear:	.asciiz "\033[H\033[2J"
# main__clear:	.asciiz "__showpage__\n" # for debugging

giveUp__0:	.asciiz "Usage: "
giveUp__1:	.asciiz " Length #Moves Seed\n"

####################################
# .TEXT <main>
	.text
main:

# Frame:	$fp, $ra, $s0, $s1, $s2, $s3, $s4
# Uses: 	$a0, $a1, $v0, $s0, $s1, $s2, $s3, $s4
# Clobbers:	$a0, $a1

# Locals:
#	- `argc' in $s0
#	- `argv' in $s1
#	- `length' in $s2
#	- `ntimes' in $s3
#	- `i' in $s4

# Structure:
#	main
#	-> [prologue]
#	-> main_seed
#	  -> main_seed_t
#	  -> main_seed_end
#	-> main_seed_phi
#	-> main_i_init
#	-> main_i_cond
#	   -> main_i_step
#	-> main_i_end
#	-> [epilogue]
#	-> main_giveup_0
#	 | main_giveup_1
#	 | main_giveup_2
#	 | main_giveup_3
#	   -> main_giveup_common

# Code:
	# set up stack frame
	sw	$fp, -4($sp)
	sw	$ra, -8($sp)
	sw	$s0, -12($sp)
	sw	$s1, -16($sp)
	sw	$s2, -20($sp)
	sw	$s3, -24($sp)
	sw	$s4, -28($sp)
	la	$fp, -4($sp)
	addiu	$sp, $sp, -28

	# save argc, argv
	add	$s0, $0, $a0
	add	$s1, $0, $a1

	# if (argc < 3) giveUp(argv[0],NULL);
	slti	$at, $s0, 4
	bne	$at, $0, main_giveup_0

	# length = intValue(argv[1]);
	addi	$a0, $s1, 4	# 1 * sizeof(word)
	lw	$a0, ($a0)	# (char *)$a0 = *(char **)$a0
	jal	intValue

	# if (length < 4 || length >= 40)
	#     giveUp(argv[0], "Invalid Length");
	# $at <- (length < 4) ? 1 : 0
	slti	$at, $v0, 4
	bne	$at, $0, main_giveup_1
	# $at <- (length < 40) ? 1 : 0
	slti	$at, $v0, 40
	beq	$at, $0, main_giveup_1
	# ... okay, save length
	add	$s2, $0, $v0

	# ntimes = intValue(argv[2]);
	addi	$a0, $s1, 8	# 2 * sizeof(word)
	lw	$a0, ($a0)
	jal	intValue

	# if (ntimes < 0 || ntimes >= 100)
	#     giveUp(argv[0], "Invalid # Iterations");
	# $at <- (ntimes < 0) ? 1 : 0
	slti	$at, $v0, 0
	bne	$at, $0, main_giveup_2
	# $at <- (ntimes < 100) ? 1 : 0
	slti	$at, $v0, 100
	beq	$at, $0, main_giveup_2
	# ... okay, save ntimes
	add	$s3, $0, $v0

main_seed:
	# seed = intValue(argv[3]);
	add	$a0, $s1, 12	# 3 * sizeof(word)
	lw	$a0, ($a0)
	jal	intValue

	# if (seed < 0) giveUp(argv[0], "Invalid Rand Seed");
	# $at <- (seed < 0) ? 1 : 0
	slt	$at, $v0, $0
	bne	$at, $0, main_giveup_3

main_seed_phi:
	add	$a0, $0, $v0
	jal	seedRand

	# start worm roughly in middle of grid

	# startCol: initial X-coord of head (X = column)
	# int startCol = 40/2 - length/2;
	addi	$s4, $0, 2
	addi	$a0, $0, 40
	div	$a0, $s4
	mflo	$a0
	# length/2
	div	$s2, $s4
	mflo	$s4
	# 40/2 - length/2
	sub	$a0, $a0, $s4

	# startRow: initial Y-coord of head (Y = row)
	# startRow = 20/2;
	addi	$s4, $0, 2
	addi	$a1, $0, 20
	div	$a1, $s4
	mflo	$a1

	# initWorm($a0=startCol, $a1=startRow, $a2=length)
	add	$a2, $0, $s2
	jal	initWorm

main_i_init:
	# int i = 0;
	add	$s4, $0, $0
main_i_cond:
	# i <= ntimes  ->  ntimes >= i  ->  !(ntimes < i)
	#   ->  $at <- (ntimes < i) ? 1 : 0
	slt	$at, $s3, $s4
	bne	$at, $0, main_i_end

	# clearGrid();
	jal	clearGrid

	# addWormToGrid($a0=length);
	add	$a0, $0, $s2
	jal	addWormToGrid

	# printf(CLEAR)
	la	$a0, main__clear
	addiu	$v0, $0, 4	# print_string
	syscall

	# printf("Iteration ")
	la	$a0, main__3
	addiu	$v0, $0, 4	# print_string
	syscall

	# printf("%d",i)
	add	$a0, $0, $s4
	addiu	$v0, $0, 1	# print_int
	syscall

	# putchar('\n')
	addi	$a0, $0, 0x0a
	addiu	$v0, $0, 11	# print_char
	syscall

	# drawGrid();
	jal	drawGrid

###################### DEBUGGING ##########################
	
	# print worm row, worm col	
# 	addi	$a0, $0, x
# 	addiu	$v0, $0, 11
# 	syscall

	li	$t0, 0
	move	$t1, $s2
	li	$t4, 4
	debug_loop:
	bge	$t0, $t1, end_debug_loop

	mul	$t2, $t0, $t4

	lw	$a0, wormCol($t2)
	addiu	$v0, $0, 1
	syscall

	li	$a0, ','
	addiu	$v0, $0, 11
	syscall

	lw	$a0, wormRow($t2)
	addiu	$v0, $0, 1
	syscall

    	li $a0, 10
	addiu	$v0, $0, 11
	syscall


	addi	$t0, $t0, 1
	j debug_loop
	end_debug_loop:



##########################################################

	# if (!moveWorm(length)) {...break}
	add	$a0, $0, $s2
	jal	moveWorm
	bne	$v0, $0, main_moveWorm_phi

	# printf("Blocked!\n")
	la	$a0, main__4
	addiu	$v0, $0, 4	# print_string
	syscall

	# break;
	j	main_i_end

main_moveWorm_phi:

	addi	$a0, $0, 1
	jal	delay

main_i_step:
	addi	$s4, $s4, 1
	j	main_i_cond
main_i_end:

	# exit (EXIT_SUCCESS)
	# ... let's return from main with `EXIT_SUCCESS' instead.
	addi	$v0, $0, 0	# EXIT_SUCCESS

main__post:
	# tear down stack frame
	lw	$s4, -24($fp)
	lw	$s3, -20($fp)
	lw	$s2, -16($fp)
	lw	$s1, -12($fp)
	lw	$s0, -8($fp)
	lw	$ra, -4($fp)
	la	$sp, 4($fp)
	lw	$fp, ($fp)
	jr	$ra

main_giveup_0:
	add	$a1, $0, $0	# NULL
	j	main_giveup_common
main_giveup_1:
	la	$a1, main__0	# "Invalid Length"
	j	main_giveup_common
main_giveup_2:
	la	$a1, main__1	# "Invalid # Iterations"
	j	main_giveup_common
main_giveup_3:
	la	$a1, main__2	# "Invalid Rand Seed"
	# fall through
main_giveup_common:
	# giveUp ($a0=argv[0], $a1)
	lw	$a0, ($s1)	# argv[0]
	jal	giveUp		# never returns

####################################
# clearGrid() ... set all grid[][] elements to '.'
# .TEXT <clearGrid>
	.text
clearGrid:

# Frame:	$fp, $ra, $s0, $s1
# Uses: 	$s0, $s1, $t1, $t2
# Clobbers:	$t0, $t1, $t2

# Locals:
#	- `row' in $s0
#	- `col' in $s1


# Code:
	# set up stack frame
	sw	$fp, -4($sp)
	sw	$ra, -8($sp)
	sw	$s0, -12($sp)
	sw	$s1, -16($sp)
	la	$fp, -4($sp)
	addiu	$sp, $sp, -16

	# NROWS = 20
	# NCOLS = 40

	li	$s0, 0 # row = 0
	r_loop_clearGrid:
	#while row < 20
	li	$t0, 20
	bge	$s0, $t0, end_r_clearGrid #while(row < 20)

		li	$s1, 0		# col = 0
		c_loop_clearGrid:
		# while col < 40
		li	$t0, 40
		bge	$s1, $t0, end_c_clearGrid

		mul	$t1, $s0, $t0	#row offset = $s0 * NCOLS
		add	$t1, $t1, $s1	#col offset = $s1

		li	$t2, '.'
		sb	$t2, grid($t1)

		addi $s1, $s1, 1
		j c_loop_clearGrid
		end_c_clearGrid:

	addi	$s0, $s0, 1
	j r_loop_clearGrid
	end_r_clearGrid:
	# tear down stack frame
	lw	$s1, -12($fp)
	lw	$s0, -8($fp)
	lw	$ra, -4($fp)
	la	$sp, 4($fp)
	lw	$fp, ($fp)
	jr	$ra


####################################
# drawGrid() ... display current grid[][] matrix
# .TEXT <drawGrid>
	.text
drawGrid:

# Frame:	$fp, $ra, $s0, $s1, $t1
# Uses: 	$s0, $s1
# Clobbers:	$t0, $t1

# Locals:
#	- `row' in $s0
#	- `col' in $s1
#	- `&grid[row][col]' in $t1

# Code:
	# set up stack frame
	sw	$fp, -4($sp)
	sw	$ra, -8($sp)
	sw	$s0, -12($sp)
	sw	$s1, -16($sp)
	la	$fp, -4($sp)
	addiu	$sp, $sp, -16

	li	$s0, 0 # row = 0
	r_loop_drawGrid:
	li	$t0, 20
	bge	$s0, $t0, end_r_drawGrid #while(row < 20)

		li	$s1, 0		# col = 0
		c_loop_drawGrid:
		li	$t0, 40
		bge	$s1, $t0, end_c_drawGrid #while(col < 40)

		mul	$t1, $s0, $t0	#row offset = $s0 * NCOLS
		add	$t1, $t1, $s1	#col offset = $s1

		lb	$a0, grid($t1)
		li	$v0, 11
		syscall
		

		addi $s1, $s1, 1
		j c_loop_drawGrid
		end_c_drawGrid:

    li $a0, 10
    li $v0, 11
    syscall

	addi	$s0, $s0, 1
	j r_loop_drawGrid
	end_r_drawGrid:

	# tear down stack frame
	lw	$s1, -12($fp)
	lw	$s0, -8($fp)
	lw	$ra, -4($fp)
	la	$sp, 4($fp)
	lw	$fp, ($fp)
	jr	$ra


####################################
# initWorm(col,row,len) ... set the wormCol[] and wormRow[]
#    arrays for a worm with head at (row,col) and body segements
#    on the same row and heading to the right (higher col values)
# .TEXT <initWorm>
	.text
initWorm:

# Frame:	$fp, $ra
# Uses: 	$a0, $a1, $a2, $t0, $t1, $t2
# Clobbers:	$t0, $t1, $t2

# Locals:
#	- `col' in $a0
#	- `row' in $a1
#	- `len' in $a2
#	- `newCol' in $t0
#	- `nsegs' in $t1
#	- temporary in $t2

# Code:
	# set up stack frame
	sw	$fp, -4($sp)
	sw	$ra, -8($sp)
	la	$fp, -4($sp)
	addiu	$sp, $sp, -8

	addi	$t0, $a0, 1	# newCol = col + 1
	sw	$a0, wormCol	# wormCol[0] = col
	sw	$a1, wormRow	# wormRow[0] = row

	li	$t1, 1 #nsegs = 1
	seg_loop_initWorm:
	bge	$t1, $a2, seg_end_initWorm	#while(nsegs < len)
	li	$t2, 40
	beq	$t0, $t2, seg_end_initWorm

	li	$t4, 4	#size of int
	mul	$t2, $t4, $t1 #4 * nsegs
	
	sw	$t0, wormCol($t2)
	addi	$t0, $t0, 1

	sw	$a1, wormRow($t2)	

	# NROWS = 20
	# NCOLS = 40
	addi	$t1, $t1, 1
	j seg_loop_initWorm
	seg_end_initWorm:


	# tear down stack frame
	lw	$ra, -4($fp)
	la	$sp, 4($fp)
	lw	$fp, ($fp)
	jr	$ra


####################################
# ongrid(col,row) ... checks whether (row,col)
#    is a valid coordinate for the grid[][] matrix
# .TEXT <onGrid>
	.text
onGrid:

# Frame:	$fp, $ra
# Uses: 	$a0, $a1, $v0
# Clobbers:	$v0

# Locals:
#	- `col' in $a0
#	- `row' in $a1

# Code:

	sw	$fp, -4($sp)
	sw	$ra, -8($sp)
	la	$fp, -4($sp)
	addiu	$sp, $sp, -8

	# NROWS = 20
	# NCOLS = 40

	li	$v0, 1 #return 1 by default
	# return (col >= 0 && col < NCOLS && row >= 0 && row < NROWS);
	# if any of the conditions fails, j to return_0
	# if(0 > col) return 0;
	bgt	$t0, $a0, return_0_onGrid

	# if (col >= NCOLS) return 0
	li	$t1, 40
	bgt	$a0, $t1, return_0_onGrid

	#if(0 > row) return 0;
	bgt	$t0, $a1, return_0_onGrid

	# if(row >=)
	li	$t1, 20
	bgt	$a1, $t1, return_0_onGrid

	
	# tear down stack frame
	j return_onGrid
	return_0_onGrid:
	li	$v0, 0
	
	return_onGrid:
	lw	$ra, -4($fp)
	la	$sp, 4($fp)
	lw	$fp, ($fp)
	jr	$ra

####################################
# overlaps(r,c,len) ... checks whether (r,c) holds a body segment
# .TEXT <overlaps>
	.text
overlaps:

# Frame:	$fp, $ra
# Uses: 	$a0, $a1, $a2
# Clobbers:	$t6, $t7

# Locals:
#	- `col' in $a0
#	- `row' in $a1
#	- `len' in $a2
#	- `i' in $t6

# Code:

	sw	$fp, -4($sp)
	sw	$ra, -8($sp)
	la	$fp, -4($sp)
	addiu	$sp, $sp, -8

	li 	$v0, 0 #return 0 by default

	li	$t4, 4
	li	$t6, 0
	loop_overlaps:
	bge	$t6, $a2, end_loop_overlaps #while (i < len)

	mul	$t3, $t6, $t4
	lw	$t2, wormCol($t3)
	beq	$t2, $a0, second_condition
	addi	$t6, $t6, 1
	j loop_overlaps
	second_condition:
	lw	$t2, wormRow($t3)
	beq	$t2, $a1, return_1_overlaps

	addi	$t6, $t6, 1
	j loop_overlaps
	end_loop_overlaps:

	j return_overlaps
	return_1_overlaps:
	li	$v0, 1
	return_overlaps:
	lw	$ra, -4($fp)
	la	$sp, 4($fp)
	lw	$fp, ($fp)
	jr	$ra



####################################
# moveWorm() ... work out new location for head
#         and then move body segments to follow
# updates wormRow[] and wormCol[] arrays

# (col,row) coords of possible places for segments
# done as global data; putting on stack is too messy
	.data
	.align 4
possibleCol: .space 8 * 4	# sizeof(word)
possibleRow: .space 8 * 4	# sizeof(word)

# .TEXT <moveWorm>
	.text
moveWorm:

# Frame:	$fp, $ra, $s0, $s1, $s2, $s3, $s4, $s5, $s6, $s7
# Uses: 	$s0, $s1, $s2, $s3, $s4, $s5, $s6, $s7, $t0, $t1, $t2, $t3
# Clobbers:	$t0, $t1, $t2, $t3

# Locals:
#	- `col' in $s0
#	- `row' in $s1
#	- `len' in $s2
#	- `dx' in $s3
#	- `dy' in $s4
#	- `n' in $s7
#	- `i' in $t0
#	- tmp in $t1
#	- tmp in $t2
#	- tmp in $t3
# 	- `&possibleCol[0]' in $s5
#	- `&possibleRow[0]' in $s6

# Code:
	# set up stack frame
	sw	$fp, -4($sp)
	sw	$ra, -8($sp)
	sw	$s0, -12($sp)
	sw	$s1, -16($sp)
	sw	$s2, -20($sp)
	sw	$s3, -24($sp)
	sw	$s4, -28($sp)
	sw	$s5, -32($sp)
	sw	$s6, -36($sp)
	sw	$s7, -40($sp)
	la	$fp, -4($sp)
	addiu	$sp, $sp, -40

	la	$s5, possibleCol
	la	$s6, possibleRow

	li	$s7, 0	#n=0
	
	li	$s3, -1	#dx = -1
	loop_dx_moveWorm:
	li	$t1, 1
	bgt	$s3, $t1, end_dx_moveWorm
	li	$s4, -1 #dy = -1
		loop_dy_moveWorm:
		bgt	$s4, $t1, end_dy_moveWorm

		lw	$t2, wormCol
		lw	$t3, wormRow

		add	$s0, $t2, $s3	#col = wormCol[0] + dx
		add	$s1, $t3, $s4	#row = wormRow[0] + dy  

		move	$a0, $s0
		move	$a1, $s1
		jal	onGrid
		li	$t1, 1
		bne	$v0, $t1, continue_dy_moveWorm

		move	$a0, $s0
		move	$a1, $s1
		move	$a2, $s2
		jal	overlaps
		li	$t1, 1
		bne	$v0, $t1, continue_dy_moveWorm

		li	$t4, 4
		mul	$t5, $t4, $s7
		sw	$s0, possibleCol($t5)
		sw	$s1, possibleRow($t5)
		addi	$s7, $s7, 1


		continue_dy_moveWorm:
		addi	$s4, $s4, 1
		j loop_dy_moveWorm
		end_dy_moveWorm:
	addi	$s3, $s3, 1
	j loop_dx_moveWorm
	end_dx_moveWorm:

	beq	$s7, $0, return_0_moveWorm

	addi	$t0, $s2, -1
	for_length_moveWorm:
	beqz	$t0, end_length_moveWorm

	li	$t4, 4
	mul	$t5, $t4, $t0
	addi	$t6, $t4, -4

	lw	$t7, wormRow($t5)
	sw	$t7, wormRow($t6)

	lw	$t7, wormCol($t5)
	sw	$t7, wormCol($t6)

	addi	$t0, $t0, -1
	j	for_length_moveWorm
	end_length_moveWorm:

	move	$a0, $s7
	jal	randValue
	move	$t0, $v0

	li	$t4, 4
	mul	$t0, $t0, $t4
	lw	$t1, possibleRow($t0)
	lw	$t2, possibleCol($t0)
	sw	$t1, wormRow
	sw	$t2, wormCol
	j	return_1_moveWorm

	return_1_moveWorm:
	li	$v0, 1
	j	return_moveWorm
	return_0_moveWorm:
	li	$v0, 0
	j	return_moveWorm
	return_moveWorm:
	# tear down stack frame
	lw	$s7, -36($fp)
	lw	$s6, -32($fp)
	lw	$s5, -28($fp)
	lw	$s4, -24($fp)
	lw	$s3, -20($fp)
	lw	$s2, -16($fp)
	lw	$s1, -12($fp)
	lw	$s0, -8($fp)
	lw	$ra, -4($fp)
	la	$sp, 4($fp)
	lw	$fp, ($fp)

	jr	$ra

####################################
# addWormTogrid(N) ... add N worm segments to grid[][] matrix
#    0'th segment is head, located at (wormRow[0],wormCol[0])
#    i'th segment located at (wormRow[i],wormCol[i]), for i > 0
# .TEXT <addWormToGrid>
	.text
addWormToGrid:

# Frame:	$fp, $ra, $s0, $s1, $s2, $s3
# Uses: 	$a0, $s0, $s1, $s2, $s3, $t1
# Clobbers:	$t1

# Locals:
#	- `len' in $a0
#	- `&wormCol[i]' in $s0
#	- `&wormRow[i]' in $s1
#	- `row` in $s2
#	- `col` in $s3
#	- `grid[row][col]'
#	- `i' in $t0

# Code:
	# set up stack frame
	sw	$fp, -4($sp)
	sw	$ra, -8($sp)
	sw	$s0, -12($sp)
	sw	$s1, -16($sp)
	sw	$s2, -20($sp)
	sw	$s3, -24($sp)
	la	$fp, -4($sp)
	addiu	$sp, $sp, -24

	lw	$s2, wormRow #row = wormRow[0]
	lw	$s3, wormCol #col = wormCol[0]

	#find grid[row][col]
	li	$t1, 40
	mul	$t2, $s2, $t1
	add	$t2, $t2, $s3

	#set head
	li	$t1, '@'
	sb	$t1, grid($t2)

	li	$t0, 1
	li	$t4, 4
	for_loop_addWormToGrid:
	bge	$t0, $a0, end_loop_addWormToGrid

	mul	$t1, $t0, $t4
	lw	$s2, wormRow($t1)
	lw	$s3, wormCol($t1)

	li	$t3, 40
	mul	$t2, $s2, $t3
	add	$t2, $t2, $s3

	li	$t1, 'o'
	sb	$t1, grid($t2)

	addi	$t0, $t0, 1
	j for_loop_addWormToGrid
	end_loop_addWormToGrid:


	# tear down stack frame
	lw	$s3, -20($fp)
	lw	$s2, -16($fp)
	lw	$s1, -12($fp)
	lw	$s0, -8($fp)
	lw	$ra, -4($fp)
	la	$sp, 4($fp)
	lw	$fp, ($fp)
	jr	$ra

####################################
# giveUp(msg) ... print error message and exit
# .TEXT <giveUp>
	.text
giveUp:

# Frame:	frameless; divergent
# Uses: 	$a0, $a1
# Clobbers:	$s0, $s1

# Locals:
#	- `progName' in $a0/$s0
#	- `errmsg' in $a1/$s1

# Code:
	add	$s0, $0, $a0
	add	$s1, $0, $a1

	# if (errmsg != NULL) printf("%s\n",errmsg);
	beq	$s1, $0, giveUp_usage

	# puts $a0
	add	$a0, $0, $s1
	addiu	$v0, $0, 4	# print_string
	syscall

	# putchar '\n'
	add	$a0, $0, 0x0a
	addiu	$v0, $0, 11	# print_char
	syscall

giveUp_usage:
	# printf("Usage: %s #Segments #Moves Seed\n", progName);
	la	$a0, giveUp__0
	addiu	$v0, $0, 4	# print_string
	syscall

	add	$a0, $0, $s0
	addiu	$v0, $0, 4	# print_string
	syscall

	la	$a0, giveUp__1
	addiu	$v0, $0, 4	# print_string
	syscall

	# exit(EXIT_FAILURE);
	addi	$a0, $0, 1 # EXIT_FAILURE
	addiu	$v0, $0, 17	# exit2
	syscall
	# doesn't return

####################################
# intValue(str) ... convert string of digits to int value
# .TEXT <intValue>
	.text
intValue:

# Frame:	$fp, $ra
# Uses: 	$t0, $t1, $t2, $t3, $t4, $t5
# Clobbers:	$t0, $t1, $t2, $t3, $t4, $t5

# Locals:
#	- `s' in $t0
#	- `*s' in $t1
#	- `val' in $v0
#	- various temporaries in $t2

# Code:
	# set up stack frame
	sw	$fp, -4($sp)
	sw	$ra, -8($sp)
	la	$fp, -4($sp)
	addiu	$sp, $sp, -8

	# int val = 0;
	add	$v0, $0, $0

	# register various useful values
	addi	$t2, $0, 0x20 # ' '
	addi	$t3, $0, 0x30 # '0'
	addi	$t4, $0, 0x39 # '9'
	addi	$t5, $0, 10

	# for (char *s = str; *s != '\0'; s++) {
intValue_s_init:
	# char *s = str;
	add	$t0, $0, $a0
intValue_s_cond:
	# *s != '\0'
	lb	$t1, ($t0)
	beq	$t1, $0, intValue_s_end

	# if (*s == ' ') continue; # ignore spaces
	beq	$t1, $t2, intValue_s_step

	# if (*s < '0' || *s > '9') return -1;
	blt	$t1, $t3, intValue_isndigit
	bgt	$t1, $t4, intValue_isndigit

	# val = val * 10
	mult	$v0, $t5
	mflo	$v0

	# val = val + (*s - '0');
	sub	$t1, $t1, $t3
	add	$v0, $v0, $t1

intValue_s_step:
	# s = s + 1
	addi	$t0, $t0, 1	# sizeof(byte)
	j	intValue_s_cond
intValue_s_end:

intValue__post:
	# tear down stack frame
	lw	$ra, -4($fp)
	la	$sp, 4($fp)
	lw	$fp, ($fp)
	jr	$ra

intValue_isndigit:
	# return -1
	addi	$v0, $0, -1
	j	intValue__post

####################################
# delay(N) ... waste some time; larger N wastes more time
#                            makes the animation believable
# .TEXT <delay>
	.text
delay:

# Frame:	$fp, $ra
# Uses: 	$a0
# Clobbers:	$t0, $t1, $t2, $t3

# Locals:
#	- `n' in $a0
#	- `i' in $t0
#	- `j' in $t1
#	- `k' in $t2
#	- `x' in $t3

# Code:
	# set up stack frame
	sw	$fp, -4($sp)
	sw	$ra, -8($sp)
	la	$fp, -4($sp)
	addiu	$sp, $sp, -8

	li	$t3, 3

	li	$t0, 0
	for_delay:
	bge	$t0, $a0, end_for_delay
	
	li	$t1, 0
	for_j_delay:
	li	$t4, 40000
	bge 	$t1, $t4, end_for_j_delay

	li	$t2, 0
	for_k_delay:
	li	$t4, 1000
	bge	$t2, $t4, end_for_k_delay

	li	$t4, 3
	mul	$t3, $t3, $t4

	end_for_k_delay:


	addi	$t1, $t1, 1
	end_for_j_delay:

	addi	$t0, $t0, 1
	end_for_delay:

	# tear down stack frame
	lw	$ra, -4($fp)
	la	$sp, 4($fp)
	lw	$fp, ($fp)
	jr	$ra


####################################
# seedRand(Seed) ... seed the random number generator
# .TEXT <seedRand>
	.text
seedRand:

# Frame:	$fp, $ra
# Uses: 	$a0
# Clobbers:	[none]

# Locals:
#	- `seed' in $a0

# Code:
	# set up stack frame
	sw	$fp, -4($sp)
	sw	$ra, -8($sp)
	la	$fp, -4($sp)
	addiu	$sp, $sp, -8

	# randSeed <- $a0
	sw	$a0, randSeed

seedRand__post:
	# tear down stack frame
	lw	$ra, -4($fp)
	la	$sp, 4($fp)
	lw	$fp, ($fp)
	jr	$ra

####################################
# randValue(n) ... generate random value in range 0..n-1
# .TEXT <randValue>
	.text
randValue:

# Frame:	$fp, $ra
# Uses: 	$a0
# Clobbers:	$t0, $t1

# Locals:	[none]
#	- `n' in $a0

# Structure:
#	rand
#	-> [prologue]
#       no intermediate control structures
#	-> [epilogue]

# Code:
	# set up stack frame
	sw	$fp, -4($sp)
	sw	$ra, -8($sp)
	la	$fp, -4($sp)
	addiu	$sp, $sp, -8

	# $t0 <- randSeed
	lw	$t0, randSeed
	# $t1 <- 1103515245 (magic)
	li	$t1, 0x41c64e6d

	# $t0 <- randSeed * 1103515245
	mult	$t0, $t1
	mflo	$t0

	# $t0 <- $t0 + 12345 (more magic)
	addi	$t0, $t0, 0x3039

	# $t0 <- $t0 & RAND_MAX
	and	$t0, $t0, 0x7fffffff

	# randSeed <- $t0
	sw	$t0, randSeed

	# return (randSeed % n)
	div	$t0, $a0
	mfhi	$v0

rand__post:
	# tear down stack frame
	lw	$ra, -4($fp)
	la	$sp, 4($fp)
	lw	$fp, ($fp)
	jr	$ra

