;
; monorail.asm
;
; Created: 22/10/2018 4:10:50 PM
; Author : Alex
;

.include "m2560def.inc"

; ==== macros ====


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


.CSEG
.org 0x0000
rjmp SETUP

.include "Config.asm"
.include "Display.asm"
.include "kpdInput.asm"
.include "StnEntry.asm"
.include "MonoEntry.asm"
.include "Emulator.asm"

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
	/*call get_num
	mov disp, temp
	subi disp, -'0'
	do_lcd_data

	rcall get_char
	mov disp, temp
	do_lcd_data

	ldi disp, 'X'
	do_lcd_data
	*/
	ldi ZH, 2*high(num_Stations)
	ldi ZL, 2*low(num_Stations)
	ldi r24, 25
	rcall print_Instruction

	ldi disp, 'B'
	do_lcd_data


	ldi r24, 1
	rcall save_station_name
	rcall save_station_time
	ldi r24, 3
	rcall save_station_name
	rcall save_station_time

; code that should loop
main:


	rjmp main


