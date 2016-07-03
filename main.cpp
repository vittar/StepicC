#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <fstream>
#include <string>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;

int main(int argc, char *argv[]) {
    char buf[1024];
    ///home/box/in.fifo и /home/box/out.fifo
    char fifoin[] = "/home/box/in.fifo";
    char fifoout[] = "/home/box/out.fifo";
    if(mkfifo(fifoin, 0666) == -1){
        exit(1);
    }
    if(mkfifo(fifoout, 0666) == -1){
        exit(1);
    }
    int fd_in = open(fifoin, O_RDONLY);
    int fd_out = open(fifoout, O_WRONLY);
    while(true){
        ssize_t rb = read(fd_in, buf, 1024);
        if (rb == -1)break;
        write(fd_out, buf, rb);
    };
    return 0;
}