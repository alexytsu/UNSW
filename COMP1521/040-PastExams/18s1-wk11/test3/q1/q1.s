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

