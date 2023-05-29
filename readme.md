---
title: Harmony 3 peripheral library application examples for SAM9X60 family
nav_order: 1
has_children: true
has_toc: false
---
[![MCHP](https://www.microchip.com/ResourcePackages/Microchip/assets/dist/images/logo.png)](https://www.microchip.com)

# Harmony 3 peripheral library application examples for SAM9X60 family

MPLAB® Harmony 3 is an extension of the MPLAB® ecosystem for creating embedded firmware solutions for Microchip 32-bit SAM and PIC® microcontroller and microprocessor devices.  Refer to the following links for more information.

- [Microchip 32-bit MCUs](https://www.microchip.com/design-centers/32-bit)
- [Microchip 32-bit MPUs](https://www.microchip.com/design-centers/32-bit-mpus)
- [Microchip MPLAB X IDE](https://www.microchip.com/mplab/mplab-x-ide)
- [Microchip MPLAB® Harmony](https://www.microchip.com/mplab/mplab-harmony)
- [Microchip MPLAB® Harmony Pages](https://microchip-mplab-harmony.github.io/)

This repository contains the MPLAB® Harmony 3 peripheral library application examples for SAM9X60 family

- [Release Notes](release_notes.md)
- [MPLAB® Harmony License](mplab_harmony_license.md)

To clone or download these applications from Github, go to the [main page of this repository](https://github.com/Microchip-MPLAB-Harmony/csp_apps_sam_9x60) and then click **Clone** button to clone this repository or download as zip file.
This content can also be downloaded using content manager by following these [instructions](https://github.com/Microchip-MPLAB-Harmony/contentmanager/wiki).

## Contents Summary

| Folder     | Description                             |
| ---        | ---                                     |
| apps       | Contains peripheral library example applications |
| docs       | Contains documentation in html format for offline viewing (to be used only after cloning this repository onto a local machine). Use [github pages](https://microchip-mplab-harmony.github.io/csp_apps_sam_9x60/) of this repository for viewing it online. |

## Code Examples

The following applications are provided to demonstrate the typical or interesting usage models of one or more peripheral libraries.

| Name | Description |
| ---- | ----------- |
| [ADC automatic window comparison](apps/adc/adc_automatic_window_comparison/readme.md) | This example application shows how to sample an analog input in polled mode and send the converted data to console using automatic window comparison of converted values |
| [ADC low power](apps/adc/adc_low_power_mode/readme.md) | This example application shows the different low power sleep modes available with Fast Wake up either enabled or disabled |
| [ADC Polling](apps/adc/adc_polled_mode/readme.md) | This example application shows how to sample an analog input in polled mode and send the converted data to console |
| [ADC user sequence](apps/adc/adc_user_sequence/readme.md) | This example application shows how to sample three analog inputs using the user sequencer in software trigger mode and send the converted data to the console |
| [CAN blocking](apps/can/can_normal_operation_blocking/readme.md) | This example application shows how to use the CAN module to transmit and receive CAN messages in polling mode |
| [CAN interrupt](apps/can/can_normal_operation_interrupt/readme.md) | This example application shows how to use the CAN module to transmit and receive CAN messages in interrupt mode |
| [CAN interrupt with timestamp](apps/can/can_normal_operation_interrupt_timestamp/readme.md) | This example application shows how to use the CAN module to transmit and receive CAN messages in interrupt mode |
| [Clock configuration](apps/clock/clock_config/readme.md) | This example application shows how to configure the clock system to run the device at maximum frequency. It also outputs a prescaled clock signal on a GPIO pin for measurement and verification |
| [Low power modes](apps/clock/low_power/readme.md) | This example application shows how to enter low power modes of SAM9X60 MPU |
| [DBGU blocking](apps/dbgu/dbgu_echo_blocking/readme.md) | This example application demonstrates how to use the DBGU peripheral to transfer a block of data in a blocking manner |
| [DBGU Interrupt](apps/dbgu/dbgu_echo_interrupt/readme.md) | This example application demonstrates how to use the DBGU peripheral to transfer a block of data in a non-blocking manner |
| [DBGU ring buffer](apps/dbgu/dbgu_ring_buffer_interrupt/readme.md) | This example application shows how to use DBGU peripheral in ring buffer mode |
| [FLEXCOM SPI EEPROM read write](apps/flexcom/flexcom_spi_eeprom/readme.md) | This example application shows how to use the flexcom module in SPI mode |
| [FLEXCOM SPI self loopback dma ](apps/flexcom/flexcom_spi_self_loopback_dma/readme.md) | This example application shows how to use the FLEXCOM SPI peripheral with DMA to transmit and receive a block of data |
| [FLEXCOM TWI (I2C) EEPROM](apps/flexcom/flexcom_twi_eeprom/readme.md) | This example application shows how to use the flexcom module in TWI mode |
| [FLEXCOM USART blocking](apps/flexcom/flexcom_usart_echo_blocking/readme.md) | This example application shows how to use the flexcom module in USART mode |
| [FLEXCOM USART interrupt](apps/flexcom/flexcom_usart_echo_interrupt/readme.md) | This example application shows how to use the flexcom module in USART mode |
| [FLEXCOM USART ring buffer](apps/flexcom/flexcom_usart_ring_buffer_interrupt/readme.md) | This example application shows how to use the FLEXCOM peripheral in USART ring buffer mode |
| [OTPC read write (emulation)](apps/otpc/otpc_read_write_emulation/readme.md) | This example application shows how to use the OTPC Peripheral library to perform OTP operations |
| [PIO interrupt](apps/pio/pio_led_on_off_interrupt/readme.md) | This example application shows how to generate GPIO interrupt on switch press and release, and indicate the switch status using the LED |
| [PIO polling](apps/pio/pio_led_on_off_polling/readme.md) | This example application shows how to poll the switch input, and indicate the switch status using the LED |
| [PIT polling](apps/pit/led_toggle_polling/readme.md) | This example application shows how to use PIT counter in polling mode |
| [PIT period change](apps/pit/period_change/readme.md) | This example application shows how PIT period can be changed during runtime |
| [PIT start stop](apps/pit/start_stop/readme.md) | This example application shows how PIT can be started and stopped at runtime |
| [PIT64B periodic interrupt](apps/pit64b/led_toggle_interrupt/readme.md) | This application shows how to use PIT64B counter in interrupt mode |
| [PWM channels](apps/pwm/pwm_channels/readme.md) | This example demonstrates how to use the PWM peripheral to generate PWM signals |
| [RSTC interrupt](apps/rstc/led_switcher/readme.md) | This example application shows how to use the RSTC peripheral to generate an interrupt instead of generating a reset, when the Reset switch is pressed on board |
| [RSTC reset cause](apps/rstc/rstc_reset_cause/readme.md) | This example shows how to use the RSTC peripheral to indicate the cause of the device reset |
| [RTC alarm interrupt](apps/rtc/rtc_alarm/readme.md) | This example application shows how to use the RTC to configure the time and generate the alarm |
| [RTT alarm interrupt](apps/rtt/rtt_alarm/readme.md) | This example application shows how to use the RTT to generate alarm interrupt |
| [RTT periodic interrupt](apps/rtt/rtt_periodic_timeout/readme.md) | This example application shows how to use the RTT to generate periodic interrupts |
| [TC capture mode](apps/tc/tc_capture_mode/readme.md) | This example application shows how to use the TC module in capture mode to measure duty cycle and frequency of an external input |
| [TC compare mode](apps/tc/tc_compare_mode/readme.md) | This example application shows how to use the TC module in compare mode to generate an active low, active high, and toggle output on compare match |
| [TC timer mode](apps/tc/tc_timer_mode/readme.md) | This example application shows how to use the TC module in timer mode to generate periodic interrupt |
| [TRNG random number](apps/trng/random_number/readme.md) | This example application shows how to use the TRNG Peripheral library to generate and read a random number |
| [WDT timeout](apps/wdt/wdt_timeout/readme.md) | This example application shows how to generate a Watchdog timer reset by emulating a deadlock |
| [XDMAC memory transfer](apps/xdmac/xdmac_memory_transfer/readme.md) | This example application shows how to use the XDMAC peripheral to do a memory to memory transfer and illustrates the usage of burst size to reduce the transfer time |

____

[![License](https://img.shields.io/badge/license-Harmony%20license-orange.svg)](https://github.com/Microchip-MPLAB-Harmony/csp_apps_sam_9x60/blob/master/mplab_harmony_license.md)
[![Latest release](https://img.shields.io/github/release/Microchip-MPLAB-Harmony/csp_apps_sam_9x60.svg)](https://github.com/Microchip-MPLAB-Harmony/csp_apps_sam_9x60/releases/latest)
[![Latest release date](https://img.shields.io/github/release-date/Microchip-MPLAB-Harmony/csp_apps_sam_9x60.svg)](https://github.com/Microchip-MPLAB-Harmony/csp_apps_sam_9x60/releases/latest)
[![Commit activity](https://img.shields.io/github/commit-activity/y/Microchip-MPLAB-Harmony/csp_apps_sam_9x60.svg)](https://github.com/Microchip-MPLAB-Harmony/csp_apps_sam_9x60/graphs/commit-activity)
[![Contributors](https://img.shields.io/github/contributors-anon/Microchip-MPLAB-Harmony/csp_apps_sam_9x60.svg)]()

____

[![Follow us on Youtube](https://img.shields.io/badge/Youtube-Follow%20us%20on%20Youtube-red.svg)](https://www.youtube.com/user/MicrochipTechnology)
[![Follow us on LinkedIn](https://img.shields.io/badge/LinkedIn-Follow%20us%20on%20LinkedIn-blue.svg)](https://www.linkedin.com/company/microchip-technology)
[![Follow us on Facebook](https://img.shields.io/badge/Facebook-Follow%20us%20on%20Facebook-blue.svg)](https://www.facebook.com/microchiptechnology/)
[![Follow us on Twitter](https://img.shields.io/twitter/follow/MicrochipTech.svg?style=social)](https://twitter.com/MicrochipTech)

[![](https://img.shields.io/github/stars/Microchip-MPLAB-Harmony/csp_apps_sam_9x60.svg?style=social)]()
[![](https://img.shields.io/github/watchers/Microchip-MPLAB-Harmony/csp_apps_sam_9x60.svg?style=social)]()