/*******************************************************************************
  Periodic Interval Timer (PIT)

  Company:
    Microchip Technology Inc.

  File Name:
    plib_pit.c

  Summary:
    Periodic Interval Timer (PIT) PLIB.

  Description:
    This file defines the interface for the Periodic Interval Timer (PIT).
*******************************************************************************/

// DOM-IGNORE-BEGIN
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
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
#include <stddef.h>
#include "device.h"
#include "plib_pit.h"
#include "interrupts.h"

#define PIT_COUNTER_FREQUENCY       (200000000U / 16U)

// *****************************************************************************
// *****************************************************************************
// Section: File Scope Data Types
// *****************************************************************************
// *****************************************************************************


void PIT_TimerInitialize(void)
{
    PIT_REGS->PIT_PIVR;
    PIT_REGS->PIT_MR = PIT_MR_PIV(624999U) | PIT_MR_PITEN_Msk;
}

void PIT_TimerRestart(void)
{
    PIT_REGS->PIT_MR &= ~PIT_MR_PITEN_Msk;
    while((PIT_REGS->PIT_PIIR & PIT_PIIR_CPIV_Msk) != 0U)
    {
        //do nothing
    }
    PIT_REGS->PIT_MR |= PIT_MR_PITEN_Msk;
}

void PIT_TimerStart(void)
{
    PIT_REGS->PIT_MR |= PIT_MR_PITEN_Msk;
}

void PIT_TimerStop(void)
{
    PIT_REGS->PIT_MR &= ~PIT_MR_PITEN_Msk;
    while ((PIT_REGS->PIT_PIIR & PIT_PIIR_CPIV_Msk) != 0U)
    {
        //do nothing
    }
}

void PIT_TimerPeriodSet(uint32_t period)
{
    PIT_TimerStop();
    PIT_REGS->PIT_MR &= ~PIT_MR_PIV_Msk;
    PIT_REGS->PIT_MR |= PIT_MR_PIV(period);
    PIT_TimerStart();
}

uint32_t PIT_TimerPeriodGet(void)
{
    return PIT_REGS->PIT_MR & PIT_MR_PIV_Msk;
}

uint32_t PIT_TimerCounterGet(void)
{
    return (PIT_REGS->PIT_PIIR & PIT_PIIR_CPIV_Msk) >> PIT_PIIR_CPIV_Pos;
}

void PIT_TimerCompareSet( uint16_t compare )
{
    (void) compare;
}

uint32_t PIT_TimerFrequencyGet(void)
{
    return PIT_COUNTER_FREQUENCY;
}

void PIT_DelayMs(uint32_t delay_ms)
{
    uint32_t period = (PIT_REGS->PIT_MR & PIT_MR_PIV_Msk) + 1U;
    uint32_t delayCount = (PIT_COUNTER_FREQUENCY / 1000U) * delay_ms;
    uint32_t oldCount = PIT_REGS->PIT_PIIR & PIT_PIIR_CPIV_Msk;
    uint32_t newCount = 0U, deltaCount = 0U, elapsedCount = 0U;

    if((PIT_REGS->PIT_MR & PIT_MR_PITEN_Msk) != 0U)
    {
        while(elapsedCount < delayCount)
        {
            newCount = PIT_REGS->PIT_PIIR & PIT_PIIR_CPIV_Msk;
            deltaCount = (newCount > oldCount) ? (newCount - oldCount) : (period - oldCount + newCount);
            elapsedCount += deltaCount;
            oldCount = newCount;
        }
    }
}

void PIT_DelayUs(uint32_t delay_us)
{
    uint32_t period = (PIT_REGS->PIT_MR & PIT_MR_PIV_Msk) + 1U;
    uint32_t delayCount = (PIT_COUNTER_FREQUENCY / 1000000U) * delay_us;
    uint32_t oldCount = PIT_REGS->PIT_PIIR & PIT_PIIR_CPIV_Msk;
    uint32_t newCount = 0U, deltaCount = 0U, elapsedCount = 0U;

    if((PIT_REGS->PIT_MR & PIT_MR_PITEN_Msk) != 0U)
    {
        while(elapsedCount < delayCount)
        {
            newCount = PIT_REGS->PIT_PIIR & PIT_PIIR_CPIV_Msk;
            deltaCount = (newCount > oldCount) ? (newCount - oldCount) : (period - oldCount + newCount);
            elapsedCount += deltaCount;
            oldCount = newCount;
        }
    }
}


bool PIT_TimerPeriodHasExpired(void)
{
    return ((PIT_REGS->PIT_SR & PIT_SR_PITS_Msk) != 0U);
}
/*******************************************************************************
 End of File
*/
