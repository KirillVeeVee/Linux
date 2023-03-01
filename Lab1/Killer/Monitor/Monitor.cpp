//
// Created by kayvee on 24.02.23.
//
#include "Monitor.h"

using namespace std;

void Monitor::Rescan() {


    std::deque<Process> newProcessesPool;
    std::map<std::string,Pointer> newProcessByName;
    std::map<int,Pointer> newProcessByPID;

    int counter=1;
    for(const auto& dir_obj:filesystem::directory_iterator(PATH)){
        if(dir_obj.is_directory()){
            std::string dir_name=dir_obj.path().filename();
            if(all_of(dir_name.begin(),dir_name.end(), [](unsigned char i){return isdigit(i);})) {
                newProcessesPool.emplace_back(dir_obj.path());
                auto newProcess=std::prev(newProcessesPool.end());
                newProcessByPID.emplace(newProcess->GetPID(),newProcess);
                if(newProcessByName.find(newProcess->GetName()) != newProcessByName.end())
                    newProcessByName.emplace(newProcess->GetName()+to_string(counter++),newProcess);
                else newProcessByName.emplace(newProcess->GetName(),newProcess);
            }
        }
    }

    processPool=std::move(newProcessesPool);
    processByName=std::move(newProcessByName);
    processByPID=std::move(newProcessByPID);
}

void Monitor::KillProcess(int PID) {
    auto process=processByPID.find(PID);
    if(process==processByPID.end()) {
        std::cerr << "Process doesn't exist" << std::endl;
        return;
    }
    kill(PID,SIGTERM);
    std::cerr<<"Process Killed!"<<std::endl;
    Rescan();
}

void Monitor::KillProcess(const std::string& processName) {
    auto process=processByName.find(processName);
    if(process==processByName.end()) {
        std::cerr << "Process doesn't exist" << std::endl;
        return;
    }
    kill(process->second->GetPID(),SIGTERM);
    std::cerr<<"Process Killed!"<<std::endl;
    Rescan();
}

Monitor::Monitor() {
    Rescan();
}

void Monitor::ShowAllProcesses(ostream &output) const {
    output<<"List of processes: "<<'\n';
    for(const auto& proc:processPool)
        output<<proc.GetPID()<<" "<<proc.GetName()<<'\n';
}

void Monitor::GetProcessInfo(int PID, ostream &output) const {
    auto process=processByPID.find(PID);
    if(process==processByPID.end()) {
        std::cerr << "Process doesn't exist" << std::endl;
        return;
    }
    process->second->ShowInfo(output);
}

void Monitor::GetProcessInfo(const string &processName, ostream &output) const {
    auto process=processByName.find(processName);
    if(process==processByName.end()) {
        std::cerr << "Process doesn't exist" << std::endl;
        return;
    }
    process->second->ShowInfo(output);
}

