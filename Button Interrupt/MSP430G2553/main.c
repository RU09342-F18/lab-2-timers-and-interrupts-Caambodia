// Created: 9/26/18
// Last Edited: 9/28/18
// Author: Cameron Bendzynski

#include <msp430.h> 

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    P1DIR |= BIT0;              // Set P1.0 to output

    P1IE  |= BIT3;              // P1.3 Interrupt enabled
    P1IES |= BIT3;              // P1.3 Falling Edge

    P1REN |= BIT3;              // P1.3 pull-up resistor enabled
    P1IFG &= ~BIT3;             // P1.3 Interrupt Flag cleared

    __bis_SR_register(GIE);     // Global Interrupt Enable
    while(1);                   // continuously runs program
}

#pragma vector = PORT1_VECTOR   // Detect interrupt on Port 1
__interrupt void Port_1(void)
{
    P1OUT ^= BIT0;              // Toggle the LED on P1.0
    P1IFG &= ~BIT3;             // P1.3 Interrupt Flag cleared
}
