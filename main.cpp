#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <fstream>
#include <string>
#include <sys/wait.h>

using namespace std;

int main(int argc, char *argv[]) {
    char buf[256];
    fgets(buf, 256, stdin);
    FILE *my_stream = popen(buf, "r");
    ofstream myfile ("/home/box/result.out");
    myfile << fgets(buf, 256, my_stream);
    myfile.flush();
    myfile.close();
    pclose(my_stream);
    return 0;
}