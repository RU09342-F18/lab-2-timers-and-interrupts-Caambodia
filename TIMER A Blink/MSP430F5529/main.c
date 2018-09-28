// Created: 9/26/18
// Last Edited: 9/28/18
// Author: Cameron Bendzynski

#include <msp430.h> 

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;           // stop watchdog timer
    UCSCTL4 = SELA_1;                   // ACLK (10kHz)

    P1DIR |= BIT0;                      // Set P1.0 to output
    P4DIR |= BIT7;                      // Set P4.7 to output

    TA0CTL = TASSEL_1 + MC_1;           // Set Timer A0 in Up Mode
    TA1CTL = TASSEL_1 + MC_1;           // Set Timer A1 in Up Mode
    TA0CCTL0 = CCIE;                    // Capture/Compare enable
    TA1CCTL0 = CCIE;                    // Capture/Compare enable
    TA0CCR0 = freqToPeriod(5);          // 5 Hz
    TA1CCR0 = freqToPeriod(3);          // 3 Hz

    __bis_SR_register(GIE);             // Global Interrupt Enable
    while(1);                           // Continuously runs program
}

int freqToPeriod(int freq)              // Function for frequency to period conversion
{
    int period = 5000 / freq;           // Turns a given frequency into the proper period

    return period;                      // Returns period
}

#pragma vector = TIMER0_A0_VECTOR       // Detects interrupt on Timer0
__interrupt void Timer_A0(void)
{
    P1OUT ^= BIT0;                      // Toggle the LED on P1.0
}

#pragma vector = TIMER1_A0_VECTOR       // Detects interrupt on Timer1
__interrupt void Timer_A1(void)
{
    P4OUT ^= BIT7;                      // Toggle the LED on P4.7
}
