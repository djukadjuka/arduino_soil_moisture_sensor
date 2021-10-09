#ifndef __KEYCARD_READER_MAIN_H
#define __KEYCARD_READER_MAIN_H

#define TRUE (1)
#define FALSE (0)

#include "state_machine.h"

StateMachine state_machine;

void setup() {
	// put your setup code here, to run once:
	Serial.begin(9600);
	
	// LED configuration
	pinMode(LED_PROG_PIN, OUTPUT);

	// SETUP LCD
	// Set display type as 16 char, 2 rows
	lcd.begin(LCD_COLS, LCD_ROWS);
	// Print on first row
	lcd.setCursor(0, 0);
	lcd.clear();
	
}

void loop() {
	state_machine.UpdateResetModules();
	state_machine.Update();
}

#endif // __KEYCARD_READER_MAIN_H