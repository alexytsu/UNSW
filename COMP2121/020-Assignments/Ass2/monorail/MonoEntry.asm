/*
 * MonoEntry.asm
 *
 *  Created: 23/10/2018 3:06:29 PM
 *   Author: rowra
 */ 

 .cseg

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
