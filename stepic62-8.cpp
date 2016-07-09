//
// Created by vitaly on 09.07.16.
//

#include "stepic62-8.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <cstdio>

//using namespace std;

struct message {
    long mtype;
    char mtext[80];
};

int stepic628(){
    extern int errno;
    FILE *file = fopen("/tmp/msg.temp", "w");
    fclose(file);
    key_t key = ftok("/tmp/msg.temp", 2);
    if (key < 0){
        printf("errno %d\n", errno);
        return 1;
    }
    int msgid = msgget(key, (IPC_CREAT | 0777));
    if (msgid < 0){
        printf("errno %d\n", errno);
        return 1;
    }
    msqid_ds perm;
    msgctl(msgid, IPC_STAT, &perm);
    perm.msg_perm.mode = 0777;
    msgctl(msgid, IPC_SET, &perm);
    message msg;
    ssize_t sizeb = msgrcv(msgid, &msg, 80, 0, 0);
    msg.mtext[sizeb] = 0;
    file = fopen("/home/box/message.txt", "w");
    fprintf(file, "%s", msg.mtext);
    fclose(file);
    msgctl(msgid, IPC_RMID, &perm);
    remove("/tmp/msg.temp");
    return 0;
}