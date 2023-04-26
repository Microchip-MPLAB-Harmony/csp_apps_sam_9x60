/*******************************************************************************
  CAN Peripheral Library Interface Header File

  Company
    Microchip Technology Inc.

  File Name
    plib_can_common.h

  Summary
    CAN peripheral library interface.

  Description
    This file defines the interface to the CAN peripheral library. This
    library provides access to and control of the associated peripheral
    instance.

  Remarks:

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

#ifndef PLIB_CAN_COMMON_H
#define PLIB_CAN_COMMON_H

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif
// DOM-IGNORE-END
/* CAN Interrupt Mask

   Summary:
    CAN Interrupt Mask.

   Description:
    This data type defines the CAN Interrupt sources number.

   Remarks:
    None.
*/

#define    CAN_INTERRUPT_MB0_MASK    (1U << 0U)
#define    CAN_INTERRUPT_MB1_MASK    (1U << 1U)
#define    CAN_INTERRUPT_MB2_MASK    (1U << 2U)
#define    CAN_INTERRUPT_MB3_MASK    (1U << 3U)
#define    CAN_INTERRUPT_MB4_MASK    (1U << 4U)
#define    CAN_INTERRUPT_MB5_MASK    (1U << 5U)
#define    CAN_INTERRUPT_MB6_MASK    (1U << 6U)
#define    CAN_INTERRUPT_MB7_MASK    (1U << 7U)
#define    CAN_INTERRUPT_ERRA_MASK   (1U << 16U)
#define    CAN_INTERRUPT_WARN_MASK   (1U << 17U)
#define    CAN_INTERRUPT_ERRP_MASK   (1U << 18U)
#define    CAN_INTERRUPT_BOFF_MASK   (1U << 19U)
#define    CAN_INTERRUPT_SLEEP_MASK  (1U << 20U)
#define    CAN_INTERRUPT_WAKEUP_MASK (1U << 21U)
#define    CAN_INTERRUPT_TOVF_MASK   (1U << 22U)
#define    CAN_INTERRUPT_TSTP_MASK   (1U << 23U)
#define    CAN_INTERRUPT_CERR_MASK   (1U << 24U)
#define    CAN_INTERRUPT_SERR_MASK   (1U << 25U)
#define    CAN_INTERRUPT_AERR_MASK   (1U << 26U)
#define    CAN_INTERRUPT_FERR_MASK   (1U << 27U)
#define    CAN_INTERRUPT_BERR_MASK   (1U << 28U)
typedef uint32_t CAN_INTERRUPT_MASK;

// *****************************************************************************
/* CAN Mailbox Object Type RX Attribute

   Summary:
    CAN Mailbox RX Attribute for Reception Mailbox, Reception Mailbox
    with overwrite, Consumer Rx Mailbox and Producer Rx Mailbox.

   Description:
    This data type defines CAN Mailbox RX Attribute. Only One attribute
    need to be passed as parameter value while invoking message receive function.

   Remarks:
    None.
*/

#define    CAN_MAILBOX_DATA_FRAME_RX            (0U)
#define    CAN_MAILBOX_DATA_FRAME_RX_OVERWRITE  (1U)
#define    CAN_MAILBOX_DATA_FRAME_CONSUMER      (2U)
typedef uint8_t CAN_MAILBOX_RX_ATTRIBUTE;

// *****************************************************************************
// *****************************************************************************
/* CAN Mailbox Object Type TX Attribute

   Summary:
    CAN Mailbox TX Attribute for Transmit mailbox, Producer Tx Mailbox and
    Consumer Tx Mailbox.

   Description:
    This data type defines CAN Mailbox TX Attribute. Only One attribute
    need to be passed as parameter value while invoking message transmit function.

   Remarks:
    None.
*/
typedef enum
{
    CAN_MAILBOX_DATA_FRAME_TX = 0,
    CAN_MAILBOX_DATA_FRAME_PRODUCER,
    CAN_MAILBOX_REMOTE_FRAME_CONSUMER
} CAN_MAILBOX_TX_ATTRIBUTE;
// *****************************************************************************
/* CAN Message Object Type RX Attribute

   Summary:
    CAN Message RX Attribute for Data Frame and Remote Frame.

   Description:
    This data type defines CAN Message RX Attribute for Data Frame and Remote Frame.

   Remarks:
    None.
*/
typedef enum
{
    CAN_MSG_RX_DATA_FRAME = 0,
    CAN_MSG_RX_REMOTE_FRAME
} CAN_MSG_RX_ATTRIBUTE;

// *****************************************************************************
/* CAN Mailbox Number

   Summary:
    CAN Mailbox Number.

   Description:
    This data type defines CAN Mailbox Number 0 to 7.

   Remarks:
    None.
*/
typedef enum
{
    CAN_MAILBOX_0 = 0,
    CAN_MAILBOX_1,
    CAN_MAILBOX_2,
    CAN_MAILBOX_3,
    CAN_MAILBOX_4,
    CAN_MAILBOX_5,
    CAN_MAILBOX_6,
    CAN_MAILBOX_7
} CAN_MAILBOX_NUM;

// *****************************************************************************
/* CAN Mailbox Mask

   Summary:
    CAN Mailbox Mask.

   Description:
    This data type defines CAN Mailbox mask.

   Remarks:
    None.
*/

#define    CAN_MAILBOX_0_MASK   (1U << 0U)
#define    CAN_MAILBOX_1_MASK   (1U << 1U)
#define    CAN_MAILBOX_2_MASK   (1U << 2U)
#define    CAN_MAILBOX_3_MASK   (1U << 3U)
#define    CAN_MAILBOX_4_MASK   (1U << 4U)
#define    CAN_MAILBOX_5_MASK   (1U << 5U)
#define    CAN_MAILBOX_6_MASK   (1U << 6U)
#define    CAN_MAILBOX_7_MASK   (1U << 7U)
typedef uint32_t CAN_MAILBOX_MASK;

/* CAN Mailbox State.

   Summary:
    CAN Mailbox State.

   Description:
    This data type defines the CAN Mailbox State.
    CAN_MAILBOX_READY - Mailbox is available for Tx/Rx transfer request.
    CAN_MAILBOX_BUSY  - Mailbox is not available for Tx/Rx transfer request
                        as Mailbox is in busy state due to previous transfer request.

   Remarks:
    None.

*/

#define    CAN_MAILBOX_READY    (0)
#define    CAN_MAILBOX_BUSY     (1)
typedef int32_t CAN_MAILBOX_STATE;

// *****************************************************************************

// *****************************************************************************
/* CAN Transfer Error

   Summary:
    CAN Transfer Error data type.

   Description:
    This data type defines the CAN Transfer Error.

   Remarks:
    None.
*/

#define    CAN_ERROR_NONE     (0x0U)
#define    CAN_ERROR_BOFF     (1U << 19U)
#define    CAN_ERROR_CERR     (1U << 24U)
#define    CAN_ERROR_SERR     (1U << 25U)
#define    CAN_ERROR_AERR     (1U << 26U)
#define    CAN_ERROR_FERR     (1U << 27U)
#define    CAN_ERROR_BERR     (1U << 28U)
typedef uint32_t CAN_ERROR;

// *****************************************************************************

/* CAN Callback

   Summary:
    CAN Callback Function Pointer.

   Description:
    This data type defines the CAN Callback Function Pointer.

   Remarks:
    None.
*/
typedef void (*CAN_CALLBACK) (uintptr_t contextHandle);

// *****************************************************************************
/* CAN PLib Instance Object

   Summary:
    CAN PLib Object structure.

   Description:
    This data structure defines the CAN PLib Instance Object.

   Remarks:
    None.
*/
typedef struct
{
    /* Rx Message ID, buffer, size, timestamp and attribute */
    uint32_t             *id;
    uint8_t              *buffer;
    uint8_t              *size;
    uint16_t             *timestamp;
    CAN_MSG_RX_ATTRIBUTE *msgAttr;
} CAN_RX_MSG;

// *****************************************************************************
/* CAN Nominal Bit Timing Parameters

   Summary:
    CAN Nominal Bit Timing Parameter structure.

   Description:
    This data structure defines Nominal Bit Timing Parameters.

   Remarks:
    None.
*/
typedef struct
{
    /* Phase 2 Segment */
    uint8_t phase2Segment;

    /* Phase 1 Segment */
    uint8_t phase1Segment;

    /* Propagation Segment */
    uint8_t propagationSegment;

    /* Baud Rate Prescaler */
    uint8_t Prescaler;

    /* Syncronization Jump Width */
    uint8_t sjw;

} CAN_NOMINAL_BIT_TIMING;

// *****************************************************************************
/* CAN Bit Timing Parameters

   Summary:
    CAN Bit Timing Parameter structure.

   Description:
    This data structure defines Bit Timing Parameters.

   Remarks:
    None.
*/
typedef struct
{
    /* Nominal bit timing set flag */
    bool nominalBitTimingSet;

    /* Nominal bit timing parameters */
    CAN_NOMINAL_BIT_TIMING nominalBitTiming;

} CAN_BIT_TIMING;

// *****************************************************************************
/* CAN Bit Timing Setup

   Summary:
    CAN Bit Timing Setup structure.

   Description:
    This data structure defines Bit Timing Setup parameters.

   Remarks:
    None.
*/
typedef struct
{
    /* Nominal bit timing set flag */
    bool nominalBitTimingSet;

    /* Nominal bit rate */
    uint32_t nominalBitRate;

    /* Nominal Sample Point */
    float nominalSamplePoint;

    /* Nominal Propagation Segment Time (ns) */
    uint32_t nominalPropagTime;

    /* Nominal Baud Rate Prescaler */
    uint8_t nominalPrescaler;

} CAN_BIT_TIMING_SETUP;


// *****************************************************************************
/* CAN Mailbox Callback

   Summary:
    CAN transfer event callback structure.

   Description:
    This data structure stores transfer event callback and it's context.

   Remarks:
    None.
*/
typedef struct
{
    /* Transfer Event Callback */
    CAN_CALLBACK callback;

    /* Transfer Event Callback Context */
    uintptr_t context;
} CAN_MAILBOX_CALLBACK;

// *****************************************************************************
/* CAN PLib Instance Object

   Summary:
    CAN PLib Object structure.

   Description:
    This data structure defines the CAN PLib Instance Object.

   Remarks:
    None.
*/
typedef struct
{
    /* Rx Messages */
    CAN_RX_MSG rxMsg[CAN_MB_NUMBER];

    /* CAN Mailbox State */
    CAN_MAILBOX_STATE mbState[CAN_MB_NUMBER];

    /* Transfer Event Callback Object */
    CAN_MAILBOX_CALLBACK mbCallback[CAN_MB_NUMBER];

    /* CAN Error Status */
    uint32_t errorStatus;

} CAN_OBJ;

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
}
#endif
// DOM-IGNORE-END

#endif //PLIB_CAN_COMMON_H
