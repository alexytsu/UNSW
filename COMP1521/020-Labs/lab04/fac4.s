# COMP1521 18s2 Week 04 Lab
# Compute factorials, recursive function

#load word takes content in memory to register
#save word saves content in register to memory

### Global data

   .data
msg1:
   .asciiz "n  = "
msg2:
   .asciiz "n! = "
eol:
   .asciiz "\n"

### main() function
   .text
   .globl main
main:
   #  set up stack frame
   sw    $fp, -4($sp)       # push $fp onto stack
   la    $fp, -4($sp)       # set up $fp for this function
   sw    $ra, -4($fp)       # save return address
   sw    $s0, -8($fp)       # save $s0 to use as ... int n;
   addi  $sp, $sp, -12      # reset $sp to last pushed item

   #  code for main()
   li    $s0, 0             # n = 0;
   la    $a0, msg1
   li    $v0, 4
   syscall                  # printf("n  = ");

## ... rest of code for main() goes here ...

#	la   $a0, eol
#	li   $v0, 4
#	syscall                  # printf("\n");

	li 	 $v0, 5
	syscall 				 # scanf("%d", &n);

	move $s0, $v0			 # to ensure n isnt changed
	
	
	la 	 $a0, msg2		
	li 	 $v0, 4			   	
	syscall					# printf("n! = ");
   
	move $a0, $s0			# set the argument of the function
	jal fac
   
	la   $a0, ($v0)			# printf("%d", fac(n));
	li 	 $v0, 1
	syscall 
	
	la   $a0, eol
	li   $v0, 4
	syscall                  # printf("\n");

   # clean up stack frame
   lw    $s0, -8($fp)       # restore $s0 value
   lw    $ra, -4($fp)       # restore $ra for return
   la    $sp, 4($fp)        # restore $sp (remove stack frame)
   lw    $fp, ($fp)         # restore $fp (remove stack frame)
   li    $v0, 0
   jr    $ra                # return 0

# fac() function
	
fac:
	# set up stack frame
	sw   $fp, -4($sp)       # push $fp onto stack
	la   $fp, -4($sp)       # set up $fp for this function
	sw   $ra, -4($fp)       # save return address
	sw   $s0, -8($fp)       # save $s0 to use as ... int n;
	addi $sp, $sp, -12      # reset $sp to last pushed item
## ... code for prologue goes here ...

	# code for fac()
	
## ... code for fac() goes here ...
	li   $v0, 1				 # initialising the return value to be 1
	ble  $a0, 1, False	     # if n<=1 go to the else part
	
	move $s0, $a0 			 # storing n into s0
	addi $a0, $a0, -1		 # decrement n to make new argument n-1
	jal fac		             # recurse-call fac function
	mul  $v0, $v0, $s0       # n*fac(n-1)
							 
	
	
False:

	# clean up stack frame
	lw   $s0, -8($fp)       # restore $s0 value
	lw   $ra, -4($fp)       # restore $ra for return
	la   $sp, 4($fp)        # restore $sp (remove stack frame)
	lw   $fp, ($fp)         # restore $fp (remove stack frame)
	#li   $v0, 0
	jr   $ra                # return 0
## ... code for epilogue goes here ...