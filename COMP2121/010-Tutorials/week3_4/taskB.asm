/*
 * taskB weeks3-4
 *
 *  Created: 6/08/2018 3:58:37 PM
 *   Author: Alex z5166086
 */ 

.include "m2560def.inc"

.def counter = r20 ;counter only counts to five

.def char = r21	; char is one byte long
.equ len = 6 ; loop termination condition

; ints are 4 bytes long
.def n1 = r16
.def n2 = r17
.def n3 = r18
.def n4 = r19

.def temp1 = r22
.def temp2 = r23
.def temp3 = r24
.def temp4 = r25

.dseg
.org 0x200
; b100  1111 1000  0001 1010 (325658 needs three bytes to be stored) 04 f8 1a
result_n: .byte 3 

.cseg
rjmp start

s: .db "999999" 
;s: .db "31645"

start:
	; char i -> R16
	; unsigned int n -> N4, N3, N2, N1 (N4 most significant byte)
	; n = 0;
	ldi n1, 0
	ldi n2, 0
	ldi n3, 	
	ldi n4, 0

	; load string from memory (address needs to be doubled)
	ldi zl, low(s<<1)
	ldi zh, high(s<<1)
	
	; for(i=0;i<=5;i++)
	clr counter
rbegin_for:
	cpi counter, len
	brsh end_for
	
	; loop body
	
	; n *= 10 -> n = n + (n << 2)

	lsl n1
	rol n2
	rol n3
	rol n4

	movw temp4:temp3, n4:n3
	movw temp2:temp1, n2:n1

	lsl temp1
	rol temp2
	rol temp3
	rol temp4
	
	lsl temp1
	rol temp2
	rol temp3
	rol temp4

	add n1, temp1
	adc n2, temp2
	adc n3, temp3
	adc n4, temp4

	; n += (s[i]-'0') -> n += char where char = s[i] - '0'
	lpm char, z+
	subi char, '0'
	add n1, char
	clr char
	adc n2, char
	adc n3, char
	adc n4, char

	; loop epilogue
	inc counter
	rjmp begin_for
end_for:

; store the result in the data segment
ldi yh, high(result_n)
ldi yl, low(result_n)
st y+, n3
st y+, n2
st y+, n1


halt:
	rjmp halt