ECE382_Lab7
===========

Lab 7: ADC Robot Sensing

C2C Jasper Arneberg  
T5 ECE 382  
Capt Trimble  

##Introduction
In this lab, we built upon the functionality developed in Lab 6. In order to autonomously control our robot, we need to implement sensors. For this lab, we use infrared (IR) LEDs to put out a beam of IR light, and then infrared sensors receive this light and give a voltage signal. This signal is then converted into a binary number using an analog-to-digital converter (ADC).

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

##Debugging
When initially testing Dr. Coulston's code, the LEDs would stay lit even when there was not an object in close range. This error was only fixed when the computer USB cord was removed. This 

##Conclusion

##Documentation
I used http://www.tablesgenerator.com/markdown_tables to generate markdown tables efficiently.  


