# COMP1521 Practice Prac Exam #1
# strings

   .data

s1:
   .asciiz ""
s2:
   .asciiz "XXX"
   .align  2
# COMP1521 Practice Prac Exam #1
# main program + show function

   .data
m1:
   .asciiz "s1 = "
m2:
   .asciiz "s2 = "
m3:
   .asciiz "n = "
   .align  2

   .text
   .globl main
main:
   addi $sp, $sp, -4
   sw   $fp, ($sp)
   la   $fp, ($sp)
   addi $sp, $sp, -4
   sw   $ra, ($sp)

   la   $a0, m1
   la   $a1, s1
   jal  showString   # printf("s1 = %s\n",s1)

   la   $a0, s1
   la   $a1, s2
   jal  lowerfy      # n = lowerfy(s1, s2)
   move $s1, $v0

   la   $a0, m1
   la   $a1, s1
   jal  showString   # printf("s1 = %s\n",s1)
   la   $a0, m2
   la   $a1, s2
   jal  showString   # printf("s1 = %s\n",s1)
   la   $a0, m3
   move $a1, $s1
   jal  showInt      # printf("n = %d\n", n)

   lw   $ra, ($sp)
   addi $sp, $sp, 4
   lw   $fp, ($sp)
   addi $sp, $sp, 4
   j    $ra

# params: msg=$a0, str=$a1
# locals: msg=$s0, str=$s1
showString:
   addi $sp, $sp, -4
   sw   $fp, ($sp)
   la   $fp, ($sp)
   addi $sp, $sp, -4
   sw   $ra, ($sp)
   addi $sp, $sp, -4
   sw   $s0, ($sp)
   addi $sp, $sp, -4
   sw   $s1, ($sp)

   move $s0, $a0
   move $s1, $a1

   move $a0, $s0
   li   $v0, 4
   syscall           # printf("%s",msg)
   move $a0, $s1
   li   $v0, 4
   syscall           # printf("%s",str)
   li   $a0, '\n'
   li   $v0, 11
   syscall           # printf("\n")

   lw   $s1, ($sp)
   addi $sp, $sp, 4
   lw   $s0, ($sp)
   addi $sp, $sp, 4
   lw   $ra, ($sp)
   addi $sp, $sp, 4
   lw   $fp, ($sp)
   addi $sp, $sp, 4
   j    $ra

# params: msg=$a0, val=$a1
# locals: msg=$s0, val=$s1
showInt:
   addi $sp, $sp, -4
   sw   $fp, ($sp)
   la   $fp, ($sp)
   addi $sp, $sp, -4
   sw   $ra, ($sp)
   addi $sp, $sp, -4
   sw   $s0, ($sp)
   addi $sp, $sp, -4
   sw   $s1, ($sp)

   move $s0, $a0
   move $s1, $a1

   move $a0, $s0
   li   $v0, 4
   syscall           # printf("%s",msg)
   move $a0, $s1
   li   $v0, 1
   syscall           # printf("%d",val)
   li   $a0, '\n'
   li   $v0, 11
   syscall           # printf("\n")

   lw   $s1, ($sp)
   addi $sp, $sp, 4
   lw   $s0, ($sp)
   addi $sp, $sp, 4
   lw   $ra, ($sp)
   addi $sp, $sp, 4
   lw   $fp, ($sp)
   addi $sp, $sp, 4
   j    $ra
# COMP1521 Practice Prac Exam #1
# int lowerfy(char *src, char *dest)

   .text
   .globl lowerfy

# params: src=$a0, dest=$a1
lowerfy:
# prologue
   addi $sp, $sp, -4
   sw   $fp, ($sp)
   la   $fp, ($sp)
   addi $sp, $sp, -4
   sw   $ra, ($sp)
   addi $sp, $sp, -4
   sw   $s0, ($sp)
   addi $sp, $sp, -4
   sw   $s1, ($sp)
   # if you need to save more $s? registers
   # add the code to save them here

# function body
# locals: ...

   # source -> s0, dest -> s1
   move $s0, $a0
   move $s1, $a1

   li $v0, 0 # n = $v0
   li $t1, 0 # char ch;

   # loop prologue
   li $t0, 0 # i = $t0
   for_loop_begin:
   add $t2, $t0, $s0 #t2 holds address of src[i]
   lb $t1, ($t2) # ch = src[i]
   beqz $t1, for_loop_end # if src[i] == 0 -> break

   # calculate ch >= 'A' ch < = Z and if either false jump to continue otherwise perform 
   # the lowerfy subroutine

   li $t5, 'A'
   li $t6, 'a'
   li $t3, 'Z'

   bgt $t1, $t3, continue
   blt $t1, $t5, continue

   #if not continue, do the substitution

   sub $t1, $t1, $t5
   add $t1, $t1, $t6

   addi $v0, $v0, 1

   continue:
   add $t2, $t0, $s1 #dest[i]
   sb $t1,($t2)

   #loop epilogue
   addi $t0, $t0, 1
   j for_loop_begin
   for_loop_end:

   add $t2, $t0, $s1
   sb $0, ($t2)

# epilogue
   # if you saved more than two $s? registers
   # add the code to restore them here
   lw   $s1, ($sp)
   addi $sp, $sp, 4
   lw   $s0, ($sp)
   addi $sp, $sp, 4
   lw   $ra, ($sp)
   addi $sp, $sp, 4
   lw   $fp, ($sp)
   addi $sp, $sp, 4
   j    $ra

