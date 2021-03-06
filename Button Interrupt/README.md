## Overview:
The main.c files function to turn an LED on and off whenever the button is pressed, utilizing interrupts instead of polling.

## Description of Code:
The line `P1DIR |= 0x01` sets the pin P1.0 as an output. This is the pin on both boards used where the LED is located, and so we set it as an output so we can control it with the rest of our code. By ORing `P1DIR` with `0x01` or `00000001`, we set the least significant bit in `P1DIR` to 1, which makes it an output. The 0s allow us to avoid disturbing the rest of the bits in `P1DIR`.

Instead of using the line `P1DIR &= ~BIT3` to set the button as an input, we use the line `P1IE |= BIT3` to enable the button to send interrupts that we can read instead of constantly checking if the button is pressed (P1.1 is used for the button on the MSP430F5529). This line is followed up with `P1IES |= BIT3` to set the interrupt to trigger on the falling edge of the button, which is when the button is pressed. We still have to enable the pull-up resistor for the button, and preemptively clear the interrupt flag on P1.3 with `P1IFG &= ~BIT3`. We then enable Global Interrupt with the line `__bis_SR_register(GIE)` and set it to run continuously with as simple `while(1)` loop.

The final portion of the code looks for an interrupt, but doesn't consume much power while doing so like a while loop would. When an interrupt is detected on Port 1, meaning that the button has been pressed, the output will be toggled, changing and LED that has been on to off and vice versa, and the interrupt flag is yet again cleared. This will run indefinitely.

No input is needed for this code. It will run on its own without any interference.
