//
// Created by vitaly on 10.07.16.
//

#include "stepic63-6.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <cstdio>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>


void check_err(int val, const char *name){
    if (val < 0){
        printf("error in %s: %d", name, errno);
        exit(1);
    }
}

int stepic636(){
    extern int errno;
    FILE *file = fopen("/tmp/sem.temp", "w");
    fclose(file);
    key_t key = ftok("/tmp/sem.temp", 1);
    check_err(key, "ftok");
    int semid = semget(key, 16, (IPC_CREAT));
    check_err(semid, "semget");
    semid_ds sembuf[16];
    for(unsigned long i=0; i<16; ++i){
        sembuf[i].sem_perm.mode = 0666;
        sembuf[i].sem_perm.gid = 0;
        sembuf[i].sem_perm.uid = 0;
        sembuf[i].sem_nsems = i;
    }
    int res = semctl(semid, 16, IPC_SET, sembuf);
    check_err(res, "semctl");
    for(unsigned long i=0; i<16; ++i){
        res = semctl(semid, (int)i, SETVAL, i);
        check_err(res, "semctl in  for");
    };
    pause();
    semctl(semid, 16, IPC_RMID);
    return 0;
};