/*
 * kpdInput.asm
 *
 *  Created: 23/10/2018 3:06:05 PM
 *   Author: rowra
 */ 
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
	breq nextcolnum ; if not go to the next column
	ldi mask, INITROWMASK ; initialise row check
	clr row ; initial row
	rowloopnum:      
	mov temp2, temp
	and temp2, mask ; check masked bit
	brne skipconvnum ; if the result is non-zero,
	; we need to look again
	rcall convert ; if bit is clear, convert the bitcode

	; return if #	
	cpi temp, 0xf
	breq terminate

	cpi temp, 10
	brge get_num_again

	ret
	get_num_again:
	rcall get_num
	terminate:
	ret
	
	skipconvnum:
	inc row ; else move to the next row
	lsl mask ; shift the mask to the next bit
	jmp rowloopnum          
	nextcolnum:     
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
	push r18
	push temp2
	clr r18

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
	breq nextcolchar ; if not go to the next column
	
	ldi mask, INITROWMASK ; initialise row check
	clr row ; initial row
	rowloopchar:      
		mov temp2, temp
		and temp2, mask ; check masked bit
		brne skipconvchar ; if the result is non-zero look again

	rcall convert 

	; check if A B or C pressed
	; A (abc def ghi)
	; B (jkl mno pqr)
	; C (stu vwx yz )

	cpi temp, 10
	breq a_to_i
	cpi temp, 11
	breq j_to_r
	cpi temp, 12
	breq s_to_space

	; wasn't a letter and letter has not been pressed previously
	cpi r18, 0x00
	brne check_if_number ; if r18 is set, then check if temp is a number
	rjmp get_char_start

	check_if_number:
	cpi temp, 10
	brlt number_to_letter ; if the key that was pressed is a number, do the conversion
	rjmp nextcolchar

	a_to_i:
		ldi r18, 'A'
		subi r18, 1
		rjmp get_char_start
	j_to_r:
		ldi r18, 'I'
		rjmp get_char_start
	s_to_space:
		ldi r18, 'R'
		rjmp get_char_start

	number_to_letter:
		add temp, r18
		pop temp2
		pop r18

		; convert '[' to space
		cpi temp, '['
		breq return_space
		ret
		return_space:
		ldi temp, ' ' 
		ret
	
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