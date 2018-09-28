## Overview:
The main.c files function to turn an LED on and off whenever the internal clock has reached a certain set point. This point is then able to be changed according to how long a button is pressed down for.

## Description of Code:
The line `P1DIR |= 0x01` sets the pin P1.0 as an output. This is the pin on both boards used where the LED is located, and so we set it as an output so we can control it with the rest of our code. By ORing `P1DIR` with `0x01` or `00000001`, we set the least significant bit in `P1DIR` to 1, which makes it an output. The 0s allow us to avoid disturbing the rest of the bits in `P1DIR`.

Instead of using the line `P1DIR &= ~BIT3` to set the button as an input, we use the line `P1IE |= BIT3` to enable the button to send interrupts that we can read instead of constantly checking if the button is pressed (P1.1 is used for the button on the MSP430F5529). This line is followed up with `P1IES |= BIT3` to set the interrupt to trigger on the falling edge of the button, which is when the button is pressed. We still have to enable the pull-up resistor for the button, and preemptively clear the interrupt flag on P1.3 with `P1IFG &= ~BIT3`. 

Instead of incrementing a counter until a certain limit, we can use the internal clocks of the boards to count for us. We use the line `TA0CTL = TASSEL_1 + MC_1` to set up a timer for the LED, and set it to Up Mode. We also enable Capture/Compare on the timer, and set the frequency of P1.0 to 3Hz. We then enable Global Interrupt with the line `__bis_SR_register(GIE)` and set it to run continuously with as simple `while(1)` loop.

Our freqToPeriod function simply takes an input frequency and divides the clock to hit that frequency.

The final portion of the code looks for an interrupt, but doesn't consume much power while doing so like a while loop would. When an interrupt is detected on Timer0, the LED is toggled and the function continues to look for the next interrupt.

The program also looks for the button press interrupt on Port 1. When it receives an interrupt, it first checks if the button has been pressed or released. This is done by checking which edge it was set to detect (rising or falling), and changing the function to detect the other edge. After doing this, if the button was pressed, the timer is cleared and set to continuous mode, then allowed to count forward. Once the button is released, the function stops the timer, sets the current count on the timer to the duty cycle of the timer (TA0CCR0), sets the timer to Up Mode, clears the timer, and lets the program continue as normal. The interrupt flag is also cleared, regardless if the button was pressed or released.
