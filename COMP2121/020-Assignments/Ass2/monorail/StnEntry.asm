/*
 * StnEntry.asm
 *
 *  Created: 23/10/2018 3:08:19 PM
 *   Author: rowra
 */ 
 
; starts the main sequence for station input
CollectInput:
	;Recieves input for number of stations
	ldi ZH, 2*high(num_Stations)
	ldi ZL, 2*low(num_Stations)
	ldi r24, 26
	rcall print_Instruction

	rcall get_number_of_stations
	rcall debounce 
	rcall debounce
	
	;Recieves input for station names
	ret

; gets from the user the number of stations and saves it to the relevant section in memory
get_number_of_stations:
	; function prologue
	ldi XH, 2*high(n_stations)
	ldi XL, 2*low(n_stations)
	push r20
	push r19
	push r18
	push temp

	call get_num
	mov disp, temp
	display_integer
	
	rcall debounce
	cpi temp, 1
	brne storeNStations

	rcall pause
	mov temp2, temp

	call get_num
	rcall debounce
	rcall debounce
	cpi temp, 0xf
	breq storeNstations
	
	cpi temp, 0
	breq digits2

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

	rjmp storeNStations

digits2:
	lsl r20
	mov r19, r20
	lsl r20
	lsl r20
	add r19, r20
	mov disp, temp
	display_integer
	add temp, r19

storeNStations:
	st X, temp

	pop temp
	pop r18
	pop r19
	pop r20

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
