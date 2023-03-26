Assignment:
Need to start UART3 with following settings: baud rate 115200, 8bit, no parity, 1 stop bit.
Need to control all 4 LED states with help of the PC keyboard. Keyboard button toggles LED state (via console). Current LED state printed to the console.
Need to control all 4 LED states with help of buttons SWT1, SWT3, SWT4, SWT5 (on the GL board) – toggle mode. Current LED state printed to the console.
One time per 5 seconds, actual temperature (external analog sensor at GL board) value should be printed at console (Celsius degrees).

Solution:
SW1: toggles BLUE LED
SW3: toggles ORANGE LED
SW4: toggles RED LED
SW5: toggles GREEN LED
For toggle with keyboard you should use: R, G, B, O, r, g, b, o.
Handling of actual temperature is like the one in previous task (Training04).