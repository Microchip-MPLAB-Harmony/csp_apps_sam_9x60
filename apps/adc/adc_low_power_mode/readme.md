---
parent: Harmony 3 peripheral library application examples for SAM9X60 family
title: ADC low power mode
has_children: false
has_toc: false
---

[![MCHP](https://www.microchip.com/ResourcePackages/Microchip/assets/dist/images/logo.png)](https://www.microchip.com)

# ADC low power

This example application shows the different low power sleep modes available with Fast Wake up either enabled or disabled.

## Description

Conversion of the three analog inputs is triggered from software trigger at every 500 ms. Sleep mode is enabled and ADC core is OFF between conversions. Reference voltage circuitry is either On or Off between conversions depending on FWUP values.  

| Board |
| ----- |
| [SAM9X60 Curiosity Development Board](https://www.microchip.com/en-us/development-tool/EV40E67A) |

Analog input voltage in the range of 0 V to 3.3 V is fed to the ADC input channel AD0, AD1 and AD2. Sleep mode is enabled and Fast Wake up value is selected. ADC conversion result is displayed on the console.

## Downloading and building the application

To clone or download this application from Github, go to the [main page of this repository](https://github.com/Microchip-MPLAB-Harmony/csp_apps_sam_9x60) and then click Clone button to clone this repository or download as zip file.
This content can also be downloaded using content manager by following these [instructions](https://github.com/Microchip-MPLAB-Harmony/contentmanager/wiki).

Path of the application within the repository is **apps/adc/adc_low_power_mode/firmware** .

To build the application, refer to the following table and open the project using its IDE.

| Project Name      | Description                                    |
| ----------------- | ---------------------------------------------- |
| sam_9x60_curiosity.X | MPLABX project for [SAM9X60 Curiosity Development Board](https://www.microchip.com/en-us/development-tool/EV40E67A) |

## Setting up AT91Bootstrap loader

To load the application binary onto the target device, we need to use at91bootstrap loader. Refer to the [at91bootstrap loader documentation](../../docs/readme_bootstrap.md) for details on how to configure, build and run bootstrap loader project and use it to bootstrap the application binaries.

## Setting up the hardware

The following table shows the target hardware for the application projects.

| Project Name| Board|
|:---------|:---------:|
| sam_9x60_curiosity.X | [SAM9X60 Curiosity Development Board](https://www.microchip.com/en-us/development-tool/EV40E67A) |
|||

### Setting up [SAM9X60 Curiosity Development Board](https://www.microchip.com/en-us/development-tool/EV40E67A)

#### Addtional hardware required

- SD Card with FAT32 file system

#### Setting up the SD Card

- Download harmony MPU bootstrap loader from this [location](firmware/at91bootstrap_sam_9x60_ek.X/binaries/boot.bin)
- Copy the downloaded boot loader binary( boot.bin) onto the SD card

#### Setting up the board

- SDMMC slot used for bootloading the application is SDMMC0 (J3)
- Connect the USB port J1 on board to the computer using a micro USB cable (to power the board).
- Use a jumper wire to connect Pin 29 of J9 (AD0 is mapped to Port Pin PB11) to 3.3 V or GND
- Use a jumper wire to connect Pin 32 of J9 (AD1 is mapped to Port Pin PB12) to 3.3 V or GND
- Use a jumper wire to connect Pin 16 of J8 (AD2 is mapped to Port Pin PB13) to 3.3 V or GND
- Use a FTDI cable to connect J11 connector to computer. 

## Running the Application

1. Build the application using its IDE
2. Copy the output binary (named 'harmony.bin') onto the SD Card (Refer to the 'Setting up hardware' section above for setting up the SD card)
3. Insert the SD card into SDMMC slot on the board (Refer to the 'Setting up hardware' section for the correct SDMMC slot)
4. Open the Terminal application (Ex.:Tera term) on the computer.
5. Connect to the EDBG/Jlink Virtual COM port and configure the serial settings as follows:
    - Baud : 115200
    - Data : 8 Bits
    - Parity : None
    - Stop : 1 Bit
    - Flow Control : None
6. Reset the board to run the application
7. The console asks to choose FWUP value
	- Press 0.
	- Observe ADC entering sleep mode with Fast Wake up OFF. Console displays the ADC Count and the ADC Input Voltage
![output](images/output_lowpower_fwupOFF.png)

8. Reset the board to run the application again. In the console window, choose 1 this time. 
	- Observe ADC entering sleep mode with Fast Wake up OFF. Console displays the ADC Count and the ADC Input Voltage
![output](images/output_lowpower_fwupON.png)


	


