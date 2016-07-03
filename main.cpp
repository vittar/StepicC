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
    string name;
    int pid = 0;
    if (fork()){
        pid = getpid();
        name = "/home/box/pid_parent";
        struct sigaction sig_act;
        sig_act.sa_sigaction = sig_handler;
        sig_act.sa_flags = SA_RESTART;
        sigaction(SIGCHLD, &sig_act, NULL);
    }
    else{
        pid = getpid();
        name="/home/box/pid_child";
    }
    ofstream myfile (name.c_str());
    myfile << pid;
    myfile.flush();
    myfile.close();
    pause();
    return 0;
}