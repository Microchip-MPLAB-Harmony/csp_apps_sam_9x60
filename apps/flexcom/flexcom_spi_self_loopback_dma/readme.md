---
parent: Harmony 3 peripheral library application examples for SAM9X60 family
title: FLEXCOM SPI self loopback dma  
has_children: false
has_toc: false
---

[![MCHP](https://www.microchip.com/ResourcePackages/Microchip/assets/dist/images/logo.png)](https://www.microchip.com)

# FLEXCOM SPI self loopback dma 

This example application shows how to use the FLEXCOM SPI peripheral with DMA to transmit and receive a block of data.

## Description

This example demonstrates transmit and receive operation over FLEXCOM SPI interface using DMA. Two DMA channels are used - one for transmission and another for receiption. The loop back test requires the MOSI output pin to be connected to the MISO input pin so that anything transmitted will also be received.
The example first transmits 10 bytes and receives 10 bytes. If the received data is same as transmitted then it transmits 0 bytes and receives 10 bytes. In this case, dummy data will be transmitted to receive 10 characters, hence all the received data should be 0xFF. Next, 10 bytes are transmitted and 5 bytes are received. Here, the received bytes must match the first 5 bytes in the transmit buffer. Finally, 5 bytes are transmitted and 10 bytes are received. In this case, the first 5 bytes in the receive buffer must match the first 5 bytes in the transmit buffer. The remaining 5 bytes in the receive buffer must be 0xFF.

## Downloading and building the application

To clone or download this application from Github, go to the [main page of this repository](https://github.com/Microchip-MPLAB-Harmony/csp_apps_sam_9x60) and then click Clone button to clone this repository or download as zip file.
This content can also be downloaded using content manager by following these [instructions](https://github.com/Microchip-MPLAB-Harmony/contentmanager/wiki).

Path of the application within the repository is **apps/flexcom/flexcom_spi_self_loopback_dma/firmware** .

To build the application, refer to the following table and open the project using its IDE.

| Project Name      | Description                                    |
| ----------------- | ---------------------------------------------- |
| sam_9x60_ek.X | MPLABX project for [SAM9X60-EK Evaluation Kit](https://www.microchip.com/developmenttools/ProductDetails/DT100126) |
|||

## Setting up AT91Bootstrap loader

To load the application binary onto the target device, we need to use at91bootstrap loader. Refer to the [at91bootstrap loader documentation](../../docs/readme_bootstrap.md) for details on how to configure, build and run bootstrap loader project and use it to bootstrap the application binaries.

## Setting up the hardware

The following table shows the target hardware for the application projects.

| Project Name| Board|
|:---------|:---------:|
| sam_9x60_ek.X | [SAM9X60-EK Evaluation Kit](https://www.microchip.com/developmenttools/ProductDetails/DT100126) |
|||

### Setting up [SAM9X60-EK Evaluation Kit](https://www.microchip.com/developmenttools/ProductDetails/DT100126)

#### Addtional hardware required

- SD Card with FAT32 file system

#### Setting up the SD Card

- Download harmony MPU bootstrap loader from this [location](firmware/at91bootstrap_sam_9x60_ek.X/binaries/boot.bin)
- Copy the downloaded boot loader binary( boot.bin) onto the SD card

#### Setting up the board

- Use jumper wire to Connect "Pin 19 of J16 Connector" to "Pin 21 of J16 Connector"
  - FLEXCOM4 MOSI signal is mapped to PA12 that is routed to "Pin 19 of J16 Connector"
  - FLEXCOM4 MISO signal is mapped to PA11 that is routed to "Pin 21 of J16 Connector"
- SDMMC slot used for bootloading the application is SDMMC0 (J4)
- Connect the USB port J22 on board to the computer using a micro USB cable (to enable debug com port)
- Connect the USB port J7 on board to the computer using a micro USB cable (to power the board)
- *NOTE - Reset push button is labelled as SW3*

## Running the Application

1. Build the application using its IDE
2. Copy the output binary (named 'harmony.bin') onto the SD Card (Refer to the 'Setting up hardware' section above for setting up the SD card)
3. Insert the SD card into SDMMC slot on the board (Refer to the 'Setting up hardware' section for the correct SDMMC slot)
4. Reset the board to run the application
5. LED indicates the success or failure:
    - The LED is turned ON when the received data matches the transmitted data

Following table provides the LED name:

| Board      | LED Name                                    |
| ----------------- | ---------------------------------------------- |
| [SAM9X60-EK Evaluation Kit](https://www.microchip.com/developmenttools/ProductDetails/DT100126) | RGB_LED(Green)  |
|||
