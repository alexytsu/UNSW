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

 initialise_motor:
	start_motor
	