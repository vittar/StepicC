#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <fstream>
#include <string>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "stepic62-8.h"

int main(int argc, char *argv[]) {
    return stepic628();
}