/*
 * Emulator.asm
 *
 *  Created: 23/10/2018 3:07:20 PM
 *   Author: rowra
 */ 


 .cseg

 .macro start_motor
	ldi speed, 0xf
	sts OCR3BL, speed
 .endmacro

 .macro stop_motor
	ldi speed, 0
	sts OCR3BL, speed
 .endmacro


		

 .macro poll_estop
	ldi mask, INITCOLMASK
	sts portl, mask
	ldi temp, 0xff
	delayestop:
	dec temp
	brne delayestop
	lds temp, pinl
	andi temp, ROWMASK
	cpi temp, 0xF
	breq estop_not_pressed
	ldi mask, INITROWMASK
	clr row
	mov temp2, temp
	and temp2, mask

	brne estop_not_pressed

	mov temp, flags
	ldi temp2, estop_mask
	eor temp, temp2
	mov flags, temp
	rcall debounce

	estop_not_pressed:
 .endmacro


pushbutton1:
	push temp
	in temp, SREG
	push temp

	mov temp, flags
	ori temp, next_stop_mask
	mov flags, temp
	
	pop temp
	out SREG, temp
	pop temp
	reti

pushbutton2:
	push temp
	in temp, SREG
	push temp
	
	mov temp, flags
	ori temp, next_stop_mask
	mov flags, temp
	
	pop temp
	out SREG, temp
	pop temp
	reti
