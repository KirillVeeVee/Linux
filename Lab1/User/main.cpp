#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    setenv("PROC_TO_KILL","telegram-deskto",1);
    pid_t Pid=fork();
    int Status;
    if(Pid == 0) execl("./Killer","Killer","-name=DesktopEditors");
    else if(Pid > 0) wait(&Status);
    else std::cerr << "Something is wrong!\n";
    return 0;
}
