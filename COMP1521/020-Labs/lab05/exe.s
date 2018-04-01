# COMP1521 18s2 Week 05 Lab
#
# Matrix data

   .data
N: .word  2
M: .word  2
P: .word  2
A: .word  1, 2, 3, 4
B: .word  5, 6, 7, 8
C: .space 16

# COMP1521 18s1 Week 05 Lab
#
# Main program to drive matrix multiplication
# Assumes that labels N,M,P,A,B,C exist, and
# refer to appropriate objects/values
   .data
labelA:
   .asciiz "A:\n"
labelB:
   .asciiz "\nB:\n"
labelC:
   .asciiz "\nC:\n"

   .text
   .globl main
main:
   # set up stack frame for main()
   sw   $fp, -4($sp)
   la   $fp, -4($sp)
   sw   $ra, -4($fp)
   addi $sp, $sp, -8

   # print matrix A
   la   $a0, labelA
   li   $v0, 4
   syscall
   lw   $a0, N
   lw   $a1, M
   la   $a2, A
   jal  printMatrix

   # print matrix B
   la   $a0, labelB
   li   $v0, 4
   syscall
   lw   $a0, M
   lw   $a1, P
   la   $a2, B
   jal  printMatrix

   # multiply C = A x B
   lw   $a0, N             # matrix dimensions in $a?
   lw   $a1, M
   lw   $a2, P
   addi $sp, $sp, -4       # matrix addresses on stack
   la   $t0, A
   sw   $t0, ($sp)         # push(&A)
   addi $sp, $sp, -4
   la   $t0, B
   sw   $t0, ($sp)         # push(&B)
   addi $sp, $sp, -4
   la   $t0, C
   sw   $t0, ($sp)         # push(&C)
   jal  multMatrices
   nop
   addi $sp, $sp, 12       # clean args off stack

   # print matrix C
   la   $a0, labelC
   li   $v0, 4
   syscall
   lw   $a0, N
   lw   $a1, P
   la   $a2, C
   jal  printMatrix

   # return 0 and clean up stack
   li   $v0, 0
   lw   $ra, -4($fp)
   la   $sp, 4($fp)
   lw   $fp, ($fp)
   jr   $ra

# COMP1521 18s1 Week 05 Lab
#
# void printMatrix(int nrows, int ncols, int m[nrows][ncols])
# {
#    for (int r = 0; r < nrows; r++) {
#       for (int c = 0; c < ncols; c++) {
#          printf(" %3d", m[r][c]);
#       }
#       printf("\n");
#    }
# }

   .text
   .globl printMatrix
printMatrix:
   # register usage:
   # nrows is $s0, ncols is $s1, r is $s2, c is $s3

   # set up stack frame for printMatrix()
   sw   $fp, -4($sp)
   la   $fp, -4($sp)
   sw   $ra, -4($fp)
   sw   $s0, -8($fp)
   sw   $s1, -12($fp)
   sw   $s2, -16($fp)
   sw   $s3, -20($fp)
   addi $sp, $sp, -24

   # set up registers
   move $s0, $a0
   move $s1, $a1
   
   # for r in 0..nrows-1
   li   $s2, 0
print_loop1:
   bge  $s2, $s0, print_end1
   # for c in 0..ncols-1
   li   $s3, 0
print_loop2:
   bge  $s3, $s1, print_end2
   # get m[r][c]
   li   $t1, 4            # sizeof(int)
   mul  $t0, $s2, $s1
   mul  $t0, $t0, $t1     # offset of start of row r
   mul  $t1, $s3, $t1     # offset of col c within row
   add  $t0, $t0, $t1     # offset from start of matrix
   add  $t0, $t0, $a2
   lw   $a0, ($t0)        # a0 = m[r][c]
   li   $v0, 1
   syscall                # printf("%d", a0)
   li   $a0, ' '
   li   $v0, 11
   syscall                # putchar(' ')
   addi $s3, $s3, 1       # c++
   j    print_loop2
print_end2:
   li   $a0, '\n'         # putchar('\n')
   li   $v0, 11
   syscall
   addi $s2, $s2, 1       # r++
   j    print_loop1
print_end1:

   # clean up stack and return
   lw   $ra, -4($fp)
   lw   $s0, -8($fp)
   lw   $s1, -12($fp)
   lw   $s2, -16($fp)
   lw   $s3, -20($fp)
   la   $sp, 4($fp)
   lw   $fp, ($fp)
   jr   $ra

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
loop2:
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
