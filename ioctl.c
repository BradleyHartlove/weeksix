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
    int openReturn = open("/dev/pts/1", O_RDONLY);
    int errno;
    if(openReturn == -1){
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
    } 

    
}