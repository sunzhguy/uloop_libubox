/*
 * @Descripttion: 
 * @vesion: 
 * @Author: sunzhguy
 * @Date: 2020-04-29 09:51:35
 * @LastEditor: sunzhguy
 * @LastEditTime: 2020-04-29 10:54:00
 */

#ifndef _UART_H
#define _UART_H

#include <termios.h>

struct ev_uart_attr {
    char name[16];
    speed_t speed;
};
typedef struct ev_uart_attr ev_uart_attr_t;

int ev_uart_open(ev_uart_attr_t *attr);
#endif