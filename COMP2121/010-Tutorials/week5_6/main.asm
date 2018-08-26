.include "m2560def.inc"

.macro	inc_loop_counter
	ldi r16, 1
	ldi r17, 0
	add @0, r16
	adc @1, r17
.endmacro

.macro mult_16_by_8
	; multiplication
	.def res1 = r2
	.def res2 = r3
	.def res3 = r4
								; result * a[i]
	.def m1L = @0
	.def m1M = @1
	.def m2 = @2

	mul m1L, m2
	mov Res1, r0
	mov Res2, r1
	mul m1M, m2
	mov res3, r1
	add res2, r0
	brcc noCarry				; skip carry if not needed
	inc Res3
noCarry:
				
.endmacro

.def temp1=r16
.def temp2=r17

.dseg
	.org 0x200
	glob_x: .byte 1
	glob_n: .byte 1
	array: .byte 11

.cseg

	main_i: .dw 0				; store initial values in
	main_sum: .dw 1				; code segment
	main_result: .dw 0			

	ldi temp1, 3				; load global variables
	sts glob_x, temp1			
	ldi temp1, 10				
	sts glob_n, temp1 

main:
	ldi r28, low(RAMEND-9)		
	ldi r29, high(RAMEND-9)	

	out spl, r28
	out sph, r29

	ldi temp1, low(0)			; store local (int i)
	ldi temp2, high(0)			
	std Y+1, temp1
	std Y+2, temp2

	ldi temp1, low(0)			; store local (sum = 0)
	ldi temp2, high(0)
	std Y+3, temp1
	std Y+4, temp2

	ldi temp1, low(0)			; store local (result)
	ldi temp2, high(0)
	std Y+5, temp1
	std Y+6, temp2

	ldi temp1, low(array)		; store local (a *)
	ldi temp2, high(array)		
	std Y+7, temp1
	std Y+8, temp2

	; end main prologue 

	ldd r18, Y+1				; get local int i
	ldd r19, Y+2
	lds r20, glob_n				; get global int n

	ldd r26, Y+3				; get local sum (26:27)
	ldd r27, Y+4
	ldd r28, Y+9

loop_begin:
	cp r20, r18					; if n < i, break
	brlo loop_end
	
	ldd r30, Y+7				; get address of array
	ldd r31, Y+8
	add r30, r18				; get address of a[i]
	adc r31, r19
	st Z, r18					; a[i] = i

	; prepare params for function call
	lds r21, glob_x  			; actual parameter x
	mov r22, r18				; actual parameter i

	call power					; power returns to r24:r25
	std y+5, r24				; result = power(x,i)
	std y+6, r25				
/*
	; multiplication
	.def res1 = r2
	.def res2 = r3
	.def res3 = r4
								; result * a[i]
	.def m1L = r24
	.def m1M = r25
	.def m2 = r18

	mul m1L, m2
	mov Res1, r0
	mov Res2, r1
	mul m1M, m2
	mov res3, r1
	add res2, r0
	brcc noCarry				; skip carry if not needed
	inc Res3
noCarry:
*/

	mult_16_by_8 r24, r25, r18				

	add r26, res1
	adc r27, res2		
	
	std Y+3, r26
	std Y+4, r27		

	inc_loop_counter r18, r19
	
	rjmp loop_begin
loop_end:

	std Y+3, r26				; save sum as local variable in main
	std Y+4, r27

	rjmp end_program

power:
	push r28					; save the stack pointer of main
	push r29


	in r28, SPL					; load the stack pointer
	in r29, SPH
	sbiw r29:r28, 8				; reserve space for locals and formal parameters
	out SPL, r28
	out SPH, r29				; update the frame positions

	; move actual parameters to formal parameters
	ldi temp1, 0
	std Y+1, r21				; pass x to number
	std Y+2, temp1
	std Y+3, r22				; pass i to power
	std Y+4, temp1
	
	
	push r18					; store conflict registers
	push r19
	push r20
	push r21
	push r22
	push r23
	push r26
	push r27

	; initialise local variables
	ldi temp2, 1
	std Y+5, temp2				; initialise local i
	std Y+6, temp1
	std Y+7, temp2
	std Y+8, temp1

	ldd r26, y+1				; number(r26:r27)
	ldd r27, y+2
	ldd r18, y+3				; power(r18:r19)
	ldd r19, y+4
	ldd r20, y+5				; i(r20:r21)
	ldd r21, y+6
	ldd r22, y+7				; num(r22:r23)
	ldd r23, y+8

for_pow:
	cp r18, r20					; pow(18:19) < i(20:21) break
	cpc r19, r21
	brlo for_pow_end

	ldd r24, Y+7
	ldd r25, Y+8

	mult_16_by_8 r24, r25, r26

	std Y+7, res1
	std Y+8, res2
	
	inc_loop_counter r20, r21
	rjmp for_pow
for_pow_end:

	; store result into 24, 25

	pop r27
	pop r26
	pop r23
	pop r22
	pop r21
	pop r20
	pop r19
	pop r18

	ldd r24, y+7
	ldd r25, y+8

	adiw r28, 8
	out sph, r29
	out spl, r28

	pop r29
	pop r28
	ret

end_program:
	nop