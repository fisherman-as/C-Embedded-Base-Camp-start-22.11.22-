Assignment:
Need to implement custom scheme for LED blinking on the board “X-Mas Lights”.
All 4 LEDs need to be used.
LEDs should blink constantly (round cycle).
Project needs to be stored with your own repository on the GitHub.

Solving:
Implemented the scheme "Round blinking".
I created the structure for each LED with PWM parameters. It allowed me to handle each LED independently of each other.
For each LED we can change the period, the duty cycle and the startpoint (the offset from zero). Also, each structure contains the pointer to the function that handles the corresponding LED.
The result is in Training01.sai
