/*
 *  DC_Motor.c
 *
 *  Created: 2/15/2025 9:06:16 AM
 *  Author : Omar
 */ 

#include <avr/io.h>
#include "config.h"
#include "GPIO.h"
#include "ADC_driver.h"
#include "PWM.h"

int main(void)
{   
    // Init he Adc .
    initADC();

    // Init the PWM .
    initPWM();
    
    // Set the pin PORTD ==> 2, 3, 4, 5 As OUTPUT .
    MY_SB(DDR_SWs_Ins, IN_ONE);
    MY_SB(DDR_SWs_Ins, IN_TWO);
    MY_CB(DDR_SWs_Ins, LEFT_SW_PIN);
    MY_CB(DDR_SWs_Ins, RIGHT_SW_PIN);

    // init the variable with default 0 .
    uint16_t value_of_speed = 0; 

    while (1) 
    {
        // Read the Analog value from chanel number 0.
        value_of_speed = readADC(0); 

        /**
         *  Set the duty value 
         *  Example if i wnat to write 255 i will read 1023 from ADC and division it .
         *  1023 / 4 = 255 .
         */ 
        setDuty((uint16_t)value_of_speed/4);

        // If the door is arrived to the left limit switch .
        if(MY_BV(SW_DPIN, LEFT_SW_PIN) && !MY_BV(SW_DPIN, RIGHT_SW_PIN))
        {
            MY_SB(PORT_SWs, IN_ONE);
            MY_CB(PORT_SWs, IN_TWO);
        }
        // If the door is arrived to the right limit switch .
        else if(!MY_BV(SW_DPIN, LEFT_SW_PIN) && MY_BV(SW_DPIN, RIGHT_SW_PIN))
        {
            MY_CB(PORT_SWs, IN_ONE);
            MY_SB(PORT_SWs, IN_TWO);
        }
        // Stop the motor .
        else
        {
            MY_CB(PORT_SWs, IN_ONE);
            MY_CB(PORT_SWs, IN_TWO);
        }
    }
}

