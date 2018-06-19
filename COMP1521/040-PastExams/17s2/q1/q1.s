# COMP1521 17s2 Final Exam
# void colSum(m, N, a)

   .text
   .globl colSum

# params: m=$a0, N=$a1, a=$a2
colSum:
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
   addi $sp, $sp, -4
   sw   $s5, ($sp)
   # if you need to save more than six $s? registers
   # add extra code here to save them on the stack

# suggestion for local variables (based on C code):
# m=#s0, N=$s1, a=$s2, row=$s3, col=$s4, sum=$s5
   move $s1, $a1
   move $s0, $a0
   move $s2, $a2
   # col loop prologue
   li $s4, 0 #col = 0
   col_for_loop:
   bge $s4, $s1, end_col_for_loop #if col >= N break
      
      #col loop body
      li $s5, 0     #sum = 0
      
      #row loop prologue
      li $s3, 0
      row_for_loop:
      bge $s3, $s1, end_row_for_loop

         #row loop body
         #calculate index [row][col]
         li $t0, 0
         li $t4, 4
         add $t0, $t0, $s4
         mul $t1, $s1, $s3
         add $t0, $t0, $t1
         
         mul $t0, $t0, $t4

         add $t0, $t0, $s0
         lw $t0, ($t0)

         add $s5, $s5, $t0
         


      #row loop epilogue
      addi $s3, $s3, 1
      j row_for_loop
      end_row_for_loop:

      # load into result array
      mul $t5, $s4, $t4
      add $t0, $t5, $a2
      sw $s5, ($t0)

   # col loop epilogue
   addi $s4, $s4, 1
   j col_for_loop
   end_col_for_loop:

# epilogue
   # if you saved more than six $s? registers
   # add extra code here to restore them
   lw   $s5, ($sp)
   addi $sp, $sp, 4
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

