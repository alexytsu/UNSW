# COMP1521 18s1 Week 05 Lab
#
# void multMatrices(int n, int m, int p,
#                   int A[n][m], int B[m][p], int C[n][p])
# {
#    for (int r = 0; r < n; r++) {
#       for (int c = 0; c < p; c++) {
#          int sum = 0;
#          for (int i = 0; i < m; i++) {
#             sum += A[r][i] * B[i][c];
#          }
#          C[r][c] = sum;
#       }
#    }
# }

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
   move $s2, $s2

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
   # 4($fp) = &C
   # 8($fp) = &B
   # 12($fp) = &A

   la $t5, 12($fp) #start of A 
   la $t6, 8($fp) #start of B

   #sum += A[r][i] * B[i][c]

   #find relevant A
   #find r_offset
   mul $t1, $s3, $s1 #r * columns in A (m)
   li $t4, 4
   mul $t1, $t1, $t4
   #find i_offset
   mul $t2, $s5, 4
   
   #find A
   add $t1, $t1, $t2
   add $t5, $t5, $t1

   #find relevant B
   #find i_offset
   mul $t1, $s5, $s2  #i * columns in B
   mul $t1, $t1, 4
   #find c_offset
   mul $t2, $s4, 4

   #find B 
   add $t1, $t1, $t2
   add $t6, $t6, $t1

   lw $t0, ($t5)
   lw $t1, ($t6)
   mul $t0, $t5, $t6

   add $s6, $s6, $t0


   addi $s5, 1
   j loop3
end3:

   la $t5, 4($fp) #start of C[n][p]

   #C[r][c] = sum;
   
   #find r_offset
   mul $t1, $s3, $s2
   mul $t1, $t1, $t4
   #find c_offset
   mul $t2, $s4, $t4
   add $t1, $t1, $t2
   add $t5, $t5, $t1

   sw $s6, ($t5)

   li $v0, 1
   move $a0, $s6
   syscall

   addi $s4, 1
   j loop2
end2:
   
   addi $s3, 1
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
