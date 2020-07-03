/**
  ******************************************************************************
  * @file    httpclient-netconn.c
  * @author  John Vedder
  * @brief   Basic http client implementation using LwIP netconn API
  ******************************************************************************
  *
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "bsp.h"
#include "lwip/apps/fs.h"
#include "string.h"
#include "api_key.h"
#include "httpclient-netconn.h"
#include "cmsis_os.h"

#include <stdio.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define WEBCLIENT_THREAD_PRIO    ( osPriorityAboveNormal )
#define TS   1

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

static uint32_t    toggle = 0;
static const char *request = 0;
static uint16_t    length = 0;


/**
 * Basic HTTP request with headers.
 * Note: IP address and port are hard-coded here
 * Ref: https://www.w3.org/Protocols/rfc2616/rfc2616-sec14.html
 */

#define TYPE     "Content-Type: text/plain;charset=UTF-8\r\n"
#define HOST     "Host: 192.168.1.113\r\n"
#define CONN     "Connection: close\r\n"
#define AGENT    "User-Agent: LwIP (Nucleo-F429ZI)\r\n"

#define LEN_OFF  "Content-Length: 13\r\n"
#define JSON_OFF "{\"on\":false}\r\n"

#define LEN_ON   "Content-Length: 31\r\n"
#define JSON_ON  "{\"on\":true,\"bri\":254,\"ct\":366}\r\n"

static const char LIGHT_ON[]  = "PUT /api/" API_KEY "/lights/9/state HTTP/1.1\r\n" HOST CONN TYPE AGENT LEN_ON  "\r\n" JSON_ON;
static const char LIGHT_OFF[] = "PUT /api/" API_KEY "/lights/9/state HTTP/1.1\r\n" HOST CONN TYPE AGENT LEN_OFF "\r\n" JSON_OFF;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  http server thread 
  * @param arg: pointer on argument(not used here) 
  * @retval None
  */
static void http_client_netconn_request( )
{
    struct netconn *conn;
    err_t err;

    struct netbuf *inbuf;
    char *buf;
    u16_t buflen;


    if (TS) printf("[%lu] ", HAL_GetTick());
    printf( "http_client_netconn_request() starting\r\n" );

    if (TS) printf("[%lu] ", HAL_GetTick());
    printf( "netconn_new()\r\n" );

    /* Create a new TCP connection handle */
    conn = netconn_new( NETCONN_TCP );
    if ( conn != NULL )
    {
        /* define the server address and port */
        //ip_addr_t ipaddr;
        //IP4_ADDR( &ipaddr, 192, 168, 1, 30 );
#if 0
        /* 192.168.1.30   = 0xC0 . 0xA8 . 0x01 . 0x1E ==> 0x1E01A8C0 */
        const ip_addr_t ipaddr = { (u32_t) 0x1E01A8C0 };
        const u16_t port = 8080;
#else
        /* 192.168.1.113  = 0xC0 . 0xA8 . 0x01 . 0x71 ==> 0x7101A8C0 */
        const ip_addr_t ipaddr = { (u32_t) 0x7101A8C0 };
        const u16_t port = 80;
#endif
        if (TS) printf("[%lu] ", HAL_GetTick());
        printf( "netconn_connect()\r\n" );
        printf( "  addr: %8lX, port: %d\r\n", ipaddr.addr, port);

        /* connect to ip address and port */
        err = netconn_connect( conn, &ipaddr, port );
        if ( err == ERR_OK )
        {
            if (TS) printf("[%lu] ", HAL_GetTick());
            printf( "netconn_write()\r\n" );

            if (toggle)
            {
                request = LIGHT_OFF;
                length = sizeof(LIGHT_OFF);
                toggle = 0;
            }
            else
            {
                request = LIGHT_ON;
                length = sizeof(LIGHT_ON);
                toggle = 1;
            }
            printf( "#REQUEST START#\r\n" );
            HAL_UART_Transmit( &huart3, (uint8_t*)request, (uint16_t)length, 5000 );
            printf( "#REQUEST END#\r\n" );

            /* write the HTTP request to the server */
            err = netconn_write( conn, (const unsigned char* )request, (size_t)length, NETCONN_NOCOPY );
            if ( err == ERR_OK )
            {
                if (TS) printf("[%lu] ", HAL_GetTick());
                printf( "start while loop\r\n" );

                while(1)
                {
                    if (TS) printf("[%lu] ", HAL_GetTick());
                    printf( "netconn_recv()\r\n" );

                    /* Read the data from the port, blocking if nothing yet there yet. */
                    err = netconn_recv( conn, &inbuf );
                    if ( err == ERR_OK )
                    {
                        if (TS) printf("[%lu] ", HAL_GetTick());
                        printf( "netconn_err() #1\r\n" );
                        err = netconn_err( conn );
                        if( err != ERR_OK )
                        {
                            if (TS) printf("[%lu] ", HAL_GetTick());
                            printf( "netconn_err() failed: %d\r\n", err );
                            break;
                        }

                        if (TS) printf("[%lu] ", HAL_GetTick());
                        printf( "netbuf_data()\r\n" );
                        err = netbuf_data( inbuf, (void**) &buf, &buflen );
                        if ( err == ERR_OK )
                        {
                            if (TS) printf("[%lu] ", HAL_GetTick());
                            printf( "length: %d\r\n", buflen );
                            printf( "#BUFFER START#\r\n" );
                            HAL_UART_Transmit( &huart3, (uint8_t*) buf, buflen,
                                    1000 );
                            printf( "#BUFFER END#\r\n" );

                            /* release the buffer */
                            netbuf_delete( inbuf );
                        }
                        else /* netbuf_data(..) != ERR_OK */
                        {
                            if (TS) printf("[%lu] ", HAL_GetTick());
                            printf( "netbuf_data() failed: %d\r\n", err );
                            break;
                        }
                    }
                    else /* netconn_recv(..) != ERR_OK */
                    {
                        if (TS) printf("[%lu] ", HAL_GetTick());
                        printf( "netconn_recv() failed: %d\r\n", err );
                        break;
                    }

                    /* bottom of while loop */

                    if (TS) printf("[%lu] ", HAL_GetTick());
                    printf( "netconn_err() #2\r\n" );
                    err =  netconn_err( conn );
                    if( err != ERR_OK )
                    {
                        if (TS) printf("[%lu] ", HAL_GetTick());
                        printf( "netconn_err() failed: %d\r\n", err );
                        break;
                    }
                } /* while loop */

                if (TS) printf("[%lu] ", HAL_GetTick());
                printf( "exit while loop\r\n" );

            }
            else /* netconn_write(..) != ERR_OK */
            {
                if (TS) printf("[%lu] ", HAL_GetTick());
                printf( "netconn_write() failed: %d\r\n", err );
            }

            /* close the connection */

            if (TS) printf("[%lu] ", HAL_GetTick());
            printf( "netconn_close()\r\n" );
            err = netconn_close( conn );
            if ( err != ERR_OK )
            {
                if (TS) printf("[%lu] ", HAL_GetTick());
                printf( "netconn_close() failed\r\n" );
            }

        }
        else /* netconn_connect(..) != ERR_OK */
        {
            if (TS) printf("[%lu] ", HAL_GetTick());
            printf( "netconn_connect() failed: %d\r\n", err );
        }
        netconn_delete(conn);
    }
    else
    {
        if (TS) printf("[%lu] ", HAL_GetTick());
        printf( "netconn_new() returned NULL\r\n" );
    }

    if (TS) printf("[%lu] ", HAL_GetTick());
    printf( "http_client_netconn_request() exiting\r\n" );
}

/**
  * @brief  http client thread
  * @param arg: pointer on argument(not used here)
  * @retval None
  */
static void http_client_netconn_thread(void *arg)
{
    for(;;)
    {
        if (BSP_Button_GetState() == 1)
        {
            http_client_netconn_request();
            osDelay(2000);
        }
        else
        {
            osDelay(100);
        }
    }
}

/**
  * @brief  Initialize the HTTP server (start its thread) 
  * @param  none
  * @retval None
  */
void http_client_netconn_init()
{
  sys_thread_new("REQST", http_client_netconn_thread, NULL, DEFAULT_THREAD_STACKSIZE, WEBCLIENT_THREAD_PRIO);
}
