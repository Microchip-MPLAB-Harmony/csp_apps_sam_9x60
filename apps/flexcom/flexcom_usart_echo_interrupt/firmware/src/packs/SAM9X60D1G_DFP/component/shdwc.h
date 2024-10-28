/*
 * Component description for SHDWC
 *
 * Copyright (c) 2024 Microchip Technology Inc. and its subsidiaries.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

/* file generated from device description file (ATDF) version 2024-01-15T14:39:57Z */
#ifndef _SAM9X6_SHDWC_COMPONENT_H_
#define _SAM9X6_SHDWC_COMPONENT_H_

/* ************************************************************************** */
/*   SOFTWARE API DEFINITION FOR SHDWC                                        */
/* ************************************************************************** */

/* -------- SHDW_CR : (SHDWC Offset: 0x00) ( /W 32) Control Register -------- */
#define SHDW_CR_SHDW_Pos                      _UINT32_(0)                                          /* (SHDW_CR) Shutdown Command Position */
#define SHDW_CR_SHDW_Msk                      (_UINT32_(0x1) << SHDW_CR_SHDW_Pos)                  /* (SHDW_CR) Shutdown Command Mask */
#define SHDW_CR_SHDW(value)                   (SHDW_CR_SHDW_Msk & (_UINT32_(value) << SHDW_CR_SHDW_Pos)) /* Assigment of value for SHDW in the SHDW_CR register */
#define SHDW_CR_KEY_Pos                       _UINT32_(24)                                         /* (SHDW_CR) Password Position */
#define SHDW_CR_KEY_Msk                       (_UINT32_(0xFF) << SHDW_CR_KEY_Pos)                  /* (SHDW_CR) Password Mask */
#define SHDW_CR_KEY(value)                    (SHDW_CR_KEY_Msk & (_UINT32_(value) << SHDW_CR_KEY_Pos)) /* Assigment of value for KEY in the SHDW_CR register */
#define   SHDW_CR_KEY_PASSWD_Val              _UINT32_(0xA5)                                       /* (SHDW_CR) Writing any other value in this field aborts the write operation.  */
#define SHDW_CR_KEY_PASSWD                    (SHDW_CR_KEY_PASSWD_Val << SHDW_CR_KEY_Pos)          /* (SHDW_CR) Writing any other value in this field aborts the write operation. Position  */
#define SHDW_CR_Msk                           _UINT32_(0xFF000001)                                 /* (SHDW_CR) Register Mask  */


/* -------- SHDW_MR : (SHDWC Offset: 0x04) (R/W 32) Mode Register -------- */
#define SHDW_MR_RTTWKEN_Pos                   _UINT32_(16)                                         /* (SHDW_MR) Real-time Timer Wakeup Enable Position */
#define SHDW_MR_RTTWKEN_Msk                   (_UINT32_(0x1) << SHDW_MR_RTTWKEN_Pos)               /* (SHDW_MR) Real-time Timer Wakeup Enable Mask */
#define SHDW_MR_RTTWKEN(value)                (SHDW_MR_RTTWKEN_Msk & (_UINT32_(value) << SHDW_MR_RTTWKEN_Pos)) /* Assigment of value for RTTWKEN in the SHDW_MR register */
#define SHDW_MR_RTCWKEN_Pos                   _UINT32_(17)                                         /* (SHDW_MR) Real-time Clock Wakeup Enable Position */
#define SHDW_MR_RTCWKEN_Msk                   (_UINT32_(0x1) << SHDW_MR_RTCWKEN_Pos)               /* (SHDW_MR) Real-time Clock Wakeup Enable Mask */
#define SHDW_MR_RTCWKEN(value)                (SHDW_MR_RTCWKEN_Msk & (_UINT32_(value) << SHDW_MR_RTCWKEN_Pos)) /* Assigment of value for RTCWKEN in the SHDW_MR register */
#define SHDW_MR_WKUPDBC_Pos                   _UINT32_(24)                                         /* (SHDW_MR) Wakeup Inputs Debouncer Period Position */
#define SHDW_MR_WKUPDBC_Msk                   (_UINT32_(0x7) << SHDW_MR_WKUPDBC_Pos)               /* (SHDW_MR) Wakeup Inputs Debouncer Period Mask */
#define SHDW_MR_WKUPDBC(value)                (SHDW_MR_WKUPDBC_Msk & (_UINT32_(value) << SHDW_MR_WKUPDBC_Pos)) /* Assigment of value for WKUPDBC in the SHDW_MR register */
#define   SHDW_MR_WKUPDBC_IMMEDIATE_Val       _UINT32_(0x0)                                        /* (SHDW_MR) Immediate, no debouncing, detected active at least on one MD_SLCK edge.  */
#define   SHDW_MR_WKUPDBC_3_SLCK_Val          _UINT32_(0x1)                                        /* (SHDW_MR) WKUP shall be in its active state for at least 3 MD_SLCK periods  */
#define   SHDW_MR_WKUPDBC_32_SLCK_Val         _UINT32_(0x2)                                        /* (SHDW_MR) WKUP shall be in its active state for at least 32 MD_SLCK periods  */
#define   SHDW_MR_WKUPDBC_512_SLCK_Val        _UINT32_(0x3)                                        /* (SHDW_MR) WKUP shall be in its active state for at least 512 MD_SLCK periods  */
#define   SHDW_MR_WKUPDBC_4096_SLCK_Val       _UINT32_(0x4)                                        /* (SHDW_MR) WKUP shall be in its active state for at least 4,096 MD_SLCK periods  */
#define   SHDW_MR_WKUPDBC_32768_SLCK_Val      _UINT32_(0x5)                                        /* (SHDW_MR) WKUP shall be in its active state for at least 32,768 MD_SLCK periods  */
#define SHDW_MR_WKUPDBC_IMMEDIATE             (SHDW_MR_WKUPDBC_IMMEDIATE_Val << SHDW_MR_WKUPDBC_Pos) /* (SHDW_MR) Immediate, no debouncing, detected active at least on one MD_SLCK edge. Position  */
#define SHDW_MR_WKUPDBC_3_SLCK                (SHDW_MR_WKUPDBC_3_SLCK_Val << SHDW_MR_WKUPDBC_Pos)  /* (SHDW_MR) WKUP shall be in its active state for at least 3 MD_SLCK periods Position  */
#define SHDW_MR_WKUPDBC_32_SLCK               (SHDW_MR_WKUPDBC_32_SLCK_Val << SHDW_MR_WKUPDBC_Pos) /* (SHDW_MR) WKUP shall be in its active state for at least 32 MD_SLCK periods Position  */
#define SHDW_MR_WKUPDBC_512_SLCK              (SHDW_MR_WKUPDBC_512_SLCK_Val << SHDW_MR_WKUPDBC_Pos) /* (SHDW_MR) WKUP shall be in its active state for at least 512 MD_SLCK periods Position  */
#define SHDW_MR_WKUPDBC_4096_SLCK             (SHDW_MR_WKUPDBC_4096_SLCK_Val << SHDW_MR_WKUPDBC_Pos) /* (SHDW_MR) WKUP shall be in its active state for at least 4,096 MD_SLCK periods Position  */
#define SHDW_MR_WKUPDBC_32768_SLCK            (SHDW_MR_WKUPDBC_32768_SLCK_Val << SHDW_MR_WKUPDBC_Pos) /* (SHDW_MR) WKUP shall be in its active state for at least 32,768 MD_SLCK periods Position  */
#define SHDW_MR_Msk                           _UINT32_(0x07030000)                                 /* (SHDW_MR) Register Mask  */


/* -------- SHDW_SR : (SHDWC Offset: 0x08) ( R/ 32) Status Register -------- */
#define SHDW_SR_WKUPS_Pos                     _UINT32_(0)                                          /* (SHDW_SR) WKUP Wakeup Status Position */
#define SHDW_SR_WKUPS_Msk                     (_UINT32_(0x1) << SHDW_SR_WKUPS_Pos)                 /* (SHDW_SR) WKUP Wakeup Status Mask */
#define SHDW_SR_WKUPS(value)                  (SHDW_SR_WKUPS_Msk & (_UINT32_(value) << SHDW_SR_WKUPS_Pos)) /* Assigment of value for WKUPS in the SHDW_SR register */
#define   SHDW_SR_WKUPS_NO_Val                _UINT32_(0x0)                                        /* (SHDW_SR) No wakeup due to the assertion of the WKUP pin has occurred since the last read of SHDW_SR.  */
#define   SHDW_SR_WKUPS_PRESENT_Val           _UINT32_(0x1)                                        /* (SHDW_SR) At least one wakeup due to the assertion of the WKUP pin has occurred since the last read of SHDW_SR.  */
#define SHDW_SR_WKUPS_NO                      (SHDW_SR_WKUPS_NO_Val << SHDW_SR_WKUPS_Pos)          /* (SHDW_SR) No wakeup due to the assertion of the WKUP pin has occurred since the last read of SHDW_SR. Position  */
#define SHDW_SR_WKUPS_PRESENT                 (SHDW_SR_WKUPS_PRESENT_Val << SHDW_SR_WKUPS_Pos)     /* (SHDW_SR) At least one wakeup due to the assertion of the WKUP pin has occurred since the last read of SHDW_SR. Position  */
#define SHDW_SR_RTTWK_Pos                     _UINT32_(4)                                          /* (SHDW_SR) Real-time Timer Wakeup Position */
#define SHDW_SR_RTTWK_Msk                     (_UINT32_(0x1) << SHDW_SR_RTTWK_Pos)                 /* (SHDW_SR) Real-time Timer Wakeup Mask */
#define SHDW_SR_RTTWK(value)                  (SHDW_SR_RTTWK_Msk & (_UINT32_(value) << SHDW_SR_RTTWK_Pos)) /* Assigment of value for RTTWK in the SHDW_SR register */
#define SHDW_SR_RTCWK_Pos                     _UINT32_(5)                                          /* (SHDW_SR) Real-time Clock Wakeup Position */
#define SHDW_SR_RTCWK_Msk                     (_UINT32_(0x1) << SHDW_SR_RTCWK_Pos)                 /* (SHDW_SR) Real-time Clock Wakeup Mask */
#define SHDW_SR_RTCWK(value)                  (SHDW_SR_RTCWK_Msk & (_UINT32_(value) << SHDW_SR_RTCWK_Pos)) /* Assigment of value for RTCWK in the SHDW_SR register */
#define SHDW_SR_WKUPIS0_Pos                   _UINT32_(16)                                         /* (SHDW_SR) Wakeup 0 Input Status Position */
#define SHDW_SR_WKUPIS0_Msk                   (_UINT32_(0x1) << SHDW_SR_WKUPIS0_Pos)               /* (SHDW_SR) Wakeup 0 Input Status Mask */
#define SHDW_SR_WKUPIS0(value)                (SHDW_SR_WKUPIS0_Msk & (_UINT32_(value) << SHDW_SR_WKUPIS0_Pos)) /* Assigment of value for WKUPIS0 in the SHDW_SR register */
#define   SHDW_SR_WKUPIS0_DISABLE_Val         _UINT32_(0x0)                                        /* (SHDW_SR) The wakeup 0 input is disabled, or was inactive at the time the debouncer triggered a wakeup event.  */
#define   SHDW_SR_WKUPIS0_ENABLE_Val          _UINT32_(0x1)                                        /* (SHDW_SR) The wakeup 0 input was active at the time the debouncer triggered a wakeup event.  */
#define SHDW_SR_WKUPIS0_DISABLE               (SHDW_SR_WKUPIS0_DISABLE_Val << SHDW_SR_WKUPIS0_Pos) /* (SHDW_SR) The wakeup 0 input is disabled, or was inactive at the time the debouncer triggered a wakeup event. Position  */
#define SHDW_SR_WKUPIS0_ENABLE                (SHDW_SR_WKUPIS0_ENABLE_Val << SHDW_SR_WKUPIS0_Pos)  /* (SHDW_SR) The wakeup 0 input was active at the time the debouncer triggered a wakeup event. Position  */
#define SHDW_SR_Msk                           _UINT32_(0x00010031)                                 /* (SHDW_SR) Register Mask  */

#define SHDW_SR_WKUPIS_Pos                    _UINT32_(16)                                         /* (SHDW_SR Position) Wakeup x Input Status */
#define SHDW_SR_WKUPIS_Msk                    (_UINT32_(0x1) << SHDW_SR_WKUPIS_Pos)                /* (SHDW_SR Mask) WKUPIS */
#define SHDW_SR_WKUPIS(value)                 (SHDW_SR_WKUPIS_Msk & (_UINT32_(value) << SHDW_SR_WKUPIS_Pos)) 

/* -------- SHDW_WUIR : (SHDWC Offset: 0x0C) (R/W 32) Wakeup Inputs Register -------- */
#define SHDW_WUIR_WKUPEN0_Pos                 _UINT32_(0)                                          /* (SHDW_WUIR) Wakeup 0 Input Enable Position */
#define SHDW_WUIR_WKUPEN0_Msk                 (_UINT32_(0x1) << SHDW_WUIR_WKUPEN0_Pos)             /* (SHDW_WUIR) Wakeup 0 Input Enable Mask */
#define SHDW_WUIR_WKUPEN0(value)              (SHDW_WUIR_WKUPEN0_Msk & (_UINT32_(value) << SHDW_WUIR_WKUPEN0_Pos)) /* Assigment of value for WKUPEN0 in the SHDW_WUIR register */
#define   SHDW_WUIR_WKUPEN0_DISABLE_Val       _UINT32_(0x0)                                        /* (SHDW_WUIR) The wakeup 0 input has no wakeup effect.  */
#define   SHDW_WUIR_WKUPEN0_ENABLE_Val        _UINT32_(0x1)                                        /* (SHDW_WUIR) The wakeup 0 input forces wakeup of the core power supply.  */
#define SHDW_WUIR_WKUPEN0_DISABLE             (SHDW_WUIR_WKUPEN0_DISABLE_Val << SHDW_WUIR_WKUPEN0_Pos) /* (SHDW_WUIR) The wakeup 0 input has no wakeup effect. Position  */
#define SHDW_WUIR_WKUPEN0_ENABLE              (SHDW_WUIR_WKUPEN0_ENABLE_Val << SHDW_WUIR_WKUPEN0_Pos) /* (SHDW_WUIR) The wakeup 0 input forces wakeup of the core power supply. Position  */
#define SHDW_WUIR_WKUPT0_Pos                  _UINT32_(16)                                         /* (SHDW_WUIR) Wakeup 0 Input Type Position */
#define SHDW_WUIR_WKUPT0_Msk                  (_UINT32_(0x1) << SHDW_WUIR_WKUPT0_Pos)              /* (SHDW_WUIR) Wakeup 0 Input Type Mask */
#define SHDW_WUIR_WKUPT0(value)               (SHDW_WUIR_WKUPT0_Msk & (_UINT32_(value) << SHDW_WUIR_WKUPT0_Pos)) /* Assigment of value for WKUPT0 in the SHDW_WUIR register */
#define   SHDW_WUIR_WKUPT0_LOW_Val            _UINT32_(0x0)                                        /* (SHDW_WUIR) A falling edge followed by a low level on the wakeup 0 input, for a period defined by WKUPDBC, forces wakeup of the core power supply.  */
#define   SHDW_WUIR_WKUPT0_HIGH_Val           _UINT32_(0x1)                                        /* (SHDW_WUIR) A rising edge followed by a high level on the wakeup 0 input, for a period defined by WKUPDBC, forces wakeup of the core power supply.  */
#define SHDW_WUIR_WKUPT0_LOW                  (SHDW_WUIR_WKUPT0_LOW_Val << SHDW_WUIR_WKUPT0_Pos)   /* (SHDW_WUIR) A falling edge followed by a low level on the wakeup 0 input, for a period defined by WKUPDBC, forces wakeup of the core power supply. Position  */
#define SHDW_WUIR_WKUPT0_HIGH                 (SHDW_WUIR_WKUPT0_HIGH_Val << SHDW_WUIR_WKUPT0_Pos)  /* (SHDW_WUIR) A rising edge followed by a high level on the wakeup 0 input, for a period defined by WKUPDBC, forces wakeup of the core power supply. Position  */
#define SHDW_WUIR_Msk                         _UINT32_(0x00010001)                                 /* (SHDW_WUIR) Register Mask  */

#define SHDW_WUIR_WKUPEN_Pos                  _UINT32_(0)                                          /* (SHDW_WUIR Position) Wakeup x Input Enable */
#define SHDW_WUIR_WKUPEN_Msk                  (_UINT32_(0x1) << SHDW_WUIR_WKUPEN_Pos)              /* (SHDW_WUIR Mask) WKUPEN */
#define SHDW_WUIR_WKUPEN(value)               (SHDW_WUIR_WKUPEN_Msk & (_UINT32_(value) << SHDW_WUIR_WKUPEN_Pos)) 
#define SHDW_WUIR_WKUPT_Pos                   _UINT32_(16)                                         /* (SHDW_WUIR Position) Wakeup x Input Type */
#define SHDW_WUIR_WKUPT_Msk                   (_UINT32_(0x1) << SHDW_WUIR_WKUPT_Pos)               /* (SHDW_WUIR Mask) WKUPT */
#define SHDW_WUIR_WKUPT(value)                (SHDW_WUIR_WKUPT_Msk & (_UINT32_(value) << SHDW_WUIR_WKUPT_Pos)) 

/** \brief SHDWC register offsets definitions */
#define SHDW_CR_REG_OFST               _UINT32_(0x00)      /* (SHDW_CR) Control Register Offset */
#define SHDW_MR_REG_OFST               _UINT32_(0x04)      /* (SHDW_MR) Mode Register Offset */
#define SHDW_SR_REG_OFST               _UINT32_(0x08)      /* (SHDW_SR) Status Register Offset */
#define SHDW_WUIR_REG_OFST             _UINT32_(0x0C)      /* (SHDW_WUIR) Wakeup Inputs Register Offset */

#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief SHDWC register API structure */
typedef struct
{
  __O   uint32_t                       SHDW_CR;            /**< Offset: 0x00 ( /W  32) Control Register */
  __IO  uint32_t                       SHDW_MR;            /**< Offset: 0x04 (R/W  32) Mode Register */
  __I   uint32_t                       SHDW_SR;            /**< Offset: 0x08 (R/   32) Status Register */
  __IO  uint32_t                       SHDW_WUIR;          /**< Offset: 0x0C (R/W  32) Wakeup Inputs Register */
} shdwc_registers_t;


#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */
#endif /* _SAM9X6_SHDWC_COMPONENT_H_ */
