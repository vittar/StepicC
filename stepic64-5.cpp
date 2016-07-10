//
// Created by vitaly on 10.07.16.
//

#include "stepic64-5.h"
#include <cstdio>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstring>
#include <signal.h>

void check_err(int val, const char *name){
    if (val < 0){
        printf("error in %s: %d", name, errno);
        exit(1);
    }
}

void sig_int(int sig){
    return;
}

int stepic645(){
    key_t key = ftok("/tmp/mem.temp", 1);
    unsigned SIZEMEM = 2*1024*1024;
    check_err(key, "ftok");
    int shmid = shmget(key, SIZEMEM, 0666|IPC_CREAT);
    check_err(shmid, "shmget");
    int *arr = (int *)shmat(shmid, NULL, 0);
    memset(arr, 42, SIZEMEM);
    signal(SIGINT, sig_int);
    pause();
    shmdt(arr);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
