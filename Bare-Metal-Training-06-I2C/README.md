Assignment:
Need to create library that will work with PWM LED controller (PCA9685).
We need a way to enable/disable all outputs, set duty cycle, set PWM frequency, enable/disable sleep mode.
LED controller functionality should be moved to separate *.c file.
All public function prototypes (API) should be provided by *.h file.
I2C1 channel should be used to communicate with LED controller. SCK = 50 kHz.
Functional testing should be made with help of PC (UART console) – send commands / receive status.
[OPTIONAL *]. Connect 16 LEDs to PWM outputs to control light intensity.

Solution:
The following commands you have to use in console to handle LEDs through the PCA9685:

/*-----------------------------------------The description of User API------------------------------------------------*/
/*
ENBL NN  		//NN=00...15 (turn ON single LED) OR 16 (Enables all LEDs, but keeps their state (On or OFF when enabled)!!)
DSBL NN  		//NN=00...15 (turn OFF single LED) OR 16 (Disables all LEDs, but keeps their state (On or OFF when enabled)!!)
FR NNNN  		//NNNN=0024...1526, sets Frequency
DTCL NN  		//NN=00...99, sets the Duty Cycle, the real value will be 1...100, in percents; brightness inverted
SLEEP N			//N=0 (SLEEP Mode OFF) or 1 (SLEEP Mode ON)
*/
/*--------------------------------------------------The end-----------------------------------------------------------*/
