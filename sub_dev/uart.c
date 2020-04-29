/*
 * @Descripttion: 
 * @vesion: 
 * @Author: sunzhguy
 * @Date: 2020-04-29 09:51:40
 * @LastEditor: sunzhguy
 * @LastEditTime: 2020-04-29 14:08:44
 */

#include "uart.h"
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>
#include <errno.h>

 int ev_uart_open(ev_uart_attr_t *attr)
{
    int fd;
	struct termios opt;
    if (-1 == (fd = open(attr->name, O_RDWR | O_NOCTTY | O_NDELAY)))
        goto err1;
	if (0 != tcgetattr(fd, &opt))
		goto err2;
	if (0 != cfsetispeed(&opt, attr->speed))
		goto err2;
	if (0 != cfsetospeed(&opt, attr->speed))
		goto err2;
	/* 8n1 */
	opt.c_cflag &= ~PARENB;
	opt.c_cflag &= ~CSTOPB;
	opt.c_cflag &= ~CSIZE;
	opt.c_cflag |= CS8;
	/* disable flowctrl */
	opt.c_cflag &= ~CRTSCTS;
	/* raw data mode */
	opt.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
	opt.c_oflag &= ~OPOST;
	opt.c_iflag &= ~(BRKINT | INPCK | ISTRIP | ICRNL| IGNCR | IXON);
	tcflush(fd, TCIOFLUSH);
	if(0 != tcsetattr(fd, TCSANOW, &opt))
		goto err2;
	return fd;
err2:
    close(fd);
err1:
    return -1;
}
