# COMP1521 Practice Prac Exam #1
# int everyKth(int *src, int n, int k, int*dest)

   .text
   .globl everyKth

# params: src=$a0, n=$a1, k=$a2, dest=$a3
everyKth:
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
   addi $sp, $sp, -4
   sw   $s2, ($sp)
   addi $sp, $sp, -4
   sw   $s3, ($sp)
   addi $sp, $sp, -4
   sw   $s4, ($sp)
   # if you need to save more $s? registers
   # add the code to save them here

# function body
# locals: 

# $s0 = src $s1 = n $s2 = k $s3 = dest

   move $s0, $a0
   move $s1, $a1
   move $s2, $a2
   move $s3, $a3

   #t0 = i
   #t1 = j
   li $t0, 0
   li $t1, 0

   # loop prologue
   begin_for_loop:
   bge $t0, $s1, end_for_loop

      # loop body

      rem $t6, $t0, $s2
      beqz $t6, copy
      # if modulo is zero then copy, otherwise j continue skips the copy subroutine

      j continue
      copy:
      li $t4, 4

      mul $t3, $t0, $t4 #find offset made by i and store in $t3
      add $t3, $t3, $s0 #calculate addr of source[i]
      lw $t3, ($t3) #store the value of source[i] into $t3

      mul $t2, $t4, $t1 #find offset made by j and store in $t2
      add $t2, $t2, $s3 #calcualate addr of dest[j]

      sw $t3, ($t2) #save source[i] into dest[j]
      addi $t1, 1 #j++

      continue:
   # loop epilogue
   addi $t0, 1
   j begin_for_loop
   end_for_loop:

   move $v0, $t1

   # add code for your everyKth function here

# epilogue
   # if you saved more than two $s? registers
   # add the code to restore them here
   lw   $s4, ($sp)
   addi $sp, $sp, 4
   lw   $s3, ($sp)
   addi $sp, $sp, 4
   lw   $s2, ($sp)
   addi $sp, $sp, 4
   lw   $s1, ($sp)
   addi $sp, $sp, 4
   lw   $s0, ($sp)
   addi $sp, $sp, 4
   lw   $ra, ($sp)
   addi $sp, $sp, 4
   lw   $fp, ($sp)
   addi $sp, $sp, 4
   j    $ra

