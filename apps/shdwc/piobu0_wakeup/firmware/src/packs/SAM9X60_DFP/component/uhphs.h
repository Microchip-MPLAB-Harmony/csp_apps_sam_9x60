/*
 * Component description for UHPHS
 *
 * Copyright (c) 2022 Microchip Technology Inc. and its subsidiaries.
 *
 * Subject to your compliance with these terms, you may use Microchip software and any derivatives
 * exclusively with Microchip products. It is your responsibility to comply with third party license
 * terms applicable to your use of third party software (including open source software) that may
 * accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY,
 * APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND
 * FITNESS FOR A PARTICULAR PURPOSE.
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF
 * MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT
 * EXCEED THE AMOUNT OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 */

/* file generated from device description version 2022-01-05T08:53:32Z */
#ifndef _SAM9X_UHPHS_COMPONENT_H_
#define _SAM9X_UHPHS_COMPONENT_H_

/* ************************************************************************** */
/*   SOFTWARE API DEFINITION FOR UHPHS                                        */
/* ************************************************************************** */

/* -------- UHPHS_HCCAPBASE : (UHPHS Offset: 0x00) ( R/ 32) UHPHS Host Controller Capability Register -------- */
#define UHPHS_HCCAPBASE_CAPLENGTH_Pos         _UINT32_(0)                                          /* (UHPHS_HCCAPBASE) Capability Registers Length Position */
#define UHPHS_HCCAPBASE_CAPLENGTH_Msk         (_UINT32_(0xFF) << UHPHS_HCCAPBASE_CAPLENGTH_Pos)    /* (UHPHS_HCCAPBASE) Capability Registers Length Mask */
#define UHPHS_HCCAPBASE_CAPLENGTH(value)      (UHPHS_HCCAPBASE_CAPLENGTH_Msk & (_UINT32_(value) << UHPHS_HCCAPBASE_CAPLENGTH_Pos)) /* Assigment of value for CAPLENGTH in the UHPHS_HCCAPBASE register */
#define UHPHS_HCCAPBASE_HCIVERSION_Pos        _UINT32_(16)                                         /* (UHPHS_HCCAPBASE) Host Controller Interface Version Number Position */
#define UHPHS_HCCAPBASE_HCIVERSION_Msk        (_UINT32_(0xFFFF) << UHPHS_HCCAPBASE_HCIVERSION_Pos) /* (UHPHS_HCCAPBASE) Host Controller Interface Version Number Mask */
#define UHPHS_HCCAPBASE_HCIVERSION(value)     (UHPHS_HCCAPBASE_HCIVERSION_Msk & (_UINT32_(value) << UHPHS_HCCAPBASE_HCIVERSION_Pos)) /* Assigment of value for HCIVERSION in the UHPHS_HCCAPBASE register */
#define UHPHS_HCCAPBASE_Msk                   _UINT32_(0xFFFF00FF)                                 /* (UHPHS_HCCAPBASE) Register Mask  */


/* -------- UHPHS_HCSPARAMS : (UHPHS Offset: 0x04) ( R/ 32) UHPHS Host Controller Structural Parameters Register -------- */
#define UHPHS_HCSPARAMS_N_PORTS_Pos           _UINT32_(0)                                          /* (UHPHS_HCSPARAMS) Number of Ports Position */
#define UHPHS_HCSPARAMS_N_PORTS_Msk           (_UINT32_(0xF) << UHPHS_HCSPARAMS_N_PORTS_Pos)       /* (UHPHS_HCSPARAMS) Number of Ports Mask */
#define UHPHS_HCSPARAMS_N_PORTS(value)        (UHPHS_HCSPARAMS_N_PORTS_Msk & (_UINT32_(value) << UHPHS_HCSPARAMS_N_PORTS_Pos)) /* Assigment of value for N_PORTS in the UHPHS_HCSPARAMS register */
#define UHPHS_HCSPARAMS_PPC_Pos               _UINT32_(4)                                          /* (UHPHS_HCSPARAMS) Port Power Control Position */
#define UHPHS_HCSPARAMS_PPC_Msk               (_UINT32_(0x1) << UHPHS_HCSPARAMS_PPC_Pos)           /* (UHPHS_HCSPARAMS) Port Power Control Mask */
#define UHPHS_HCSPARAMS_PPC(value)            (UHPHS_HCSPARAMS_PPC_Msk & (_UINT32_(value) << UHPHS_HCSPARAMS_PPC_Pos)) /* Assigment of value for PPC in the UHPHS_HCSPARAMS register */
#define UHPHS_HCSPARAMS_N_PCC_Pos             _UINT32_(8)                                          /* (UHPHS_HCSPARAMS) Number of Ports per Companion Controller Position */
#define UHPHS_HCSPARAMS_N_PCC_Msk             (_UINT32_(0xF) << UHPHS_HCSPARAMS_N_PCC_Pos)         /* (UHPHS_HCSPARAMS) Number of Ports per Companion Controller Mask */
#define UHPHS_HCSPARAMS_N_PCC(value)          (UHPHS_HCSPARAMS_N_PCC_Msk & (_UINT32_(value) << UHPHS_HCSPARAMS_N_PCC_Pos)) /* Assigment of value for N_PCC in the UHPHS_HCSPARAMS register */
#define UHPHS_HCSPARAMS_N_CC_Pos              _UINT32_(12)                                         /* (UHPHS_HCSPARAMS) Number of Companion Controllers Position */
#define UHPHS_HCSPARAMS_N_CC_Msk              (_UINT32_(0xF) << UHPHS_HCSPARAMS_N_CC_Pos)          /* (UHPHS_HCSPARAMS) Number of Companion Controllers Mask */
#define UHPHS_HCSPARAMS_N_CC(value)           (UHPHS_HCSPARAMS_N_CC_Msk & (_UINT32_(value) << UHPHS_HCSPARAMS_N_CC_Pos)) /* Assigment of value for N_CC in the UHPHS_HCSPARAMS register */
#define UHPHS_HCSPARAMS_P_INDICATOR_Pos       _UINT32_(16)                                         /* (UHPHS_HCSPARAMS) Port Indicators Position */
#define UHPHS_HCSPARAMS_P_INDICATOR_Msk       (_UINT32_(0x1) << UHPHS_HCSPARAMS_P_INDICATOR_Pos)   /* (UHPHS_HCSPARAMS) Port Indicators Mask */
#define UHPHS_HCSPARAMS_P_INDICATOR(value)    (UHPHS_HCSPARAMS_P_INDICATOR_Msk & (_UINT32_(value) << UHPHS_HCSPARAMS_P_INDICATOR_Pos)) /* Assigment of value for P_INDICATOR in the UHPHS_HCSPARAMS register */
#define UHPHS_HCSPARAMS_N_DP_Pos              _UINT32_(20)                                         /* (UHPHS_HCSPARAMS) Debug Port Number Position */
#define UHPHS_HCSPARAMS_N_DP_Msk              (_UINT32_(0xF) << UHPHS_HCSPARAMS_N_DP_Pos)          /* (UHPHS_HCSPARAMS) Debug Port Number Mask */
#define UHPHS_HCSPARAMS_N_DP(value)           (UHPHS_HCSPARAMS_N_DP_Msk & (_UINT32_(value) << UHPHS_HCSPARAMS_N_DP_Pos)) /* Assigment of value for N_DP in the UHPHS_HCSPARAMS register */
#define UHPHS_HCSPARAMS_Msk                   _UINT32_(0x00F1FF1F)                                 /* (UHPHS_HCSPARAMS) Register Mask  */


/* -------- UHPHS_HCCPARAMS : (UHPHS Offset: 0x08) ( R/ 32) UHPHS Host Controller Capability Parameters Register -------- */
#define UHPHS_HCCPARAMS_AC_Pos                _UINT32_(0)                                          /* (UHPHS_HCCPARAMS) 64-bit Addressing Capability Position */
#define UHPHS_HCCPARAMS_AC_Msk                (_UINT32_(0x1) << UHPHS_HCCPARAMS_AC_Pos)            /* (UHPHS_HCCPARAMS) 64-bit Addressing Capability Mask */
#define UHPHS_HCCPARAMS_AC(value)             (UHPHS_HCCPARAMS_AC_Msk & (_UINT32_(value) << UHPHS_HCCPARAMS_AC_Pos)) /* Assigment of value for AC in the UHPHS_HCCPARAMS register */
#define UHPHS_HCCPARAMS_PFLF_Pos              _UINT32_(1)                                          /* (UHPHS_HCCPARAMS) Programmable Frame List Flag Position */
#define UHPHS_HCCPARAMS_PFLF_Msk              (_UINT32_(0x1) << UHPHS_HCCPARAMS_PFLF_Pos)          /* (UHPHS_HCCPARAMS) Programmable Frame List Flag Mask */
#define UHPHS_HCCPARAMS_PFLF(value)           (UHPHS_HCCPARAMS_PFLF_Msk & (_UINT32_(value) << UHPHS_HCCPARAMS_PFLF_Pos)) /* Assigment of value for PFLF in the UHPHS_HCCPARAMS register */
#define UHPHS_HCCPARAMS_ASPC_Pos              _UINT32_(2)                                          /* (UHPHS_HCCPARAMS) Asynchronous Schedule Park Capability Position */
#define UHPHS_HCCPARAMS_ASPC_Msk              (_UINT32_(0x1) << UHPHS_HCCPARAMS_ASPC_Pos)          /* (UHPHS_HCCPARAMS) Asynchronous Schedule Park Capability Mask */
#define UHPHS_HCCPARAMS_ASPC(value)           (UHPHS_HCCPARAMS_ASPC_Msk & (_UINT32_(value) << UHPHS_HCCPARAMS_ASPC_Pos)) /* Assigment of value for ASPC in the UHPHS_HCCPARAMS register */
#define UHPHS_HCCPARAMS_IST_Pos               _UINT32_(4)                                          /* (UHPHS_HCCPARAMS) Isochronous Scheduling Threshold Position */
#define UHPHS_HCCPARAMS_IST_Msk               (_UINT32_(0xF) << UHPHS_HCCPARAMS_IST_Pos)           /* (UHPHS_HCCPARAMS) Isochronous Scheduling Threshold Mask */
#define UHPHS_HCCPARAMS_IST(value)            (UHPHS_HCCPARAMS_IST_Msk & (_UINT32_(value) << UHPHS_HCCPARAMS_IST_Pos)) /* Assigment of value for IST in the UHPHS_HCCPARAMS register */
#define UHPHS_HCCPARAMS_EECP_Pos              _UINT32_(8)                                          /* (UHPHS_HCCPARAMS) EHCI Extended Capabilities Pointer Position */
#define UHPHS_HCCPARAMS_EECP_Msk              (_UINT32_(0xFF) << UHPHS_HCCPARAMS_EECP_Pos)         /* (UHPHS_HCCPARAMS) EHCI Extended Capabilities Pointer Mask */
#define UHPHS_HCCPARAMS_EECP(value)           (UHPHS_HCCPARAMS_EECP_Msk & (_UINT32_(value) << UHPHS_HCCPARAMS_EECP_Pos)) /* Assigment of value for EECP in the UHPHS_HCCPARAMS register */
#define UHPHS_HCCPARAMS_Msk                   _UINT32_(0x0000FFF7)                                 /* (UHPHS_HCCPARAMS) Register Mask  */


/* -------- UHPHS_USBCMD : (UHPHS Offset: 0x10) (R/W 32) UHPHS USB Command Register -------- */
#define UHPHS_USBCMD_RS_Pos                   _UINT32_(0)                                          /* (UHPHS_USBCMD) Run/Stop (read/write) Position */
#define UHPHS_USBCMD_RS_Msk                   (_UINT32_(0x1) << UHPHS_USBCMD_RS_Pos)               /* (UHPHS_USBCMD) Run/Stop (read/write) Mask */
#define UHPHS_USBCMD_RS(value)                (UHPHS_USBCMD_RS_Msk & (_UINT32_(value) << UHPHS_USBCMD_RS_Pos)) /* Assigment of value for RS in the UHPHS_USBCMD register */
#define UHPHS_USBCMD_HCRESET_Pos              _UINT32_(1)                                          /* (UHPHS_USBCMD) Host Controller Reset (read/write) Position */
#define UHPHS_USBCMD_HCRESET_Msk              (_UINT32_(0x1) << UHPHS_USBCMD_HCRESET_Pos)          /* (UHPHS_USBCMD) Host Controller Reset (read/write) Mask */
#define UHPHS_USBCMD_HCRESET(value)           (UHPHS_USBCMD_HCRESET_Msk & (_UINT32_(value) << UHPHS_USBCMD_HCRESET_Pos)) /* Assigment of value for HCRESET in the UHPHS_USBCMD register */
#define UHPHS_USBCMD_FLS_Pos                  _UINT32_(2)                                          /* (UHPHS_USBCMD) Frame List Size (read/write or read-only) Position */
#define UHPHS_USBCMD_FLS_Msk                  (_UINT32_(0x3) << UHPHS_USBCMD_FLS_Pos)              /* (UHPHS_USBCMD) Frame List Size (read/write or read-only) Mask */
#define UHPHS_USBCMD_FLS(value)               (UHPHS_USBCMD_FLS_Msk & (_UINT32_(value) << UHPHS_USBCMD_FLS_Pos)) /* Assigment of value for FLS in the UHPHS_USBCMD register */
#define UHPHS_USBCMD_PSE_Pos                  _UINT32_(4)                                          /* (UHPHS_USBCMD) Periodic Schedule Enable (read/write) Position */
#define UHPHS_USBCMD_PSE_Msk                  (_UINT32_(0x1) << UHPHS_USBCMD_PSE_Pos)              /* (UHPHS_USBCMD) Periodic Schedule Enable (read/write) Mask */
#define UHPHS_USBCMD_PSE(value)               (UHPHS_USBCMD_PSE_Msk & (_UINT32_(value) << UHPHS_USBCMD_PSE_Pos)) /* Assigment of value for PSE in the UHPHS_USBCMD register */
#define UHPHS_USBCMD_ASE_Pos                  _UINT32_(5)                                          /* (UHPHS_USBCMD) Asynchronous Schedule Enable (read/write) Position */
#define UHPHS_USBCMD_ASE_Msk                  (_UINT32_(0x1) << UHPHS_USBCMD_ASE_Pos)              /* (UHPHS_USBCMD) Asynchronous Schedule Enable (read/write) Mask */
#define UHPHS_USBCMD_ASE(value)               (UHPHS_USBCMD_ASE_Msk & (_UINT32_(value) << UHPHS_USBCMD_ASE_Pos)) /* Assigment of value for ASE in the UHPHS_USBCMD register */
#define UHPHS_USBCMD_IAAD_Pos                 _UINT32_(6)                                          /* (UHPHS_USBCMD) Interrupt on Async Advance Doorbell (read/write) Position */
#define UHPHS_USBCMD_IAAD_Msk                 (_UINT32_(0x1) << UHPHS_USBCMD_IAAD_Pos)             /* (UHPHS_USBCMD) Interrupt on Async Advance Doorbell (read/write) Mask */
#define UHPHS_USBCMD_IAAD(value)              (UHPHS_USBCMD_IAAD_Msk & (_UINT32_(value) << UHPHS_USBCMD_IAAD_Pos)) /* Assigment of value for IAAD in the UHPHS_USBCMD register */
#define UHPHS_USBCMD_LHCR_Pos                 _UINT32_(7)                                          /* (UHPHS_USBCMD) Light Host Controller Reset (optional) (read/write) Position */
#define UHPHS_USBCMD_LHCR_Msk                 (_UINT32_(0x1) << UHPHS_USBCMD_LHCR_Pos)             /* (UHPHS_USBCMD) Light Host Controller Reset (optional) (read/write) Mask */
#define UHPHS_USBCMD_LHCR(value)              (UHPHS_USBCMD_LHCR_Msk & (_UINT32_(value) << UHPHS_USBCMD_LHCR_Pos)) /* Assigment of value for LHCR in the UHPHS_USBCMD register */
#define UHPHS_USBCMD_ASPMC_Pos                _UINT32_(8)                                          /* (UHPHS_USBCMD) Asynchronous Schedule Park Mode Count (optional) (read/write or read-only) Position */
#define UHPHS_USBCMD_ASPMC_Msk                (_UINT32_(0x3) << UHPHS_USBCMD_ASPMC_Pos)            /* (UHPHS_USBCMD) Asynchronous Schedule Park Mode Count (optional) (read/write or read-only) Mask */
#define UHPHS_USBCMD_ASPMC(value)             (UHPHS_USBCMD_ASPMC_Msk & (_UINT32_(value) << UHPHS_USBCMD_ASPMC_Pos)) /* Assigment of value for ASPMC in the UHPHS_USBCMD register */
#define UHPHS_USBCMD_ASPME_Pos                _UINT32_(11)                                         /* (UHPHS_USBCMD) Asynchronous Schedule Park Mode Enable (optional) (read/write or read-only) Position */
#define UHPHS_USBCMD_ASPME_Msk                (_UINT32_(0x1) << UHPHS_USBCMD_ASPME_Pos)            /* (UHPHS_USBCMD) Asynchronous Schedule Park Mode Enable (optional) (read/write or read-only) Mask */
#define UHPHS_USBCMD_ASPME(value)             (UHPHS_USBCMD_ASPME_Msk & (_UINT32_(value) << UHPHS_USBCMD_ASPME_Pos)) /* Assigment of value for ASPME in the UHPHS_USBCMD register */
#define UHPHS_USBCMD_ITC_Pos                  _UINT32_(16)                                         /* (UHPHS_USBCMD) Interrupt Threshold Control (read/write) Position */
#define UHPHS_USBCMD_ITC_Msk                  (_UINT32_(0xFF) << UHPHS_USBCMD_ITC_Pos)             /* (UHPHS_USBCMD) Interrupt Threshold Control (read/write) Mask */
#define UHPHS_USBCMD_ITC(value)               (UHPHS_USBCMD_ITC_Msk & (_UINT32_(value) << UHPHS_USBCMD_ITC_Pos)) /* Assigment of value for ITC in the UHPHS_USBCMD register */
#define UHPHS_USBCMD_Msk                      _UINT32_(0x00FF0BFF)                                 /* (UHPHS_USBCMD) Register Mask  */


/* -------- UHPHS_USBSTS : (UHPHS Offset: 0x14) (R/W 32) UHPHS USB Status Register -------- */
#define UHPHS_USBSTS_USBINT_Pos               _UINT32_(0)                                          /* (UHPHS_USBSTS) USB Interrupt (cleared on write) Position */
#define UHPHS_USBSTS_USBINT_Msk               (_UINT32_(0x1) << UHPHS_USBSTS_USBINT_Pos)           /* (UHPHS_USBSTS) USB Interrupt (cleared on write) Mask */
#define UHPHS_USBSTS_USBINT(value)            (UHPHS_USBSTS_USBINT_Msk & (_UINT32_(value) << UHPHS_USBSTS_USBINT_Pos)) /* Assigment of value for USBINT in the UHPHS_USBSTS register */
#define UHPHS_USBSTS_USBERRINT_Pos            _UINT32_(1)                                          /* (UHPHS_USBSTS) USB Error Interrupt (cleared on write) Position */
#define UHPHS_USBSTS_USBERRINT_Msk            (_UINT32_(0x1) << UHPHS_USBSTS_USBERRINT_Pos)        /* (UHPHS_USBSTS) USB Error Interrupt (cleared on write) Mask */
#define UHPHS_USBSTS_USBERRINT(value)         (UHPHS_USBSTS_USBERRINT_Msk & (_UINT32_(value) << UHPHS_USBSTS_USBERRINT_Pos)) /* Assigment of value for USBERRINT in the UHPHS_USBSTS register */
#define UHPHS_USBSTS_PCD_Pos                  _UINT32_(2)                                          /* (UHPHS_USBSTS) Port Change Detect (cleared on write) Position */
#define UHPHS_USBSTS_PCD_Msk                  (_UINT32_(0x1) << UHPHS_USBSTS_PCD_Pos)              /* (UHPHS_USBSTS) Port Change Detect (cleared on write) Mask */
#define UHPHS_USBSTS_PCD(value)               (UHPHS_USBSTS_PCD_Msk & (_UINT32_(value) << UHPHS_USBSTS_PCD_Pos)) /* Assigment of value for PCD in the UHPHS_USBSTS register */
#define UHPHS_USBSTS_FLR_Pos                  _UINT32_(3)                                          /* (UHPHS_USBSTS) Frame List Rollover (cleared on write) Position */
#define UHPHS_USBSTS_FLR_Msk                  (_UINT32_(0x1) << UHPHS_USBSTS_FLR_Pos)              /* (UHPHS_USBSTS) Frame List Rollover (cleared on write) Mask */
#define UHPHS_USBSTS_FLR(value)               (UHPHS_USBSTS_FLR_Msk & (_UINT32_(value) << UHPHS_USBSTS_FLR_Pos)) /* Assigment of value for FLR in the UHPHS_USBSTS register */
#define UHPHS_USBSTS_HSE_Pos                  _UINT32_(4)                                          /* (UHPHS_USBSTS) Host System Error (cleared on write) Position */
#define UHPHS_USBSTS_HSE_Msk                  (_UINT32_(0x1) << UHPHS_USBSTS_HSE_Pos)              /* (UHPHS_USBSTS) Host System Error (cleared on write) Mask */
#define UHPHS_USBSTS_HSE(value)               (UHPHS_USBSTS_HSE_Msk & (_UINT32_(value) << UHPHS_USBSTS_HSE_Pos)) /* Assigment of value for HSE in the UHPHS_USBSTS register */
#define UHPHS_USBSTS_IAA_Pos                  _UINT32_(5)                                          /* (UHPHS_USBSTS) Interrupt on Async Advance (cleared on write) Position */
#define UHPHS_USBSTS_IAA_Msk                  (_UINT32_(0x1) << UHPHS_USBSTS_IAA_Pos)              /* (UHPHS_USBSTS) Interrupt on Async Advance (cleared on write) Mask */
#define UHPHS_USBSTS_IAA(value)               (UHPHS_USBSTS_IAA_Msk & (_UINT32_(value) << UHPHS_USBSTS_IAA_Pos)) /* Assigment of value for IAA in the UHPHS_USBSTS register */
#define UHPHS_USBSTS_HCHLT_Pos                _UINT32_(12)                                         /* (UHPHS_USBSTS) HCHalted (read-only) Position */
#define UHPHS_USBSTS_HCHLT_Msk                (_UINT32_(0x1) << UHPHS_USBSTS_HCHLT_Pos)            /* (UHPHS_USBSTS) HCHalted (read-only) Mask */
#define UHPHS_USBSTS_HCHLT(value)             (UHPHS_USBSTS_HCHLT_Msk & (_UINT32_(value) << UHPHS_USBSTS_HCHLT_Pos)) /* Assigment of value for HCHLT in the UHPHS_USBSTS register */
#define UHPHS_USBSTS_RCM_Pos                  _UINT32_(13)                                         /* (UHPHS_USBSTS) Reclamation (read-only) Position */
#define UHPHS_USBSTS_RCM_Msk                  (_UINT32_(0x1) << UHPHS_USBSTS_RCM_Pos)              /* (UHPHS_USBSTS) Reclamation (read-only) Mask */
#define UHPHS_USBSTS_RCM(value)               (UHPHS_USBSTS_RCM_Msk & (_UINT32_(value) << UHPHS_USBSTS_RCM_Pos)) /* Assigment of value for RCM in the UHPHS_USBSTS register */
#define UHPHS_USBSTS_PSS_Pos                  _UINT32_(14)                                         /* (UHPHS_USBSTS) Periodic Schedule Status (read-only) Position */
#define UHPHS_USBSTS_PSS_Msk                  (_UINT32_(0x1) << UHPHS_USBSTS_PSS_Pos)              /* (UHPHS_USBSTS) Periodic Schedule Status (read-only) Mask */
#define UHPHS_USBSTS_PSS(value)               (UHPHS_USBSTS_PSS_Msk & (_UINT32_(value) << UHPHS_USBSTS_PSS_Pos)) /* Assigment of value for PSS in the UHPHS_USBSTS register */
#define UHPHS_USBSTS_ASS_Pos                  _UINT32_(15)                                         /* (UHPHS_USBSTS) Asynchronous Schedule Status (read-only) Position */
#define UHPHS_USBSTS_ASS_Msk                  (_UINT32_(0x1) << UHPHS_USBSTS_ASS_Pos)              /* (UHPHS_USBSTS) Asynchronous Schedule Status (read-only) Mask */
#define UHPHS_USBSTS_ASS(value)               (UHPHS_USBSTS_ASS_Msk & (_UINT32_(value) << UHPHS_USBSTS_ASS_Pos)) /* Assigment of value for ASS in the UHPHS_USBSTS register */
#define UHPHS_USBSTS_Msk                      _UINT32_(0x0000F03F)                                 /* (UHPHS_USBSTS) Register Mask  */


/* -------- UHPHS_USBINTR : (UHPHS Offset: 0x18) (R/W 32) UHPHS USB Interrupt Enable Register -------- */
#define UHPHS_USBINTR_USBIE_Pos               _UINT32_(0)                                          /* (UHPHS_USBINTR) USBINT Interrupt Enable Position */
#define UHPHS_USBINTR_USBIE_Msk               (_UINT32_(0x1) << UHPHS_USBINTR_USBIE_Pos)           /* (UHPHS_USBINTR) USBINT Interrupt Enable Mask */
#define UHPHS_USBINTR_USBIE(value)            (UHPHS_USBINTR_USBIE_Msk & (_UINT32_(value) << UHPHS_USBINTR_USBIE_Pos)) /* Assigment of value for USBIE in the UHPHS_USBINTR register */
#define UHPHS_USBINTR_USBEIE_Pos              _UINT32_(1)                                          /* (UHPHS_USBINTR) USBERRINT Interrupt Enable Position */
#define UHPHS_USBINTR_USBEIE_Msk              (_UINT32_(0x1) << UHPHS_USBINTR_USBEIE_Pos)          /* (UHPHS_USBINTR) USBERRINT Interrupt Enable Mask */
#define UHPHS_USBINTR_USBEIE(value)           (UHPHS_USBINTR_USBEIE_Msk & (_UINT32_(value) << UHPHS_USBINTR_USBEIE_Pos)) /* Assigment of value for USBEIE in the UHPHS_USBINTR register */
#define UHPHS_USBINTR_PCIE_Pos                _UINT32_(2)                                          /* (UHPHS_USBINTR) Port Change Detect Interrupt Enable Position */
#define UHPHS_USBINTR_PCIE_Msk                (_UINT32_(0x1) << UHPHS_USBINTR_PCIE_Pos)            /* (UHPHS_USBINTR) Port Change Detect Interrupt Enable Mask */
#define UHPHS_USBINTR_PCIE(value)             (UHPHS_USBINTR_PCIE_Msk & (_UINT32_(value) << UHPHS_USBINTR_PCIE_Pos)) /* Assigment of value for PCIE in the UHPHS_USBINTR register */
#define UHPHS_USBINTR_FLRE_Pos                _UINT32_(3)                                          /* (UHPHS_USBINTR) Frame List Rollover Interrupt Enable Position */
#define UHPHS_USBINTR_FLRE_Msk                (_UINT32_(0x1) << UHPHS_USBINTR_FLRE_Pos)            /* (UHPHS_USBINTR) Frame List Rollover Interrupt Enable Mask */
#define UHPHS_USBINTR_FLRE(value)             (UHPHS_USBINTR_FLRE_Msk & (_UINT32_(value) << UHPHS_USBINTR_FLRE_Pos)) /* Assigment of value for FLRE in the UHPHS_USBINTR register */
#define UHPHS_USBINTR_HSEE_Pos                _UINT32_(4)                                          /* (UHPHS_USBINTR) Host System Error Interrupt Enable Position */
#define UHPHS_USBINTR_HSEE_Msk                (_UINT32_(0x1) << UHPHS_USBINTR_HSEE_Pos)            /* (UHPHS_USBINTR) Host System Error Interrupt Enable Mask */
#define UHPHS_USBINTR_HSEE(value)             (UHPHS_USBINTR_HSEE_Msk & (_UINT32_(value) << UHPHS_USBINTR_HSEE_Pos)) /* Assigment of value for HSEE in the UHPHS_USBINTR register */
#define UHPHS_USBINTR_IAAE_Pos                _UINT32_(5)                                          /* (UHPHS_USBINTR) Interrupt on Async Advance Enable Position */
#define UHPHS_USBINTR_IAAE_Msk                (_UINT32_(0x1) << UHPHS_USBINTR_IAAE_Pos)            /* (UHPHS_USBINTR) Interrupt on Async Advance Enable Mask */
#define UHPHS_USBINTR_IAAE(value)             (UHPHS_USBINTR_IAAE_Msk & (_UINT32_(value) << UHPHS_USBINTR_IAAE_Pos)) /* Assigment of value for IAAE in the UHPHS_USBINTR register */
#define UHPHS_USBINTR_Msk                     _UINT32_(0x0000003F)                                 /* (UHPHS_USBINTR) Register Mask  */


/* -------- UHPHS_FRINDEX : (UHPHS Offset: 0x1C) (R/W 32) UHPHS USB Frame Index Register -------- */
#define UHPHS_FRINDEX_FI_Pos                  _UINT32_(0)                                          /* (UHPHS_FRINDEX) Frame Index Position */
#define UHPHS_FRINDEX_FI_Msk                  (_UINT32_(0x3FFF) << UHPHS_FRINDEX_FI_Pos)           /* (UHPHS_FRINDEX) Frame Index Mask */
#define UHPHS_FRINDEX_FI(value)               (UHPHS_FRINDEX_FI_Msk & (_UINT32_(value) << UHPHS_FRINDEX_FI_Pos)) /* Assigment of value for FI in the UHPHS_FRINDEX register */
#define UHPHS_FRINDEX_Msk                     _UINT32_(0x00003FFF)                                 /* (UHPHS_FRINDEX) Register Mask  */


/* -------- UHPHS_CTRLDSSEGMENT : (UHPHS Offset: 0x20) (R/W 32) UHPHS Control Data Structure Segment Register -------- */
#define UHPHS_CTRLDSSEGMENT_Msk               _UINT32_(0x00000000)                                 /* (UHPHS_CTRLDSSEGMENT) Register Mask  */


/* -------- UHPHS_PERIODICLISTBASE : (UHPHS Offset: 0x24) (R/W 32) UHPHS Periodic Frame List Base Address Register -------- */
#define UHPHS_PERIODICLISTBASE_BA_Pos         _UINT32_(12)                                         /* (UHPHS_PERIODICLISTBASE) Base Address (Low) Position */
#define UHPHS_PERIODICLISTBASE_BA_Msk         (_UINT32_(0xFFFFF) << UHPHS_PERIODICLISTBASE_BA_Pos) /* (UHPHS_PERIODICLISTBASE) Base Address (Low) Mask */
#define UHPHS_PERIODICLISTBASE_BA(value)      (UHPHS_PERIODICLISTBASE_BA_Msk & (_UINT32_(value) << UHPHS_PERIODICLISTBASE_BA_Pos)) /* Assigment of value for BA in the UHPHS_PERIODICLISTBASE register */
#define UHPHS_PERIODICLISTBASE_Msk            _UINT32_(0xFFFFF000)                                 /* (UHPHS_PERIODICLISTBASE) Register Mask  */


/* -------- UHPHS_ASYNCLISTADDR : (UHPHS Offset: 0x28) (R/W 32) UHPHS Asynchronous List Address Register -------- */
#define UHPHS_ASYNCLISTADDR_LPL_Pos           _UINT32_(5)                                          /* (UHPHS_ASYNCLISTADDR) Link Pointer Low Position */
#define UHPHS_ASYNCLISTADDR_LPL_Msk           (_UINT32_(0x7FFFFFF) << UHPHS_ASYNCLISTADDR_LPL_Pos) /* (UHPHS_ASYNCLISTADDR) Link Pointer Low Mask */
#define UHPHS_ASYNCLISTADDR_LPL(value)        (UHPHS_ASYNCLISTADDR_LPL_Msk & (_UINT32_(value) << UHPHS_ASYNCLISTADDR_LPL_Pos)) /* Assigment of value for LPL in the UHPHS_ASYNCLISTADDR register */
#define UHPHS_ASYNCLISTADDR_Msk               _UINT32_(0xFFFFFFE0)                                 /* (UHPHS_ASYNCLISTADDR) Register Mask  */


/* -------- UHPHS_CONFIGFLAG : (UHPHS Offset: 0x50) (R/W 32) UHPHS Configured Flag Register -------- */
#define UHPHS_CONFIGFLAG_CF_Pos               _UINT32_(0)                                          /* (UHPHS_CONFIGFLAG) Configure Flag (Read/Write) Position */
#define UHPHS_CONFIGFLAG_CF_Msk               (_UINT32_(0x1) << UHPHS_CONFIGFLAG_CF_Pos)           /* (UHPHS_CONFIGFLAG) Configure Flag (Read/Write) Mask */
#define UHPHS_CONFIGFLAG_CF(value)            (UHPHS_CONFIGFLAG_CF_Msk & (_UINT32_(value) << UHPHS_CONFIGFLAG_CF_Pos)) /* Assigment of value for CF in the UHPHS_CONFIGFLAG register */
#define UHPHS_CONFIGFLAG_Msk                  _UINT32_(0x00000001)                                 /* (UHPHS_CONFIGFLAG) Register Mask  */


/* -------- UHPHS_PORTSC : (UHPHS Offset: 0x54) (R/W 32) UHPHS Port Status and Control Register (port = 0) -------- */
#define UHPHS_PORTSC_CCS_Pos                  _UINT32_(0)                                          /* (UHPHS_PORTSC) Current Connect Status (read-only) Position */
#define UHPHS_PORTSC_CCS_Msk                  (_UINT32_(0x1) << UHPHS_PORTSC_CCS_Pos)              /* (UHPHS_PORTSC) Current Connect Status (read-only) Mask */
#define UHPHS_PORTSC_CCS(value)               (UHPHS_PORTSC_CCS_Msk & (_UINT32_(value) << UHPHS_PORTSC_CCS_Pos)) /* Assigment of value for CCS in the UHPHS_PORTSC register */
#define UHPHS_PORTSC_CSC_Pos                  _UINT32_(1)                                          /* (UHPHS_PORTSC) Connect Status Change (read/write clear) Position */
#define UHPHS_PORTSC_CSC_Msk                  (_UINT32_(0x1) << UHPHS_PORTSC_CSC_Pos)              /* (UHPHS_PORTSC) Connect Status Change (read/write clear) Mask */
#define UHPHS_PORTSC_CSC(value)               (UHPHS_PORTSC_CSC_Msk & (_UINT32_(value) << UHPHS_PORTSC_CSC_Pos)) /* Assigment of value for CSC in the UHPHS_PORTSC register */
#define UHPHS_PORTSC_PED_Pos                  _UINT32_(2)                                          /* (UHPHS_PORTSC) Port Enabled/Disabled (read/write) Position */
#define UHPHS_PORTSC_PED_Msk                  (_UINT32_(0x1) << UHPHS_PORTSC_PED_Pos)              /* (UHPHS_PORTSC) Port Enabled/Disabled (read/write) Mask */
#define UHPHS_PORTSC_PED(value)               (UHPHS_PORTSC_PED_Msk & (_UINT32_(value) << UHPHS_PORTSC_PED_Pos)) /* Assigment of value for PED in the UHPHS_PORTSC register */
#define UHPHS_PORTSC_PEDC_Pos                 _UINT32_(3)                                          /* (UHPHS_PORTSC) Port Enable/Disable Change (read/write clear) Position */
#define UHPHS_PORTSC_PEDC_Msk                 (_UINT32_(0x1) << UHPHS_PORTSC_PEDC_Pos)             /* (UHPHS_PORTSC) Port Enable/Disable Change (read/write clear) Mask */
#define UHPHS_PORTSC_PEDC(value)              (UHPHS_PORTSC_PEDC_Msk & (_UINT32_(value) << UHPHS_PORTSC_PEDC_Pos)) /* Assigment of value for PEDC in the UHPHS_PORTSC register */
#define UHPHS_PORTSC_OCA_Pos                  _UINT32_(4)                                          /* (UHPHS_PORTSC) Over-current Active (read-only) Position */
#define UHPHS_PORTSC_OCA_Msk                  (_UINT32_(0x1) << UHPHS_PORTSC_OCA_Pos)              /* (UHPHS_PORTSC) Over-current Active (read-only) Mask */
#define UHPHS_PORTSC_OCA(value)               (UHPHS_PORTSC_OCA_Msk & (_UINT32_(value) << UHPHS_PORTSC_OCA_Pos)) /* Assigment of value for OCA in the UHPHS_PORTSC register */
#define UHPHS_PORTSC_OCC_Pos                  _UINT32_(5)                                          /* (UHPHS_PORTSC) Over-current Change (read/write clear) Position */
#define UHPHS_PORTSC_OCC_Msk                  (_UINT32_(0x1) << UHPHS_PORTSC_OCC_Pos)              /* (UHPHS_PORTSC) Over-current Change (read/write clear) Mask */
#define UHPHS_PORTSC_OCC(value)               (UHPHS_PORTSC_OCC_Msk & (_UINT32_(value) << UHPHS_PORTSC_OCC_Pos)) /* Assigment of value for OCC in the UHPHS_PORTSC register */
#define UHPHS_PORTSC_FPR_Pos                  _UINT32_(6)                                          /* (UHPHS_PORTSC) Force Port Resume (read/write) Position */
#define UHPHS_PORTSC_FPR_Msk                  (_UINT32_(0x1) << UHPHS_PORTSC_FPR_Pos)              /* (UHPHS_PORTSC) Force Port Resume (read/write) Mask */
#define UHPHS_PORTSC_FPR(value)               (UHPHS_PORTSC_FPR_Msk & (_UINT32_(value) << UHPHS_PORTSC_FPR_Pos)) /* Assigment of value for FPR in the UHPHS_PORTSC register */
#define UHPHS_PORTSC_SUS_Pos                  _UINT32_(7)                                          /* (UHPHS_PORTSC) Suspend (read/write) Position */
#define UHPHS_PORTSC_SUS_Msk                  (_UINT32_(0x1) << UHPHS_PORTSC_SUS_Pos)              /* (UHPHS_PORTSC) Suspend (read/write) Mask */
#define UHPHS_PORTSC_SUS(value)               (UHPHS_PORTSC_SUS_Msk & (_UINT32_(value) << UHPHS_PORTSC_SUS_Pos)) /* Assigment of value for SUS in the UHPHS_PORTSC register */
#define UHPHS_PORTSC_PR_Pos                   _UINT32_(8)                                          /* (UHPHS_PORTSC) Port Reset (read/write) Position */
#define UHPHS_PORTSC_PR_Msk                   (_UINT32_(0x1) << UHPHS_PORTSC_PR_Pos)               /* (UHPHS_PORTSC) Port Reset (read/write) Mask */
#define UHPHS_PORTSC_PR(value)                (UHPHS_PORTSC_PR_Msk & (_UINT32_(value) << UHPHS_PORTSC_PR_Pos)) /* Assigment of value for PR in the UHPHS_PORTSC register */
#define UHPHS_PORTSC_LS_Pos                   _UINT32_(10)                                         /* (UHPHS_PORTSC) Line Status (read-only) Position */
#define UHPHS_PORTSC_LS_Msk                   (_UINT32_(0x3) << UHPHS_PORTSC_LS_Pos)               /* (UHPHS_PORTSC) Line Status (read-only) Mask */
#define UHPHS_PORTSC_LS(value)                (UHPHS_PORTSC_LS_Msk & (_UINT32_(value) << UHPHS_PORTSC_LS_Pos)) /* Assigment of value for LS in the UHPHS_PORTSC register */
#define   UHPHS_PORTSC_LS_SE0_Val             _UINT32_(0x0)                                        /* (UHPHS_PORTSC) Not a low-speed device, perform EHCI reset  */
#define   UHPHS_PORTSC_LS_K_STATE_Val         _UINT32_(0x1)                                        /* (UHPHS_PORTSC) Low-speed device, release ownership of port  */
#define   UHPHS_PORTSC_LS_J_STATE_Val         _UINT32_(0x2)                                        /* (UHPHS_PORTSC) Not a low-speed device, perform EHCI reset  */
#define   UHPHS_PORTSC_LS_UNDEFINED_Val       _UINT32_(0x3)                                        /* (UHPHS_PORTSC) Not a low-speed device, perform EHCI reset  */
#define UHPHS_PORTSC_LS_SE0                   (UHPHS_PORTSC_LS_SE0_Val << UHPHS_PORTSC_LS_Pos)     /* (UHPHS_PORTSC) Not a low-speed device, perform EHCI reset Position  */
#define UHPHS_PORTSC_LS_K_STATE               (UHPHS_PORTSC_LS_K_STATE_Val << UHPHS_PORTSC_LS_Pos) /* (UHPHS_PORTSC) Low-speed device, release ownership of port Position  */
#define UHPHS_PORTSC_LS_J_STATE               (UHPHS_PORTSC_LS_J_STATE_Val << UHPHS_PORTSC_LS_Pos) /* (UHPHS_PORTSC) Not a low-speed device, perform EHCI reset Position  */
#define UHPHS_PORTSC_LS_UNDEFINED             (UHPHS_PORTSC_LS_UNDEFINED_Val << UHPHS_PORTSC_LS_Pos) /* (UHPHS_PORTSC) Not a low-speed device, perform EHCI reset Position  */
#define UHPHS_PORTSC_PP_Pos                   _UINT32_(12)                                         /* (UHPHS_PORTSC) Port Power (read/write or read-only) Position */
#define UHPHS_PORTSC_PP_Msk                   (_UINT32_(0x1) << UHPHS_PORTSC_PP_Pos)               /* (UHPHS_PORTSC) Port Power (read/write or read-only) Mask */
#define UHPHS_PORTSC_PP(value)                (UHPHS_PORTSC_PP_Msk & (_UINT32_(value) << UHPHS_PORTSC_PP_Pos)) /* Assigment of value for PP in the UHPHS_PORTSC register */
#define UHPHS_PORTSC_PO_Pos                   _UINT32_(13)                                         /* (UHPHS_PORTSC) Port Owner (read/write) Position */
#define UHPHS_PORTSC_PO_Msk                   (_UINT32_(0x1) << UHPHS_PORTSC_PO_Pos)               /* (UHPHS_PORTSC) Port Owner (read/write) Mask */
#define UHPHS_PORTSC_PO(value)                (UHPHS_PORTSC_PO_Msk & (_UINT32_(value) << UHPHS_PORTSC_PO_Pos)) /* Assigment of value for PO in the UHPHS_PORTSC register */
#define UHPHS_PORTSC_PIC_Pos                  _UINT32_(14)                                         /* (UHPHS_PORTSC) Port Indicator Control (read/write) Position */
#define UHPHS_PORTSC_PIC_Msk                  (_UINT32_(0x3) << UHPHS_PORTSC_PIC_Pos)              /* (UHPHS_PORTSC) Port Indicator Control (read/write) Mask */
#define UHPHS_PORTSC_PIC(value)               (UHPHS_PORTSC_PIC_Msk & (_UINT32_(value) << UHPHS_PORTSC_PIC_Pos)) /* Assigment of value for PIC in the UHPHS_PORTSC register */
#define UHPHS_PORTSC_PTC_Pos                  _UINT32_(16)                                         /* (UHPHS_PORTSC) Port Test Control (read/write) Position */
#define UHPHS_PORTSC_PTC_Msk                  (_UINT32_(0xF) << UHPHS_PORTSC_PTC_Pos)              /* (UHPHS_PORTSC) Port Test Control (read/write) Mask */
#define UHPHS_PORTSC_PTC(value)               (UHPHS_PORTSC_PTC_Msk & (_UINT32_(value) << UHPHS_PORTSC_PTC_Pos)) /* Assigment of value for PTC in the UHPHS_PORTSC register */
#define UHPHS_PORTSC_WKCNNT_E_Pos             _UINT32_(20)                                         /* (UHPHS_PORTSC) Wake on Connect Enable (read/write) Position */
#define UHPHS_PORTSC_WKCNNT_E_Msk             (_UINT32_(0x1) << UHPHS_PORTSC_WKCNNT_E_Pos)         /* (UHPHS_PORTSC) Wake on Connect Enable (read/write) Mask */
#define UHPHS_PORTSC_WKCNNT_E(value)          (UHPHS_PORTSC_WKCNNT_E_Msk & (_UINT32_(value) << UHPHS_PORTSC_WKCNNT_E_Pos)) /* Assigment of value for WKCNNT_E in the UHPHS_PORTSC register */
#define UHPHS_PORTSC_WKDSCNNT_E_Pos           _UINT32_(21)                                         /* (UHPHS_PORTSC) Wake on Disconnect Enable (read/write) Position */
#define UHPHS_PORTSC_WKDSCNNT_E_Msk           (_UINT32_(0x1) << UHPHS_PORTSC_WKDSCNNT_E_Pos)       /* (UHPHS_PORTSC) Wake on Disconnect Enable (read/write) Mask */
#define UHPHS_PORTSC_WKDSCNNT_E(value)        (UHPHS_PORTSC_WKDSCNNT_E_Msk & (_UINT32_(value) << UHPHS_PORTSC_WKDSCNNT_E_Pos)) /* Assigment of value for WKDSCNNT_E in the UHPHS_PORTSC register */
#define UHPHS_PORTSC_WKOC_E_Pos               _UINT32_(22)                                         /* (UHPHS_PORTSC) Wake on Over-current Enable (read/write) Position */
#define UHPHS_PORTSC_WKOC_E_Msk               (_UINT32_(0x1) << UHPHS_PORTSC_WKOC_E_Pos)           /* (UHPHS_PORTSC) Wake on Over-current Enable (read/write) Mask */
#define UHPHS_PORTSC_WKOC_E(value)            (UHPHS_PORTSC_WKOC_E_Msk & (_UINT32_(value) << UHPHS_PORTSC_WKOC_E_Pos)) /* Assigment of value for WKOC_E in the UHPHS_PORTSC register */
#define UHPHS_PORTSC_Msk                      _UINT32_(0x007FFDFF)                                 /* (UHPHS_PORTSC) Register Mask  */


/* -------- UHPHS_INSNREG06 : (UHPHS Offset: 0xA8) (R/W 32) EHCI Specific Registers 06 -------- */
#define UHPHS_INSNREG06_Nb_Success_Burst_Pos  _UINT32_(0)                                          /* (UHPHS_INSNREG06) Number of Successful Bursts (Read-only) Position */
#define UHPHS_INSNREG06_Nb_Success_Burst_Msk  (_UINT32_(0xF) << UHPHS_INSNREG06_Nb_Success_Burst_Pos) /* (UHPHS_INSNREG06) Number of Successful Bursts (Read-only) Mask */
#define UHPHS_INSNREG06_Nb_Success_Burst(value) (UHPHS_INSNREG06_Nb_Success_Burst_Msk & (_UINT32_(value) << UHPHS_INSNREG06_Nb_Success_Burst_Pos)) /* Assigment of value for Nb_Success_Burst in the UHPHS_INSNREG06 register */
#define UHPHS_INSNREG06_Nb_Burst_Pos          _UINT32_(4)                                          /* (UHPHS_INSNREG06) Number of Bursts (Read-only) Position */
#define UHPHS_INSNREG06_Nb_Burst_Msk          (_UINT32_(0x1F) << UHPHS_INSNREG06_Nb_Burst_Pos)     /* (UHPHS_INSNREG06) Number of Bursts (Read-only) Mask */
#define UHPHS_INSNREG06_Nb_Burst(value)       (UHPHS_INSNREG06_Nb_Burst_Msk & (_UINT32_(value) << UHPHS_INSNREG06_Nb_Burst_Pos)) /* Assigment of value for Nb_Burst in the UHPHS_INSNREG06 register */
#define UHPHS_INSNREG06_HBURST_Pos            _UINT32_(9)                                          /* (UHPHS_INSNREG06) Burst Value (Read-only) Position */
#define UHPHS_INSNREG06_HBURST_Msk            (_UINT32_(0x7) << UHPHS_INSNREG06_HBURST_Pos)        /* (UHPHS_INSNREG06) Burst Value (Read-only) Mask */
#define UHPHS_INSNREG06_HBURST(value)         (UHPHS_INSNREG06_HBURST_Msk & (_UINT32_(value) << UHPHS_INSNREG06_HBURST_Pos)) /* Assigment of value for HBURST in the UHPHS_INSNREG06 register */
#define UHPHS_INSNREG06_AHB_ERR_Pos           _UINT32_(31)                                         /* (UHPHS_INSNREG06) AHB Error Position */
#define UHPHS_INSNREG06_AHB_ERR_Msk           (_UINT32_(0x1) << UHPHS_INSNREG06_AHB_ERR_Pos)       /* (UHPHS_INSNREG06) AHB Error Mask */
#define UHPHS_INSNREG06_AHB_ERR(value)        (UHPHS_INSNREG06_AHB_ERR_Msk & (_UINT32_(value) << UHPHS_INSNREG06_AHB_ERR_Pos)) /* Assigment of value for AHB_ERR in the UHPHS_INSNREG06 register */
#define UHPHS_INSNREG06_Msk                   _UINT32_(0x80000FFF)                                 /* (UHPHS_INSNREG06) Register Mask  */


/* -------- UHPHS_INSNREG07 : (UHPHS Offset: 0xAC) (R/W 32) EHCI Specific Registers 07 -------- */
#define UHPHS_INSNREG07_AHB_ADDR_Pos          _UINT32_(0)                                          /* (UHPHS_INSNREG07) AHB Address (Read Only) Position */
#define UHPHS_INSNREG07_AHB_ADDR_Msk          (_UINT32_(0xFFFFFFFF) << UHPHS_INSNREG07_AHB_ADDR_Pos) /* (UHPHS_INSNREG07) AHB Address (Read Only) Mask */
#define UHPHS_INSNREG07_AHB_ADDR(value)       (UHPHS_INSNREG07_AHB_ADDR_Msk & (_UINT32_(value) << UHPHS_INSNREG07_AHB_ADDR_Pos)) /* Assigment of value for AHB_ADDR in the UHPHS_INSNREG07 register */
#define UHPHS_INSNREG07_Msk                   _UINT32_(0xFFFFFFFF)                                 /* (UHPHS_INSNREG07) Register Mask  */


/** \brief UHPHS register offsets definitions */
#define UHPHS_HCCAPBASE_REG_OFST       _UINT32_(0x00)      /* (UHPHS_HCCAPBASE) UHPHS Host Controller Capability Register Offset */
#define UHPHS_HCSPARAMS_REG_OFST       _UINT32_(0x04)      /* (UHPHS_HCSPARAMS) UHPHS Host Controller Structural Parameters Register Offset */
#define UHPHS_HCCPARAMS_REG_OFST       _UINT32_(0x08)      /* (UHPHS_HCCPARAMS) UHPHS Host Controller Capability Parameters Register Offset */
#define UHPHS_USBCMD_REG_OFST          _UINT32_(0x10)      /* (UHPHS_USBCMD) UHPHS USB Command Register Offset */
#define UHPHS_USBSTS_REG_OFST          _UINT32_(0x14)      /* (UHPHS_USBSTS) UHPHS USB Status Register Offset */
#define UHPHS_USBINTR_REG_OFST         _UINT32_(0x18)      /* (UHPHS_USBINTR) UHPHS USB Interrupt Enable Register Offset */
#define UHPHS_FRINDEX_REG_OFST         _UINT32_(0x1C)      /* (UHPHS_FRINDEX) UHPHS USB Frame Index Register Offset */
#define UHPHS_CTRLDSSEGMENT_REG_OFST   _UINT32_(0x20)      /* (UHPHS_CTRLDSSEGMENT) UHPHS Control Data Structure Segment Register Offset */
#define UHPHS_PERIODICLISTBASE_REG_OFST _UINT32_(0x24)      /* (UHPHS_PERIODICLISTBASE) UHPHS Periodic Frame List Base Address Register Offset */
#define UHPHS_ASYNCLISTADDR_REG_OFST   _UINT32_(0x28)      /* (UHPHS_ASYNCLISTADDR) UHPHS Asynchronous List Address Register Offset */
#define UHPHS_CONFIGFLAG_REG_OFST      _UINT32_(0x50)      /* (UHPHS_CONFIGFLAG) UHPHS Configured Flag Register Offset */
#define UHPHS_PORTSC_REG_OFST          _UINT32_(0x54)      /* (UHPHS_PORTSC) UHPHS Port Status and Control Register (port = 0) Offset */
#define UHPHS_PORTSC0_REG_OFST         _UINT32_(0x54)      /* (UHPHS_PORTSC0) UHPHS Port Status and Control Register (port = 0) Offset */
#define UHPHS_PORTSC1_REG_OFST         _UINT32_(0x58)      /* (UHPHS_PORTSC1) UHPHS Port Status and Control Register (port = 0) Offset */
#define UHPHS_PORTSC2_REG_OFST         _UINT32_(0x5C)      /* (UHPHS_PORTSC2) UHPHS Port Status and Control Register (port = 0) Offset */
#define UHPHS_INSNREG06_REG_OFST       _UINT32_(0xA8)      /* (UHPHS_INSNREG06) EHCI Specific Registers 06 Offset */
#define UHPHS_INSNREG07_REG_OFST       _UINT32_(0xAC)      /* (UHPHS_INSNREG07) EHCI Specific Registers 07 Offset */

#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief UHPHS register API structure */
typedef struct
{
  __I   uint32_t                       UHPHS_HCCAPBASE;    /**< Offset: 0x00 (R/   32) UHPHS Host Controller Capability Register */
  __I   uint32_t                       UHPHS_HCSPARAMS;    /**< Offset: 0x04 (R/   32) UHPHS Host Controller Structural Parameters Register */
  __I   uint32_t                       UHPHS_HCCPARAMS;    /**< Offset: 0x08 (R/   32) UHPHS Host Controller Capability Parameters Register */
  __I   uint8_t                        Reserved1[0x04];
  __IO  uint32_t                       UHPHS_USBCMD;       /**< Offset: 0x10 (R/W  32) UHPHS USB Command Register */
  __IO  uint32_t                       UHPHS_USBSTS;       /**< Offset: 0x14 (R/W  32) UHPHS USB Status Register */
  __IO  uint32_t                       UHPHS_USBINTR;      /**< Offset: 0x18 (R/W  32) UHPHS USB Interrupt Enable Register */
  __IO  uint32_t                       UHPHS_FRINDEX;      /**< Offset: 0x1C (R/W  32) UHPHS USB Frame Index Register */
  __IO  uint32_t                       UHPHS_CTRLDSSEGMENT; /**< Offset: 0x20 (R/W  32) UHPHS Control Data Structure Segment Register */
  __IO  uint32_t                       UHPHS_PERIODICLISTBASE; /**< Offset: 0x24 (R/W  32) UHPHS Periodic Frame List Base Address Register */
  __IO  uint32_t                       UHPHS_ASYNCLISTADDR; /**< Offset: 0x28 (R/W  32) UHPHS Asynchronous List Address Register */
  __I   uint8_t                        Reserved2[0x24];
  __IO  uint32_t                       UHPHS_CONFIGFLAG;   /**< Offset: 0x50 (R/W  32) UHPHS Configured Flag Register */
  __IO  uint32_t                       UHPHS_PORTSC[3];    /**< Offset: 0x54 (R/W  32) UHPHS Port Status and Control Register (port = 0) */
  __I   uint8_t                        Reserved3[0x48];
  __IO  uint32_t                       UHPHS_INSNREG06;    /**< Offset: 0xA8 (R/W  32) EHCI Specific Registers 06 */
  __IO  uint32_t                       UHPHS_INSNREG07;    /**< Offset: 0xAC (R/W  32) EHCI Specific Registers 07 */
} uhphs_registers_t;


#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */
#endif /* _SAM9X_UHPHS_COMPONENT_H_ */
