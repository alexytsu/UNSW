/*
 * StnEntry.asm
 *
 *  Created: 23/10/2018 3:08:19 PM
 *   Author: rowra
 */ 


 .cseg

 .org 0x100
num_Stations: .db "Enter max number of stations:"
station_prompt: .db "Enter name for station "