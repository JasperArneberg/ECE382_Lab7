/*******************************************
  * Title: Lab 7: ADC - Robot Sensing
  * Author: C2C Jasper Arneberg
  * Created: 4 December 2014
  * Description: This program was developed from Dr. Coulston's code. It measures
  * the voltage coming from three IR sensors on a robot by converting these values
  * to a hexidecimal number using the ADC on the MSP430. When the voltages are above
  * a threshold value, one or both of the LEDs on the launchpad board light up.
*******************************************/

#include "msp430g2553.h"

#define LEFT_WALL 0x200
#define CENTER_WALL 0x300										//needs to be higher for center sensor
#define RIGHT_WALL 0x200

void initMSP430();

//----------------------------------------------------------------------
//----------------------------------------------------------------------
int main(void) {

	unsigned short leftSignal;									// used for converted signal
	unsigned short centerSignal;
	unsigned short rightSignal;


	IFG1=0; 													// clear interrupt flag1
	WDTCTL = WDTPW + WDTHOLD;									// disable WDT

	BCSCTL1 = CALBC1_8MHZ;										// 8MHz clock
	DCOCTL = CALDCO_8MHZ;

	P1DIR |= BIT0 | BIT6;										// Set the red LED and green LED as output

	while(1) {

		// Configure P1.2 to be the ADC input for Left Sensor
		ADC10CTL0 = 0;											// Turn off ADC subsystem
		ADC10CTL1 = INCH_2 | ADC10DIV_3 ;						// Channel 2, ADC10CLK/4
		ADC10AE0 = BIT2;		 								// Make P1.2 analog input
		ADC10CTL0 = SREF_0 | ADC10SHT_3 | ADC10ON | ENC;		// Vcc & Vss as reference

		ADC10CTL0 |= ADC10SC;									// Start a conversion
		while(ADC10CTL1 & ADC10BUSY);							// Wait for conversion to complete
		leftSignal = ADC10MEM;									// collect that 10-bit value

		// Configure P1.3 to be the ADC input for Center Sensor
		ADC10CTL0 = 0;											// Turn off ADC subsystem
		ADC10CTL1 = INCH_3 | ADC10DIV_3 ;						// Channel 3, ADC10CLK/4
		ADC10AE0 = BIT3;		 								// Make P1.3 analog input
		ADC10CTL0 = SREF_0 | ADC10SHT_3 | ADC10ON | ENC;		// Vcc & Vss as reference

		ADC10CTL0 |= ADC10SC;									// Start a conversion
		while(ADC10CTL1 & ADC10BUSY);							// Wait for conversion to complete
		centerSignal = ADC10MEM;									// collect that 10-bit value

		// Configure P1.4 to be the ADC input for Right Sensor
		ADC10CTL0 = 0;											// Turn off ADC subsystem
		ADC10CTL1 = INCH_4 | ADC10DIV_3 ;						// Channel 4, ADC10CLK/4
		ADC10AE0 = BIT4;		 								// Make P1.4 analog input
		ADC10CTL0 = SREF_0 | ADC10SHT_3 | ADC10ON | ENC;		// Vcc & Vss as reference

		ADC10CTL0 |= ADC10SC;									// Start a conversion
		while(ADC10CTL1 & ADC10BUSY);							// Wait for conversion to complete
		rightSignal = ADC10MEM;									// collect that 10-bit value

		if (leftSignal > LEFT_WALL) {							// Compare left IR sensor to threshold
			P1OUT |= BIT6;										// Green LED on
			P1OUT &= ~BIT0;										// Red LED off
		}
		else if (centerSignal > CENTER_WALL) {					// Compare center IR sensor to threshold
			P1OUT |= BIT0;										// Red LED on
			P1OUT |= BIT6;										// Green LED on
		}
		else if (rightSignal > RIGHT_WALL) {					// Compare right IR sensor to threshold
			P1OUT |= BIT0;										// Red LED on
			P1OUT &= ~BIT6;										// Green LED off
		}
		else {
			P1OUT &= ~BIT0;										// Red LED off
			P1OUT &= ~BIT6;										// Green LED off
		}

	} // end infinite loop

} // end main

