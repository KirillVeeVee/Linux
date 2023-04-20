#include <iostream>
#include <filesystem>
#include <unistd.h>
#include <vector>
#include <string>
#include <array>
#include <unistd.h>
#include <csignal>
#include <sys/types.h>
#include <sys/wait.h>


template <size_t PROC_NUMBER=0>
class ProcessManager{
public:

//enum class PROC_ID{M=0,A,P,S};

explicit ProcessManager(std::array<std::filesystem::path,PROC_NUMBER> paths) : PROCESSES_PATH(std::move(paths)){
    for(auto& io:processesIO){
        pipe(io);
    }
}

void InitiateProcesses(){
    for(size_t i=0;i<PROC_NUMBER;++i){
        CreateProcess(i);
    }
}

void ReconnectOutput(){
    dup2(processesIO[0][1],STDIN_FILENO);
    close(dup(STDIN_FILENO));
}

void Write(){
    int number;
    while(std::cin>>number){
        std::cout<<number;
    }
    std::cout<<std::end();
   // close(dup(STDOUT_FILENO));
}

~ProcessManager(){
    for(auto& i:processes){
        int ret;
        waitpid(i, &ret, 0);
    }
}

private:

    void CreateProcess(size_t id){
        processes[id]=fork();
        if(processes[id]==0) {
            if (id+1 != PROC_NUMBER) {
                dup2(processesIO[id+1][1],STDOUT_FILENO);
            }
            dup2(processesIO[id][1],STDIN_FILENO);
            //dup2(processesIO[id][0],STDOUT_FILENO);
            //close(processesIO[id][1]);
            execl(PROCESSES_PATH[id].c_str(),PROCESSES_PATH[id].c_str());
            exit(EXIT_SUCCESS);
        }
        else if(processes[id]==-1){
            std::cerr<<"Error in creating process: "<< id <<'\n';
        }
        else {
            std::cerr<<"Process created: "<< id <<'\n';
        }
    }

    const std::array<std::filesystem::path,PROC_NUMBER> PROCESSES_PATH;
    std::array<int,PROC_NUMBER> processes;
    std::array<int[2],PROC_NUMBER> processesIO;
};



int main() {
    ProcessManager<1> newProcM({"./Process_A"/*,"./Process_M","./Process_P","./Process_S"*/});
    newProcM.InitiateProcesses();
    newProcM.ReconnectOutput();
    newProcM.Write();
}
