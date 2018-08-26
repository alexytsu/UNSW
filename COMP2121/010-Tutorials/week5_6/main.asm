.include "m2560def.inc"

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
	ldi r28, low(RAMEND-8)		
	ldi r29, high(RAMEND-8)	

	out spl, r28
	out sph, r29

	ldi temp1, low(0)			; store local (int i)
	ldi temp2, high(0)			
	std Y+1, temp1
	std Y+2, temp2

	ldi temp1, low(1)			; store local (num = 1)
	ldi temp2, high(1)
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

	; end main prologue ------------------------------


	ldd r18, Y+1				; get local int i
	ldd r19, Y+2

	lds r20, glob_n				; get global int n

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

	call power

	inc r18
	rjmp loop_begin
loop_end:

power:
	push r28					; save the stack pointer of main
	push r29
	push r16
	push r17
	push r18
	push r19

	in r28, SPL					; update the frame pointer
	in r29, SPH

	sbiw r29:r28, 10			; reserve space for locals and formal parameters
	
	out SPL, r28
	out SPH, r29

	std Y+1, r21				; pass x to number
	std Y+2, r22				; pass i to power
	
	ldi temp1, 0
	std Y+3, temp1				; declare i

	ldi temp1, low(1)
	ldi temp2, high(1)
	std Y+4, temp1				; declare num = 1
	std Y+5, temp2

	ldd r16, Y+3				; load i in r16
	ldd r18, Y+4				; load num into r18:r19
	ldd r19, Y+5				

	ldd r20, Y+2				; load power into r20

for_pow:
	cp r20, r16
	brlo for_pow_end

	

	inc r16
	rjmp for_pow
for_pow_end:

	


	nop