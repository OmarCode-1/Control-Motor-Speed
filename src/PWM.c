/*
 * PWM.c
 *
 * Created: 2/15/2025 10:05:25 AM
 *  Author: Omar
 */ 

#include <avr/io.h>
#include "PWM.h"
#include "GPIO.h"

void initPWM()
{
    /*  **************************************
     *  Set the Mode is Fast PWM
     *  By set the Bits (WGM20, WGM21)
     *  **************************************
     *  Set the clear on Compare match
     *  ***************************************
     */
    TCCR2 = (1 << WGM20) | (1 << WGM21) | (1 << COM21); 

    // Set PreScaller 32 .
    TCCR2 |= (1 << CS21) | (1 << CS20);

    // Set the PWM OUPUT .
    MY_SB(DDR_PWM_PIN, PWM_PIN);
}


void setDuty(uint16_t duty_value){
    OCR2 = duty_value;
}