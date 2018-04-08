   .text
   .globl multMatrices
multMatrices:
   # possible register usage:
   # n is $s0, m is $s1, p is $s2,
   # r is $s3, c is $s4, i is $s5, sum is $s6

   # set up stack frame for multMatrices()
   sw $fp, -4($sp)
   la $fp, -4($sp)
   sw $ra, -4($fp)
   sw $s0, -8($fp)
   sw $s1, -12($fp)
   sw $s2, -16($fp)
   sw $s3, -20($fp)
   sw $s4, -24($fp)
   sw $s5, -28($fp)
   sw $s6, -32($fp)
   addi $sp, $sp, -36

   # setup n and m and p
   move $s0, $a0
   move $s1, $a1
   move $s2, $a2

   li $s3, 0 #r
loop1:
   bge $s3,$s0, end1 #while(r < n)

   li $s4, 0 #c
   loop2: #s2shouldnt be -
      bge $s4, $s2, end2 #while(c < p)
      li $s6, 0 #sum
      li $s5, 0 #i
      loop3:
         bge $s5, $s1, end3 #while(i < m)

         #sum += A[r][i] * B[i][c]
         #A[n][m] B[m][p]

         #find A[r][i]
         li $t4, 4 #sizeof(int)
         mul $t0, $s3, $s1 # $t0 = r * m
         add $t0, $t0, $s5 # $t0 += i
         mul $t0, $t0, $t4 # $t0 *= 4 (size of int)

         #find B[i][c]
         mul $t1, $s5, $s2
         add $t1, $t1, $s4
         mul $t1, $t1, $t4

         lw $t2, A($t0)
         lw $t3, B($t1)

         mul $t5, $t2, $t3
         add $s6, $s6, $t5


         addi $s5, $s5, 1
         j loop3
      end3:

      #C[r][c] = sum;
      mul $t0, $s3, $s2
      add $t0, $t0, $s4
      mul $t0, $t0, $t4
      sw  $s6, C($t0)
      #find r_offset
      addi $s4,$s4, 1
      j loop2
   end2:
   addi $s3, $s3, 1
   j loop1

end1:
   lw $s6, -32($fp)
   lw $s5, -28($fp)
   lw $s4, -24($fp)
   lw $s3, -20($fp)
   lw $s2, -16($fp)
   lw $s1, -12($fp)
   lw $s0, -8($fp)
   lw $ra, -4($fp)
   la $sp, 4($fp)
   lw $fp, ($fp)
   jr $ra
