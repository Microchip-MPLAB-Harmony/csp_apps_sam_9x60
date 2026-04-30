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

#define FLEXCOM_USART_RHR_8BIT_REG      (*(volatile uint8_t* const)((FLEXCOM5_BASE_ADDRESS + FLEX_US_RHR_REG_OFST)))
#define FLEXCOM_USART_RHR_9BIT_REG      (*(volatile uint16_t* const)((FLEXCOM5_BASE_ADDRESS + FLEX_US_RHR_REG_OFST)))

#define FLEXCOM_USART_THR_8BIT_REG      (*(volatile uint8_t* const)((FLEXCOM5_BASE_ADDRESS + FLEX_US_THR_REG_OFST)))
#define FLEXCOM_USART_THR_9BIT_REG      (*(volatile uint16_t* const)((FLEXCOM5_BASE_ADDRESS + FLEX_US_THR_REG_OFST)))

#ifndef FLEX_US_IER_LIN_FRAME_Msk
#define FLEX_US_IER_LIN_FRAME_Msk   FLEX_US_IER_FRAME_Msk
#endif
#ifndef FLEX_US_IER_LIN_PARE_Msk
#define FLEX_US_IER_LIN_PARE_Msk    FLEX_US_IER_PARE_Msk
#endif
#ifndef FLEX_US_IER_LIN_TIMEOUT_Msk
#define FLEX_US_IER_LIN_TIMEOUT_Msk FLEX_US_IER_TIMEOUT_Msk
#endif
#ifndef FLEX_US_IDR_LIN_FRAME_Msk
#define FLEX_US_IDR_LIN_FRAME_Msk   FLEX_US_IDR_FRAME_Msk
#endif
#ifndef FLEX_US_IDR_LIN_PARE_Msk
#define FLEX_US_IDR_LIN_PARE_Msk    FLEX_US_IDR_PARE_Msk
#endif
#ifndef FLEX_US_IDR_LIN_TIMEOUT_Msk
#define FLEX_US_IDR_LIN_TIMEOUT_Msk FLEX_US_IDR_TIMEOUT_Msk
#endif
#ifndef FLEX_US_CSR_LIN_FRAME_Msk
#define FLEX_US_CSR_LIN_FRAME_Msk   FLEX_US_CSR_FRAME_Msk
#endif
#ifndef FLEX_US_CSR_LIN_PARE_Msk
#define FLEX_US_CSR_LIN_PARE_Msk    FLEX_US_CSR_PARE_Msk
#endif
/* These macros are not defined in the device header file */
#ifndef FLEX_US_IER_LIN_LINBE_Msk
    #define FLEX_US_IER_LIN_LINBE_Msk   ((uint32_t)1<<25)
#endif
#ifndef FLEX_US_IER_LIN_LINISFE_Msk
    #define FLEX_US_IER_LIN_LINISFE_Msk ((uint32_t)1<<26)
#endif
#ifndef FLEX_US_IER_LIN_LINIPE_Msk
    #define FLEX_US_IER_LIN_LINIPE_Msk  ((uint32_t)1<<27)
#endif
#ifndef FLEX_US_IER_LIN_LINCE_Msk
    #define FLEX_US_IER_LIN_LINCE_Msk   ((uint32_t)1<<28)
#endif
#ifndef FLEX_US_IER_LIN_LINSNRE_Msk
#define FLEX_US_IER_LIN_LINSNRE_Msk ((uint32_t)1<<29)
#endif
#ifndef FLEX_US_IER_LIN_LINSTE_Msk
    #define FLEX_US_IER_LIN_LINSTE_Msk  ((uint32_t)1<<30)
#endif
#ifndef FLEX_US_IER_LIN_LINHTE_Msk
    #define FLEX_US_IER_LIN_LINHTE_Msk  ((uint32_t)1<<31)
#endif
#ifndef FLEX_US_IER_LIN_LINID_Msk
    #define FLEX_US_IER_LIN_LINID_Msk   ((uint32_t)1<<14)
#endif
#ifndef FLEX_US_IER_LIN_LINTC_Msk
    #define FLEX_US_IER_LIN_LINTC_Msk   ((uint32_t)1<<15)
#endif
#ifndef FLEX_US_IDR_LIN_LINBK_Msk
    #define FLEX_US_IDR_LIN_LINBK_Msk   ((uint32_t)1<<13)
#endif
#ifndef FLEX_US_IER_LIN_LINBK_Msk
    #define FLEX_US_IER_LIN_LINBK_Msk   ((uint32_t)1<<13)
#endif
#ifndef FLEX_US_CSR_LIN_TIMEOUT_Msk
    #define FLEX_US_CSR_LIN_TIMEOUT_Msk ((uint32_t)1<<8)
#endif
#ifndef FLEX_US_CSR_LIN_LINBE_Msk
    #define FLEX_US_CSR_LIN_LINBE_Msk   ((uint32_t)1<<25)
#endif
#ifndef FLEX_US_CSR_LIN_LINISFE_Msk
    #define FLEX_US_CSR_LIN_LINISFE_Msk ((uint32_t)1<<26)
#endif
#ifndef FLEX_US_CSR_LIN_LINIPE_Msk
    #define FLEX_US_CSR_LIN_LINIPE_Msk  ((uint32_t)1<<27)
#endif
#ifndef FLEX_US_CSR_LIN_LINCE_Msk
    #define FLEX_US_CSR_LIN_LINCE_Msk   ((uint32_t)1<<28)
#endif
#ifndef FLEX_US_CSR_LIN_LINSNRE_Msk
    #define FLEX_US_CSR_LIN_LINSNRE_Msk ((uint32_t)1<<29)
#endif
#ifndef FLEX_US_CSR_LIN_LINSTE_Msk
    #define FLEX_US_CSR_LIN_LINSTE_Msk  ((uint32_t)1<<30)
#endif
#ifndef FLEX_US_CSR_LIN_LINHTE_Msk
    #define FLEX_US_CSR_LIN_LINHTE_Msk  ((uint32_t)1<<31)
#endif
#ifndef FLEX_US_CSR_LIN_LINBK_Msk
    #define FLEX_US_CSR_LIN_LINBK_Msk   ((uint32_t)1<<13)
#endif
#ifndef FLEX_US_CSR_LIN_LINID_Msk
    #define FLEX_US_CSR_LIN_LINID_Msk   ((uint32_t)1<<14)
#endif
#ifndef FLEX_US_CSR_LIN_LINTC_Msk
    #define FLEX_US_CSR_LIN_LINTC_Msk   ((uint32_t)1<<15)
#endif


/* Disable Read, Overrun, Parity and Framing error interrupts */
#define FLEXCOM5_USART_RX_INT_DISABLE()      FLEXCOM5_REGS->FLEX_US_IDR = (FLEX_US_IDR_RXRDY_Msk |  FLEX_US_IDR_OVRE_Msk | FLEX_US_IDR_LIN_FRAME_Msk | FLEX_US_IDR_LIN_PARE_Msk | FLEX_US_IDR_LIN_TIMEOUT_Msk \
                                                            | FLEX_US_IDR_LIN_LINBE_Msk | FLEX_US_IDR_LIN_LINISFE_Msk | FLEX_US_IDR_LIN_LINIPE_Msk \
                                                            | FLEX_US_IDR_LIN_LINCE_Msk | FLEX_US_IDR_LIN_LINSNRE_Msk | FLEX_US_IDR_LIN_LINSTE_Msk | FLEX_US_IDR_LIN_LINHTE_Msk)

/* Enable Read, Overrun, Parity and Framing error interrupts */
#define FLEXCOM5_USART_RX_INT_ENABLE()       FLEXCOM5_REGS->FLEX_US_IER = (FLEX_US_IER_RXRDY_Msk | FLEX_US_IER_OVRE_Msk | FLEX_US_IER_LIN_FRAME_Msk | FLEX_US_IER_LIN_PARE_Msk | FLEX_US_IER_LIN_TIMEOUT_Msk \
                                                            | FLEX_US_IER_LIN_LINBE_Msk | FLEX_US_IER_LIN_LINISFE_Msk | FLEX_US_IER_LIN_LINIPE_Msk \
                                                            | FLEX_US_IER_LIN_LINCE_Msk | FLEX_US_IER_LIN_LINSNRE_Msk | FLEX_US_IER_LIN_LINSTE_Msk | FLEX_US_IER_LIN_LINHTE_Msk)

#define FLEXCOM5_USART_TX_INT_DISABLE()      FLEXCOM5_REGS->FLEX_US_IDR = FLEX_US_IDR_TXRDY_Msk
#define FLEXCOM5_USART_TX_INT_ENABLE()       FLEXCOM5_REGS->FLEX_US_IER = FLEX_US_IER_TXRDY_Msk

#define FLEXCOM5_USART_READ_BUFFER_SIZE             128U
#define FLEXCOM5_USART_9BIT_READ_BUFFER_SIZE        (128U >> 1U)

#define FLEXCOM5_USART_WRITE_BUFFER_SIZE            128U
#define FLEXCOM5_USART_9BIT_WRITE_BUFFER_SIZE       (128U >> 1U)

static volatile uint8_t FLEXCOM5_USART_ReadBuffer[FLEXCOM5_USART_READ_BUFFER_SIZE];
static volatile uint8_t FLEXCOM5_USART_WriteBuffer[FLEXCOM5_USART_WRITE_BUFFER_SIZE];

/* LIN related Interrupts */
#define FLEXCOM5_LIN_LINTC_INT_DISABLE()      FLEXCOM5_REGS->FLEX_US_IDR = FLEX_US_IDR_LIN_LINTC_Msk
#define FLEXCOM5_LIN_LINTC_INT_ENABLE()       FLEXCOM5_REGS->FLEX_US_IER = FLEX_US_IER_LIN_LINTC_Msk

#define FLEXCOM5_LIN_LINID_INT_DISABLE()      FLEXCOM5_REGS->FLEX_US_IDR = FLEX_US_IDR_LIN_LINID_Msk
#define FLEXCOM5_LIN_LINID_INT_ENABLE()       FLEXCOM5_REGS->FLEX_US_IER = FLEX_US_IER_LIN_LINID_Msk

#define FLEXCOM5_LIN_LINBK_INT_DISABLE()      FLEXCOM5_REGS->FLEX_US_IDR = FLEX_US_IDR_LIN_LINBK_Msk
#define FLEXCOM5_LIN_LINBK_INT_ENABLE()       FLEXCOM5_REGS->FLEX_US_IER = FLEX_US_IER_LIN_LINBK_Msk

static volatile FLEXCOM_LIN_CALLBACK_OBJECT flexcom5LinObj;

// *****************************************************************************
// *****************************************************************************
// Section: FLEXCOM5 USART Ring Buffer Implementation
// *****************************************************************************
// *****************************************************************************

static volatile FLEXCOM_USART_RING_BUFFER_OBJECT flexcom5UsartObj;

void FLEXCOM5_USART_Initialize( void )
{
    /* Set FLEXCOM USART operating mode */
    FLEXCOM5_REGS->FLEX_MR = FLEX_MR_OPMODE_USART;

    /* Reset FLEXCOM5 USART */
    FLEXCOM5_REGS->FLEX_US_CR = (FLEX_US_CR_RSTRX_Msk | FLEX_US_CR_RSTTX_Msk | FLEX_US_CR_RSTSTA_Msk);

    /* Enable FLEXCOM5 USART */
    FLEXCOM5_REGS->FLEX_US_CR = (FLEX_US_CR_TXEN_Msk | FLEX_US_CR_RXEN_Msk);

    /* Configure FLEXCOM5 USART LIN_MASTER mode */
    FLEXCOM5_REGS->FLEX_US_MR = (FLEX_US_MR_USCLKS_MCK | FLEX_US_MR_CHRL_8_BIT | FLEX_US_MR_PAR_NO | FLEX_US_MR_NBSTOP_1_BIT | FLEX_US_MR_OVER(0));

    /* Write FLEX_US_MR.USART_MODE to select the LIN mode and the client node configuration. */
    /* LIN client node (USART_MODE = 0xB) */
    FLEXCOM5_REGS->FLEX_US_MR |= FLEX_US_MR_USART_MODE_LIN_MASTER;

    /* CHKTYP: Checksum Type: 0 LIN 2.0 enhanced checksum
     * DLM: Data Length Mode: The response data length is defined by the DLC field of this register.
     * DLC: Data Length Control: Defines the response data length if DLM = 0, in that case the response data length is equal to DLC+1 bytes.
     * WKUPTYP: Wake-up Signal Type: Setting the LINWKUP bit in the control register sends a LIN 2.0 wake-up signal. */
    FLEXCOM5_REGS->FLEX_US_LINMR = FLEX_US_LINMR_CHKTYP(0x0U) | FLEX_US_LINMR_DLM(0x0U) | FLEX_US_LINMR_DLC(8U) | FLEX_US_LINMR_WKUPTYP(0x0U);

    /* Write FLEX_US_BRGR.CD and FLEX_US_BRGR.FP to configure the baud rate. */
    FLEXCOM5_REGS->FLEX_US_BRGR = FLEX_US_BRGR_CD(625) | FLEX_US_BRGR_FP(0);

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

    if ((FLEXCOM5_REGS->FLEX_US_MR & FLEX_US_MR_MODE9_Msk) != 0U)
    {
        flexcom5UsartObj.rdBufferSize = FLEXCOM5_USART_9BIT_READ_BUFFER_SIZE;
        flexcom5UsartObj.wrBufferSize = FLEXCOM5_USART_9BIT_WRITE_BUFFER_SIZE;
    }
    else
    {
        flexcom5UsartObj.rdBufferSize = FLEXCOM5_USART_READ_BUFFER_SIZE;
        flexcom5UsartObj.wrBufferSize = FLEXCOM5_USART_WRITE_BUFFER_SIZE;
    }

    /* Enable Read, Overrun, Parity and Framing error interrupts */
    FLEXCOM5_USART_RX_INT_ENABLE();

    /* Enable LIN ID interrupt */
    FLEXCOM5_LIN_LINID_INT_ENABLE();

    /* Enable LIN Transfer Complete interrupt */
    FLEXCOM5_LIN_LINTC_INT_ENABLE();

    /* Enable LIN Break interrupt */
    FLEXCOM5_LIN_LINBK_INT_ENABLE();
}

static void FLEXCOM5_USART_ErrorClear( void )
{
    /* Clear the error flags */
    FLEXCOM5_REGS->FLEX_US_CR = FLEX_US_CR_RSTSTA_Msk;

    /* Flush existing error bytes from the RX FIFO */
    while((FLEXCOM5_REGS->FLEX_US_CSR & FLEX_US_CSR_RXRDY_Msk) != 0U)
    {
        if ((FLEXCOM5_REGS->FLEX_US_MR & FLEX_US_MR_MODE9_Msk) != 0U)
        {
            (void)(FLEXCOM_USART_RHR_9BIT_REG);
        }
        else
        {
            (void)(FLEXCOM_USART_RHR_8BIT_REG);
        }
    }
}

FLEXCOM_USART_ERROR FLEXCOM5_USART_ErrorGet( void )
{
    FLEXCOM_USART_ERROR errors = flexcom5UsartObj.errorStatus;

    flexcom5UsartObj.errorStatus = FLEXCOM_USART_ERROR_NONE;

    /* All errors are cleared, but send the previous error state */
    return errors;
}

static void FLEXCOM5_USART_BaudCalculate(uint32_t srcClkFreq, uint32_t reqBaud, uint8_t overSamp, uint32_t* cd, uint32_t* fp, uint32_t* baudError)
{
    uint32_t actualBaud = 0;

    *cd = srcClkFreq / (reqBaud * 8U * (2U - (uint32_t)overSamp));

    if (*cd > 0U)
    {
        *fp = ((srcClkFreq / (reqBaud * (2U - (uint32_t)overSamp))) - ((*cd) * 8U));
        actualBaud = (srcClkFreq / (((*cd) * 8U) + (*fp))) / (2U - overSamp);
        *baudError = ((100U * actualBaud)/reqBaud) - 100U;
    }
}

bool FLEXCOM5_USART_SerialSetup( FLEXCOM_USART_SERIAL_SETUP *setup, uint32_t srcClkFreq )
{
    uint32_t baud = 0;
    uint32_t overSampVal = 0;
    uint32_t usartMode;
    uint32_t cd0, fp0, cd1, fp1, baudError0, baudError1;
    bool status = false;

    cd0 = fp0 = cd1 = fp1 = baudError0 = baudError1 = 0U;

    if (setup != NULL)
    {
        baud = setup->baudRate;

        if(srcClkFreq == 0U)
        {
            srcClkFreq = FLEXCOM5_USART_FrequencyGet();
        }

        /* Calculate baud register values for 8x/16x oversampling values */

        FLEXCOM5_USART_BaudCalculate(srcClkFreq, baud, 0, &cd0, &fp0, &baudError0);
        FLEXCOM5_USART_BaudCalculate(srcClkFreq, baud, 1, &cd1, &fp1, &baudError1);

        if ( (!(cd0 > 0U && cd0 <= 65535U)) && (!(cd1 > 0U && cd1 <= 65535U)) )
        {
            /* Requested baud cannot be generated with current clock settings */
            return status;
        }

        if ( ((cd0 > 0U) && (cd0 <= 65535U)) && ((cd1 > 0U) && (cd1 <= 65535U)) )
        {
            /* Requested baud can be generated with both 8x and 16x oversampling. Select the one with less % error. */
            if (baudError1 < baudError0)
            {
                cd0 = cd1;
                fp0 = fp1;
                overSampVal = (1UL << FLEX_US_MR_OVER_Pos) & FLEX_US_MR_OVER_Msk;
            }
        }
        else
        {
            /* Requested baud can be generated with either with 8x oversampling or with 16x oversampling. Select valid one. */
            if ((cd1 > 0U) && (cd1 <= 65535U))
            {
                cd0 = cd1;
                fp0 = fp1;
                overSampVal = (1UL << FLEX_US_MR_OVER_Pos) & FLEX_US_MR_OVER_Msk;
            }
        }

        /* Configure FLEXCOM5 USART mode */
        usartMode = FLEXCOM5_REGS->FLEX_US_MR;
        usartMode &= ~(FLEX_US_MR_CHRL_Msk | FLEX_US_MR_MODE9_Msk | FLEX_US_MR_PAR_Msk | FLEX_US_MR_NBSTOP_Msk | FLEX_US_MR_OVER_Msk);
        FLEXCOM5_REGS->FLEX_US_MR = usartMode | ((uint32_t)setup->dataWidth | (uint32_t)setup->parity | (uint32_t)setup->stopBits | overSampVal);

        /* Configure FLEXCOM5 USART Baud Rate */
        FLEXCOM5_REGS->FLEX_US_BRGR = FLEX_US_BRGR_CD(cd0) | FLEX_US_BRGR_FP(fp0);

        if ((FLEXCOM5_REGS->FLEX_US_MR & FLEX_US_MR_MODE9_Msk) != 0U)
        {
            flexcom5UsartObj.rdBufferSize = FLEXCOM5_USART_9BIT_READ_BUFFER_SIZE;
            flexcom5UsartObj.wrBufferSize = FLEXCOM5_USART_9BIT_WRITE_BUFFER_SIZE;
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
static bool FLEXCOM5_USART_TxPullByte(void* pWrData)
{
    bool isSuccess = false;
    uint32_t wrOutIndex = flexcom5UsartObj.wrOutIndex;
    uint32_t wrInIndex = flexcom5UsartObj.wrInIndex;
    uint8_t* pWrByte = (uint8_t*)pWrData;
    if (wrOutIndex != wrInIndex)
    {
        if ((FLEXCOM5_REGS->FLEX_US_MR & FLEX_US_MR_MODE9_Msk) != 0U)
        {
            uint32_t wrOutIdx = wrOutIndex << 1U;
            pWrByte[0] = FLEXCOM5_USART_WriteBuffer[wrOutIdx];
            pWrByte[1] = FLEXCOM5_USART_WriteBuffer[wrOutIdx + 1U];
        }
        else
        {
            *pWrByte = FLEXCOM5_USART_WriteBuffer[wrOutIndex];
        }
        wrOutIndex++;

        if (wrOutIndex >= flexcom5UsartObj.wrBufferSize)
        {
            wrOutIndex = 0U;
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

    tempInIndex = wrInIndex + 1U;
    if (tempInIndex >= flexcom5UsartObj.wrBufferSize)
    {
        tempInIndex = 0U;
    }
    if (tempInIndex != wrOutIndex)
    {
        if ((FLEXCOM5_REGS->FLEX_US_MR & FLEX_US_MR_MODE9_Msk) != 0U)
        {
            uint32_t wrInIdx = wrInIndex << 1U;
            FLEXCOM5_USART_WriteBuffer[wrInIdx] = (uint8_t)wrByte;
            FLEXCOM5_USART_WriteBuffer[wrInIdx + 1U] = (uint8_t)(wrByte >> 8U);
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
static void FLEXCOM5_USART_SendWriteNotification(void)
{
    uint32_t nFreeWrBufferCount;

    if (flexcom5UsartObj.isWrNotificationEnabled == true)
    {
        nFreeWrBufferCount = FLEXCOM5_USART_WriteFreeBufferCountGet();

        if(flexcom5UsartObj.wrCallback != NULL)
        {
            uintptr_t wrContext = flexcom5UsartObj.wrContext;

            if (flexcom5UsartObj.isWrNotifyPersistently == true)
            {
                if (nFreeWrBufferCount >= flexcom5UsartObj.wrThreshold)
                {
                    flexcom5UsartObj.wrCallback(FLEXCOM_USART_EVENT_WRITE_THRESHOLD_REACHED, wrContext);
                }
            }
            else
            {
                if (nFreeWrBufferCount == flexcom5UsartObj.wrThreshold)
                {
                    flexcom5UsartObj.wrCallback(FLEXCOM_USART_EVENT_WRITE_THRESHOLD_REACHED, wrContext);
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
        if ((FLEXCOM5_REGS->FLEX_US_MR & FLEX_US_MR_MODE9_Msk) != 0U)
        {
            uint16_t halfWordData = (uint16_t)(pWrBuffer[(2U * nBytesWritten) + 1U]);
            halfWordData <<= 8U;
            halfWordData |= (uint16_t)pWrBuffer[2U * nBytesWritten];
            if (FLEXCOM5_USART_TxPushByte(halfWordData) == true)
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
    if (FLEXCOM5_USART_WritePendingBytesGet() > 0U)
    {
        /* Enable TX interrupt as data is pending for transmission */
        FLEXCOM5_USART_TX_INT_ENABLE();
    }

    return nBytesWritten;
}

size_t FLEXCOM5_USART_WriteFreeBufferCountGet(void)
{
    return (flexcom5UsartObj.wrBufferSize - 1U) - FLEXCOM5_USART_WriteCountGet();
}

size_t FLEXCOM5_USART_WriteBufferSizeGet(void)
{
    return (flexcom5UsartObj.wrBufferSize - 1U);
}

bool FLEXCOM5_USART_TransmitComplete(void)
{
    bool status = false;

    if ((FLEXCOM5_REGS->FLEX_US_CSR & FLEX_US_CSR_TXEMPTY_Msk) != 0U)
    {
        status = true;
    }

    return status;
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
    if (nBytesThreshold > 0U)
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

    tempInIndex = flexcom5UsartObj.rdInIndex + 1U;

    if (tempInIndex >= flexcom5UsartObj.rdBufferSize)
    {
        tempInIndex = 0U;
    }

    if (tempInIndex == flexcom5UsartObj.rdOutIndex)
    {
        /* Queue is full - Report it to the application. Application gets a chance to free up space by reading data out from the RX ring buffer */
        if(flexcom5UsartObj.rdCallback != NULL)
        {
            uintptr_t rdContext = flexcom5UsartObj.rdContext;

            flexcom5UsartObj.rdCallback(FLEXCOM_USART_EVENT_READ_BUFFER_FULL, rdContext);

            /* Read the indices again in case application has freed up space in RX ring buffer */
            tempInIndex = flexcom5UsartObj.rdInIndex + 1U;

            if (tempInIndex >= flexcom5UsartObj.rdBufferSize)
            {
                tempInIndex = 0U;
            }
        }
    }

    /* Attempt to push the data into the ring buffer */
    if (tempInIndex != flexcom5UsartObj.rdOutIndex)
    {
        uint32_t rdInIdx;

        if ((FLEXCOM5_REGS->FLEX_US_MR & FLEX_US_MR_MODE9_Msk) != 0U)
        {
            rdInIdx = flexcom5UsartObj.rdInIndex << 1U;
            FLEXCOM5_USART_ReadBuffer[rdInIdx] = (uint8_t)rdByte;
            FLEXCOM5_USART_ReadBuffer[rdInIdx + 1U] = (uint8_t)(rdByte >> 8U);
        }
        else
        {
            rdInIdx = flexcom5UsartObj.rdInIndex;
            FLEXCOM5_USART_ReadBuffer[rdInIdx] = (uint8_t)rdByte;
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
static void FLEXCOM5_USART_SendReadNotification(void)
{
    uint32_t nUnreadBytesAvailable;

    if (flexcom5UsartObj.isRdNotificationEnabled == true)
    {
        nUnreadBytesAvailable = FLEXCOM5_USART_ReadCountGet();

        if(flexcom5UsartObj.rdCallback != NULL)
        {
            uintptr_t rdContext = flexcom5UsartObj.rdContext;

            if (flexcom5UsartObj.isRdNotifyPersistently == true)
            {
                if (nUnreadBytesAvailable >= flexcom5UsartObj.rdThreshold)
                {
                    flexcom5UsartObj.rdCallback(FLEXCOM_USART_EVENT_READ_THRESHOLD_REACHED, rdContext);
                }
            }
            else
            {
                if (nUnreadBytesAvailable == flexcom5UsartObj.rdThreshold)
                {
                    flexcom5UsartObj.rdCallback(FLEXCOM_USART_EVENT_READ_THRESHOLD_REACHED, rdContext);
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
            if ((FLEXCOM5_REGS->FLEX_US_MR & FLEX_US_MR_MODE9_Msk) != 0U)
            {
                uint32_t rdOutIdx = rdOutIndex << 1U;
                uint32_t nBytesReadIdx = nBytesRead << 1U;
                pRdBuffer[nBytesReadIdx] = FLEXCOM5_USART_ReadBuffer[rdOutIdx];
                pRdBuffer[nBytesReadIdx + 1U] = FLEXCOM5_USART_ReadBuffer[rdOutIdx + 1U];
                nBytesRead++;
                rdOutIndex++;
            }
            else
            {
                pRdBuffer[nBytesRead++] = FLEXCOM5_USART_ReadBuffer[rdOutIndex];
                rdOutIndex++;
            }

            if (rdOutIndex >= flexcom5UsartObj.rdBufferSize)
            {
                rdOutIndex = 0U;
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
    return (flexcom5UsartObj.rdBufferSize - 1U) - FLEXCOM5_USART_ReadCountGet();
}

size_t FLEXCOM5_USART_ReadBufferSizeGet(void)
{
    return (flexcom5UsartObj.rdBufferSize - 1U);
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
    if (nBytesThreshold > 0U)
    {
        flexcom5UsartObj.rdThreshold = nBytesThreshold;

    }
}

void FLEXCOM5_USART_ReadCallbackRegister( FLEXCOM_USART_RING_BUFFER_CALLBACK callback, uintptr_t context)
{
    flexcom5UsartObj.rdCallback = callback;

    flexcom5UsartObj.rdContext = context;
}

static void __attribute__((used)) FLEXCOM5_USART_ISR_RX_Handler( void )
{
    uint16_t rdData = 0;

    /* Keep reading until there is a character availabe in the RX FIFO */
    while(FLEX_US_CSR_RXRDY_Msk == (FLEXCOM5_REGS->FLEX_US_CSR & FLEX_US_CSR_RXRDY_Msk))
    {
        if ((FLEXCOM5_REGS->FLEX_US_MR & FLEX_US_MR_MODE9_Msk) != 0U)
        {
            rdData = FLEXCOM_USART_RHR_9BIT_REG & (uint16_t)FLEX_US_RHR_RXCHR_Msk;
        }
        else
        {
            rdData = (uint8_t)FLEXCOM_USART_RHR_8BIT_REG;
        }

        if (FLEXCOM5_USART_RxPushByte( rdData ) == true)
        {
            FLEXCOM5_USART_SendReadNotification();
        }
        else
        {
            /* UART RX buffer is full */
        }
    }


}

static void __attribute__((used)) FLEXCOM5_USART_ISR_TX_Handler( void )
{
    uint16_t wrByte;

    /* Keep writing to the TX FIFO as long as there is space */
    while(FLEX_US_CSR_TXRDY_Msk == (FLEXCOM5_REGS->FLEX_US_CSR & FLEX_US_CSR_TXRDY_Msk))
    {
        if (FLEXCOM5_USART_TxPullByte(&wrByte) == true)
        {
            if ((FLEXCOM5_REGS->FLEX_US_MR & FLEX_US_MR_MODE9_Msk) != 0U)
            {
                FLEXCOM_USART_THR_9BIT_REG = wrByte & (uint16_t)FLEX_US_THR_TXCHR_Msk;
            }
            else
            {
                FLEXCOM_USART_THR_8BIT_REG = (uint8_t)wrByte;
            }

            /* Send notification */
            FLEXCOM5_USART_SendWriteNotification();
        }
        else
        {
            /* Nothing to transmit. Disable the data register empty interrupt. */
            FLEXCOM5_USART_TX_INT_DISABLE();
            break;
        }
    }

}

void __attribute__((used)) FLEXCOM5_InterruptHandler( void )
{
    /* Channel status */
    uint32_t channelStatus = FLEXCOM5_REGS->FLEX_US_CSR;

    /* Error status */
    uint32_t errorStatus = (channelStatus & (FLEX_US_CSR_OVRE_Msk | FLEX_US_CSR_LIN_FRAME_Msk | FLEX_US_CSR_LIN_PARE_Msk | FLEX_US_CSR_LIN_TIMEOUT_Msk
                                           | FLEX_US_CSR_LIN_LINBE_Msk | FLEX_US_CSR_LIN_LINISFE_Msk | FLEX_US_CSR_LIN_LINIPE_Msk
                                           | FLEX_US_CSR_LIN_LINCE_Msk | FLEX_US_CSR_LIN_LINSNRE_Msk | FLEX_US_CSR_LIN_LINSTE_Msk | FLEX_US_CSR_LIN_LINHTE_Msk));


    if(errorStatus != 0U)
    {
        /* Save the error so that it can be reported when application calls the FLEXCOM5_USART_ErrorGet() API */
        flexcom5UsartObj.errorStatus = (FLEXCOM_USART_ERROR)errorStatus;

        /* Clear the error flags and flush out the error bytes */
        FLEXCOM5_USART_ErrorClear();

        /* USART errors are normally associated with the receiver, hence calling receiver context */
        if( flexcom5UsartObj.rdCallback != NULL )
        {
            uintptr_t rdContext = flexcom5UsartObj.rdContext;

            flexcom5UsartObj.rdCallback(FLEXCOM_USART_EVENT_READ_ERROR, rdContext);
        }
    }

    /* Receiver status. RX interrupt is never disabled. */
    if ((channelStatus & FLEX_US_CSR_RXRDY_Msk) != 0U)
    {
        FLEXCOM5_USART_ISR_RX_Handler();
    }

    /* Transmitter status */
    if( ((channelStatus & FLEX_US_CSR_TXRDY_Msk) != 0U) && ((FLEXCOM5_REGS->FLEX_US_IMR & FLEX_US_IMR_TXRDY_Msk) != 0U) )
    {
        FLEXCOM5_USART_ISR_TX_Handler();
    }

    /* LIN Break Detected */
    if((FLEXCOM5_REGS->FLEX_US_CSR & FLEX_US_CSR_LIN_LINBK_Msk) != 0U)
    {
        FLEXCOM5_REGS->FLEX_US_CR = FLEX_US_CR_RSTSTA_Msk;

        if( flexcom5LinObj.breakCallback != NULL)
        {
            uintptr_t breakContext = flexcom5LinObj.breakContext;
            flexcom5LinObj.breakCallback(breakContext);
        }
    }

    /* LIN ID Receive */
    if((FLEXCOM5_REGS->FLEX_US_CSR & FLEX_US_CSR_LIN_LINID_Msk) != 0U)
    {
        /* Clear the status register */
        FLEXCOM5_REGS->FLEX_US_CR = FLEX_US_CR_RSTSTA_Msk;

        /* Check if the ID callback function is set */
        if( flexcom5LinObj.idCallback != NULL)
        {
            /* Retrieve the context for the ID callback */
            uintptr_t idContext = flexcom5LinObj.idContext;
            /* Check if the ID callback function is set */
            flexcom5LinObj.idCallback(idContext);
        }
    }

    /* LIN Transfer Complete */
    if((FLEXCOM5_REGS->FLEX_US_CSR & FLEX_US_CSR_LIN_LINTC_Msk) != 0U)
    {
        /* Clear the status register */
        FLEXCOM5_REGS->FLEX_US_CR = FLEX_US_CR_RSTSTA_Msk;

        /* Check if the transfer callback function is set */
        if( flexcom5LinObj.tranferCallback != NULL)
        {
            /* Retrieve the context for the transfer callback */
            uintptr_t transferContext = flexcom5LinObj.tranferContext;
            /* Call the transfer callback function with the context */
            flexcom5LinObj.tranferCallback(transferContext);
        }
    }
}

/* Sets the LIN (Local Interconnect Network) node action for FLEXCOM5. */
void FLEXCOM5_LIN_NodeActionSet( FLEXCOM_LIN_NACT action )
{
    /* Clear the current node action bits in the LIN Mode Register (LINMR). */
    FLEXCOM5_REGS->FLEX_US_LINMR &= ~(FLEX_US_LINMR_NACT_Msk);
    /* Set the new node action by applying the provided action value. */
    FLEXCOM5_REGS->FLEX_US_LINMR |= FLEX_US_LINMR_NACT(action);
}

/* Writes an identifier to the LIN Identifier Register (LINIR) of FLEXCOM5. */
bool FLEXCOM5_LIN_IdentifierWrite( uint8_t id)
{
    bool status = false;

    /* Reset the status bits in the Control Register (CR). */
    FLEXCOM5_REGS->FLEX_US_CR = FLEX_US_CR_RSTSTA_Msk;

    /* Check if the Transmit Ready (TXRDY) flag is set in the Channel Status Register (CSR). */
    if((FLEXCOM5_REGS->FLEX_US_CSR & FLEX_US_CSR_TXRDY_Msk) != 0U)
    {
        /* If TXRDY is set, write the identifier to the LIN Identifier Register (LINIR). */
        FLEXCOM5_REGS->FLEX_US_LINIR = id;
        /* Set the status to true indicating the identifier was successfully written. */
        status = true;
    }

    return status;
}

/* Reads and returns the LIN identifier from the FLEXCOM5 register. */
uint8_t FLEXCOM5_LIN_IdentifierRead(void)
{
    return (uint8_t)(FLEXCOM5_REGS->FLEX_US_LINIR);
}

/* Enables or disables the parity check for LIN communication. */
void FLEXCOM5_LIN_ParityEnable(bool parityEnable)
{
    if(parityEnable == true)
    {
        /* Clear the PARDIS bit to enable parity. */
        FLEXCOM5_REGS->FLEX_US_LINMR &= ~FLEX_US_LINMR_PARDIS_Msk;
    }
    else
    {
        /* Set the PARDIS bit to disable parity. */
        FLEXCOM5_REGS->FLEX_US_LINMR |= FLEX_US_LINMR_PARDIS_Msk;
    }
}

/* Enables or disables the checksum for LIN communication. */
void FLEXCOM5_LIN_ChecksumEnable(bool checksumEnable)
{
    if(checksumEnable == true)
    {
        /* Clear the CHKDIS bit to enable checksum. */
        FLEXCOM5_REGS->FLEX_US_LINMR &= ~FLEX_US_LINMR_CHKDIS_Msk;
    }
    else
    {
        /* Set the CHKDIS bit to disable checksum. */
        FLEXCOM5_REGS->FLEX_US_LINMR |= FLEX_US_LINMR_CHKDIS_Msk;
    }
}

/* Sets the type of checksum to be used in LIN communication. */
void FLEXCOM5_LIN_ChecksumTypeSet(FLEXCOM_LIN_CHECKSUM_TYPE checksumType)
{
    /* Clear Existing Checksum Type */
    FLEXCOM5_REGS->FLEX_US_LINMR &= ~FLEX_US_LINMR_CHKTYP_Msk;
    /* Set New Checksum Type */
    FLEXCOM5_REGS->FLEX_US_LINMR |= (uint32_t)checksumType;
}

/* Enables or disables the frame slot for LIN communication. */
void FLEXCOM5_LIN_FrameSlotEnable(bool frameSlotEnable)
{
    if(frameSlotEnable == true)
    {
        /* Clear the FSDIS bit to enable frame slot. */
        FLEXCOM5_REGS->FLEX_US_LINMR &= ~FLEX_US_LINMR_FSDIS_Msk;
    }
    else
    {
        /* Set the FSDIS bit to disable frame slot. */
        FLEXCOM5_REGS->FLEX_US_LINMR |= FLEX_US_LINMR_FSDIS_Msk;
    }
}

/* Sets the data length mode for LIN communication. */
void FLEXCOM5_LIN_DataLenModeSet(FLEXCOM_LIN_DATA_LEN dataLenMode)
{
    FLEXCOM5_REGS->FLEX_US_LINMR &= ~FLEX_US_LINMR_DLM_Msk;
    FLEXCOM5_REGS->FLEX_US_LINMR |= (uint32_t)dataLenMode;
}

/* Sets the response data length for LIN communication. */
void FLEXCOM5_LIN_ResponseDataLenSet(uint8_t len)
{
    FLEXCOM5_REGS->FLEX_US_LINMR &= ~FLEX_US_LINMR_DLC_Msk;
    FLEXCOM5_REGS->FLEX_US_LINMR |= FLEX_US_LINMR_DLC((uint32_t)len-1U);
}

/* Checks if the LIN transfer is complete and returns the status. */
/* If a LIN transfer has completed, it returns 1; otherwise, it returns 0. */
uint8_t FLEXCOM5_LIN_TransferComplete(void)
{
    /* Check if the LIN transfer complete status bit is set in the status register */
    return (uint8_t)((FLEXCOM5_REGS->FLEX_US_CSR & FLEX_US_CSR_LIN_LINTC_Msk) > 0U);
}

/* Registers a callback for LIN identifier events. */
void FLEXCOM5_LINIdCallbackRegister(FLEXCOM_LIN_CALLBACK callback, uintptr_t context)
{
    flexcom5LinObj.idCallback = callback;
    flexcom5LinObj.idContext = context;
}

/* Registers a callback for LIN transfer complete events. */
void FLEXCOM5_LINTcCallbackRegister(FLEXCOM_LIN_CALLBACK callback, uintptr_t context)
{
    flexcom5LinObj.tranferCallback = callback;
    flexcom5LinObj.tranferContext = context;
}

/* Registers a callback for LIN break events. */
void FLEXCOM5_LINBreakCallbackRegister(FLEXCOM_LIN_CALLBACK callback, uintptr_t context)
{
    flexcom5LinObj.breakCallback = callback;
    flexcom5LinObj.breakContext = context;
}
