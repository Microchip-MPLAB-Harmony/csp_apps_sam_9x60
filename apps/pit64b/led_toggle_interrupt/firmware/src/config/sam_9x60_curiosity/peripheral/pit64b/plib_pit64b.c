/*******************************************************************************
  Periodic Interval Timer (PIT64B)

  Company:
    Microchip Technology Inc.

  File Name:
    plib_pit64b.h

  Summary:
    Periodic Interval Timer (PIT64B) PLIB.

  Description:
    This file declares the interface for the Periodic Interval Timer (PIT64B).
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

#include <stddef.h>
#include "plib_pit64b.h"

#define PIT64B_COUNTER_FREQUENCY (200000000U / 1U)

typedef struct
{
    bool running;
    uint32_t periodLSB;
    uint32_t periodMSB;
    PIT64B_CALLBACK callback;
    uintptr_t context;
} PIT64B_OBJECT;


static PIT64B_OBJECT pit64b = 
{
    false,
    100000000U,
    0U,
    NULL,
    0U
};


static inline void PIT64B_PERIOD_SET(uint32_t periodLSB, uint32_t periodMSB)
{
    /* Note: MSBPR should be updated first, as writing into LSBPR while
       SMOD is set will restart the timer */
    PIT64B_REGS->PIT64B_MSBPR = periodMSB;
    PIT64B_REGS->PIT64B_LSBPR = periodLSB;
}


void PIT64B_TimerInitialize(void)
{
    PIT64B_REGS->PIT64B_CR = PIT64B_CR_SWRST_Msk;
    PIT64B_REGS->PIT64B_MR = PIT64B_MR_CONT(1U) | PIT64B_MR_SGCLK(0U) | PIT64B_MR_PRESCALER(0U) | PIT64B_MR_SMOD(0U);
    PIT64B_PERIOD_SET(pit64b.periodLSB, pit64b.periodMSB);

    PIT64B_REGS->PIT64B_IDR = PIT64B_IDR_Msk;
    PIT64B_REGS->PIT64B_IER = PIT64B_IER_PERIOD(1U) | PIT64B_IER_OVRE(0U) | PIT64B_IER_SECE(0U);
}


void PIT64B_TimerRestart(void)
{
    PIT64B_TimerInitialize();
    PIT64B_TimerStart();
}


void PIT64B_TimerStart(void)
{
    PIT64B_REGS->PIT64B_CR = PIT64B_CR_START_Msk;
    pit64b.running = true;
}


void PIT64B_TimerStop(void)
{
    PIT64B_TimerInitialize();
    pit64b.running = false;
}


void PIT64B_TimerPeriodSet(uint64_t period)
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wlong-long"
    pit64b.periodMSB = (uint32_t)((period & 0xFFFFFFFF00000000U) >> 32U);
    pit64b.periodLSB = (uint32_t)(period & 0xFFFFFFFFU);
#pragma GCC diagnostic pop
    PIT64B_PERIOD_SET(pit64b.periodLSB, pit64b.periodMSB);
}


uint64_t PIT64B_TimerPeriodGet(void)
{
    uint64_t reg = PIT64B_REGS->PIT64B_MSBPR;
    reg <<= 32U;
    reg |= PIT64B_REGS->PIT64B_LSBPR;
    return reg;
}


uint64_t PIT64B_TimerCounterGet(void)
{
    uint64_t reg = PIT64B_REGS->PIT64B_TMSBR;
    reg <<= 32U;
    reg |= PIT64B_REGS->PIT64B_TLSBR;
    return reg;
}


uint32_t PIT64B_TimerFrequencyGet(void)
{
    return PIT64B_COUNTER_FREQUENCY;
}


void PIT64B_DelayMs(uint32_t delay_ms)
{
    uint64_t newCount = 0U, deltaCount = 0U, elapsedCount = 0U;
    uint64_t period = PIT64B_TimerPeriodGet() + 1UL;
    uint64_t delayCount = (PIT64B_COUNTER_FREQUENCY / 1000U) * (uint64_t)delay_ms;
    uint64_t oldCount = PIT64B_TimerCounterGet();
    if(pit64b.running)
    {
        while(elapsedCount < delayCount)
        {
            newCount = PIT64B_TimerCounterGet();
            deltaCount = (newCount > oldCount) ? (newCount - oldCount) : (period - oldCount + newCount);
            elapsedCount += deltaCount;
            oldCount = newCount;
        }
    }
}


void PIT64B_DelayUs(uint32_t delay_us)
{
    uint64_t newCount = 0U, deltaCount = 0U, elapsedCount = 0U;
    uint64_t period = PIT64B_TimerPeriodGet() + 1UL;
    uint64_t delayCount = (PIT64B_COUNTER_FREQUENCY / 1000000U) * (uint64_t)delay_us;
    uint64_t oldCount = PIT64B_TimerCounterGet();
    if(pit64b.running)
    {
        while(elapsedCount < delayCount)
        {
            newCount = PIT64B_TimerCounterGet();
            deltaCount = (newCount > oldCount) ? (newCount - oldCount) : (period - oldCount + newCount);
            elapsedCount += deltaCount;
            oldCount = newCount;
        }
    }
}


void PIT64B_TimerCallbackSet(PIT64B_CALLBACK callback, uintptr_t context)
{
    pit64b.callback = callback;
    pit64b.context = context;
}


void PIT64B_InterruptHandler(void)
{
    volatile uint32_t reg = PIT64B_REGS->PIT64B_ISR;
    (void)reg;
    if(pit64b.callback != NULL)
    {
        pit64b.callback(pit64b.context);
    }
}
