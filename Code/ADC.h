/* 
 * File:   ADC.h
 * Author: albertoheras
 *
 * Created on March 17, 2015, 9:04 PM
 */

#ifndef ADC_H
#define	ADC_H
/* AD1CON1, AD1CON2 and AD1CON3
 *
 * Function of these registers includes enabling the
 * module, configuring the conversion clock and voltage reference sources, selecting the sampling
 * and conversion triggers, and manually controlling the sample/convert sequences.
 *
 *
 *  TAD is analog module clock that controls the conversion timing
 *  TAD = (TCY)(ADCS+1)
 *
 */
void initADC();

int readVoltage(int pinNumber); // This is an integer because  AD1CON1bits.FORM = 0 sets output as integer

// Code for main
//void _ISR _ADC1Interrupt(void)
//{
//    IFS0bits.AD1IF = 0;
//
//    int i = 0;
//    unsigned int *adcPtr;
//    adcVal = 0;
//    adcPtr = (unsigned int *) (&ADC1BUF0); // points to address of ADC1BUF0
//
//    // By incrementing adcPtr you draw out the values of the voltage in ADC1BUF0
//    // and divide them by 16, effectively averaging the value of voltage
//    for(i = 0; i < 16; i++)
//    {
//        adcVal = adcVal + *adcPtr/16;
//        adcPtr++;
//    }
//    done = 1;
//}
#endif	/* ADC_H */

