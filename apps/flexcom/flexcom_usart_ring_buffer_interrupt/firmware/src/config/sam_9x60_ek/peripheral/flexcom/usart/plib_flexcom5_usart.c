/*******************************************************************************
  FLEXCOM5 USART PLIB

  Company:
    Microchip Technology Inc.

  File Name:
    plib_flexcom5_usart.c

  Summary:
    FLEXCOM5 USART PLIB Implementation File

  Description
    This file defines the interface to the FLEXCOM5 USART
    peripheral library. This library provides access to and control of the
    associated peripheral instance.

  Remarks:
    None.
*******************************************************************************/

/*******************************************************************************
* Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries.
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

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "plib_flexcom5_usart.h"
#include "interrupts.h"

#define FLEXCOM5_USART_READ_BUFFER_SIZE             20
#define FLEXCOM5_USART_READ_BUFFER_SIZE_9BIT        (20 >> 1)


/* Disable Read, Overrun, Parity and Framing error interrupts */
#define FLEXCOM5_USART_RX_INT_DISABLE()      FLEXCOM5_REGS->FLEX_US_IDR = (FLEX_US_IDR_RXRDY_Msk | FLEX_US_IDR_FRAME_Msk | FLEX_US_IDR_PARE_Msk | FLEX_US_IDR_OVRE_Msk)

/* Enable Read, Overrun, Parity and Framing error interrupts */
#define FLEXCOM5_USART_RX_INT_ENABLE()       FLEXCOM5_REGS->FLEX_US_IER = (FLEX_US_IER_RXRDY_Msk | FLEX_US_IER_FRAME_Msk | FLEX_US_IER_PARE_Msk | FLEX_US_IER_OVRE_Msk)

#define FLEXCOM5_USART_TX_INT_DISABLE()      FLEXCOM5_REGS->FLEX_US_IDR = FLEX_US_IDR_TXRDY_Msk
#define FLEXCOM5_USART_TX_INT_ENABLE()       FLEXCOM5_REGS->FLEX_US_IER = FLEX_US_IER_TXRDY_Msk

static uint8_t FLEXCOM5_USART_ReadBuffer[FLEXCOM5_USART_READ_BUFFER_SIZE];

#define FLEXCOM5_USART_WRITE_BUFFER_SIZE            128
#define FLEXCOM5_USART_WRITE_BUFFER_SIZE_9BIT       (128 >> 1)

static uint8_t FLEXCOM5_USART_WriteBuffer[FLEXCOM5_USART_WRITE_BUFFER_SIZE];

// *****************************************************************************
// *****************************************************************************
// Section: FLEXCOM5 USART Ring Buffer Implementation
// *****************************************************************************
// *****************************************************************************

FLEXCOM_USART_RING_BUFFER_OBJECT flexcom5UsartObj;

void FLEXCOM5_USART_Initialize( void )
{
    /* Set FLEXCOM USART operating mode */
    FLEXCOM5_REGS->FLEX_MR = FLEX_MR_OPMODE_USART;

    /* Reset FLEXCOM5 USART */
    FLEXCOM5_REGS->FLEX_US_CR = (FLEX_US_CR_RSTRX_Msk | FLEX_US_CR_RSTTX_Msk | FLEX_US_CR_RSTSTA_Msk);


    FLEXCOM5_REGS->FLEX_US_TTGR = 0;

    /* Enable FLEXCOM5 USART */
    FLEXCOM5_REGS->FLEX_US_CR = (FLEX_US_CR_TXEN_Msk | FLEX_US_CR_RXEN_Msk);

    /* Configure FLEXCOM5 USART mode */
    FLEXCOM5_REGS->FLEX_US_MR = ( FLEX_US_MR_USART_MODE_NORMAL | FLEX_US_MR_USCLKS_MCK | FLEX_US_MR_CHRL_8_BIT | FLEX_US_MR_PAR_NO | FLEX_US_MR_NBSTOP_1_BIT | (0 << FLEX_US_MR_OVER_Pos));

    /* Configure FLEXCOM5 USART Baud Rate */
    FLEXCOM5_REGS->FLEX_US_BRGR = FLEX_US_BRGR_CD(108);

    flexcom5UsartObj.rdCallback = NULL;
    flexcom5UsartObj.rdInIndex = 0;
    flexcom5UsartObj.rdOutIndex = 0;
    flexcom5UsartObj.isRdNotificationEnabled = false;
    flexcom5UsartObj.isRdNotifyPersistently = false;
    flexcom5UsartObj.rdThreshold = 0;
    flexcom5UsartObj.rdBufferSize = FLEXCOM5_USART_READ_BUFFER_SIZE;
    flexcom5UsartObj.wrCallback = NULL;
    flexcom5UsartObj.wrInIndex = 0;
    flexcom5UsartObj.wrOutIndex = 0;
    flexcom5UsartObj.isWrNotificationEnabled = false;
    flexcom5UsartObj.isWrNotifyPersistently = false;
    flexcom5UsartObj.wrThreshold = 0;
    flexcom5UsartObj.wrBufferSize = FLEXCOM5_USART_WRITE_BUFFER_SIZE;
    flexcom5UsartObj.errorStatus = FLEXCOM_USART_ERROR_NONE;

    if (FLEXCOM5_REGS->FLEX_US_MR & FLEX_US_MR_MODE9_Msk)
    {
        flexcom5UsartObj.rdBufferSize = FLEXCOM5_USART_READ_BUFFER_SIZE_9BIT;
        flexcom5UsartObj.wrBufferSize = FLEXCOM5_USART_WRITE_BUFFER_SIZE_9BIT;
    }
    else
    {
        flexcom5UsartObj.rdBufferSize = FLEXCOM5_USART_READ_BUFFER_SIZE;
        flexcom5UsartObj.wrBufferSize = FLEXCOM5_USART_WRITE_BUFFER_SIZE;
    }

    FLEXCOM5_USART_RX_INT_ENABLE();
}

void static FLEXCOM5_USART_ErrorClear( void )
{
    uint16_t dummyData = 0u;

    /* Clear the error flags */
    FLEXCOM5_REGS->FLEX_US_CR = FLEX_US_CR_RSTSTA_Msk;

    /* Flush existing error bytes from the RX FIFO */
    while( FLEX_US_CSR_RXRDY_Msk == (FLEXCOM5_REGS->FLEX_US_CSR& FLEX_US_CSR_RXRDY_Msk) )
    {
        if (FLEXCOM5_REGS->FLEX_US_MR & FLEX_US_MR_MODE9_Msk)
        {
            dummyData = *((uint16_t*)&FLEXCOM5_REGS->FLEX_US_RHR) & FLEX_US_RHR_RXCHR_Msk;
        }
        else
        {
            dummyData = *((uint8_t*)&FLEXCOM5_REGS->FLEX_US_RHR);
        }
    }

    /* Ignore the warning */
    (void)dummyData;

    return;
}

FLEXCOM_USART_ERROR FLEXCOM5_USART_ErrorGet( void )
{
    FLEXCOM_USART_ERROR errors = flexcom5UsartObj.errorStatus;

    flexcom5UsartObj.errorStatus = FLEXCOM_USART_ERROR_NONE;

    /* All errors are cleared, but send the previous error state */
    return errors;
}

bool FLEXCOM5_USART_SerialSetup( FLEXCOM_USART_SERIAL_SETUP *setup, uint32_t srcClkFreq )
{
    uint32_t baud = 0;
    uint32_t brgVal = 0;
    uint32_t overSampVal = 0;
    uint32_t usartMode;
    bool status = false;

    if (setup != NULL)
    {
        baud = setup->baudRate;
        if(srcClkFreq == 0)
        {
            srcClkFreq = FLEXCOM5_USART_FrequencyGet();
        }

        /* Calculate BRG value */
        if (srcClkFreq >= (16 * baud))
        {
            brgVal = (srcClkFreq / (16 * baud));
        }
        else if (srcClkFreq >= (8 * baud))
        {
            brgVal = (srcClkFreq / (8 * baud));
            overSampVal = (1 << FLEX_US_MR_OVER_Pos) & FLEX_US_MR_OVER_Msk;
        }
        else
        {
            /* The input clock source - srcClkFreq, is too low to generate the desired baud */
            return status;
        }
        if (brgVal > 65535)
        {
            /* The requested baud is so low that the ratio of srcClkFreq to baud exceeds the 16-bit register value of CD register */
            return status;
        }

        /* Configure FLEXCOM5 USART mode */
        usartMode = FLEXCOM5_REGS->FLEX_US_MR;
        usartMode &= ~(FLEX_US_MR_CHRL_Msk | FLEX_US_MR_MODE9_Msk | FLEX_US_MR_PAR_Msk | FLEX_US_MR_NBSTOP_Msk | FLEX_US_MR_OVER_Msk);
        FLEXCOM5_REGS->FLEX_US_MR = usartMode | ((uint32_t)setup->dataWidth | (uint32_t)setup->parity | (uint32_t)setup->stopBits | overSampVal);

        /* Configure FLEXCOM5 USART Baud Rate */
        FLEXCOM5_REGS->FLEX_US_BRGR = FLEX_US_BRGR_CD(brgVal);

        if (FLEXCOM5_REGS->FLEX_US_MR & FLEX_US_MR_MODE9_Msk)
        {
            flexcom5UsartObj.rdBufferSize = FLEXCOM5_USART_READ_BUFFER_SIZE_9BIT;
            flexcom5UsartObj.wrBufferSize = FLEXCOM5_USART_WRITE_BUFFER_SIZE_9BIT;
        }
        else
        {
            flexcom5UsartObj.rdBufferSize = FLEXCOM5_USART_READ_BUFFER_SIZE;
            flexcom5UsartObj.wrBufferSize = FLEXCOM5_USART_WRITE_BUFFER_SIZE;
        }

        status = true;
    }

    return status;
}

/* This routine is only called from ISR. Hence do not disable/enable USART interrupts. */
static bool FLEXCOM5_USART_TxPullByte(uint16_t* pWrByte)
{
    bool isSuccess = false;
    uint32_t wrOutIndex = flexcom5UsartObj.wrOutIndex;
    uint32_t wrInIndex = flexcom5UsartObj.wrInIndex;

    if (wrOutIndex != wrInIndex)
    {
        if (FLEXCOM5_REGS->FLEX_US_MR & FLEX_US_MR_MODE9_Msk)
        {
            *pWrByte = ((uint16_t*)&FLEXCOM5_USART_WriteBuffer)[wrOutIndex++];
        }
        else
        {
            *pWrByte = FLEXCOM5_USART_WriteBuffer[wrOutIndex++];
        }

        if (wrOutIndex >= flexcom5UsartObj.wrBufferSize)
        {
            wrOutIndex = 0;
        }

        flexcom5UsartObj.wrOutIndex = wrOutIndex;

        isSuccess = true;
    }

    return isSuccess;
}

static inline bool FLEXCOM5_USART_TxPushByte(uint16_t wrByte)
{
    uint32_t tempInIndex;
    uint32_t wrOutIndex;
    uint32_t wrInIndex;
    bool isSuccess = false;

    /* Take a snapshot of indices to avoid creation of critical section */
    wrOutIndex = flexcom5UsartObj.wrOutIndex;
    wrInIndex = flexcom5UsartObj.wrInIndex;

    tempInIndex = wrInIndex + 1;

    if (tempInIndex >= flexcom5UsartObj.wrBufferSize)
    {
        tempInIndex = 0;
    }
    if (tempInIndex != wrOutIndex)
    {
        if (FLEXCOM5_REGS->FLEX_US_MR & FLEX_US_MR_MODE9_Msk)
        {
            ((uint16_t*)&FLEXCOM5_USART_WriteBuffer)[wrInIndex] = wrByte;
        }
        else
        {
            FLEXCOM5_USART_WriteBuffer[wrInIndex] = (uint8_t)wrByte;
        }

        flexcom5UsartObj.wrInIndex = tempInIndex;
        isSuccess = true;
    }
    else
    {
        /* Queue is full. Report Error. */
    }

    return isSuccess;
}

/* This routine is only called from ISR. Hence do not disable/enable USART interrupts. */
static void FLEXCOM5_USART_WriteNotificationSend(void)
{
    uint32_t nFreeWrBufferCount;

    if (flexcom5UsartObj.isWrNotificationEnabled == true)
    {
        nFreeWrBufferCount = FLEXCOM5_USART_WriteFreeBufferCountGet();

        if(flexcom5UsartObj.wrCallback != NULL)
        {
            if (flexcom5UsartObj.isWrNotifyPersistently == true)
            {
                if (nFreeWrBufferCount >= flexcom5UsartObj.wrThreshold)
                {
                    flexcom5UsartObj.wrCallback(FLEXCOM_USART_EVENT_WRITE_THRESHOLD_REACHED, flexcom5UsartObj.wrContext);
                }
            }
            else
            {
                if (nFreeWrBufferCount == flexcom5UsartObj.wrThreshold)
                {
                    flexcom5UsartObj.wrCallback(FLEXCOM_USART_EVENT_WRITE_THRESHOLD_REACHED, flexcom5UsartObj.wrContext);
                }
            }
        }
    }
}

static size_t FLEXCOM5_USART_WritePendingBytesGet(void)
{
    size_t nPendingTxBytes;

    /* Take a snapshot of indices to avoid creation of critical section */

    uint32_t wrOutIndex = flexcom5UsartObj.wrOutIndex;
    uint32_t wrInIndex = flexcom5UsartObj.wrInIndex;

    if ( wrInIndex >=  wrOutIndex)
    {
        nPendingTxBytes =  wrInIndex -  wrOutIndex;
    }
    else
    {
        nPendingTxBytes =  (flexcom5UsartObj.wrBufferSize -  wrOutIndex) + wrInIndex;
    }

    return nPendingTxBytes;
}

size_t FLEXCOM5_USART_WriteCountGet(void)
{
    size_t nPendingTxBytes;

    nPendingTxBytes = FLEXCOM5_USART_WritePendingBytesGet();

    return nPendingTxBytes;
}

size_t FLEXCOM5_USART_Write(uint8_t* pWrBuffer, const size_t size )
{
    size_t nBytesWritten  = 0;

    while (nBytesWritten < size)
    {
        if (FLEXCOM5_REGS->FLEX_US_MR & FLEX_US_MR_MODE9_Msk)
        {
            if (FLEXCOM5_USART_TxPushByte(((uint16_t*)pWrBuffer)[nBytesWritten]) == true)
            {
                nBytesWritten++;
            }
            else
            {
                /* Queue is full, exit the loop */
                break;
            }
        }
        else
        {
            if (FLEXCOM5_USART_TxPushByte(pWrBuffer[nBytesWritten]) == true)
            {
                nBytesWritten++;
            }
            else
            {
                /* Queue is full, exit the loop */
                break;
            }
        }
    }

    /* Check if any data is pending for transmission */
    if (FLEXCOM5_USART_WritePendingBytesGet() > 0)
    {
        /* Enable TX interrupt as data is pending for transmission */
        FLEXCOM5_USART_TX_INT_ENABLE();
    }

    return nBytesWritten;
}

size_t FLEXCOM5_USART_WriteFreeBufferCountGet(void)
{
    return (flexcom5UsartObj.wrBufferSize - 1) - FLEXCOM5_USART_WriteCountGet();
}

size_t FLEXCOM5_USART_WriteBufferSizeGet(void)
{
    return (flexcom5UsartObj.wrBufferSize - 1);
}

bool FLEXCOM5_USART_WriteNotificationEnable(bool isEnabled, bool isPersistent)
{
    bool previousStatus = flexcom5UsartObj.isWrNotificationEnabled;

    flexcom5UsartObj.isWrNotificationEnabled = isEnabled;

    flexcom5UsartObj.isWrNotifyPersistently = isPersistent;

    return previousStatus;
}

void FLEXCOM5_USART_WriteThresholdSet(uint32_t nBytesThreshold)
{
    if (nBytesThreshold > 0)
    {
        flexcom5UsartObj.wrThreshold = nBytesThreshold;
    }
}

void FLEXCOM5_USART_WriteCallbackRegister( FLEXCOM_USART_RING_BUFFER_CALLBACK callback, uintptr_t context)
{
    flexcom5UsartObj.wrCallback = callback;

    flexcom5UsartObj.wrContext = context;
}

/* This routine is only called from ISR. Hence do not disable/enable USART interrupts. */
static inline bool FLEXCOM5_USART_RxPushByte(uint16_t rdByte)
{
    uint32_t tempInIndex;
    bool isSuccess = false;

    tempInIndex = flexcom5UsartObj.rdInIndex + 1;

    if (tempInIndex >= flexcom5UsartObj.rdBufferSize)
    {
        tempInIndex = 0;
    }

    if (tempInIndex == flexcom5UsartObj.rdOutIndex)
    {
        /* Queue is full - Report it to the application. Application gets a chance to free up space by reading data out from the RX ring buffer */
        if(flexcom5UsartObj.rdCallback != NULL)
        {
            flexcom5UsartObj.rdCallback(FLEXCOM_USART_EVENT_READ_BUFFER_FULL, flexcom5UsartObj.rdContext);

            /* Read the indices again in case application has freed up space in RX ring buffer */
            tempInIndex = flexcom5UsartObj.rdInIndex + 1;

            if (tempInIndex >= flexcom5UsartObj.rdBufferSize)
            {
                tempInIndex = 0;
            }
        }
    }

    /* Attempt to push the data into the ring buffer */
    if (tempInIndex != flexcom5UsartObj.rdOutIndex)
    {
        if (FLEXCOM5_REGS->FLEX_US_MR & FLEX_US_MR_MODE9_Msk)
        {
            ((uint16_t*)&FLEXCOM5_USART_ReadBuffer)[flexcom5UsartObj.rdInIndex] = rdByte;
        }
        else
        {
            FLEXCOM5_USART_ReadBuffer[flexcom5UsartObj.rdInIndex] = (uint8_t)rdByte;
        }

        flexcom5UsartObj.rdInIndex = tempInIndex;
        isSuccess = true;
    }
    else
    {
        /* Queue is full. Data will be lost. */
    }

    return isSuccess;
}

/* This routine is only called from ISR. Hence do not disable/enable USART interrupts. */
static void FLEXCOM5_USART_ReadNotificationSend(void)
{
    uint32_t nUnreadBytesAvailable;

    if (flexcom5UsartObj.isRdNotificationEnabled == true)
    {
        nUnreadBytesAvailable = FLEXCOM5_USART_ReadCountGet();

        if(flexcom5UsartObj.rdCallback != NULL)
        {
            if (flexcom5UsartObj.isRdNotifyPersistently == true)
            {
                if (nUnreadBytesAvailable >= flexcom5UsartObj.rdThreshold)
                {
                    flexcom5UsartObj.rdCallback(FLEXCOM_USART_EVENT_READ_THRESHOLD_REACHED, flexcom5UsartObj.rdContext);
                }
            }
            else
            {
                if (nUnreadBytesAvailable == flexcom5UsartObj.rdThreshold)
                {
                    flexcom5UsartObj.rdCallback(FLEXCOM_USART_EVENT_READ_THRESHOLD_REACHED, flexcom5UsartObj.rdContext);
                }
            }
        }
    }
}

size_t FLEXCOM5_USART_Read(uint8_t* pRdBuffer, const size_t size)
{
    size_t nBytesRead = 0;
    uint32_t rdOutIndex = 0;
    uint32_t rdInIndex = 0;


    /* Take a snapshot of indices to avoid creation of critical section */
    rdOutIndex = flexcom5UsartObj.rdOutIndex;
    rdInIndex = flexcom5UsartObj.rdInIndex;

    while (nBytesRead < size)
    {
        if (rdOutIndex != rdInIndex)
        {
            if (FLEXCOM5_REGS->FLEX_US_MR & FLEX_US_MR_MODE9_Msk)
            {
                ((uint16_t*)pRdBuffer)[nBytesRead++] = ((uint16_t*)&FLEXCOM5_USART_ReadBuffer)[rdOutIndex++];
            }
            else
            {
                pRdBuffer[nBytesRead++] = FLEXCOM5_USART_ReadBuffer[rdOutIndex++];
            }

            if (rdOutIndex >= flexcom5UsartObj.rdBufferSize)
            {
                rdOutIndex = 0;
            }
        }
        else
        {
            /* No more data available in the RX buffer */
            break;
        }
    }

    flexcom5UsartObj.rdOutIndex = rdOutIndex;

    return nBytesRead;
}

size_t FLEXCOM5_USART_ReadCountGet(void)
{
    size_t nUnreadBytesAvailable;
    uint32_t rdOutIndex;
    uint32_t rdInIndex;


    /* Take a snapshot of indices to avoid creation of critical section */
    rdOutIndex = flexcom5UsartObj.rdOutIndex;
    rdInIndex = flexcom5UsartObj.rdInIndex;

    if ( rdInIndex >=  rdOutIndex)
    {
        nUnreadBytesAvailable =  rdInIndex -  rdOutIndex;
    }
    else
    {
        nUnreadBytesAvailable =  (flexcom5UsartObj.rdBufferSize -  rdOutIndex) + rdInIndex;
    }

    return nUnreadBytesAvailable;
}

size_t FLEXCOM5_USART_ReadFreeBufferCountGet(void)
{
    return (flexcom5UsartObj.rdBufferSize - 1) - FLEXCOM5_USART_ReadCountGet();
}

size_t FLEXCOM5_USART_ReadBufferSizeGet(void)
{
    return (flexcom5UsartObj.rdBufferSize - 1);
}


bool FLEXCOM5_USART_ReadNotificationEnable(bool isEnabled, bool isPersistent)
{
    bool previousStatus = flexcom5UsartObj.isRdNotificationEnabled;

    flexcom5UsartObj.isRdNotificationEnabled = isEnabled;

    flexcom5UsartObj.isRdNotifyPersistently = isPersistent;


    return previousStatus;
}

void FLEXCOM5_USART_ReadThresholdSet(uint32_t nBytesThreshold)
{
    if (nBytesThreshold > 0)
    {
        flexcom5UsartObj.rdThreshold = nBytesThreshold;

    }
}

void FLEXCOM5_USART_ReadCallbackRegister( FLEXCOM_USART_RING_BUFFER_CALLBACK callback, uintptr_t context)
{
    flexcom5UsartObj.rdCallback = callback;

    flexcom5UsartObj.rdContext = context;
}

void static FLEXCOM5_USART_ISR_RX_Handler( void )
{
    uint16_t rdData = 0;

    /* Keep reading until there is a character availabe in the RX FIFO */
    while(FLEX_US_CSR_RXRDY_Msk == (FLEXCOM5_REGS->FLEX_US_CSR & FLEX_US_CSR_RXRDY_Msk))
    {
        if (FLEXCOM5_REGS->FLEX_US_MR & FLEX_US_MR_MODE9_Msk)
        {
            rdData = *((uint16_t*)&FLEXCOM5_REGS->FLEX_US_RHR) & FLEX_US_RHR_RXCHR_Msk;
        }
        else
        {
            rdData = *((uint8_t*)&FLEXCOM5_REGS->FLEX_US_RHR);
        }

        if (FLEXCOM5_USART_RxPushByte( rdData ) == true)
        {
            FLEXCOM5_USART_ReadNotificationSend();
        }
        else
        {
            /* UART RX buffer is full */
        }
    }


}

void static FLEXCOM5_USART_ISR_TX_Handler( void )
{
    uint16_t wrByte;

    /* Keep writing to the TX FIFO as long as there is space */
    while(FLEX_US_CSR_TXRDY_Msk == (FLEXCOM5_REGS->FLEX_US_CSR & FLEX_US_CSR_TXRDY_Msk))
    {
        if (FLEXCOM5_USART_TxPullByte(&wrByte) == true)
        {
            if (FLEXCOM5_REGS->FLEX_US_MR & FLEX_US_MR_MODE9_Msk)
            {
                *((uint16_t*)&FLEXCOM5_REGS->FLEX_US_THR) = wrByte & FLEX_US_THR_TXCHR_Msk;
            }
            else
            {
                *((uint8_t*)&FLEXCOM5_REGS->FLEX_US_THR) = (uint8_t)wrByte;
            }

            /* Send notification */
            FLEXCOM5_USART_WriteNotificationSend();
        }
        else
        {
            /* Nothing to transmit. Disable the data register empty/fifo Threshold interrupt. */
            FLEXCOM5_USART_TX_INT_DISABLE();
            break;
        }
    }

}

void FLEXCOM5_InterruptHandler( void )
{
    /* Channel status */
    uint32_t channelStatus = FLEXCOM5_REGS->FLEX_US_CSR;

    /* Error status */
    uint32_t errorStatus = (channelStatus & (FLEX_US_CSR_OVRE_Msk | FLEX_US_CSR_FRAME_Msk | FLEX_US_CSR_PARE_Msk));


    if(errorStatus != 0)
    {
        /* Save the error so that it can be reported when application calls the FLEXCOM5_USART_ErrorGet() API */
        flexcom5UsartObj.errorStatus = (FLEXCOM_USART_ERROR)errorStatus;

        /* Clear the error flags and flush out the error bytes */
        FLEXCOM5_USART_ErrorClear();

        /* USART errors are normally associated with the receiver, hence calling receiver context */
        if( flexcom5UsartObj.rdCallback != NULL )
        {
            flexcom5UsartObj.rdCallback(FLEXCOM_USART_EVENT_READ_ERROR, flexcom5UsartObj.rdContext);
        }
    }

    /* Receiver status. RX interrupt is never disabled. */
    if (channelStatus & FLEX_US_CSR_RXRDY_Msk)
    {
        FLEXCOM5_USART_ISR_RX_Handler();
    }

    /* Transmitter status */
    if( (channelStatus & FLEX_US_CSR_TXRDY_Msk) && (FLEXCOM5_REGS->FLEX_US_IMR & FLEX_US_IMR_TXRDY_Msk) )
    {
        FLEXCOM5_USART_ISR_TX_Handler();
    }
}
