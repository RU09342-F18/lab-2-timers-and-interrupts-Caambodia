// Created: 9/26/18
// Last Edited: 9/28/18
// Author: Cameron Bendzynski

#include <msp430.h> 

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;                       // stop watchdog timer
    UCSCTL4 = SELA_1;                               // ACLK (10kHz)

    P1DIR |= BIT0;                                  // Set P1.0 to output - LED
    P1REN |= BIT1;                                  // Enable resistor on P1.1
    P1OUT |= BIT1;                                  // Set resistor to pull-up

    P1IE |= BIT1;                                   // P1.1 Interrupt enabled
    P1IES |= BIT1;                                  // P1.1 Falling edge selected
    P1IFG &= ~BIT1;                                 // P1.1 Interrupt Flag cleared

    TA0CTL = TASSEL_1 + MC_1;                       // Set Timer A0 in Up Mode with divider, counter clear, and interrupt enabled
    TA0CCTL0 = CCIE;                                // Capture/Compare enable
    TA0CCR0 = freqToPeriod(3);                      // 3 Hz

    __bis_SR_register(GIE);                         // Global Interrupt Enable
    while(1);                                       // Continuously runs program
}

int freqToPeriod(int freq)                          // Function for frequency to period conversion
{
    int period = 5000 / freq;                       // Turns a given frequency into the proper period

    return period;                                  // Returns period
}

#pragma vector = TIMER0_A0_VECTOR                   // Detects interrupt on Timer0
__interrupt void Timer_A0(void)
{
    P1OUT ^= BIT0;                                  // Toggle the LED on P1.0
}

#pragma vector = PORT1_VECTOR                       // Detects interrupt on Port 1
__interrupt void Port_1(void)
{
    if (P1IES & BIT1)                               // If set to falling edge...
    {
        P1IES &= ~BIT1;                             // Set to detect rising edge
        TA0CTL = TACLR;                             // Timer cleared
        TA0CTL = TASSEL_1 + MC_2;                   // Continuous mode enabled
    }
    else
    {
        P1IES |= BIT1;                              // Set to detect falling edge
        TA0CTL = MC_0;                              // Timer stopped
        TA0CCR0 = TA0R;                             // CCR0 set to current timer value
        TA0CTL |= TACLR;                            // Timer cleared
        TA0CTL = TASSEL_1 + MC_1;                   // Up mode enabled
    }

    P1IFG &= ~BIT1;                                 // P1.1 Interrupt Flag cleared
}
