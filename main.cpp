#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <fstream>
#include <string>
#include <sys/wait.h>

using namespace std;

void sig_handler(int res, siginfo_t *info, void *tmp){
    int status;
    waitpid(-1, &status, NULL);
}

int main(int argc, char *argv[]) {
    string name="/home/box/pid_parent";
    if (fork()){
        name="/home/box/pid_child";
    }
    else{
        struct sigaction sig_act;
        sig_act.sa_sigaction = sig_handler;
        sig_act.sa_flags = SA_RESTART;
        sigaction(SIGCHLD, &sig_act, NULL);
    }
    ofstream myfile (name);
    myfile << getpid();
    myfile.flush();
    myfile.close();
    pause();
    return 0;
}