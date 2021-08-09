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

struct winsize changeValues(struct winsize win){
    win.ws_row = 50;
    win.ws_col = 50;
    win.ws_xpixel = 50;
    win.ws_ypixel = 50;
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
    if(isTty == -1){
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        exit(-1);
    }

    

}