# Project Description

This project aims to configure the Raspberry Pi as a station hotspot, enabling connections with mobile applications for data sharing via HTTP requests. Additionally, it provides the capability to program the Bluepill device through the Raspberry Pi using Firmware Over-The-Air (FOTA) functionality. Below is a brief description of the files included in this repository:

## Files Description:

1. `can_bootloader.c`: 
   - This file contains the code for the CAN bootloader, responsible for transferring the processed data file from the preprogramming script to a Bluepill device over the CAN bus. The communication with the device is established at address `0x111`.

2. `preprograming.py`:
   - This Python script extracts data from an SREC (Motorola S-record) file. The extracted data is intended to be sent to a Bluepill device for programming.

3. `processed_image.txt`:
   - This file likely contains processed image data or related information.

4. `can_recive.c`:
   - This file appears to be related to CAN bus communication, potentially for receiving data from the vehicle, such as speed, direction, temperature, battery charge level, etc. This data can be sent to the mobile application for monitoring and analysis. Refer to the file for details on its usage.

5. `rpihotspot-master`:
   - This directory contains resources or scripts necessary for configuring the Raspberry Pi as a station hotspot. Explore this directory for relevant configuration files or scripts.

## Instructions:

Please follow the instructions provided in this README file to configure the Raspberry Pi as a station hotspot and utilize the included files for data sharing with mobile applications. For detailed guidance on setting up the project environment and usage, refer to the respective sections below.

