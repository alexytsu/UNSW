/*
 * AsmFile1.asm
 *
 *  Created: 23/10/2018 3:09:27 PM
 *   Author: rowra
 */ 

 ; LCD CODE -----------------

.equ LCD_RS = 7
.equ LCD_E = 6
.equ LCD_RW = 5
.equ LCD_BE = 4

; macros for lcd
.macro do_lcd_command
	ldi r16, @0
	rcall lcd_command
	rcall lcd_wait
.endmacro

.macro clear
	do_lcd_command 0x01
.endmacro

.macro do_lcd_data
	rcall lcd_data
	rcall lcd_wait
.endmacro
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
	ret


 ; pass in n (number of characters to print) as register 24
 ; pass in cseg location with ZL and ZH
 print_Instruction:
	; function prologue	
	push YL	; save the current stack frame pointer
	push YH
	in YL, SPL ; get the stack frame
	in YH, SPH
	sbiw Y, 1	; reserve two bytes for local loop counter and parameter station number
	out SPL, YL
	out SPH, YH ; update the frame position

	; store conflict registers
	push r18	; i
	push r19	; n 
	push r20

	clr r18
	mov r19, r24
	;do_lcd_command 0xc0
	;Loop from 0 to n-1 printing each character as it goes
	displayLoop:
	inc r18
	subi r19, 1
	cpi r18, 17
	out PORTC, r18
	brlt skipLineChange
	do_lcd_command 0b11000000
	ldi r18, 1
skipLineChange:
	lpm r16, Z+
	do_lcd_data
	cpi r19, 1
	brne displayLoop

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

; prompt for nth out of m total stations
; n in r24, m in r25
prompt_name:
	
	push YL
	push YH
	in YL, SPL
	in YH, SPH
	
	sbiw Y, 2 ; reserve two bytes for input parameters

	out SPL, YL
	out SPH, YH ; update the frame to the local frame

	; move actual parameters to formal parameters
	std Y+1, r24 ; n
	std Y+2, r25 ; m

	; store conflict registers
	push r24
	push r25

	clear
	ldi ZH, high(station_prompt<<1)
	ldi ZL, low(station_prompt<<1)
	ldi r24, 12
	rcall print_Instruction
	
	; show the user which station they are entering a name for
	ldd disp, Y+1
	subi disp, -1
	display_integer
	ldi disp, '/'
	display
	ldd disp, Y+2
	display_integer
	ldi disp, ':'
	display
	
	do_lcd_command 0b11000000
	

	; epilogue
	
	; restore conflict registers
	pop r25
	pop r24

	; restore stack frame 
	adiw Y, 2
	out SPH, YH
	out SPL, YL

	; restore y pointer
	pop YH
	pop YL

	ret

; prompt for nth out of m total stations
; n in r24, m in r25
prompt_time:
	
	push YL
	push YH
	in YL, SPL
	in YH, SPH
	
	sbiw Y, 2 ; reserve two bytes for input parameters

	out SPL, YL
	out SPH, YH ; update the frame to the local frame

	; move actual parameters to formal parameters
	std Y+1, r24 ; n
	std Y+2, r25 ; m

	; store conflict registers
	push r23
	push r24
	push r25

	clear
	ldi ZH, high(time_prompt<<1)
	ldi ZL, low(time_prompt<<1)
	ldi r24, 11
	rcall print_Instruction
	
	ldd r23, Y+2
	inc r23

	; show the user which station they are entering a name for
	ldd disp, Y+1
	subi disp, -1
	display_integer
	ldi disp, '-'
	display
	ldd disp, Y+1
	subi disp, -1

	cp disp, r23 ; last station? wrap around to beginning
	breq dont_wrap_station
	ldi disp, 1 ; wrwap station
	dont_wrap_station:
	display_integer
	ldi disp, ':'
	display
	
	do_lcd_command 0b11000000
	

	; epilogue
	
	; restore conflict registers
	pop r25
	pop r24
	pop r23

	; restore stack frame 
	adiw Y, 2
	out SPH, YH
	out SPL, YL

	; restore y pointer
	pop YH
	pop YL

	ret