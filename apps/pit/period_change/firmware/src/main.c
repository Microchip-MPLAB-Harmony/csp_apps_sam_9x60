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

static int timerState = 0;
static int initPeriod;

static void timerHandler (uintptr_t context)
{
    static uint32_t overflowCntr = 0;
    (void)context;
    
    overflowCntr++;
    
    /* Depending on the period value, the overflowCntr will count to 20 in 1000ms
     * or 500ms or 250ms or 125ms.
     */
    if (overflowCntr == 20)
    {        
        overflowCntr = 0;
        
        LED_GREEN_Toggle();
    }
    
}

static void handlePin(PIO_PIN pin, uintptr_t context)
{
    uint32_t period;
    static uint32_t switchPressToggle = 1;
    (void)context;
    (void)pin;
    
    switchPressToggle ^= 0x01;

    /* Pressing the switch will toggle the timer between on and off.
     * Each time the timer is turned on, the value of the new period is 
     * set to half of the current period value. This should result in LED toggling
     * rate change between 1000ms, 500ms, 250ms and 125ms every alternate switch
     * press.
     */
    if (switchPressToggle)
    {
        PIT_TimerStop();

        period = PIT_TimerPeriodGet();    
        period = period >> 1;

        timerState++;    
        if (timerState >= 4) {
            timerState = 0;
            period = initPeriod;
        }

        PIT_TimerPeriodSet(period);

        PIT_TimerStart();
    }
    else
    {
        PIT_TimerStop();
    }
}


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    
    initPeriod = PIT_TimerPeriodGet();

    PIT_TimerCallbackSet(timerHandler, 0);
    PIO_PinInterruptCallbackRegister(SW1_PIN, handlePin, 0);
    PIO_PinInterruptEnable(SW1_PIN);

    while ( true )
    {        
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

