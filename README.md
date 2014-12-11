ECE382_Lab7
===========

Lab 7: ADC Robot Sensing

C2C Jasper Arneberg  
T5 ECE 382  
Capt Trimble  

##Introduction
In this lab, we built upon the functionality developed in Lab 6. In order to autonomously control our robot, we need to implement sensors. For this lab, we use infrared (IR) LEDs to put out a beam of IR light, and then infrared sensors receive this light and give a voltage signal. This signal is then converted into a hexadecimal number using an analog-to-digital converter (ADC).

##Prelab
The functionality of the IR sensors were verified with a DMM. The IR LEDs were powered with 3.3 V, eliminating the possibility of providing too high of a voltage to the MSP430, which operates at 3.3 V.

####Approximate Characterization of IR Sensors
|         | Left | Center | Right |
|---------|------|--------|-------|
| Min (V) | 0.38 | 0.68   | 0.19  |
| Max (V) | 1.16 | 2.57   | 2.28  |

Next a schematic was developed showing changes from the last lab. Three pins of the MSP430 need to be inputs for the three IR sensors. These pins are P1.2, P1.3, and P1.4. These pins all have the ability to perform analog-to-digital conversion.

####Updated Schematic
![alt text](https://github.com/JasperArneberg/ECE382_Lab7/blob/master/schematic.png?raw=true "Schematic")

####Important Registers
ADC10CTL0: Control Register 0, used to select references (SREFx), sample-and-hold times (ADC10SHTx), can enable interrupts (ADC10IE)  
ADC10CTL1: Control Register 1, used to select input channel (INCHx), ADC10BUSY tells user conversion is still happening  
P1DIR: set BIT0 as output for red LED  
P1OUT: use to set or clear BIT0, the red LED  

####Software Overview
The ADC can create interrupts, but this creates unnecessary confusion in the coding. It is much easier to simply wait for the conversion to finish, and then move on in the code rather than using interrupts. An approach similar to the one on Dr. Coulston's website will be used.  

The signals from all three IR sensors will be decoded sequentially one after the other. This will allow the voltages of each sensor to have an effect on the decision processes of the robot.

##Required Functionality
In order to implement required functionality, signals from all three IR sensors were decoded sequentially. These voltages were then compared to threshold values. If the threshold value for any sensor was exceeded, LEDs were turned on. The right sensor lit up the red LED, the left sensor lit up the green LED, and the center sensor lit up both LEDs. When no wall was present, both LEDs were turned off.

The LEDs were lit by setting specific bits on port 1 to high or low. The red LED is tied to pin 0, and the green LED is tied to pin 6. In order to allow this functionality, pins 0 and 6 were not used for ADC.

It is important to note that the opearting voltage of the IR sensors was changed to 5 V. This change was made in an attempt to be able to operate correctly at a higher level of noise. 

##B Functionality
For B functionality, a standalone library for the ADC was created and released on github. Although this library was not actually used in the Lab 7 code, it was used heavily in the Lab 8 code. The library and an example of its usage can be found at the following address:

[https://github.com/JasperArneberg/ADC10_Library](https://github.com/JasperArneberg/ADC10_Library)


##A Functionality
For A functionality, all three IR sensors were fully characterized. The robot was placed a certain distance from the wall at a certain orientation, and then the ADC value of the signal was recorded. This hexadecimal value was then converted to decimal so that it could be graphed. This value was then converted to the original voltage by dividing by 1023 and multiplying by 3.3 V.

![alt text](https://github.com/JasperArneberg/ECE382_Lab7/blob/master/characterization.png?raw=true "IR Sensor Characterization")

The left and right sensors appear to follow an exponential curve, which makes sense for light reflection. The center sensor, however, does not drop off quickly at all. This is because the max value that the MSP430 ADC can interpret is 3.3 V, its operating voltage. The voltage of the center sensor was above 3.3 V, making for a slightly skewed graph. For the purposes of Lab 8, however, it should work just fine.

It is also important to note that once the robot is more than 6 inches away from a wall, there is a very negligible difference in the IR signal. This means that the IR sensors are only useful in short distance applications.

##Debugging
When initially testing Dr. Coulston's code, the LEDs would stay lit even when there was not an object in close range. This error was only fixed when the computer USB cord was removed. The reason for this was probably noise from the USB connection.

This code did not work as planned:
```
		if (leftSignal > LEFT_WALL) {							// Compare left IR sensor to threshold
			P1OUT |= BIT6;										      // Green LED on
			P1OUT &= ~BIT0;	      									// Red LED off
		} 
		else if (centerSignal > CENTER_WALL) {		// Compare center IR sensor to threshold
			P1OUT |= BIT0;									    	  // Red LED on
			P1OUT |= BIT6;									      	// Green LED on
		} 
		else if (rightSignal > RIGHT_WALL) {			// Compare right IR sensor to threshold
			P1OUT |= BIT0;										      // Red LED on
			P1OUT &= ~BIT6;									      	// Green LED off
		} 
```

The problem with this code is that it did not work when there were no walls in proximity. The LEDs stayed in the same state even when no walls were present. This code was fixed by adding the following line:
```
else {
			P1OUT &= ~BIT0;									      	// Red LED off
			P1OUT &= ~BIT6;										      // Green LED off
		}
```

##Conclusion
The purpose of this laboratory exercise was to prepare for the final project, Lab 8. Now that the sensor can detect if a wall is present, it can use this knowledge to navigate the maze. The next step will be to incorporate the robot motion of Lab 6 with the wall detection ability utilized in Lab 7.

##Documentation
I used http://www.tablesgenerator.com/markdown_tables to generate markdown tables efficiently.  


