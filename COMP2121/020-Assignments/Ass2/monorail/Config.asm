/*
 * AsmFile1.asm
 *
 *  Created: 23/10/2018 3:04:30 PM
 *   Author: rowra
 */ 

 .cseg
num_Stations: .db "Enter number of stations: "
station_prompt: .db "Enter name "
time_prompt: .db "t(s) from "
time_prompta: .db "Time from Station "
time_promptb: .db " to Station "
stop_time: .db "The stop time for all station:"
configuration_complete: .db "Configuration Complete. Initialising system ... "
incorrect: .db "Incorrect! "
numSerror: .db "Station count is 10"
timeSerror: .db "Time incorrect"

resetNames:
	ldi temp, ' '
	ldi temp2, 100
	ldi XH, high(station_names)
	ldi XL, low(station_names)

clearnames:
	st X+, temp
	dec temp2
	brne clearnames

	ret