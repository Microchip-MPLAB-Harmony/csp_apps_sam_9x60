/*******************************************************************************
  Controller Area Network (CAN) Peripheral Library Source File

  Company:
    Microchip Technology Inc.

  File Name:
    plib_can1.c

  Summary:
    CAN peripheral library interface.

  Description:
    This file defines the interface to the CAN peripheral library. This
    library provides access to and control of the associated peripheral
    instance.

  Remarks:
    None.
*******************************************************************************/

//DOM-IGNORE-BEGIN
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
//DOM-IGNORE-END
// *****************************************************************************
// *****************************************************************************
// Header Includes
// *****************************************************************************
// *****************************************************************************

#include "plib_can1.h"
#include "interrupts.h"

// *****************************************************************************
// *****************************************************************************
// Global Data
// *****************************************************************************
// *****************************************************************************

#define BYTE_MASK  (0xFFU)
static const uint32_t can_mb_number = CAN_MB_NUMBER;

// *****************************************************************************
// *****************************************************************************
// CAN1 PLib Interface Routines
// *****************************************************************************
// *****************************************************************************
// *****************************************************************************
/* Function:
    void CAN1_Initialize(void)

   Summary:
    Initializes given instance of the CAN peripheral.

   Precondition:
    None.

   Parameters:
    None.

   Returns:
    None
*/
void CAN1_Initialize(void)
{
    /* Disable CAN Controller */
    CAN1_REGS->CAN_MR &= ~CAN_MR_CANEN_Msk;

    /* Set CAN Baudrate */
    CAN1_REGS->CAN_BR  = CAN_BR_PHASE2(3) | CAN_BR_PHASE1(7) |
                                         CAN_BR_PROPAG(2) | CAN_BR_BRP(24) |
                                         CAN_BR_SJW(3);

    /* Configure Mailbox */
    CAN1_REGS->CAN_IDR = CAN_IDR_MB0_Msk;
    CAN1_REGS->CAN_MB[0].CAN_MCR = 0;
    CAN1_REGS->CAN_MB[0].CAN_MMR = CAN_MMR_MOT_MB_TX;
    CAN1_REGS->CAN_IDR = CAN_IDR_MB1_Msk;
    CAN1_REGS->CAN_MB[1].CAN_MCR = 0;
    CAN1_REGS->CAN_MB[1].CAN_MID = CAN_MID_MIDvA(0) | CAN_MID_MIDE_Msk;
    CAN1_REGS->CAN_MB[1].CAN_MAM = CAN_MAM_MIDvA(0);
    CAN1_REGS->CAN_MB[1].CAN_MMR = CAN_MMR_MOT_MB_RX_OVERWRITE;
    CAN1_REGS->CAN_IDR = CAN_IDR_MB2_Msk;
    CAN1_REGS->CAN_MB[2].CAN_MCR = 0;
    CAN1_REGS->CAN_MB[2].CAN_MMR = CAN_MMR_MOT_MB_DISABLED;
    CAN1_REGS->CAN_IDR = CAN_IDR_MB3_Msk;
    CAN1_REGS->CAN_MB[3].CAN_MCR = 0;
    CAN1_REGS->CAN_MB[3].CAN_MMR = CAN_MMR_MOT_MB_DISABLED;
    CAN1_REGS->CAN_IDR = CAN_IDR_MB4_Msk;
    CAN1_REGS->CAN_MB[4].CAN_MCR = 0;
    CAN1_REGS->CAN_MB[4].CAN_MMR = CAN_MMR_MOT_MB_DISABLED;
    CAN1_REGS->CAN_IDR = CAN_IDR_MB5_Msk;
    CAN1_REGS->CAN_MB[5].CAN_MCR = 0;
    CAN1_REGS->CAN_MB[5].CAN_MMR = CAN_MMR_MOT_MB_DISABLED;
    CAN1_REGS->CAN_IDR = CAN_IDR_MB6_Msk;
    CAN1_REGS->CAN_MB[6].CAN_MCR = 0;
    CAN1_REGS->CAN_MB[6].CAN_MMR = CAN_MMR_MOT_MB_DISABLED;
    CAN1_REGS->CAN_IDR = CAN_IDR_MB7_Msk;
    CAN1_REGS->CAN_MB[7].CAN_MCR = 0;
    CAN1_REGS->CAN_MB[7].CAN_MMR = CAN_MMR_MOT_MB_DISABLED;

    /* Enable Timestamp */
    CAN1_REGS->CAN_MR &= ~CAN_MR_TTM_Msk;

    /* Enable CAN Controller */
    CAN1_REGS->CAN_MR |= CAN_MR_CANEN_Msk;
}

// *****************************************************************************
/* Function:
    bool CAN1_MessageTransmit(uint32_t id, uint8_t length, uint8_t* data, CAN_MAILBOX_TX_ATTRIBUTE mailboxAttr)

   Summary:
    Transmits a message into CAN bus.

   Precondition:
    CAN1_Initialize must have been called for the associated CAN instance.

   Parameters:
    id          - 11-bit / 29-bit identifier (ID).
    length      - length of data buffer in number of bytes.
    data        - pointer to source data buffer
    mailboxAttr - Mailbox type TX Mailbox or Consumer Mailbox or Producer Mailbox

   Returns:
    Request status.
    true  - Request was successful.
    false - Request has failed.
*/

/* MISRA C-2012 Rule 16.1, 16.3 and 16.6 deviated below. Deviation record ID -
   H3_MISRAC_2012_R_16_1_DR_1, H3_MISRAC_2012_R_16_3_DR_1 & H3_MISRAC_2012_R_16_6_DR_1*/

bool CAN1_MessageTransmit(uint32_t id, uint8_t length, uint8_t* data, CAN_MAILBOX_TX_ATTRIBUTE mailboxAttr)
{
    uint8_t mailbox = 0;
    bool mbIsReady = false;
    uint8_t dataIndex = 0;
    bool status = false;

    for (mailbox = 0U; mailbox < can_mb_number; mailbox++)
    {
        switch (CAN1_REGS->CAN_MB[mailbox].CAN_MMR & CAN_MMR_MOT_Msk)
        {
            case CAN_MMR_MOT_MB_TX:
                if ((mailboxAttr == CAN_MAILBOX_DATA_FRAME_TX) &&
                   ((CAN1_REGS->CAN_MB[mailbox].CAN_MSR & CAN_MSR_MRDY_Msk) == CAN_MSR_MRDY_Msk))
                {
                    mbIsReady = true;
                }
                break;
            case CAN_MMR_MOT_MB_PRODUCER:
                if ((mailboxAttr == CAN_MAILBOX_DATA_FRAME_PRODUCER) &&
                   ((CAN1_REGS->CAN_MB[mailbox].CAN_MSR & CAN_MSR_MRDY_Msk) == CAN_MSR_MRDY_Msk))
                {
                    mbIsReady = true;
                }
                break;
            case CAN_MMR_MOT_MB_CONSUMER:
                if (mailboxAttr == CAN_MAILBOX_REMOTE_FRAME_CONSUMER)
                {
                    mbIsReady = true;
                }
                break;
            default:
                     /* Do Nothing */
                break;
        }
        if (mbIsReady)
        {
            break;
        }
    }

    if (!mbIsReady)
    {
        return status;
    }

    /* If the id is longer than 11 bits, it is considered as extended identifier */
    if (id > (CAN_MID_MIDvA_Msk >> CAN_MID_MIDvA_Pos))
    {
        /* An extended identifier is stored into ID */
        CAN1_REGS->CAN_MB[mailbox].CAN_MID = (id & CAN_MFID_Msk) | CAN_MID_MIDE_Msk;
    }
    else
    {
        /* A standard identifier is stored into MID[28:18] */
        CAN1_REGS->CAN_MB[mailbox].CAN_MID = CAN_MID_MIDvA(id);
    }

    /* Limit length */
    if (length > 8U)
    {
        length = 8U;
    }
    CAN1_REGS->CAN_MB[mailbox].CAN_MCR = CAN_MCR_MDLC(length);

    switch (mailboxAttr)
    {
        case CAN_MAILBOX_DATA_FRAME_TX:
        case CAN_MAILBOX_DATA_FRAME_PRODUCER:
            /* Copy the data into the payload */
            for (; dataIndex < length; dataIndex++)
            {
                if (dataIndex == 0U)
                {
                    CAN1_REGS->CAN_MB[mailbox].CAN_MDL = data[dataIndex];
                }
                else if (dataIndex < 4U)
                {
                    CAN1_REGS->CAN_MB[mailbox].CAN_MDL |= ((uint32_t)data[dataIndex] << (8U * dataIndex));
                }
                else if (dataIndex == 4U)
                {
                    CAN1_REGS->CAN_MB[mailbox].CAN_MDH = data[dataIndex];
                }
                else
                {
                    CAN1_REGS->CAN_MB[mailbox].CAN_MDH |= ((uint32_t)data[dataIndex] << (8U * (dataIndex - 4U)));
                }
            }
            status = true;
            break;
        case CAN_MAILBOX_REMOTE_FRAME_CONSUMER:
            status = true;
            break;
        default:
            return status;
    }

    /* Request the transmit */
    CAN1_REGS->CAN_TCR = 1UL << mailbox;
    return status;
}

// *****************************************************************************
/* Function:
    bool CAN1_MessageReceive(uint32_t *id, uint8_t *length, uint8_t *data, uint16_t *timestamp,
                                             CAN_MAILBOX_RX_ATTRIBUTE mailboxAttr, CAN_MSG_RX_ATTRIBUTE *msgAttr)

   Summary:
    Receives a message from CAN bus.

   Precondition:
    CAN1_Initialize must have been called for the associated CAN instance.

   Parameters:
    id          - Pointer to 11-bit / 29-bit identifier (ID) to be received.
    length      - Pointer to data length in number of bytes to be received.
    data        - pointer to destination data buffer
    timestamp   - Pointer to Rx message timestamp
    mailboxAttr - Mailbox type either RX Mailbox or RX Mailbox with overwrite
    msgAttr     - Data frame or Remote frame to be received

   Returns:
    Request status.
    true  - Request was successful.
    false - Request has failed.
*/
bool CAN1_MessageReceive(uint32_t *id, uint8_t *length, uint8_t *data, uint16_t *timestamp,
                                         CAN_MAILBOX_RX_ATTRIBUTE mailboxAttr, CAN_MSG_RX_ATTRIBUTE *msgAttr)
{
    uint8_t mailbox = 0;
    bool mbIsReady = false;
    uint8_t dataIndex = 0;
    bool status = false;
    for (mailbox = 0U; mailbox < can_mb_number; mailbox++)
    {
        if ((CAN1_REGS->CAN_MB[mailbox].CAN_MSR & CAN_MSR_MRDY_Msk) != CAN_MSR_MRDY_Msk)
        {
            continue;
        }

        switch (CAN1_REGS->CAN_MB[mailbox].CAN_MMR & CAN_MMR_MOT_Msk)
        {
            case CAN_MMR_MOT_MB_RX:
                if (mailboxAttr == CAN_MAILBOX_DATA_FRAME_RX)
                {
                    mbIsReady = true;
                }
                break;
            case CAN_MMR_MOT_MB_RX_OVERWRITE:
                if (mailboxAttr == CAN_MAILBOX_DATA_FRAME_RX_OVERWRITE)
                {
                    mbIsReady = true;
                }
                break;
            case CAN_MMR_MOT_MB_CONSUMER:
                if (mailboxAttr == CAN_MAILBOX_DATA_FRAME_CONSUMER)
                {
                    mbIsReady = true;
                }
                break;
            default:
                      /* Do Nothing */
                break;
        }
        if (mbIsReady)
        {
            break;
        }
    }

    if (!mbIsReady)
    {
        return status;
    }

    switch (mailboxAttr)
    {
        case CAN_MAILBOX_DATA_FRAME_RX:
        case CAN_MAILBOX_DATA_FRAME_RX_OVERWRITE:
        case CAN_MAILBOX_DATA_FRAME_CONSUMER:
            if ((CAN1_REGS->CAN_MB[mailbox].CAN_MID & CAN_MID_MIDE_Msk) == CAN_MID_MIDE_Msk)
            {
                *id = CAN1_REGS->CAN_MB[mailbox].CAN_MID & CAN_MFID_Msk;
            }
            else
            {
                *id = (CAN1_REGS->CAN_MB[mailbox].CAN_MID & CAN_MID_MIDvA_Msk) >> CAN_MID_MIDvA_Pos;
            }

            if (((CAN1_REGS->CAN_MB[mailbox].CAN_MSR & CAN_MSR_MRTR_Msk) != 0U) &&
               (mailboxAttr != CAN_MAILBOX_DATA_FRAME_CONSUMER))
            {
                *msgAttr = CAN_MSG_RX_REMOTE_FRAME;
            }
            else
            {
                *msgAttr = CAN_MSG_RX_DATA_FRAME;
            }

            *length = (uint8_t)((CAN1_REGS->CAN_MB[mailbox].CAN_MSR & CAN_MSR_MDLC_Msk) >> CAN_MSR_MDLC_Pos);
            /* Copy the data into the payload */
            for (; dataIndex < *length; dataIndex++)
            {
                if (dataIndex == 0U)
                {
                    data[dataIndex] = (uint8_t)(CAN1_REGS->CAN_MB[mailbox].CAN_MDL & BYTE_MASK);
                }
                else if (dataIndex < 4U)
                {
                    data[dataIndex] = (uint8_t)((CAN1_REGS->CAN_MB[mailbox].CAN_MDL >> (8U * dataIndex)) & BYTE_MASK);
                }
                else if (dataIndex == 4U)
                {
                    data[dataIndex] = (uint8_t)(CAN1_REGS->CAN_MB[mailbox].CAN_MDH & BYTE_MASK);
                }
                else
                {
                    data[dataIndex] = (uint8_t)((CAN1_REGS->CAN_MB[mailbox].CAN_MDH >> (8U * (dataIndex - 4U))) & BYTE_MASK);
                }
            }

            /* Get timestamp from received message */
            if (timestamp != NULL)
            {
                *timestamp = (uint16_t)(CAN1_REGS->CAN_MB[mailbox].CAN_MSR & CAN_MSR_MTIMESTAMP_Msk);
            }

            CAN1_REGS->CAN_MB[mailbox].CAN_MCR = CAN_MCR_MTCR_Msk;
            status = true;
            break;
        default:
            return status;
    }
    return status;
}

/* MISRAC 2012 deviation block end */

// *****************************************************************************
/* Function:
    void CAN1_MessageAbort(CAN_MAILBOX_MASK mailboxMask)

   Summary:
    Abort request for a Mailbox.

   Precondition:
    CAN1_Initialize must have been called for the associated CAN instance.

   Parameters:
    mailboxMask - Mailbox mask

   Returns:
    None.
*/
void CAN1_MessageAbort(CAN_MAILBOX_MASK mailboxMask)
{
    CAN1_REGS->CAN_ACR = mailboxMask;
}

// *****************************************************************************
/* Function:
    void CAN1_MessageIDSet(CAN_MAILBOX_NUM mailbox, uint32_t id)

   Summary:
    Set Message ID in mailbox.

   Precondition:
    CAN1_Initialize must have been called for the associated CAN instance.

   Parameters:
    mailbox - Mailbox number
    id      - 11-bit or 29-bit identifier

   Returns:
    None.
*/
void CAN1_MessageIDSet(CAN_MAILBOX_NUM mailbox, uint32_t id)
{
    if (id > (CAN_MID_MIDvA_Msk >> CAN_MID_MIDvA_Pos))
    {
        CAN1_REGS->CAN_MB[mailbox].CAN_MID = (id & CAN_MFID_Msk) | CAN_MID_MIDE_Msk;
    }
    else
    {
        CAN1_REGS->CAN_MB[mailbox].CAN_MID = CAN_MID_MIDvA(id) | CAN_MID_MIDE_Msk;
    }
}

// *****************************************************************************
/* Function:
    uint32_t CAN1_MessageIDGet(CAN_MAILBOX_NUM mailbox)

   Summary:
    Get Message ID from mailbox.

   Precondition:
    CAN1_Initialize must have been called for the associated CAN instance.

   Parameters:
    mailbox - Mailbox number

   Returns:
    Returns Message ID
*/
uint32_t CAN1_MessageIDGet(CAN_MAILBOX_NUM mailbox)
{
    uint32_t id = 0;

    if ((CAN1_REGS->CAN_MB[mailbox].CAN_MID & CAN_MID_MIDvB_Msk) != 0U)
    {
        id = CAN1_REGS->CAN_MB[mailbox].CAN_MID & CAN_MFID_Msk;
    }
    else
    {
        id = (CAN1_REGS->CAN_MB[mailbox].CAN_MID & CAN_MID_MIDvA_Msk) >> CAN_MID_MIDvA_Pos;
    }
    return id;
}

// *****************************************************************************
/* Function:
    void CAN1_MessageAcceptanceMaskSet(CAN_MAILBOX_NUM mailbox, uint32_t id)

   Summary:
    Set Message acceptance identifier mask in mailbox.

   Precondition:
    CAN1_Initialize must have been called for the associated CAN instance.

   Parameters:
    mailbox - Mailbox number
    id      - 11-bit or 29-bit identifier

   Returns:
    None.
*/
void CAN1_MessageAcceptanceMaskSet(CAN_MAILBOX_NUM mailbox, uint32_t id)
{
    if (id > (CAN_MAM_MIDvA_Msk >> CAN_MAM_MIDvA_Pos))
    {
        CAN1_REGS->CAN_MB[mailbox].CAN_MAM = (id & CAN_MFID_Msk) | CAN_MAM_MIDE_Msk;
    }
    else
    {
        CAN1_REGS->CAN_MB[mailbox].CAN_MAM = CAN_MAM_MIDvA(id);
    }
}

// *****************************************************************************
/* Function:
    uint32_t CAN1_MessageAcceptanceMaskGet(CAN_MAILBOX_NUM mailbox)

   Summary:
    Get Message acceptance identifier mask from mailbox.

   Precondition:
    CAN1_Initialize must have been called for the associated CAN instance.

   Parameters:
    mailbox - Mailbox number

   Returns:
    Returns Message acceptance identifier mask
*/
uint32_t CAN1_MessageAcceptanceMaskGet(CAN_MAILBOX_NUM mailbox)
{
    uint32_t id = 0;

    if ((CAN1_REGS->CAN_MB[mailbox].CAN_MAM & CAN_MAM_MIDE_Msk) == CAN_MAM_MIDE_Msk)
    {
        id = CAN1_REGS->CAN_MB[mailbox].CAN_MAM & CAN_MFID_Msk;
    }
    else
    {
        id = (CAN1_REGS->CAN_MB[mailbox].CAN_MAM & CAN_MAM_MIDvA_Msk) >> CAN_MAM_MIDvA_Pos;
    }
    return id;
}

// *****************************************************************************
/* Function:
    uint16_t CAN1_MessageTimestampGet(CAN_MAILBOX_NUM mailbox)

   Summary:
    Get the message timestamp from a mailbox.

   Precondition:
    CAN1_Initialize must have been called for the associated CAN instance.

   Parameters:
    mailbox - Mailbox number

   Returns:
    Returns the message timestamp from a mailbox.
*/
uint16_t CAN1_MessageTimestampGet(CAN_MAILBOX_NUM mailbox)
{
    return (uint16_t)(CAN1_REGS->CAN_MB[mailbox].CAN_MSR & CAN_MSR_MTIMESTAMP_Msk);
}

// *****************************************************************************
/* Function:
    CAN_ERROR CAN1_ErrorGet(void)

   Summary:
    Returns the error during transfer.

   Precondition:
    CAN1_Initialize must have been called for the associated CAN instance.

   Parameters:
    None.

   Returns:
    Error during transfer.
*/
CAN_ERROR CAN1_ErrorGet(void)
{
    CAN_ERROR error = CAN_ERROR_NONE;
    uint32_t errorStatus = CAN1_REGS->CAN_SR;

    /* Check if error occurred */
    error = (CAN_ERROR)((errorStatus & CAN_SR_BOFF_Msk) |
                        (errorStatus & CAN_SR_CERR_Msk) |
                        (errorStatus & CAN_SR_SERR_Msk) |
                        (errorStatus & CAN_SR_AERR_Msk) |
                        (errorStatus & CAN_SR_FERR_Msk) |
                        (errorStatus & CAN_SR_BERR_Msk));

    if ((errorStatus & CAN_SR_BOFF_Msk) == CAN_SR_BOFF_Msk)
    {
        /* Reset CAN Controller if Bus off */
        CAN1_REGS->CAN_MR &= ~CAN_MR_CANEN_Msk;
        CAN1_REGS->CAN_MR |= CAN_MR_CANEN_Msk;
    }

    return error;
}

// *****************************************************************************
/* Function:
    void CAN1_ErrorCountGet(uint16_t *txErrorCount, uint8_t *rxErrorCount)

   Summary:
    Returns the transmit and receive error count during transfer.

   Precondition:
    CAN1_Initialize must have been called for the associated CAN instance.

   Parameters:
    txErrorCount - Transmit Error Count to be received
    rxErrorCount - Receive Error Count to be received

   Returns:
    None.
*/
void CAN1_ErrorCountGet(uint16_t *txErrorCount, uint8_t *rxErrorCount)
{
    *txErrorCount = (uint16_t)((CAN1_REGS->CAN_ECR & CAN_ECR_TEC_Msk) >> CAN_ECR_TEC_Pos);
    *rxErrorCount = (uint8_t)(CAN1_REGS->CAN_ECR & CAN_ECR_REC_Msk);
}

// *****************************************************************************
/* Function:
    bool CAN1_InterruptGet(CAN_INTERRUPT_MASK interruptMask)

   Summary:
    Returns the Interrupt status.

   Precondition:
    CAN1_Initialize must have been called for the associated CAN instance.

   Parameters:
    interruptMask - Interrupt source number

   Returns:
    true - Requested interrupt is occurred.
    false - Requested interrupt is not occurred.
*/
bool CAN1_InterruptGet(CAN_INTERRUPT_MASK interruptMask)
{
    return ((CAN1_REGS->CAN_SR & interruptMask) != 0x0U);
}

// *****************************************************************************
/* Function:
    void CAN1_InterruptEnable(CAN_INTERRUPT_MASK interruptMask)

   Summary:
    Enables CAN Interrupt.

   Precondition:
    CAN1_Initialize must have been called for the associated CAN instance.

   Parameters:
    interruptMask - Interrupt to be enabled

   Returns:
    None
*/
void CAN1_InterruptEnable(CAN_INTERRUPT_MASK interruptMask)
{
    CAN1_REGS->CAN_IER = interruptMask;
}

// *****************************************************************************
/* Function:
    void CAN1_InterruptDisable(CAN_INTERRUPT_MASK interruptMask)

   Summary:
    Disables CAN Interrupt.

   Precondition:
    CAN1_Initialize must have been called for the associated CAN instance.

   Parameters:
    interruptMask - Interrupt to be disabled

   Returns:
    None
*/
void CAN1_InterruptDisable(CAN_INTERRUPT_MASK interruptMask)
{
    CAN1_REGS->CAN_IDR = interruptMask;
}

// *****************************************************************************
/* Function:
    bool CAN1_MailboxIsReady(CAN_MAILBOX_NUM mailbox)

   Summary:
    Returns true if Mailbox is ready otherwise false.

   Precondition:
    CAN1_Initialize must have been called for the associated CAN instance.

   Parameters:
    mailbox - Mailbox number

   Returns:
    true  - Mailbox is ready and Mailbox data registers can be read/written.
    false - Mailbox is not ready and Mailbox data registers can not be read/written.
*/
bool CAN1_MailboxIsReady(CAN_MAILBOX_NUM mailbox)
{
    return ((CAN1_REGS->CAN_MB[mailbox].CAN_MSR & CAN_MSR_MRDY_Msk) == CAN_MSR_MRDY_Msk);
}

bool CAN1_BitTimingCalculationGet(CAN_BIT_TIMING_SETUP *setup, CAN_BIT_TIMING *bitTiming)
{
    bool status = false;
    uint32_t numOfTimeQuanta;
    uint8_t phase1;
    float temp1;
    float temp2;

    if ((setup != NULL) && (bitTiming != NULL))
    {
        if (setup->nominalBitTimingSet == true)
        {
            numOfTimeQuanta = CAN1_CLOCK_FREQUENCY / (setup->nominalBitRate * ((uint32_t)setup->nominalPrescaler + 1U));
            if ((numOfTimeQuanta >= 8U) && (numOfTimeQuanta <= 25U))
            {
                if (setup->nominalSamplePoint < 50.0f)
                {
                    setup->nominalSamplePoint = 50.0f;
                }
                temp1 = (float)numOfTimeQuanta;
                temp2 = (temp1 * setup->nominalSamplePoint) / 100.0f;
                phase1 = (uint8_t)temp2;
                bitTiming->nominalBitTiming.phase2Segment = (uint8_t)(numOfTimeQuanta - phase1 - 1U);
                /* The propagation segment time is equal to twice the sum of the signal's propagation time on the bus line,
                   the receiver delay and the output driver delay */
                temp2 = (((float)numOfTimeQuanta * ((float)setup->nominalBitRate / 1000.0f) * (float)setup->nominalPropagTime) / 1000000.0f);
                bitTiming->nominalBitTiming.propagationSegment = ((uint8_t)temp2 - 1U);
                bitTiming->nominalBitTiming.phase1Segment = phase1 - (bitTiming->nominalBitTiming.propagationSegment + 1U) - 2U;
                if ((bitTiming->nominalBitTiming.phase2Segment + 1U) > 4U)
                {
                    bitTiming->nominalBitTiming.sjw = 3U;
                }
                else
                {
                    bitTiming->nominalBitTiming.sjw = bitTiming->nominalBitTiming.phase2Segment;
                }
                bitTiming->nominalBitTiming.Prescaler = setup->nominalPrescaler;
                bitTiming->nominalBitTimingSet = true;
                status = true;
            }
            else
            {
                bitTiming->nominalBitTimingSet = false;
            }
        }
    }

    return status;
}

bool CAN1_BitTimingSet(CAN_BIT_TIMING *bitTiming)
{
    bool status = false;

    if ((bitTiming->nominalBitTimingSet == true)
    && (bitTiming->nominalBitTiming.phase1Segment <= 0x7U)
    && (bitTiming->nominalBitTiming.phase2Segment <= 0x7U)
    && (bitTiming->nominalBitTiming.propagationSegment <= 0x7U)
    && ((bitTiming->nominalBitTiming.Prescaler >= 0x1U) && (bitTiming->nominalBitTiming.Prescaler <= 0x7FU))
    && (bitTiming->nominalBitTiming.sjw <= 0x3U))
    {
        /* Disable CAN Controller */
        CAN1_REGS->CAN_MR &= ~CAN_MR_CANEN_Msk;

        /* Set CAN Baudrate */
        CAN1_REGS->CAN_BR  = CAN_BR_PHASE2(bitTiming->nominalBitTiming.phase2Segment) | CAN_BR_PHASE1(bitTiming->nominalBitTiming.phase1Segment) |
                                             CAN_BR_PROPAG(bitTiming->nominalBitTiming.propagationSegment) | CAN_BR_BRP(bitTiming->nominalBitTiming.Prescaler) |
                                             CAN_BR_SJW(bitTiming->nominalBitTiming.sjw);

        /* Enable CAN Controller */
        CAN1_REGS->CAN_MR |= CAN_MR_CANEN_Msk;

        status = true;
    }
    return status;
}

