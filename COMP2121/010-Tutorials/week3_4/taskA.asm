;
; week3_4.asm
;
; Created: 6/08/2018 3:12:12 PM
; Author : Alex
;

; Replace with your application code
.include "m2560def.inc"
start:

	ldi XL, low(4135)
	ldi XH, high(4135)

	ldi YL, low(45110)
	ldi YH, high(45110)
	
	; while a!=b
start_while:
	cp XH, YH
	breq check_low // if high equal check low registers	
	rjmp check_avsb // otherwise check if a < b
check_low:
	cp XL, YL
	breq end_while
check_avsb:
	; if (a<b)
	brlo case_b_less_a
case_a_less_b:
	sub XL, YL
	sbc XH, YH
	rjmp start_while
case_b_less_a:
	sub YL, XL
	sbc YH, XH
	rjmp start_while
end_while:

halt:
	rjmp halt