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
#include <string.h>

typedef struct
{
    uint32_t scsr;
    uint32_t pcsr0;
    uint32_t pcsr1;
    uint32_t cpu_ckr;
    uint32_t mor;
} CLOCK_CFG;
  
__attribute__((__section__(".ramdata_section"))) CLOCK_CFG clock_cfg;
__attribute__((__section__(".ramdata_section"))) int tmp_stack[256];

static void enter_idle(void);
static void ramcode_init(void);
void enter_idle_sram(void);
void enter_ulp0(void);
void enter_ulp0_sram(void);
void really_enter_ulp0_sram(void);


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************
void pit_callback(uintptr_t context)
{
    int *timer_count = (int *)context;
    (*timer_count)++;
    if (*timer_count == 5) {
        LED_BLUE_Toggle();
        *timer_count = 0;
    }
}

void print_menu(void)
{
    printf(" ------------------------------------------\r\n"
            " Select an option :\r\n"
            " 0 -> Enter Idle mode\r\n"
            " 1 -> Enter Ultra Low Power mode 0\r\n"
            " =>");

}

int main ( void )
{
    char c = 0;
    int timer_count = 0;
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    
    PIT64B_TimerCallbackSet(pit_callback, (uintptr_t)&timer_count);
    PIT64B_TimerStart();
    ramcode_init();

    while ( true )
    {
        print_menu();
        DBGU_Read(&c, 1);
        switch (c) {
            case '0':
                printf("\r\n");
                enter_idle();
                break;
            case '1':
                printf("\r\n");
                enter_ulp0();
                break;
            default:
                printf("\r\n");
        }
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}

extern uint32_t _ramcode_lma, _sramcode, _eramcode;
extern uint32_t _ramdata_lma, _sramdata, _eramdata;   

static void ramcode_init(void)
{
	memcpy(&_sramcode, &_ramcode_lma, (uint32_t)&_eramcode - (uint32_t)&_sramcode);
	memcpy(&_sramdata, &_ramdata_lma, (uint32_t)&_eramdata - (uint32_t)&_sramdata);
    DCACHE_CLEAN_INVALIDATE_ALL();
    L1_ICACHE_INVALIDATE_ALL();
}

void enter_idle(void)
{
    struct tm time;
    /* configure RTC alarm */
    RTC_TimeGet(&time);
    if (time.tm_sec < 30) {
        time.tm_sec += 30;
    } else {
        time.tm_sec += 30;
        time.tm_sec = time.tm_sec % 60;
    }
    RTC_AlarmSet(&time, RTC_ALARM_MASK_SS);
    RTC_InterruptEnable(RTC_INT_ALARM);

    /* disbale PIT since we don't want it as a wake-up source */
    PIT64B_TimerStop();
    
    printf(" ------------------------------------------\r\n"
           "Entering Idle Mode for 30 seconds\r\n");

    enter_idle_sram();
    
    printf(" ------------------------------------------\r\n"
           "Leaving Idle Mode\r\n");

    /* enable PIT */
    PIT64B_TimerStart();
    /* disable RTC alarm */
    RTC_InterruptDisable(RTC_INT_ALARM);
}

__attribute__((__section__(".ramcode_section"))) void enter_idle_sram(void)
{
  
    PMC_REGS->PMC_SCDR = PMC_SCDR_PCK_Msk;
 
    asm("mcr p15, 0, %0, c7, c0, 4" :: "r"(0));
}

void enter_ulp0(void)
{
    struct tm time;
    /* configure RTC alarm */
    RTC_TimeGet(&time);
    time.tm_sec += 30;
    time.tm_sec %= 60;
    RTC_AlarmSet(&time, RTC_ALARM_MASK_SS);
    RTC_InterruptEnable(RTC_INT_ALARM);

    /* disbale PIT since we don't want it as a wake-up source */
    PIT64B_TimerStop();
    
    printf(" ------------------------------------------\r\n"
           "Entering ULP0 Mode for 30 seconds\r\n");

    enter_ulp0_sram();


    DBGU_Initialize();
    
    printf(" ------------------------------------------\r\n"
           "Leaving ULP0 Mode\r\n");

    /* enable PIT */
    PIT64B_TimerStart();
    /* disable RTC alarm */
    RTC_InterruptDisable(RTC_INT_ALARM);

}

__attribute__((__section__(".ramcode_section"))) void enter_ulp0_sram(void)
{
    /* set up new stack in sram since ddr will be unavailable */
    uint32_t sp = (uint32_t)&tmp_stack[256];
    asm("mov r3, %0" : : "r"(sp));
    asm("mov r0, sp");
    asm("mov sp, r3");
    asm("push {r0}");

    /* broken up like this so we can use stack variables */
    really_enter_ulp0_sram();


    /* use original ddr based stack */
    asm("pop {r0}");
    asm("mov sp, r0");
}

__attribute__((__section__(".ramcode_section")))void really_enter_ulp0_sram(void)
{
    clock_cfg.scsr = PMC_REGS->PMC_SCSR;
    clock_cfg.cpu_ckr = PMC_REGS->PMC_CPU_CKR;
    clock_cfg.mor = PMC_REGS->CKGR_MOR;
    
    /* set DDR in self-refresh mode */
    MPDDRC_REGS->MPDDRC_LPR = (MPDDRC_REGS->MPDDRC_LPR & ~MPDDRC_LPR_LPCB_Msk) | MPDDRC_LPR_LPCB_SELFREFRESH;
    while (!(MPDDRC_REGS->MPDDRC_LPR & MPDDRC_LPR_SELF_DONE_Msk));
 
    /* disable all unused peripheral clocks */
    PMC_REGS->PMC_SCDR = 0xFFFFFFFF;    
    
    /* switch to slow clock */
    PMC_REGS->PMC_CPU_CKR = (PMC_REGS->PMC_CPU_CKR & ~PMC_CPU_CKR_CSS_Msk) | PMC_CPU_CKR_CSS_SLOW_CLK;
    while (!(PMC_REGS->PMC_SR & PMC_SR_MCKRDY_Msk));
    
    /* disable main clock */
    PMC_REGS->CKGR_MOR &= ~(CKGR_MOR_MOSCXTEN_Msk | CKGR_MOR_MOSCRCEN_Msk) | CKGR_MOR_KEY_PASSWD;
    
    /* enter ULP0 */
    __disable_irq();
    __DSB();
    asm("mcr p15, 0, %0, c7, c0, 4" :: "r"(0));

    /* enable main clock */
    PMC_REGS->CKGR_MOR = clock_cfg.mor |  CKGR_MOR_KEY_PASSWD;
    if (clock_cfg.mor & CKGR_MOR_MOSCSEL_Msk)
        while (!(PMC_REGS->PMC_SR & PMC_SR_MOSCXTS_Msk));

    /* wait for pll lock */
    while (!(PMC_REGS->PMC_PLL_ISR0 & PMC_PLL_ISR0_LOCKA_Msk));
    
    /* switch master clock to pll */
    PMC_REGS->PMC_CPU_CKR = clock_cfg.cpu_ckr;
    while (!(PMC_REGS->PMC_SR & PMC_SR_MCKRDY_Msk));


    PMC_REGS->PMC_SCER = clock_cfg.scsr;
    __enable_irq();
}