## Overview:
The main.c files function to turn an LED on and off whenever the internal clock has reached a certain set point. Two LEDs are used here with individual blinking frequencies of appoximately 5Hz and 3Hz.

## Description of Code:
The line `P1DIR |= 0x01` sets the pin P1.0 as an output. This is the pin on both boards used where the LED is located, and so we set it as an output so we can control it with the rest of our code. By ORing `P1DIR` with `0x01` or `00000001`, we set the least significant bit in `P1DIR` to 1, which makes it an output. The 0s allow us to avoid disturbing the rest of the bits in `P1DIR`. The same is done with P1.6 on the MSP430G2553 and P4.7 on the MSP430F5529.

Instead of incrementing a counter until a certain limit, we can use the internal clocks of the boards to count for us. We use the lines `TA0CTL = TASSEL_1 + MC_1` and `TA1CTL = TASSEL_1 + MC_1` to set up a seperate timer for each LED, and set it to Up Mode. We also enable Capture/Compare on both timers, and set the frequency of P1.0 to 5Hz and P1.6/P4.7 to 3Hz. We then enable Global Interrupt with the line `__bis_SR_register(GIE)` and set it to run continuously with as simple `while(1)` loop.

Our freqToPeriod function simply takes an input frequency and divides the clock to hit that frequency.

The final portion of the code looks for an interrupt, but doesn't consume much power while doing so like a while loop would. When an interrupt is detected on either Timer0 or Timer1, the corresponding LED is toggled and the function continues to look for the next interrupt.

No input is needed for this code. It will run on its own without any interference.
