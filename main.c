/*
 * @Descripttion: 
 * @vesion: 
 * @Author: sunzhguy
 * @Date: 2020-04-28 17:13:09
 * @LastEditor: sunzhguy
 * @LastEditTime: 2020-04-29 14:58:02
 */
#include "uloop.h"
#include "sub_dev/uart.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>

static void read_uart_callback(struct uloop_fd *u, unsigned int events)
{
    unsigned char buffer[1024] = {0};
    int len = 0;
    int ii;
    if (ULOOP_READ) {
        len = read(u->fd, buffer, 128);
        if (len > 0) 
        {
            {
                #if 0
                char PrintBuff[1024];
                int uiPrintLen = 0;
                uiPrintLen = sprintf((PrintBuff + uiPrintLen), "######## Uart Read(%02d)", len);
                for(ii = 0; ii < len; ii++)
                {
                    uiPrintLen += sprintf((PrintBuff + uiPrintLen),"%02X ", buffer[ii]);
                }
                #endif
                printf("%s\r\n", buffer);
            }
        }
    }
}

static void timeout_cb(struct uloop_timeout *t)
{
	printf("+++++timeout:\r\n");
	uloop_timeout_set(t, 50000);//设置下次的超时时间
}


static void uartpthread_creator() 
{
    int ret =0;
    struct uloop_fd ev_uart_fd;
    struct ev_uart_attr uart_attr;
    sprintf(uart_attr.name,"/dev/ttyUSB0");
    uart_attr.speed = B115200;
    int fd = ev_uart_open(&uart_attr);
    if(fd < 0)
    {
        printf("uart open failed....\r\n");
        return NULL;
    }
     ev_uart_fd.fd = fd;
     ev_uart_fd.cb = read_uart_callback;
     uloop_fd_add(&ev_uart_fd,ULOOP_READ);
}



struct uloop_timeout timeout;
void timer_creator(void)
{
 
 timeout.cb = timeout_cb; 
 uloop_timeout_set(&timeout,500); 
    
}


int main()
{

    uloop_init(); 
    timer_creator();
    uartpthread_creator();
    uloop_run();
    printf("hello wolrd\r\n");

}




