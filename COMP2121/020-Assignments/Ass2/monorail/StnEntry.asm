/*
 * StnEntry.asm
 *
 *  Created: 23/10/2018 3:08:19 PM
 *   Author: rowra
 */ 


 .cseg


; gets from the user the number of stations and saves it to the relevant section in memory
get_number_of_stations:
	; function prologue
	ldi XH, high(n_stations)
	ldi XL, low(n_stations)

	ldi disp, 'A'
	do_lcd_data

	call get_num
	st X, temp

	ld disp, X
	subi disp, -'0'
	
	do_lcd_data

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

