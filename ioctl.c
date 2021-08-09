/*****************************************************************************
/ PROGRAM NAME: ioctl.c
/ AUTHOR:       Bradley Hartlove
/ COURSE:       CS431
/ SYNOPSIS:     This program utilizes the ioctl system call to change the
                size attributes of the tty virtual terminal. There are
                calls such as isatty as well in order to verify the terminal
                is indeed being opened correctly.
/
/               (c) Regis University
/ *****************************************************************************/

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <asm-generic/ioctls.h>
#include <termios.h>

struct winsize changeValues(struct winsize win){
    win.ws_row = 50;
    win.ws_col = 50;
    win.ws_xpixel = 50;
    win.ws_ypixel = 50;
    return win;
}

void printWinsize(struct winsize win){
    printf("\nWinsize Attributes: \nws_row: %d\nws_col: %d\nws_xpixel: %d\nws_ypixel: %d\n", 
    win.ws_row, win.ws_col, win.ws_xpixel, win.ws_ypixel);
}

int main(){
    //2.1 Open the device
    int fd = open("/dev/pts/1", O_RDONLY);
    int errno;
    if(fd == -1){
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        exit(-1);
    } 

    //Check if the device is our virtual terminal
    int isTty = isatty(fd);
    if(isTty == 0){
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        exit(-1);
    }

    //2.2 Read Devices Attributes
    struct winsize win;
    int ioCtlReturn = ioctl(fd, TIOCGWINSZ, &win);
    if(ioCtlReturn == -1)
    {
        fprintf(stderr, "Error with ioctl system call: %s\n", strerror(errno));
        exit(-1);
    }

    printWinsize(win);

    //2.3 Set Device Attributes
    win = changeValues(win);
    int changeIoReturn = ioctl(fd, TIOCSWINSZ, &win);
    if(ioCtlReturn == -1)
    {
        fprintf(stderr, "Error with ioctl system call: %s\n", strerror(errno));
        exit(-1);
    }

    struct winsize newWin;
    int newIoReturn = ioctl(fd, TIOCGWINSZ, &newWin);
    if(newIoReturn == -1)
    {
        fprintf(stderr, "Error with ioctl system call: %s\n", strerror(errno));
        exit(-1);
    }

    printWinsize(newWin);

    return 0;
}