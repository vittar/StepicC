//
// Created by vitaly on 10.07.16.
//

#include "stepic72-4.h"

#include <pthread.h>
#include <cstring>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <thread>

struct lockid_abstract{
public:
    lockid_abstract(){};
    virtual void locks(void) = 0;
    virtual void unlock(void) = 0;
    virtual void print_self(void) = 0;
    virtual ~lockid_abstract(){};
};

struct lockid_mutex: public lockid_abstract{
    pthread_mutex_t lock;
public:
    lockid_mutex(){
        int res = pthread_mutex_init(&this->lock, NULL);
        if (res != 0){
            perror("mutex not init!");
            exit(1);
        };
    };
    void locks(){
        printf("mutex_lock\n");
        pthread_mutex_lock(&this->lock);
    }
    void unlock(void){
        printf("mutex_unlock\n");
        pthread_mutex_unlock(&this->lock);
    }
    virtual void print_self(void){
        printf("mutex started\n");
    }
    ~lockid_mutex(){
        printf("mutex_destroy\n");
        pthread_mutex_destroy(&this->lock);
    }
};

struct lockid_spin: public lockid_abstract{
    pthread_spinlock_t lock;
public:
    lockid_spin(){
        int res = pthread_spin_init(&this->lock, NULL);
        if (res != 0){
            perror("spin not init!");
            exit(1);
        }
    }
    void locks(void){
        printf("spin_lock\n");
        pthread_spin_lock(&this->lock);
    }
    void unlock(void){
        printf("spin_unlock\n");
        pthread_spin_unlock(&this->lock);
    }
    virtual void print_self(void){
        printf("spin started\n");
    }
    ~lockid_spin(){
        printf("spin_destroy\n");
        pthread_spin_destroy(&this->lock);
    }
};

struct lockid_readlock: public lockid_abstract{
    pthread_rwlock_t lock;
public:
    lockid_readlock(){
        int res = pthread_rwlock_init(&this->lock, NULL);
        if (res != 0){
            perror("rwlock not init!");
            exit(1);
        }
    }
    void locks(void){
        printf("rwlock_lock_read\n");
        pthread_rwlock_rdlock(&this->lock);
    }
    void unlock(void){
        printf("rwlock_unlock\n");
        pthread_rwlock_unlock(&this->lock);
    }
    virtual void print_self(void){
        printf("rwlock read started\n");
    }
    ~lockid_readlock(){
        printf("rwlock_destroy\n");
        pthread_rwlock_destroy(&this->lock);
    }
};

struct lockid_writelock: public lockid_readlock{
    pthread_rwlock_t lock;
public:
    lockid_writelock(): lockid_readlock(){};
    void locks(void){
        printf("rwlock_lock_write\n");
        pthread_rwlock_wrlock(&this->lock);
    }
    void unlock(void){
        printf("rwlock_unlock\n");
        pthread_rwlock_unlock(&this->lock);
    }
    virtual void print_self(void){
        printf("rwlock write started\n");
    }
};

void sig_int(int sig){
    printf("signal!");
    return;
}

void *thread_func(void *val){
    lockid_abstract *ptr= (lockid_abstract*)val;
    ptr->print_self();
    ptr->locks();
    return NULL;
}

int stepic724(){
    int mypid = getpid();
    FILE *file = fopen("/home/box/main.pid", "w");
    fprintf(file, "%d", mypid);
    fclose(file);
    lockid_abstract *ptr[4];
    ptr[0] = new lockid_mutex();
    ptr[1] = new lockid_spin();
    ptr[2] = new lockid_readlock();
    ptr[3] = new lockid_writelock();
    for(int i=0; i<4; ++i){
        ptr[i]->locks();
    };
    printf("----------\n");
    pthread_t thread[4];
    for(int i=0; i<4; ++i){
        pthread_create(&thread[i], NULL, thread_func, ptr[i]);
    }
    // Set signal handler
    sigset_t sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGTERM);
    sigaddset(&sigset, SIGINT);
    sigprocmask(SIG_BLOCK, &sigset, NULL);
    int sig;
    printf("----------\n");
    sigwait( &sigset, &sig );
    printf("----------\n");
    for(int i=0; i<4; ++i){
        ptr[i]->unlock();
        pthread_join(thread[i], NULL);
        delete ptr[i];
    };
    return 0;
}