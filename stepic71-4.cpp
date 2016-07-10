//
// Created by vitaly on 10.07.16.
//

#include "stepic71-4.h"

#include <pthread.h>
#include <cstring>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>

void *thread_func(void *val){
    pause();
    return NULL;
}

int stepic714(){
    int mypid = getpid();
    FILE *file = fopen("/home/box/main.pid", "w");
    fprintf(file, "%d", mypid);
    fclose(file);
    pthread_t thread = NULL;
    pthread_create(&thread, NULL, thread_func, NULL);
    pthread_join(thread, NULL);
    return 0;
}

