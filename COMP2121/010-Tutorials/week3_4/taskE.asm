;
; LabTask5.asm
;
; Created: 11/08/2018 11:03:37 AM
; Author : Rowan Rama
;

.include "m2560def.inc"

.equ size = 5
.def c_high=r19
.def c_higher=r18
.def c_low=r17
.def c_lower=r16
.def i=r8
.def j=r9
.def k=r10
.def a_high=r21
.def a_low=r20
.def b_high=r23
.def b_low=r22
.def temp=r24

.dseg
ArrayA: .byte 50
ArrayB: .byte 50
ArrayC: .byte 100
	
.cseg
	ldi xl, low(ArrayA)
	ldi xh, high(ArrayA)
	ldi yl, low(ArrayB)
	ldi yh, high(ArrayB)
	ldi zl, low(ArrayC)
	ldi zh, high(ArrayC)
	clr i

.macro multiply

; https://sites.google.com/site/avrasmintro/home/2b-basic-math
		CLR ZERO            ;Set R2 to zero
        MUL AH,BH            ;Multiply high bytes AHxBH
        MOVW ANS4:ANS3,R1:R0 ;Move two-byte result into answer

        MUL AL,BL            ;Multiply low bytes ALxBL
        MOVW ANS2:ANS1,R1:R0 ;Move two-byte result into answer

        MUL AH,BL            ;Multiply AHxBL
        ADD ANS2,R0          ;Add result to answer
        ADC ANS3,R1          ;
        ADC ANS4,ZERO        ;Add the Carry Bit

        MUL BH,AL            ;Multiply BHxAL
        ADD ANS2,R0          ;Add result to answer
        ADC ANS3,R1          ;
        ADC ANS4,ZERO        ;Add the Carry Bit
.endmacro

main:
	
fori1:
	
	clr j
forj1:
		
	clr a_low
	ldi temp, 1024
	add a_low, i
	add a_low, j
	muls temp, a_low
	clr c_low

	st x+, r0
	st x+, r1
	st y+, r0
	st y+, r1
	st z+, c_low
	st z+, c_low
	st z+, c_low
	st z+, c_low

	inc j
	cpi j, size
	brlt forj1
	
	inc i
	cpi i, size
	brlt fori1

	clr i
	clr j
	clr k
	ldi zl, low(ArrayC)
	ldi zh, high(ArrayC)
	
fori2:

	clr j
	ldi xl, low(ArrayA)
	ldi xh, high(ArrayA)
	ldi temp, 5
	mul i, temp
	add xl, r0
	adc xh, r1
		
		forj2:
			
			ldi yl, low(ArrayB)
			ldi yh, high(ArrayB)
			add yl, j
			adc yh, r7
			
			clr k
			fork:

				ld a, x
				ld b, y
				ld c_high, z+
				ld c_low, z
				muls a, b
				add c_low, r0
				adc c_high, r1
				st z, c_low
				st -z, c_high

				adiw yh:yl, 5
				adiw xh:xl, 1

			inc k
			cpi k, 5
			brlt fork

			sbiw xh:xl, 5
			adiw zh:zl, 2


		inc j
		cpi j, size
		brlt forj2

		adiw xh:xl, 5

	inc i
	cpi i, size
	brlt fori2

stop: nop
	rjmp stop
