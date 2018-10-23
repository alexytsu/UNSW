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

.macro do_lcd_data
	rcall lcd_data
	rcall lcd_wait
.endmacro

; ==== aliases ====
; for displaying
.def disp=r16

; temporary registers
.def temp=r17
.def temp1=r18
.def temp2=r19

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
station_prompt: .db "Enter name for station:"
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
	

	; test subroutines
	rcall get_number_of_stations
	ldi r24, 1
	rcall save_station_name
	rcall save_station_time
	ldi r24, 3
	rcall save_station_name
	rcall save_station_time

; code that should loop
main:


	rjmp main

; gets from the user the number of stations and saves it to the relevant section in memory
get_number_of_stations:
	; function prologue
	ldi XH, high(n_stations)
	ldi XL, low(n_stations)

	ldi temp, 3
	st X, temp

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
	ldi r16, 5
	st X+, r16

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