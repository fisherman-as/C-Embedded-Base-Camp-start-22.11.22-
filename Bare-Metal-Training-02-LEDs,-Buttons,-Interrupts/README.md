Assignment:
Need to implement at least 3 blinking schemes for all 4 LEDs on the board.
2 buttons would be used to select scheme (next one, previous one).
2 buttons would be used to select blinking speed (speed up, slow down).
Button at the middle of cross should be used to turn on/off blinking.
All buttons need to be processed by interrupts.

Solution:
There were implemented 3 different blinking schemes.
Each LED has its own structure which contains LED and PWM parameters. For each LED we can change the period, the duty cycle and the startpoint (the offset from zero). Also, each structure contains the pointer to the function that handles the corresponding LED.
SW1: decreases blinking speed
SW2: turns on/off blinking
SW3: increases blinking speed
SW4: calls the next blinking scheme
SW5: calls the previous blinking scheme

The oscillogram is in Training02.sai