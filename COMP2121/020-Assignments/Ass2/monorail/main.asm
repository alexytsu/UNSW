;
; monorail.asm
;
; Created: 22/10/2018 4:10:50 PM
; Author : Alex
;

.include "m2560def.inc"

; ==== macros ====

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

; timer handling
.def time = r18
.def flags = r1

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
stop_time: .byte 1
lcd_position: .byte 1


.equ estop_mask = 0b00000001
.equ next_stop_mask = 0b00000010
.equ at_station_mask = 0b00000100

; logic controlling monorail operation
status_current_time: .byte 1
status_next_station_time: .byte 1 ; time for stopping at next station

.CSEG
.org 0x0000
rjmp SETUP
<<<<<<< HEAD
.org INT0ADDR
rjmp pushbutton1
.org INT1ADDR
=======
.org INT0addr
rjmp pushbutton1
.org INT1addr
>>>>>>> b26b3801267384ad55e1e762afa8be676e787484
rjmp pushbutton2

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

	; Motor PWM on PortE
	ldi temp, (1<<4)
	out DDRE, temp
	clr temp
	sts OCR3BH, temp
	ldi temp, (1 << CS30)
	sts TCCR3B, temp
	ldi temp, (1 << WGM30)|(1 << WGM32)|(1<<COM3B1)
	sts TCCR3A, temp

	; Enable interrupts on the pushbuttons
	ldi temp, (2 << ISC10) | (2 << ISC00) ; The built-in constants ISC10=2 and ISC00=0 are
	sts EICRA, temp ; temp=0b00001010, so both interrupts are configured as falling edge
	in temp, EIMSK
	ori temp, (1<<INT0) | (1<<INT1) ; INT0=0 & INT1=1
	out EIMSK, temp ; Enable External Interrupts 0 and 1
	sei

	; ==== reset hardware ====
	; reset the screen
	do_lcd_command 0b00111000 ; 2x5x7
	rcall sleep_5ms
	do_lcd_command 0b00111000 ; 2x5x7
	rcall sleep_1ms
	do_lcd_command 0b00111000 ; 2x5x7
	do_lcd_command 0b00111000 ; 2x5x7
	do_lcd_command 0b00001000 ; display off?
	clear ; clear display
	do_lcd_command 0b00000110 ; increment, no display shift
	do_lcd_command 0b00001111 ; Cursor on, bar, with blink
	;do_lcd_command 0xc0
	
	rcall resetNames
	/*rcall CollectInput

	rcall get_number_of_stations
	mov disp, r25
	
	display_integer

	ldi r24, 0
	get_all_names:	

	rcall prompt_name
	rcall save_station_name
	rcall pause

	rcall prompt_time
	rcall save_station_time
	
	inc r24
	cp r24, r25
	brne get_all_names

	*/


; code that should loop
main:
	;out PORTC, flags
	;poll_estop

/*clr r24
show_all_names:
	rcall print_station_name
	rcall pause
	rcall get_station_time
	mov disp, r25
	display_integer
	rcall pause
	inc r24
	rcall get_number_of_stations
	mov temp, r25
	cp r24, temp
	brne show_all_names*/
	



	rjmp main

