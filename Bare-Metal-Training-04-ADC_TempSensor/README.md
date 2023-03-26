Assignment:
Need to read voltage from potentiometer (connect it to IN3 channel). Show voltage with help of BLUE led (light intensity change). Too high voltage needs to be indicated with RED led.
Need to read temperature from internal temperature sensor (inside STM32F407). Show temperature with help of ORANGE led (light intensity change). Too high temperature needs to be indicated with RED led.
Need to read temperature from external analog temperature sensor (present at GL board). Show temperature with help of GREEN led (light intensity change). Too high temperature needs to be indicated with RED led.
RED led should be turned off if there is no “emergency situation” presented (see p.1,2,3 “too high cases”). It should blink with 1Hz frequency if we have “one emergency situation”, it should blink with 2.5Hz frequency for case when we have 2 “emergency situations” at the same time. And 5Hz – if all 3 “emergencies” presented.
Use hairdryer to get high temperature for components. Please be careful to save your health and HW equipment. Safety first!!!

Solution:
The program handles each ADC channel sequentially one time per 100ms, then handles the result of ADS measuring, counts frequency and duty cycle and puts them to the structure which contains PWM settings.
Program does it for each ADC channel (also for corresponding PWM channel) and for PWM channel that manages Red LED blinking.
1. There aren't any perticularities for handling voltage. Red LED will blink if the Duty Cycle of the corresponding PWM channel >60%.
2. 	We have such parameters for internal temperature sensor:
//	(+0.0025V per 1C) or (+0.025V per 10C); Vref=3.3V, I did check it!!! Not 1.21V.
	//  0.71V -> 5C
	//	0.76V -> 25C
	//  0.86V -> 65C (25+40)
	//  0.885V -> 75C - it will be the threshold for red blinking
	//  0.96V -> 105C
	// So, we can imagine that voltage will be changed from 0.71V (880) to 0.96V (1200) in general(5C - 105C)
	// However, for the best result presenting, let's indicate  the range from ~25C to 105C only
	// Therefore, the ADC will give us the values from 1050 to 1200, threshold is ~1100
	// So, the DutyCycle will be 0% at temp=1050 and 100% at temp=1200
	// So, the formula is following: DutyCycle = (2*temp/3 - 700)
Red LED will blink if the Duty Cycle >33%.
3. There aren't any perticularities for handling voltage. Red LED will blink if the Duty Cycle of the corresponding PWM channel <30%.

The oscillogram is in Training04.sai

