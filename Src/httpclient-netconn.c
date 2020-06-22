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
#include "main.h"
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

/**
 * Basic HTTP request with headers.
 * Note: IP address and port are hard-coded here
 * Ref: https://www.w3.org/Protocols/rfc2616/rfc2616-sec14.html
 */
static const char REQUEST[] = "GET / HTTP/1.1\r\nHost: 192.168.1.30:8080\r\nConnection: close\r\nAccept-Encoding: identity\r\n\r\n";

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
        /* 192.168.1.30  = 0xC0 . 0xA8 . 0x01 . 0x1E ==> 0x1E01A8C0 */
        const ip_addr_t ipaddr = { (u32_t) 0x1E01A8C0 };
        const u16_t port = 8080;

        if (TS) printf("[%lu] ", HAL_GetTick());
        printf( "netconn_connect()\r\n" );
        printf( "  addr: %8lX, port: %d\r\n", ipaddr.addr, port);

        /* connect to ip address and port */
        err = netconn_connect( conn, &ipaddr, port );
        if ( err == ERR_OK )
        {
            if (TS) printf("[%lu] ", HAL_GetTick());
            printf( "netconn_write()\r\n" );

            /* write the HTTP request to the server */
            err = netconn_write( conn, (const unsigned char* )REQUEST, (size_t )sizeof(REQUEST), NETCONN_NOCOPY );
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
                            printf( "#Buffer Start#\r\n" );
                            HAL_UART_Transmit( &huart3, (uint8_t*) buf, buflen,
                                    1000 );
                            printf( "#Buffer End#\r\n" );

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
        if (BSP_PB_GetState(BUTTON_USER) == 1)
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
