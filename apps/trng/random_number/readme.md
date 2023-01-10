---
parent: Harmony 3 peripheral library application examples for SAM9X60 family
title: TRNG random number 
has_children: false
has_toc: false
---

[![MCHP](https://www.microchip.com/ResourcePackages/Microchip/assets/dist/images/logo.png)](https://www.microchip.com)

# TRNG random number

This example application shows how to use the TRNG Peripheral library to generate and read a random number.

## Description

This example application shows how to use the TRNG peripheral library to produce a 32-bit true random number. Generated random number can be used as an entropy source for seeding a Deterministic Random Number Generator (DRNG), creating cryptographic keys for ciphers etc.

## Downloading and building the application

To clone or download this application from Github, go to the [main page of this repository](https://github.com/Microchip-MPLAB-Harmony/csp_apps_sam_9x60) and then click Clone button to clone this repository or download as zip file.
This content can also be downloaded using content manager by following these [instructions](https://github.com/Microchip-MPLAB-Harmony/contentmanager/wiki).

Path of the application within the repository is **apps/trng/random_number/firmware** .

To build the application, refer to the following table and open the project using its IDE.

| Project Name      | Description                                    |
| ----------------- | ---------------------------------------------- |
| sam_9x60_curiosity.X | MPLABX project for [SAM9X60 Curiosity Development Board](https://www.microchip.com/en-us/development-tool/EV40E67A) |
|||

## Setting up AT91Bootstrap loader

To load the application binary onto the target device, we need to use at91bootstrap loader. Refer to the [at91bootstrap loader documentation](../../docs/readme_bootstrap.md) for details on how to configure, build and run bootstrap loader project and use it to bootstrap the application binaries.

## Setting up the hardware

The following table shows the target hardware for the application projects.

| Project Name| Board|
|:---------|:---------:|
| sam_9x60_curiosity.X | [SAM9X60 Curiosity Development Board](https://www.microchip.com/en-us/development-tool/EV40E67A) |
|||

### Setting up [SAM9X60 Curiosity Development Board](https://www.microchip.com/en-us/development-tool/EV40E67A)

- Connect a programming cable from JTAG connector J12 on board to programmer(J-32 Debugger).
- Connect programmer(J-32 Debugger) to computer using a micro USB cable. 
- Connect the USB port J1 on board to the computer using a micro USB cable (to power the board).
- Connect a FTDI cable from J11 connector to computer.


## Running the Application

1. Open the Terminal application (Ex.:Tera term) on the computer.
2. Connect to the USB Serial COM port and configure the serial settings as follows:
    - Baud : 115200
    - Data : 8 Bits
    - Parity : None
    - Stop : 1 Bit
    - Flow Control : None
3. Build and Program the application using its IDE.
4. The console displays the following message

    ![output](images/output_trng_random_number_1.png)

6. Every time the switch is pressed, a new 32 bit random number is generated and displayed on the console

    ![output](images/output_trng_random_number_2.png)

Following table provides the switch name:

| Board      | Switch Name  |
| ---------- | ------------ |
| [SAM9X60 Curiosity Development Board](https://www.microchip.com/en-us/development-tool/EV40E67A) | USER SW |
|||
