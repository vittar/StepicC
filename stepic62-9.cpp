//
// Created by vitaly on 10.07.16.
//

#include "stepic62-9.h"
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <cstdio>
#include <errno.h>

int stepic629(){
    extern int errno;
    mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_msgsize = 1024;
    attr.mq_maxmsg = 10;
    attr.mq_curmsgs = 0;
    mqd_t mqid = mq_open("/test.mq", (O_CREAT | O_EXCL | O_RDONLY), 0666, &attr);
    if (mqid < 0){
        printf("error in mq_open: %d", errno);
        return 1;
    }
    char *buf = new char[1024];
    ssize_t bufcount = mq_receive(mqid, buf, 1024, NULL);
    if (bufcount < 0){
        printf("error in mq_receive: %d", errno);
        return 1;
    }
    buf[bufcount] = 0;
    FILE *file = fopen("/home/box/message.txt", "w");
    fprintf(file, "%s", buf);
    fclose(file);
    mq_close(mqid);
    mq_unlink("/test.mq");
    return 0;
};
