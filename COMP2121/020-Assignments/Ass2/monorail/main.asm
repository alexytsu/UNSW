;
; monorail.asm
;
; Created: 22/10/2018 4:10:50 PM
; Author : Alex
;

.include "m2560def.inc"

; ==== macros ====
; macros for lcd
.macro do_lcd_command
	ldi r16, @0
	rcall lcd_command
	rcall lcd_wait
.endmacro

.macro display
	rcall lcd_data
	rcall lcd_wait
.endmacro

.macro display_integer
	subi disp, -'0'
	display
.endmacro

; ==== aliases ====
; for displaying
.def disp=r16

; temporary registers
.def temp=r17
.def temp2=r23

; keypad reading
.def row = r20
.def col = r21
.def mask = r22

.def program_status=r1

; masks 
.equ PORTLDIR = 0xF0
.equ INITCOLMASK = 0xEF
.equ INITROWMASK = 0x01
.equ ROWMASK = 0x0F

.dseg
.org 0x200
station_names: .byte 100
travel_times: .byte 10
n_stations: .byte 1


.cseg
rjmp SETUP

.org 0x72

station_prompt: .db "Station"
configuration_complete: .db "Configuration Complete. Initialising system ..."

; initialisation etc. that should run once
SETUP:
	ldi temp, low(RAMEND)
	out spl, temp
	ldi temp, high(RAMEND)
	out sph, temp

	; ===== setup pins and ports =====
	; LED strip on PORTC
	ser temp
	out DDRC, temp
	out PORTC, temp
	
	; Keypad is connected on PORTL
	ldi temp, PORTLDIR ; columns are outputs, rows are inputs
	sts DDRL, temp     ; cannot use out

	; LCD is outputs on PORTA and PORTF
	ser temp
	out DDRF, temp
	out DDRA, temp
	clr temp
	out PORTF, temp
	out PORTA, temp

	; ==== reset hardware ====
	; reset the screen
	do_lcd_command 0b00111000 ; 2x5x7
	rcall sleep_5ms
	do_lcd_command 0b00111000 ; 2x5x7
	rcall sleep_1ms
	do_lcd_command 0b00111000 ; 2x5x7
	do_lcd_command 0b00111000 ; 2x5x7
	do_lcd_command 0b00001000 ; display off?
	do_lcd_command 0b00000001 ; clear display
	do_lcd_command 0b00000110 ; increment, no display shift
	do_lcd_command 0b00001111 ; Cursor on, bar, with blink
	
	ldi r24, 0
	get_all_names:
	rcall save_station_name
	rcall print_station_name
	do_lcd_command 0b00000001
	ldi disp, 't'
	display
	rcall save_station_time
	rcall pause
	inc r24
	cpi r24, 2
	brne get_all_names
	


; code that should loop
main:

clr r24
show_all_names:
	rcall print_station_name
	rcall pause
	rcall get_station_time
	display_integer
	rcall pause
	inc r24
	cpi r24, 2
	brne show_all_names


	rjmp main


; gets from the user the number of stations and saves it to the relevant section in memory
get_number_of_stations:
	; function prologue
	ldi XH, high(n_stations)
	ldi XL, low(n_stations)
	
	ldi disp, 'N'
	display
	ldi disp, '?'
	display	
	ldi disp, ':'
	display

	call get_num
	st X, temp

	ld disp, X
	display_integer

	ret

; pass in n as register r24
print_station_name:
	; function prologue	
	push YL	; save the current stack frame pointer
	push YH
	in YL, SPL ; get the stack frame
	in YH, SPH
	sbiw Y, 1	; reserve two bytes for local loop counter and parameter station number
	out SPL, YL
	out SPH, YH ; update the frame position

	; move actual parameters to formal parameters
	std Y+1, r24
	
	; store conflict registers
	push r18	; i
	push r19	; n *10
	push r20	; temp n

	; makes r19 hold 10xr20
	ldd r20, Y+1 
	
	lsl r20
	mov r19, r20
	lsl r20
	lsl r20
	add r19, r20

	; get address of the station name's storage location
	ldi XH, high(station_names)
	ldi XL, low(station_names)
	; add increment for nth station name
	clr r20
	add XL, r19
	adc XH, r20

	do_lcd_command 0b0000001
	
	ldd disp, Y+1
	display_integer

	do_lcd_command 0b11000000

	ldi temp2, 10
	load_name_letter:
		ld disp, X+
		display
		dec temp2
		brne load_name_letter

	; epilogue
	pop r20
	pop r19
	pop r18

	adiw Y, 1
	out SPH, YH
	out SPL, YL
	
	pop YH
	pop YL 
	ret

; pass in n as register r24
save_station_name:
	; function prologue	
	push YL	; save the current stack frame pointer
	push YH
	in YL, SPL ; get the stack frame
	in YH, SPH
	sbiw Y, 1	; reserve two bytes for local loop counter and parameter station number
	out SPL, YL
	out SPH, YH ; update the frame position

	; move actual parameters to formal parameters
	std Y+1, r24
	
	; store conflict registers
	push r18	; i
	push r19	; n *10
	push r20	; temp n
	
	do_lcd_command 0b00000001

	; makes r19 hold 10xr20
	ldd r20, Y+1 
	
	lsl r20
	mov r19, r20
	lsl r20
	lsl r20
	add r19, r20

	; get address of the station name's storage location
	ldi XH, high(station_names)
	ldi XL, low(station_names)
	; add increment for nth station name
	clr r20

	out PORTC, r20

	add XL, r19
	adc XH, r20

	ldi temp2, 10
	get_name_letter:
		rcall get_char
		mov disp, temp
		display

		st X+, disp

		rcall debounce

		dec temp2
		brne get_name_letter

	; epilogue
	pop r20
	pop r19
	pop r18

	adiw Y, 1
	out SPH, YH
	out SPL, YL
	
	pop YH
	pop YL 
	ret

; save travel time for station n (r24)
save_station_time:
	; function prologue	
	push YL	; save the current stack frame pointer
	push YH
	in YL, SPL ; get the stack frame
	in YH, SPH
	sbiw Y, 1	; reserve two bytes for local loop counter and parameter station number
	out SPL, YL
	out SPH, YH ; update the frame position

	; move actual parameters to formal parameters
	std Y+1, r24
	
	; store conflict registers
	push r18	; temp
	push r19	; temp n

	ldd r19, Y+1
	; get address of the station name's storage location
	ldi XH, high(travel_times)
	ldi XL, low(travel_times)
	; add increment for nth station name
	clr r18
	add XL, r19
	adc XH, r18

	; dummy 5 seconds
	rcall get_num
	st X, temp
	out PORTC, temp
	rcall pause

	; epilogue
	pop r19
	pop r18

	adiw Y, 1
	out SPH, YH
	out SPL, YL
	
	pop YH
	pop YL 

	ret

; gets travel time for station n to station n+1 (r24) returns int in r25
get_station_time:
	; function prologue	
	push YL	; save the current stack frame pointer
	push YH
	in YL, SPL ; get the stack frame
	in YH, SPH
	sbiw Y, 1	; reserve two bytes for local loop counter and parameter station number
	out SPL, YL
	out SPH, YH ; update the frame position

	; move actual parameters to formal parameters
	std Y+1, r24
	
	; store conflict registers
	push r18	; temp
	push r19	; temp n

	ldd r19, Y+1
	; get address of the station name's storage location
	ldi XH, high(travel_times)
	ldi XL, low(travel_times)
	; add increment for nth station name
	clr r18
	add XL, r19
	adc XH, r18

	ld r25, X

	; epilogue
	pop r19
	pop r18

	adiw Y, 1
	out SPH, YH
	out SPL, YL
	
	pop YH
	pop YL 

	ret

; pass in n as register 24
print_prompt:
	; function prologue	
	push YL	; save the current stack frame pointer
	push YH
	in YL, SPL ; get the stack frame
	in YH, SPH
	sbiw Y, 1	; reserve two bytes for local loop counter and parameter station number
	out SPL, YL
	out SPH, YH ; update the frame position

	; move actual parameters to formal parameters
	std Y+1, r24
	
	; store conflict registers
	push r18	; i
	push r19	; n *10
	push r20	; temp n

	; makes r19 hold 10xr20
	ldd r20, Y+1 
	lsl r20
	mov r19, r20
	lsl r20
	lsl r20
	add r19, r20

	; get address of the station name's storage location
	ldi XH, high(station_names)
	ldi XL, low(station_names)
	; add increment for nth station name
	add XL, r19
	adc XH, r20

	ldi r16, 'A'
	st X+, r16
	inc r16
	st X+, r16

	; epilogue
	pop r20
	pop r19
	pop r18

	adiw Y, 1
	out SPH, YH
	out SPL, YL
	
	pop YH
	pop YL 

	ret

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

pause:
	rcall debounce
	rcall debounce
	rcall debounce
	rcall debounce
	rcall debounce
	rcall debounce
	rcall debounce
	rcall debounce
	rcall debounce
	rcall debounce
	ret

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
	rjmp number_to_letter

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