/*******************************************************************************
* Copyright (C) 2020 Microchip Technology Inc. and its subsidiaries.
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
#include <string.h>
#include <stdio.h>
#include "definitions.h"                // SYS function prototypes

uint8_t txBuffer[50];
uint8_t rxBuffer[10];
static volatile uint32_t nBytesRead = 0;
volatile bool txThresholdEventReceived = false;
volatile bool rxThresholdEventReceived = false;

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

#if   defined(__SAM9X60D1G__) || defined(SAM9X60D1G)
#define FLEXCOM_USART_ReadCountGet          FLEXCOM7_USART_ReadCountGet
#define FLEXCOM_USART_Read                  FLEXCOM7_USART_Read
#define FLEXCOM_USART_WriteCallbackRegister FLEXCOM7_USART_WriteCallbackRegister
#define FLEXCOM_USART_ReadCallbackRegister  FLEXCOM7_USART_ReadCallbackRegister
#define FLEXCOM_USART_ReadBufferSizeGet     FLEXCOM7_USART_ReadBufferSizeGet
#define FLEXCOM_USART_Write                 FLEXCOM7_USART_Write
#define FLEXCOM_USART_WriteBufferSizeGet    FLEXCOM7_USART_WriteBufferSizeGet
#define FLEXCOM_USART_WriteCountGet         FLEXCOM7_USART_WriteCountGet
#define FLEXCOM_USART_WriteFreeBufferCountGet FLEXCOM7_USART_WriteFreeBufferCountGet
#define FLEXCOM_USART_WriteThresholdSet     FLEXCOM7_USART_WriteThresholdSet
#define FLEXCOM_USART_WriteNotificationEnable FLEXCOM7_USART_WriteNotificationEnable
#define FLEXCOM_USART_ReadThresholdSet      FLEXCOM7_USART_ReadThresholdSet
#define FLEXCOM_USART_ReadNotificationEnable FLEXCOM7_USART_ReadNotificationEnable

#elif defined(__SAM9X60__)    || defined(SAM9X60)
#define FLEXCOM_USART_ReadCountGet          FLEXCOM5_USART_ReadCountGet
#define FLEXCOM_USART_Read                  FLEXCOM5_USART_Read
#define FLEXCOM_USART_WriteCallbackRegister FLEXCOM5_USART_WriteCallbackRegister
#define FLEXCOM_USART_ReadCallbackRegister  FLEXCOM5_USART_ReadCallbackRegister
#define FLEXCOM_USART_ReadBufferSizeGet     FLEXCOM5_USART_ReadBufferSizeGet
#define FLEXCOM_USART_Write                 FLEXCOM5_USART_Write
#define FLEXCOM_USART_WriteBufferSizeGet    FLEXCOM5_USART_WriteBufferSizeGet
#define FLEXCOM_USART_WriteCountGet         FLEXCOM5_USART_WriteCountGet
#define FLEXCOM_USART_WriteFreeBufferCountGet FLEXCOM5_USART_WriteFreeBufferCountGet
#define FLEXCOM_USART_WriteThresholdSet     FLEXCOM5_USART_WriteThresholdSet
#define FLEXCOM_USART_WriteNotificationEnable FLEXCOM5_USART_WriteNotificationEnable
#define FLEXCOM_USART_ReadThresholdSet      FLEXCOM5_USART_ReadThresholdSet
#define FLEXCOM_USART_ReadNotificationEnable FLEXCOM5_USART_ReadNotificationEnable

#else
#   error "Unsupported device: please provide the proper device."
#endif

void dbguReadEventHandler(FLEXCOM_USART_EVENT event, uintptr_t context )
{
    uint32_t nBytesAvailable = 0;

    if (event == FLEXCOM_USART_EVENT_READ_THRESHOLD_REACHED)
    {
        /* Receiver should atleast have the threshold number of bytes in the ring buffer */
        nBytesAvailable = FLEXCOM_USART_ReadCountGet();

        nBytesRead += FLEXCOM_USART_Read((uint8_t*)&rxBuffer[nBytesRead], nBytesAvailable);
    }
}

void dbguWriteEventHandler(FLEXCOM_USART_EVENT event, uintptr_t context )
{
    txThresholdEventReceived = true;
}

int main ( void )
{
    uint32_t nBytes = 0;        
    
    /* Initialize all modules */
    SYS_Initialize ( NULL );          
    
    /* Register a callback for write events */
    FLEXCOM_USART_WriteCallbackRegister(dbguWriteEventHandler, (uintptr_t) NULL);

    /* Register a callback for read events */
    FLEXCOM_USART_ReadCallbackRegister(dbguReadEventHandler, (uintptr_t) NULL);

    /* Print the size of the read buffer on the terminal */
    nBytes = sprintf((char*)txBuffer, "RX Buffer Size = %d\r\n", (int)FLEXCOM_USART_ReadBufferSizeGet());

    FLEXCOM_USART_Write((uint8_t*)txBuffer, nBytes);

    /* Print the size of the write buffer on the terminal */
    nBytes = sprintf((char*)txBuffer, "TX Buffer Size = %d\r\n", (int)FLEXCOM_USART_WriteBufferSizeGet());

    FLEXCOM_USART_Write((uint8_t*)txBuffer, nBytes);

    FLEXCOM_USART_Write((uint8_t*)"Adding 10 characters to the TX buffer - ", sizeof("Adding 10 characters to the TX buffer - "));

    /* Wait for all bytes to be transmitted out */
    while (FLEXCOM_USART_WriteCountGet() != 0);

    FLEXCOM_USART_Write((uint8_t*)"0123456789", 10);

    /* Print the amount of free space available in the TX buffer. This should be 10 bytes less than the configured write buffer size. */
    nBytes = sprintf((char*)txBuffer, "\r\nFree Space in Transmit Buffer = %d\r\n", (int)FLEXCOM_USART_WriteFreeBufferCountGet());

    FLEXCOM_USART_Write((uint8_t*)txBuffer, nBytes);

    /* Let's enable notifications to get notified when the TX buffer is empty */
    FLEXCOM_USART_WriteThresholdSet(FLEXCOM_USART_WriteBufferSizeGet());

    /* Enable notifications */
    FLEXCOM_USART_WriteNotificationEnable(true, false);

    /* Wait for the TX buffer to become empty. Flag "txThresholdEventReceived" is set in the callback. */
    while (txThresholdEventReceived == false);

    txThresholdEventReceived = false;

    /* Disable TX notifications */
    FLEXCOM_USART_WriteNotificationEnable(false, false);

    FLEXCOM_USART_Write((uint8_t*)"Enter 10 characters. The received characters are echoed back. \r\n>", sizeof("Enter 10 characters. The received characters are echoed back. \r\n>"));

    /* Wait till 10 (or more) characters are received */
    while (FLEXCOM_USART_ReadCountGet() < 10);

    /* At-least 10 characters are available in the RX buffer. Read out into the application buffer */
    FLEXCOM_USART_Read((uint8_t*)rxBuffer, 10);

    /* Echo the received data */
    FLEXCOM_USART_Write((uint8_t*)rxBuffer, 10);

    /* Now demonstrating receiver notifications */
    FLEXCOM_USART_Write((uint8_t*)"\r\n Now turning on RX notifications \r\n>", sizeof("\r\n Now turning on RX notifications \r\n>"));

    /* For demonstration purpose, set a threshold value to receive a callback after every 5 characters are received */
    FLEXCOM_USART_ReadThresholdSet(5);

    /* Enable RX event notifications */
    FLEXCOM_USART_ReadNotificationEnable(true, false);

    while(1)
    {
        /* Wait until at-least 10 characters are entered by the user */
        while (nBytesRead < 10);

        /* Echo the received data */
        FLEXCOM_USART_Write((uint8_t*)rxBuffer, nBytesRead);

        FLEXCOM_USART_Write((uint8_t*)"\r\n>", 3);

        nBytesRead = 0;
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

