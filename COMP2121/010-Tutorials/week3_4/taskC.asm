;
; week3_4.asm
;
; Created: 6/08/2018 3:12:12 PM
; Author : Alex
;

.include "m2560def.inc"

.equ len = 10
.def sum1 = r16
.def sum2 = r17

.def counter = r23
.def zero = r22

.def temp1 = r18
.def temp2 = r19

.def result1 = r20
.def result2 = r21

.dseg
.org 0x200
A: .byte 20

.cseg

	; generate the array
clr zero
clr counter
generate:
	cpi counter, len
	brsh end_generate
	

	; << 3 + <<2 + <<1 +
	clr result1
	clr result2
	clr temp1
	clr temp2
	
	mov temp1, counter
	
	lsl temp1
	rol temp2
	
	lsl temp1
	rol temp2

	lsl temp1
	rol temp2

	add result1, temp1
	adc result2, temp2
	
	lsl temp1
	rol temp2

	lsl temp1
	rol temp2

	lsl temp1
	rol temp2

	add result1, temp1
	adc result2, temp2

	lsl temp1
	rol temp2

	add result1, temp1
	adc result2, temp2

	ldi yh, high(A)
	ldi yl, low(A)

	mov temp1, counter
	lsl temp1

	add yl, temp1
	adc yh, zero

	st y+, result2
	st y, result1

	inc counter
	rjmp generate
end_generate:

	clr sum1
	clr sum2
	clr counter
	
	ldi zh, high(A)
	ldi zl, low(A)

start_sum:
	cpi counter, len
	brsh end_sum

	ld result2	, z+
	ld result1, z+

	add sum1, result1
	adc sum2, result2

	inc counter
	rjmp start_sum
end_sum:
	

halt:
	rjmp halt