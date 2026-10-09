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

// DOM-IGNORE-BEGIN
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
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes

#if defined(__SAM9X60D6K__)
    /* Curiosity Hybrid - 2 channels via mikroBUS */
    #define APP_ADC_CH_FIRST      ADC_CH4
    #define APP_ADC_CH_SECOND     ADC_CH5
    #define APP_ADC_NUM_CHANNELS  2
#elif defined(__SAM9X60D1G__) || defined(__SAM9X60__)
    /* Curiosity Standard - 3 channels */
    #define APP_ADC_CH_FIRST      ADC_CH0
    #define APP_ADC_CH_SECOND     ADC_CH1
    #define APP_ADC_CH_THIRD      ADC_CH2
    #define APP_ADC_NUM_CHANNELS  3
#endif

#define ADC_VREF               (3.3f)

uint16_t adc_ch_first_count, adc_ch_second_count;
float adc_ch_first_voltage, adc_ch_second_voltage;

#if (APP_ADC_NUM_CHANNELS == 3)
uint16_t adc_ch_third_count;
float adc_ch_third_voltage;
#endif

volatile bool result_ready = false;

/* This function is called after conversion of last channel in the user sequence */
void ADC_EventHandler(uint32_t status, uintptr_t context)
{
    /* Read the results */
    adc_ch_first_count = ADC_ChannelResultGet(APP_ADC_CH_FIRST);
    adc_ch_second_count = ADC_ChannelResultGet(APP_ADC_CH_SECOND);
#if (APP_ADC_NUM_CHANNELS == 3)
    adc_ch_third_count = ADC_ChannelResultGet(APP_ADC_CH_THIRD);
#endif

    result_ready = true;
}

void sleepmode_fwup_off(void)
{
    printf("\n\r-----------------entering FWUP OFF mode------------------\n\r");
    ADC_SleepModeEnable();
    ADC_FastWakeupDisable();
    ADC_ConversionStart();
}

void sleepmode_fwup_on(void)
{
    printf("\n\r-----------------entering FWUP ON mode------------------\n\r");
    ADC_SleepModeEnable();
    ADC_FastWakeupEnable();
    ADC_ConversionStart();
}

void print_menu(void)
{
    printf("\n\r---------------------------------------------------------");
    printf("\n\r                    ADC Low Power Demo                 ");
    printf("\n\r---------------------------------------------------------\n\r");
    printf(" Select an option for FWUP :\n\r"
            " 0 -> both ADC core and Vref are OFF between conversions\n\r"
            " 1 -> ADC core is OFF and Vref is ON between conversions\n\r"
            " =>");
}

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main ( void )
{
    char c = 0;
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    /* Register callback function for ADC end of conversion interrupt*/
    ADC_CallbackRegister(ADC_EventHandler, (uintptr_t)NULL);
    print_menu();
    DBGU_Read(&c, 1);
        switch (c) {
            case '0':
                printf(" 0 selected\n\r");
                sleepmode_fwup_off();
                break;
            case '1':
                printf("1 selected\n\r");
                sleepmode_fwup_on();
                break;
            default:
                printf("\n\r");
        }

#if (APP_ADC_NUM_CHANNELS == 2)
    printf("CH4 (mikroBUS1)  CH5 (mikroBUS2)\n\r");
#else
    printf("CH0 Count  CH0 Voltage  CH1 Count  CH1 Voltage  CH2 Count  CH2 Voltage \n\r");
#endif

    while ( true )
    {
        /* Check if result is ready to be transmitted to console */
        if (result_ready == true)
        {
            adc_ch_first_voltage = (float)adc_ch_first_count * ADC_VREF / 4095U;
            adc_ch_second_voltage = (float)adc_ch_second_count * ADC_VREF / 4095U;

#if (APP_ADC_NUM_CHANNELS == 3)
            adc_ch_third_voltage = (float)adc_ch_third_count * ADC_VREF / 4095U;
            printf("0x%03x      %0.2f V       0x%03x      %0.2f V       0x%03x      %0.2f V \t\r",
                    adc_ch_first_count, adc_ch_first_voltage,
                    adc_ch_second_count, adc_ch_second_voltage,
                    adc_ch_third_count, adc_ch_third_voltage);
#else
            printf("0x%03x (%0.2fV)     0x%03x (%0.2fV)\r",
                    adc_ch_first_count, adc_ch_first_voltage,
                    adc_ch_second_count, adc_ch_second_voltage);
#endif

            result_ready = false;

            PIT_DelayMs(500);

            /* Start ADC conversion */
            ADC_ConversionStart();
        }
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}



/*******************************************************************************
 End of File
*/
