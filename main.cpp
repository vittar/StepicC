#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <fstream>

using namespace std;

void sig_handler(int res, siginfo_t *info, void *tmp){
    printf("Вызов!");
}

int main(int argc, char *argv[]) {
    struct sigaction sig_act;
    sig_act.sa_handler = SIG_IGN;
//    sig_act.sa_sigaction = sig_handler;
    sig_act.sa_flags = SA_RESTART;
    ofstream myfile ("/home/box/pid");
    int pid = getpid();
    myfile << pid;
    myfile.flush();
    myfile.close();
    sigaction(SIGTERM, &sig_act, NULL);
    sigaction(SIGINT, &sig_act, NULL);
    pause();
    return 0;
}