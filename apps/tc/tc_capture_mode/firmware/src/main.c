/*******************************************************************************
* Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/

/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes

/* Input waveform - compare value increment*/
#define DUTY_VAL_INCREMENT (100U)

/* Calculated duty cycle of the input waveform in %*/
float duty;
/* Calculated frequency of the input waveform in Hz*/
float frequency;

volatile bool one_sec_delay_timer_fired = false;
void timer0_channel1_callback(TC_TIMER_STATUS status, uintptr_t context)
{
  if( status == TC_TIMER_PERIOD_MATCH)
  {
    one_sec_delay_timer_fired = true;
  }
}

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main ( void )
{
    uint16_t period, on_time, off_time;
    uint16_t pwm_period, pwm_duty=0; 
    
    RTC_REGS->RTC_TIMR = 0x0;
    RTC_REGS->RTC_TIMALR = 0x0;
    RTC_REGS->RTC_SCCR = 0x1f;
  
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    
    WILC_EN_Clear();
    
    pwm_period = PWM_ChannelPeriodGet(PWM_CHANNEL_0);
    TC0_CH0_CaptureStart();
    PWM_ChannelsStart(PWM_CHANNEL_0_MASK);
    
    TC0_CH1_TimerCallbackRegister(timer0_channel1_callback, 0);
    TC0_CH1_TimerStart();
    
    printf("\n\r---------------------------------------------------------");
    printf("\n\r                    TC Capture Demo                 ");
    printf("\n\r---------------------------------------------------------\n\r"); 
    
    printf("Connect input signal to Timer 0 Channel 0 (Pin PA21).\n\n\r");

    while ( true )
    {
      
      /* Change the duty cycle of the input waveform  */
        pwm_duty += DUTY_VAL_INCREMENT;
        if (pwm_duty >= pwm_period)
        {
            pwm_duty = DUTY_VAL_INCREMENT;
        }
        PWM_ChannelDutySet(PWM_CHANNEL_0, pwm_duty);
        
        /* Wait for compare event */
        while((TC0_CH0_CaptureStatusGet() & TC_CAPTURE_B_LOAD) != TC_CAPTURE_B_LOAD);
        
        /* Read Captured values */ 
        off_time = TC0_CH0_CaptureAGet();
        period = TC0_CH0_CaptureBGet();

        /* Compute Duty Cycle in percentage and Frequency in Hz */
        on_time = period - off_time;
        duty = ((on_time) * 100U) / period;
        frequency = (TC0_CH0_CaptureFrequencyGet() / period);
        
        /* Send the measured data to console for display  */
        printf("Frequency of waveform: %.2f Hz \t Duty Cycle of waveform: %.2f %%", frequency, duty);
        printf("\r\n"); 
                
        /* Wait for 1 second */ 
        while(false == one_sec_delay_timer_fired);
        one_sec_delay_timer_fired = false;
        
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

