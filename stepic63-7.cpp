//
// Created by vitaly on 10.07.16.
//

#include "stepic63-7.h"
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include <errno.h>
#include <stdlib.h>
#include <cstdio>
#include <unistd.h>

void check_err(int val, const char *name){
    extern int errno;
    if (val < 0){
        printf("error in %s: %d", name, errno);
        exit(1);
    }
}

int stepic637(){
    extern int errno;
    sem_t *semid = sem_open("/test.sem", (O_CREAT), 0666, 66);
    pause();
    sem_close(semid);
    sem_unlink("/test.sem");
    return 0;
};