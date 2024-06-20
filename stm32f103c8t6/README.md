# Project Description

This project directory encompasses various components necessary for developing and deploying an embedded system application on the STM32F103C8T6 microcontroller. Below is a consolidated description of the three main folders included:

1. `drivers`:
   - This directory contains two subfolders:
     - `hal`: Hosts hardware abstraction layer (HAL) drivers facilitating interaction with hardware peripherals.
     - `app`: Contains application-specific algorithms responsible for controlling the vehicle's behavior.

2. `dynamic_project`:
   - This folder houses the complete project setup, integrating FreeRTOS for real-time operating system functionality. It includes source files, configuration files, and implementation of algorithms controlling the vehicle's behavior. The project is structured to efficiently manage concurrent tasks with different priorities and timing requirements.

3. `stm32f103_can_bootloader`:
   - This directory encompasses the bootloader responsible for receiving firmware updates from the Raspberry Pi over the CAN bus. The bootloader stores the received firmware on the microcontroller and has the capability to execute it, enabling over-the-air (FOTA) updates of the device firmware. It contains source code and configuration files on using the bootloader for firmware updates.

Together, these folders provide essential resources for developing and deploying embedded systems applications on the STM32F103C8T6 microcontroller, including hardware drivers, application-specific logic, real-time task management, and firmware update capabilities.

