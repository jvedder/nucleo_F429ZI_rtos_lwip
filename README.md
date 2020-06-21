## nucleo_F429ZI_rtos_lwip

This project is a port of the **LwIP_HTTP_Server_Netconn_RTOS** project found in
**STM32Cube_FW_F4_V1.25.0** for the **STM32F429ZI-Nucleo** board. 
I am using this project to tinker with LwIP and FreeRTOS.  Currently I am developing
the code in the httpclient-netconn.c/.h to GET/POST data to a web server.

This project compiles in __System Workbench for STM32__ ([openstm32.org](https://www.openstm32.org/)) 
under Eclipse. The original ST project in **STM32Cube_FW_F4** contained virtual
links to the Driver and Middleware files. All those files were pulled into
the Eclipse project and the virtual links removed, allowing this repo to stand alone.

I needed to modify the BSP (Board Support Package) files in the **STM32Cube_FW_F4** for this 
Nucleo board, so those files have been pulled into the project source folder.

Please see the ST Microelectronics licenses in their respective files and **st_readme.txt**.

I appreciate the support of [Ac6](https://www.ac6.fr/) towards free tools for the STM32 microcontrollers.



