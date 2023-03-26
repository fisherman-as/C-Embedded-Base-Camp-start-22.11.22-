Assignment:
Need to implement PWM signal generator.
Timer4 need to be used (this is mandatory).
STM32F407 need to be switched for external clock (HSE).
2 buttons would be used to set signal frequency (up and down; +/- 5 kHz step).
2 buttons would be used to set duty cycle (+/- 5% step each button press).
Middle button would be used to select signal output (PD15, PD14, PD13, PD12 or no output (disable case)). Cyclic selection scheme.

Solution:
There were implemented a structure which contains PWM parameters - channel, frequency and duty cycle.
SW1: this button decreases a frequency
SW2: this button selects the signal output
SW3: this button increases a frequency
SW4: this button increases the duty cycle
SW5: this button decreases the duty cycle
The frequency is being changed from 0KHz (PWM off) to 100KHz with the step of 5KHz.
The Duty Cycle is being changed from 0% (PWM off) to 100%.
One time per millisecond (each SysTick) program watches the state of each button. If the button is pressed, program watches its state during ~100 ms (anti-jitter), and then changes the variable <Button> to corresponding state. After that the function <HandlePWM> reads this variable and calls corresponding handler for the pressed button.

The oscillogram is in Training03.sai