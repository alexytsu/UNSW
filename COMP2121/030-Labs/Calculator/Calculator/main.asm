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

.def temp2 =r20
.def temp = r21

.def curr1 = r22
.def curr2 = r23

.equ PORTLDIR = 0xF0
.equ INITCOLMASK = 0xEF
.equ INITROWMASK = 0x01
.equ ROWMASK = 0x0F

.dseg
numbers: .byte 5*2
operators: .byte 4


.cseg
jmp RESET	; set the reset vector

.org 0x72
RESET:

	; initialise the stack pointer
	ldi temp, low(RAMEND)
	out SPL, temp
	ldi temp, high(RAMEND)
	out SPH, temp

	; Keypad is connected on PORTL
	ldi temp, PORTLDIR ; columns are outputs, rows are inputs
	sts DDRL, temp     ; cannot use out

	; LED Strip is connected on PORTC
	ser temp
	out DDRC, temp ; Make PORTC all outputs
	out PORTC, temp ; Turn on all the LEDs

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
		ldi temp, 0xF ; else we'll output 0xF for hash
		jmp convert_end
		star:
			ldi temp, 0xE ; we'll output 0xE for star
			jmp convert_end
		zero:
			clr temp ; set to zero
	convert_end:
		mov disp, temp
		subi disp, -'0'
		do_lcd_data
		rcall debounce

	skip_lcd:
		ret ; return to caller


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
	rcall sleep_100ms
	rcall sleep_100ms
	rcall sleep_100ms
	ret