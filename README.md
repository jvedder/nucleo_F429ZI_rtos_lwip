# Project: nucleo_F429ZI_rtos_lwip

This project is a port of the **LwIP_HTTP_Server_Netconn_RTOS** project found in
**STM32Cube_FW_F4_V1.25.0** for the **STM32F429ZI-Nucleo** board. 
I was using this project to tinker with LwIP and FreeRTOS. I am no longer actively
working on it.  

I have a working example in `httpclient-netconn.c/.h` to `POST` 
a small snippet of JSON data to a Phillips HUE server. The code will toggle light #9
on/off with pressing the blue user button on the Nucleo board. The IP address and 
JSON details are are hard-coded.

Note: you need to add `#define API_KEY "string_constant"` in `Inc/api_key.h`, which is 
not included in the  repo. See the Phillips Hue Developers
[Getting Started](https://developers.meethue.com/develop/get-started-2/) documentation to create 
an API key.

The `httpserver-netconn.c` web server in the original example project has been
disabled, but the code is still present.
 
This project compiles in  _System Workbench for STM32_  \([openstm32.org](https://www.openstm32.org/)\) 
under Eclipse. The original ST project in **STM32Cube_FW_F4** contained virtual
links to the Driver and Middleware source and include files. All those files were pulled into
the Eclipse project and the virtual links removed, allowing this repo to stand alone.

I had to modify the BSP (Board Support Package) files in the **STM32Cube_FW_F4** for this 
Nucleo board, so those files have been moved from `Drivers/BSP/` into the `Src/` folder.

Please see the ST Microelectronics licenses in their respective files and `st_readme.txt`. 

I appreciate the support of [Ac6](https://www.ac6.fr/) towards free compiler tools for the STM32
microcontrollers and the availability of Eclipse, FreeRTOS, and LWIP as free and open software.

