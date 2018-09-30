; IMPORTANT NOTICE: 
; The labels on PORTL are reversed, i.e., PLi is actually PL7-i (i=0, 1, бн, 7).  

; Board settings: 
; Connect the four columns C0~C3 of the keypad to PL3~PL0 of PORTL and the four rows R0~R3 to PL7~PL4 of PORTL.
; Connect LED0~LED7 of LEDs to PC0~PC7 of PORTC.
    
; For I/O registers located in extended I/O map, "IN", "OUT", "SBIS", "SBIC", 
; "CBI", and "SBI" instructions must be replaced with instructions that allow access to 
; extended I/O. Typically "LDS" and "STS" combined with "SBRS", "SBRC", "SBR", and "CBR".

.include "m2560def.inc"

.macro do_lcd_command
	ldi r16, @0
	rcall lcd_command
	rcall lcd_wait
.endmacro

.macro do_lcd_data
	rcall lcd_data
	rcall lcd_wait
.endmacro



.def disp = r16

.def row = r17
.def col = r18
.def mask = r19

.def temp = r27
.def temp1 = r20
.def temp2 = r21

.def curr1 = r22
.def curr2 = r23

.def acc1 = r24
.def acc2 = r25

.def prevop = r26
.def rmp = r27

.equ PORTLDIR = 0xF0
.equ INITCOLMASK = 0xEF
.equ INITROWMASK = 0x01
.equ ROWMASK = 0x0F

.dseg
numbers: .byte 5*2
operators: .byte 4
ascii_result: .byte 5


.cseg
jmp RESET	; set the reset vector

.org 0x72
overflowmsg: .db "Overflow occured"
RESET:
	; initialise the stack pointer
	ldi temp, low(RAMEND)
	out SPL, temp
	ldi temp, high(RAMEND)
	out SPH, temp

	clr acc1
	clr acc2
	clr curr1
	clr curr2
	clr prevop

	; Keypad is connected on PORTL
	ldi temp, PORTLDIR ; columns are outputs, rows are inputs
	sts DDRL, temp     ; cannot use out

	; LED Strip is connected on PORTC
	ser temp
	out DDRC, temp ; Make PORTC all outputs
	out PORTC, acc1 ; Turn on all the LEDs

	; Display is on PORTA and F
	ser temp
	out DDRF, temp
	out DDRA, temp
	clr temp
	out PORTF, temp
	out PORTA, temp

	; Reset the screen
	do_lcd_command 0b00111000 ; 2x5x7
	rcall sleep_5ms
	do_lcd_command 0b00111000 ; 2x5x7
	rcall sleep_1ms
	do_lcd_command 0b00111000 ; 2x5x7
	do_lcd_command 0b00111000 ; 2x5x7
	do_lcd_command 0b00001000 ; display off?
	do_lcd_command 0b00000001 ; clear display
	do_lcd_command 0b00000110 ; increment, no display shift
	do_lcd_command 0b00001110 ; Cursor on, bar, no blink




; main keeps scanning the keypad to find which key is pressed.
main:
	ldi mask, INITCOLMASK ; initial column mask
	clr col ; initial column


	colloop: 
		STS PORTL, mask ; set column to mask value (sets column 0 off)
	
		ldi temp, 0xFF ; implement a delay so the hardware can stabilise
		delay:
		dec temp
		brne delay

		lds temp, PINL ; read PORTL. Cannot use in 
		andi temp, ROWMASK ; read only the row bits
		cpi temp, 0xF ; check if any rows are grounded
		breq nextcol ; if not go to the next column

		; row was grounded
		ldi mask, INITROWMASK ; initialise row check
		clr row ; initial row
		rowloop:      
			mov temp2, temp
			and temp2, mask ; check masked bit
			brne skipconv ; if the result is non-zero,

			; we need to look again
			rcall convert ; if bit is clear, convert the bitcode
			jmp main ; and start again
	
			skipconv:
			inc row ; else move to the next row
			lsl mask ; shift the mask to the next bit
			jmp rowloop          
	
		nextcol:     
			cpi col, 3 ; check if we are on the last column
			breq main ; if so, no buttons were pushed

			
			sec ; rotate the mask with carry bit set
			rol mask ; and then rotate left by a bit,
			inc col ; increment column value
			jmp colloop ; and check the next column

	.macro accumulate
	; multiply by 10
		clr temp1
		clr temp2

		lsl curr1
		rol curr2

		add temp1, curr1
		adc temp2, curr2
	

		lsl curr1
		rol curr2

		lsl curr1
		rol curr2

		add temp1, curr1
		adc temp2, curr2

		; add the current digit in
		add temp1, temp
		brcc skip_inc
		inc temp2
		skip_inc:

		mov curr1, temp1
		mov curr2, temp2
	.endmacro


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
		accumulate
		jmp convert_end
	
	letters:

		cpi prevop, 0
		breq addition
			
		cpi prevop, 1
		breq subtraction

		cpi prevop, 2
		breq addition

		jmp skip_eval
		addition:
			add acc1, curr1
			adc acc2, curr2
			brvs overflow
			jmp skip_eval

		subtraction:
			sub acc1, curr1
			sbc acc2, curr2
			brvs overflow
			jmp skip_eval

		skip_eval:

		clr curr1
		clr curr2
		clr temp
		
		cpi row, 0
		breq A		; -
		cpi row, 1
		breq B		; +
		cpi row, 2
		breq C		; =
		
		A:
		ldi temp, -3
		ldi prevop, 1
		jmp convert_end
		B:
		ldi temp, -5
		ldi prevop, 2
		jmp convert_end
		C:
		ldi temp, 13
		ldi prevop, 3
		jmp convert_end

	symbols:
		cpi col, 0 ; check if we have a star
		breq star
		cpi col, 1 ; or if we have zero
		breq zero
		ldi temp, 0xF ; else we'll output 0xF for hash
		jmp convert_end
		star:
			ldi temp, 0xE ; we'll output 0xE for star
			jmp convert_end
		zero:
			clr temp ; set to zero
			accumulate
			jmp convert_end

	overflow:
		do_lcd_command 0b00111000 ; 2x5x7
		rcall sleep_5ms
		do_lcd_command 0b00111000 ; 2x5x7
		rcall sleep_1ms
		do_lcd_command 0b00111000 ; 2x5x7
		do_lcd_command 0b00111000 ; 2x5x7
		do_lcd_command 0b00001000 ; display off?
		do_lcd_command 0b00000001 ; clear display
		do_lcd_command 0b00000110 ; increment, no display shift
		do_lcd_command 0b00001110 ; Cursor on, bar, no blink

		ldi zl, low(overflowmsg<<1)
		ldi zh, high(overflowmsg<<1)
		ldi prevop, 20
		loop_overflow:

		lpm disp, z+
		do_lcd_data

		subi prevop, 1
		brne loop_overflow
		
		jmp halt

	convert_end:
		
		out PORTC, acc1 ; write to led bar
		mov disp, temp
		subi disp, -'0' ; convert to ascii
		do_lcd_data
		rcall debounce

		cpi prevop, 3
		breq show_result

		ret

	skip_lcd:
		ret ; return to caller

	show_result:
		out portC, acc1

		; check if number is negative
		tst acc2
		brmi invert
		rjmp skipinvert
		invert:
		ldi temp, 0xff
		eor acc1, temp
		eor acc2, temp
		inc acc1
		ldi disp, '-'
		do_lcd_data
		skipinvert:


		ldi zh, high(ascii_result)
		ldi zl, low(ascii_result)
		rcall Bin2ToAsc5
		
		ldi prevop, 5
		display_loop:
		
		ld disp, z+
		cpi disp, ' '
		breq skip_disp
		do_lcd_data
		skip_disp:
		subi prevop, 1
		brne display_loop
	
	
	halt:
		jmp halt




; LCD CODE -----------------
.equ LCD_RS = 7
.equ LCD_E = 6
.equ LCD_RW = 5
.equ LCD_BE = 4

.macro lcd_set
	sbi PORTA, @0
.endmacro
.macro lcd_clr
	cbi PORTA, @0
.endmacro

;
; Send a command to the LCD (r16)
;

lcd_command:
	out PORTF, r16
	nop
	lcd_set LCD_E
	nop
	nop
	nop
	lcd_clr LCD_E
	nop
	nop
	nop
	ret

lcd_data:
	out PORTF, r16
	lcd_set LCD_RS
	nop
	nop
	nop
	lcd_set LCD_E
	nop
	nop
	nop
	lcd_clr LCD_E
	nop
	nop
	nop
	lcd_clr LCD_RS
	ret

lcd_wait:
	push r16
	clr r16
	out DDRF, r16
	out PORTF, r16
	lcd_set LCD_RW
lcd_wait_loop:
	nop
	lcd_set LCD_E
	nop
	nop
    nop
	in r16, PINF
	lcd_clr LCD_E
	sbrc r16, 7
	rjmp lcd_wait_loop
	lcd_clr LCD_RW
	ser r16
	out DDRF, r16
	pop r16
	ret

.equ F_CPU = 16000000
.equ DELAY_1MS = F_CPU / 4 / 1000 - 4
; 4 cycles per iteration - setup/call-return overhead

sleep_1ms:
	push r24
	push r25
	ldi r25, high(DELAY_1MS)
	ldi r24, low(DELAY_1MS)
delayloop_1ms:
	sbiw r25:r24, 1
	brne delayloop_1ms
	pop r25
	pop r24
	ret

sleep_5ms:
	rcall sleep_1ms
	rcall sleep_1ms
	rcall sleep_1ms
	rcall sleep_1ms
	rcall sleep_1ms
	ret

sleep_25ms:
	rcall sleep_5ms
	rcall sleep_5ms
	rcall sleep_5ms
	rcall sleep_5ms
	rcall sleep_5ms
	ret

sleep_100ms:
	rcall sleep_25ms
	rcall sleep_25ms
	rcall sleep_25ms
	rcall sleep_25ms
	ret

debounce:
	rcall sleep_100ms
	rcall sleep_100ms
	ret

; Bin2ToAsc5
; ==========
; converts a 16-bit-binary to a 5 digit ASCII-coded decimal
; In: 16-bit-binary in acc2:L, Z points to the highest
;   of 5 ASCII digits, where the result goes to
; Out: Z points to the beginning of the ASCII string, lea-
;   ding zeros are filled with blanks
; Used registers: acc2:L (content is not changed),
;   temp2:L (content is changed), rmp
; Called subroutines: Bin2ToBcd5
;
Bin2ToAsc5:
	rcall Bin2ToBcd5 ; convert binary to BCD
	ldi rmp,4 ; Counter is 4 leading digits
	mov temp1,rmp
Bin2ToAsc5a:
	ld rmp,z ; read a BCD digit
	tst rmp ; check if leading zero
	brne Bin2ToAsc5b ; No, found digit >0
	ldi rmp,' ' ; overwrite with blank
	st z+,rmp ; store and set to next position
	dec temp1 ; decrement counter
	brne Bin2ToAsc5a ; further leading blanks
	ld rmp,z ; Read the last BCD
Bin2ToAsc5b:
	inc temp1 ; one more char
Bin2ToAsc5c:
	subi rmp,-'0' ; Add ASCII-0
	st z+,rmp ; store and inc pointer
	ld rmp,z ; read next char
	dec temp1 ; more chars?
	brne Bin2ToAsc5c ; yes, go on
	sbiw ZL,5 ; Pointer to beginning of the BCD
	ret ; done
;

; Bin2ToBcd5
; ==========
; converts a 16-bit-binary to a 5-digit-BCD
; In: 16-bit-binary in acc2:L, Z points to first digit
;   where the result goes to
; Out: 5-digit-BCD, Z points to first BCD-digit
; Used registers: acc2:L (unchanged), temp2:L (changed),
;   rmp
; Called subroutines: Bin2ToDigit
;
Bin2ToBcd5:
	push acc2 ; Save number
	push acc1
	ldi rmp,HIGH(10000) ; Start with tenthousands
	mov temp2,rmp
	ldi rmp,LOW(10000)
	mov temp1,rmp
	rcall Bin2ToDigit ; Calculate digit
	ldi rmp,HIGH(1000) ; Next with thousands
	mov temp2,rmp
	ldi rmp,LOW(1000)
	mov temp1,rmp
	rcall Bin2ToDigit ; Calculate digit
	ldi rmp,HIGH(100) ; Next with hundreds
	mov temp2,rmp
	ldi rmp,LOW(100)
	mov temp1,rmp
	rcall Bin2ToDigit ; Calculate digit
	ldi rmp,HIGH(10) ; Next with tens
	mov temp2,rmp
	ldi rmp,LOW(10)
	mov temp1,rmp
	rcall Bin2ToDigit ; Calculate digit
	st z,acc1 ; Remainder are ones
	sbiw ZL,4 ; Put pointer to first BCD
	pop acc1 ; Restore original binary
	pop acc2
	ret ; and return
;
; Bin2ToDigit
; ===========
; converts one decimal digit by continued subraction of a
;   binary coded decimal
; Used by: Bin2ToBcd5, Bin2ToAsc5, Bin2ToAsc
; In: 16-bit-binary in acc2:L, binary coded decimal in
;   temp2:L, Z points to current BCD digit
; Out: Result in Z, Z incremented
; Used registers: acc2:L (holds remainder of the binary),
;   temp2:L (unchanged), rmp
; Called subroutines: -
;
Bin2ToDigit:
	clr rmp ; digit count is zero
Bin2ToDigita:
	cp acc2,temp2 ; Number bigger than decimal?
	brcs Bin2ToDigitc ; MSB smaller than decimal
	brne Bin2ToDigitb ; MSB bigger than decimal
	cp acc1,temp1 ; LSB bigger or equal decimal
	brcs Bin2ToDigitc ; LSB smaller than decimal
Bin2ToDigitb:
	sub acc1,temp1 ; Subtract LSB decimal
	sbc acc2,temp2 ; Subtract MSB decimal
	inc rmp ; Increment digit count
	rjmp Bin2ToDigita ; Next loop
Bin2ToDigitc:
	st z+,rmp ; Save digit and increment
	ret ; done

