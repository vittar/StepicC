#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <fstream>
#include <string>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>

using namespace std;

void child(int sock){
    pause();
}

void parent(int sock) {
    pause();

}

int main(int argc, char *argv[]) {
    int sv[2];
    int pid;

    if (socketpair(AF_LOCAL, SOCK_STREAM, 0, sv) < 0) {
        perror("socketpair");
        exit(1);
    }
    switch ((pid = fork())) {
        case 0:
            close(sv[0]);
            child(sv[1]);
            break;
        case -1:
            perror("fork");
            return 1;
        default:
            close(sv[1]);
            parent(sv[0]);
            break;
    }
    return 0;
}