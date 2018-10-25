/*
 * MonoEntry.asm
 *
 *  Created: 23/10/2018 3:06:29 PM
 *   Author: rowra
 */ 
; gets from the user the number of stations and saves it to the relevant section in memory
set_stop_time:
	; function prologue
	ldi XH, high(stop_time)
	ldi XL, low(stop_time)
	push r20
	push r19
	push r18
	push temp

	call get_num
	mov disp, temp
	display_integer
	
	rcall debounce
	cpi temp, 1
	brne storeStoptime

	rcall pause
	mov temp2, temp

	call get_num
	rcall debounce
	rcall debounce
	cpi temp, 0xf
	breq storeStoptime
	
	cpi temp, 0
	breq digits5

	ldi temp, 10
	do_lcd_command 0x01
	ldi ZH, 2*high(incorrect)
	ldi ZL, 2*low(incorrect)
	ldi r24, 11
	rcall print_Instruction
	ldi ZH, 2*high(numSerror)
	ldi ZL, 2*low(numSerror)
	ldi r24, 19
	rcall print_Instruction

	rjmp storeStoptime

	digits5:
		ldi disp, 0
		display_integer
		ldi temp, 10

	storeStoptime:
		st X, temp

		pop temp
		pop r18
		pop r19
		pop r20

		ret

; places the number of stations in r25
get_stop_time:
	ldi ZH, high(stop_time)
	ldi ZL, low(stop_time)
	ld r25, Z
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
	push temp

	ldd r19, Y+1
	; get address of the station name's storage location
	ldi XH, high(travel_times)
	ldi XL, low(travel_times)
	; add increment for nth station name
	clr r18
	add XL, r19
	adc XH, r18

	call get_num
	mov disp, temp
	display_integer
	
	rcall debounce
	cpi temp, 1
	brne storeStnTime

	rcall pause

	call get_num
	rcall debounce
	rcall debounce
	cpi temp, 0xf
	breq storeStnTime
	
	cpi temp, 0
	breq digitsTime

	ldi temp, 10
	do_lcd_command 0x01
	ldi ZH, 2*high(incorrect)
	ldi ZL, 2*low(incorrect)
	ldi r24, 12
	rcall print_Instruction
	ldi ZH, 2*high(timeSerror)
	ldi ZL, 2*low(timeSerror)
	ldi r24, 19
	rcall print_Instruction

	rjmp storeStoptime

digitsTime:
	ldi temp, 10

storeStnTime:
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
