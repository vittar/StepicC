//
// Created by vitaly on 10.07.16.
//

#include "stepic64-6.h"
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <cstring>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>


void check_err(int val, const char *name){
    if (val < 0){
        printf("error in %s: %d", name, errno);
        exit(1);
    }
}

void sig_int(int sig){
    return;
}

int stepic646(){
    unsigned SIZEMEM = 1*1024*1024;
    int shmid = shm_open("/test.shm", O_CREAT | O_RDWR, 0666);
    check_err(shmid, "shm_open");
    int res = ftruncate(shmid, SIZEMEM);
    check_err(res, "ftruncate");
    int *arr = (int *)mmap(NULL, SIZEMEM, PROT_READ | PROT_WRITE, MAP_SHARED, shmid, 0);
    memset(arr, 13, SIZEMEM);
    signal(SIGINT, sig_int);
    pause();
    munmap(arr, SIZEMEM);
    shm_unlink("/test.shm");
    return 0;
};