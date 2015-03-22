
#include "p24FJ64GA002.h"
#include "PWM.h"

#define FCY 14745600.0                 // System Frequency
#define TTOT .001                      // Total time signal is high
#define PRVAL (((FCY*TTOT)/1.0) - 1.0) // PRVAL that will count up to TTOT, is equal to range of possible output voltages
#define DUTYCYCLE .5                   // Percentage TTOT that VHIGH will be outputted for, voltage VOUT = VHIGH*DUTYCYCLE
#define THIGH DUTYCYCLE*PRVAL          // THIGH

/*
 *      // Helpful Stuff //
 *
 *      ?If the duty cycle register, OCxR, is loaded with 0000, the OCx pin will remain low
 *  (0% duty cycle).
 *      ? If OCxR is greater than PRy (Timer Period register), the pin will remain high
 *  (100% duty cycle).
 *      ? If OCxR is equal to PRy, the OCx pin will be low for one time base count value and high for
 *  all other count values.
 */
/************************************************************************************/

// Look at PDF page 25 of Output Compare for help

// Initializes the PWM module
void initPWM(){

    // Initalize Timer 2
    TMR2 = 0;               // Resets Timer 2
    PR2 = PRVAL;            // Sets PRVAL
    T2CONbits.TCKPS = 0b00; // prescalar of 1 for more acurrate output
    IFS0bits.T2IF = 0;      // Timer 2 interrupt flag down
    // End Initalize Timer

    // Initialize PWM
    // Set Output Pin
    OC1CONbits.OCTSEL = 0;  // using timer 2
    OC1CONbits.OCM = 6;
    RPOR5bits.RP11R = 18;   // map OC1 to pin 22

    OC1R = 0;               // Very important
    setDutyCycle(THIGH);    // Sets how long Voltage will be high
    T2CONbits.TON = 1;      // Turns on timer 2
    // End Initialize PWM
}

/************************************************************************************/

// Sets or changes the current duty cycle
void setDutyCycle(float dutyCycle)
{
    OC1RS = PRVAL*dutyCycle;
}

/************************************************************************************/