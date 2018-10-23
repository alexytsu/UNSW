/*
 * kpdInput.asm
 *
 *  Created: 23/10/2018 3:06:05 PM
 *   Author: rowra
 */ 
 
 .cseg

 
; takes no parameters, returns the number that entered
get_num:
get_num_start:
	ldi mask, INITCOLMASK ; initial column mask
	clr col ; initial column
	colloopnum:
	STS PORTL, mask ; set column to mask value
	; (sets column 0 off)
	ldi temp, 0xFF ; implement a delay so the
	; hardware can stabilize
	delaynum:
	dec temp
	brne delaynum
	LDS temp, PINL ; read PORTL. Cannot use in 
	andi temp, ROWMASK ; read only the row bits
	cpi temp, 0xF ; check if any rows are grounded
	breq nextcol ; if not go to the next column
	ldi mask, INITROWMASK ; initialise row check
	clr row ; initial row
	rowloopnum:      
	mov temp2, temp
	and temp2, mask ; check masked bit
	brne skipconvnum ; if the result is non-zero,
	; we need to look again
	rcall convert ; if bit is clear, convert the bitcode
	ret
	skipconvnum:
	inc row ; else move to the next row
	lsl mask ; shift the mask to the next bit
	jmp rowloopnum          
	nextcol:     
	cpi col, 3 ; check if we're on the last column
	breq get_num_start  ; if so, no buttons were pushed,
	; so start again.

	sec ; else shift the column mask:
	; We must set the carry bit
	rol mask ; and then rotate left by a bit,
	; shifting the carry into
	; bit zero. We need this to make
	; sure all the rows have
	; pull-up resistors
	inc col ; increment column value
	jmp colloopnum ; and check the next column

	ret

get_char:
	; function prologue	
	push YL	; save the current stack frame pointer
	push YH
	in YL, SPL ; get the stack frame
	in YH, SPH
	sbiw Y, 1
	out SPL, YL
	out SPH, YH ; update the frame position

	; move actual parameters to formal parameters
	std Y+1, r24
	
	; store conflict registers
	push r18	; first character
	push r19	; A B or C pressed?
	push r20	;

	clr r18
	clr r19

get_char_start:
	ldi mask, INITCOLMASK ; initial column mask
	clr col ; initial column
	colloopchar:
	STS PORTL, mask ; set column to mask value
	; (sets column 0 off)
	ldi temp, 0xFF ; implement a delay so the
	; hardware can stabilize
	delaychar:
	dec temp
	brne delaychar
	LDS temp, PINL ; read PORTL. Cannot use in 
	andi temp, ROWMASK ; read only the row bits
	cpi temp, 0xF ; check if any rows are grounded
	breq nextcol ; if not go to the next column
	ldi mask, INITROWMASK ; initialise row check
	clr row ; initial row
	rowloopchar:      
	mov temp2, temp
	and temp2, mask ; check masked bit
	brne skipconvchar ; if the result is non-zero,
	; we need to look again
	rcall convert ; if bit is clear, convert the bitcode
	; check if A B or C pressed
	; A (abc def ghi)
	; B (jkl mno pqr)
	; C (stu vwx yz )

	; if r19 is still zero, we need to look at the letter
	cpi r19, 0
	brne number_to_letter
		ser r19 ; set the r19 "flag" so that next time we know to look for a number

		cpi temp, 10
		breq a_to_i
		cpi temp, 11
		breq j_to_r
		cpi temp, 12
		breq s_to_space

		a_to_i:
			ldi r18, 'A'
			subi r18, 1
		j_to_r:
			ldi r18, 'I'
		s_to_space:
			ldi r18, 'R'
	
		jmp get_char_start
	

	number_to_letter:
		add r18, temp
		rjmp return_char
	
	skipconvchar:
	inc row ; else move to the next row
	lsl mask ; shift the mask to the next bit
	jmp rowloopchar          
	nextcolchar:     
	cpi col, 3 ; check if we're on the last column
	breq get_char_start  ; if so, no buttons were pushed,
	; so start again.

	sec ; else shift the column mask:
	; We must set the carry bit
	rol mask ; and then rotate left by a bit,
	; shifting the carry into
	; bit zero. We need this to make
	; sure all the rows have
	; pull-up resistors
	inc col ; increment column value
	jmp colloopchar ; and check the next column
	
	
	; epilogue
	return_char:
	mov temp, r18
	pop r20
	pop r19
	pop r18

	adiw Y, 1
	out SPH, YH
	out SPL, YL
	
	pop YH
	pop YL 
	ret
	

; convert function converts the row and column given to a
; binary number and also outputs the value to PORTC.
; Inputs come from registers row and col and output is in
; temp.
convert:
cpi col, 3 ; if column is 3 we have a letter
breq letters
cpi row, 3 ; if row is 3 we have a symbol or 0
breq symbols
mov temp, row ; otherwise we have a number (1-9)
lsl temp ; temp = row * 2
add temp, row ; temp = row * 3
add temp, col ; add the column address
; to get the offset from 1
inc temp ; add 1. Value of switch is
; row*3 + col + 1.
jmp convert_end
letters:
ldi temp, 0xA
add temp, row ; increment from 0xA by the row value
jmp convert_end
symbols:
cpi col, 0 ; check if we have a star
breq star
cpi col, 1 ; or if we have zero
breq zero
ldi temp, 0xF ; we'll output 0xF for hash
jmp convert_end
star:
ldi temp, 0xE ; we'll output 0xE for star
jmp convert_end
zero:
clr temp ; set to zero
convert_end:
out PORTC, temp ; write value to PORTC
ret ; return to caller