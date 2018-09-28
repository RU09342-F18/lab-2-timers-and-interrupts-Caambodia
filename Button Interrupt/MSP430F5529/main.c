// Created: 9/26/18
// Last Edited: 9/28/18
// Author: Cameron Bendzynski

#include <msp430.h> 

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    P1DIR |= BIT0;              // Set P1.0 to output

    P1IE  |= BIT1;              // P1.1 Interrupt enabled
    P1IES |= BIT1;              // P1.1 Falling Edge

    P1REN |= BIT1;              // P1.1 pull-up resistor enabled
    P1IFG &= ~BIT1;             // P1.1 Interrupt Flag cleared

    __bis_SR_register(GIE);     // Global Interrupt Enable
    while(1);                   // continuously runs program
}

#pragma vector = PORT1_VECTOR   // Detect interrupt on Port 1
__interrupt void Port_1(void)
{
    P1OUT ^= BIT0;              // Toggle the LED on P1.0
    P1IFG &= ~BIT1;             // P1.1 Interrupt Flag cleared
}
