#include "p24FJ64GA002.h"
#include "ADC.h"

// Can have a lst of PIN numbers and names if we are using multiple analog inputs
#define PIN 1

/******************************************************************************/

void initADC()
{

    AD1PCFGbits.PCFG0 = 0;      // Set pin 25 to analog
    AD1CON1bits.FORM = 0;       // Output formatted as an integer
    AD1CON1bits.SSRC = 0b0111;  // Auto internal clock usage
    AD1CON1bits.ASAM = 0;       // Auto start sampling
    AD1CON2bits.VCFG = 0;       // Uses system voltage for reference voltages
    AD1CON2bits.CSCNA = 0;      // Uses CH0SA bits as MUXA input, inputs only work on MUXA
    AD1CON2bits.SMPI = 0b1111;  // Interrupt at 16th sample convert sequence
    AD1CON2bits.ALTS = 0;       // Always uses MUXA input multiplexor settings
    AD1CON3bits.ADRC = 0;       // Uses system clock for conversions
    AD1CON3bits.SAMC = 1;       // 1 = use TAD
    AD1CON3bits.ADCS = 10;      // Clock period select bits = 10 so *FCY
    AD1CHS = 0;                 // Connect pin as positive input: AN0
    AD1CSSL = 0;                // Channel scanning is disabled anyway.
    AD1CON1bits.ADON = 1;       // Turn on A/D

    IEC0bits.AD1IE = 1;         //Enable the interrupt
    IFS0bits.AD1IF = 0;         //Put the flag down
}

/******************************************************************************/

int readVoltage(int pinNumber)
{
    int count = 0;
    int analogVoltage;
    unsigned int *ADCPtr;
    ADCPtr = (unsigned int*) &ADC1BUF0;
    IFS0bits.AD1IF = 0; // Puts A/D flag down

    switch(pinNumber)
    {
        case(PIN):
            AD1CON1bits.ASAM = 1;       // Starts Auto Sampling
            while (!IFS0bits.AD1IF){};  // Waits for sampling to finish
            AD1CON1bits.ASAM = 0;       // Stops sampling

            // Adds up all the voltage measurements and then averages the value
            for(count = 0; count < 2; count++)
            {
                analogVoltage = analogVoltage + *ADCPtr++;
            }
        break;
    }

    // Divides by 2
    analogVoltage = analogVoltage >> 1;

    return(analogVoltage);
}