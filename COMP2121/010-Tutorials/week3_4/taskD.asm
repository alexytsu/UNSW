
; LabTask4.asm
;
; Created: 11/08/2018 11:03:37 AM
; Author : Rowan Rama
;
; Multiplies 2 5x5 matrices of size 1 byte into 1 5x5 matrix of size 2 bytes


.include "m2560def.inc"

	.equ size = 5		; defines size of row or column
	.def c_high=r22		; define variables to be used 
	.def c_low=r21
	.def i=r16
	.def j=r17
	.def k=r20
	.def a=r18
	.def b=r19
	.def temp=r23

	.dseg
ArrayA: .byte 25		; saves 25 bytes of space for the first matrix
ArrayB: .byte 25		; saves 25 bytes of space for the second matrix
ArrayC: .byte 50		; saves 50 bytes of space for the resulting matrix
	
	.cseg
	ldi xl, low(ArrayA)		; initialises all the values
	ldi xh, high(ArrayA)
	ldi yl, low(ArrayB)
	ldi yh, high(ArrayB)
	ldi zl, low(ArrayC)
	ldi zh, high(ArrayC)
	clr i

main:
	
	fori1:					; for (i=0; i<5; i++)
	
		clr j				;j=0
		forj1:				; for (j=0; j<5; j++)
		
			clr a
			clr b
			add a, i
			add a, j		; A[i][j] = i+j
			add b, i
			sub b, j		; B[i][j] = i-j
			clr c_high
			clr c_low

			st x+, a
			st y+, b
			st z+, c_high	;sets values for array elements
			st z+, c_low

		inc j				; j++
		cpi j, size			
		brlt forj1			; checks j<5
	
	inc i				; i++
	cpi i, size
	brlt fori1			; checks i<5

	clr i
	clr j
	clr k
	ldi zl, low(ArrayC)
	ldi zh, high(ArrayC)	; reinitialises values and counters
	

	fori2:				; for(i=0;i<5;i++)

		clr j
		ldi xl, low(ArrayA)
		ldi xh, high(ArrayA)		;resets location of the ArrayA
		ldi temp, 5
		mul i, temp
		add xl, r0
		adc xh, r1
				
		forj2:				; for(j=0;j<5;j++)
			
			ldi yl, low(ArrayB)
			ldi yh, high(ArrayB)	;resets location of ArrayB
			add yl, j
			adc yh, r7
			
			clr k
			fork:				; for(k=0;k<5;k++)

				ld a, x			; loads value in A[i][k]
				ld b, y			; loads value in B[k][j]
				ld c_high, z+
				ld c_low, z
				muls a, b		; A[i][k] * B[k][j]
				add c_low, r0
				adc c_high, r1
				st z, c_low		; stores 2 byte result in C[i][j]
				st -z, c_high

				adiw yh:yl, 5	; goes to next row of A
				adiw xh:xl, 1	; goes to next col of B

			inc k			; k++
			cpi k, 5		
			brlt fork		; checks k<5

			sbiw xh:xl, 5	;resets B back to start of row
			adiw zh:zl, 2	;goes to next element in C


		inc j			; j++
		cpi j, size		
		brlt forj2		; checks j<5

	inc i			; i++
	cpi i, size
	brlt fori2		; checks i<5

stop: nop
	rjmp stop