#include <string_view>
#include <iostream>
#include <string>
#include <variant>
#include <vector>
#include "Monitor.h"

enum class CMD_TYPE{ID,NAME,SHOW};

using namespace std;

using Request=std::pair<CMD_TYPE,std::variant<int,std::string>>;

Request ParseCommand(std::string_view str){
    auto pos1=str.find('-');
    auto pos2=str.find('=');

    if(pos1 == string::npos || pos2 == string::npos) throw std::invalid_argument("Invalid arguments!\n");
    std::string_view command=str.substr(++pos1,pos2-1);

    Request newRequest;
    if(command == "ID") {
        newRequest.first = CMD_TYPE::ID;
        newRequest.second=stoi((string)str.substr(pos2+1));
    }
    else if(command == "name") {
        newRequest.first=CMD_TYPE::NAME;
        newRequest.second=(string)str.substr(pos2+1);
    }
    else if(command == "show") {
        newRequest.first=CMD_TYPE::SHOW;
        newRequest.second=(string)str.substr(pos2+1);
    }
    else throw std::invalid_argument("Invalid arguments!\n");

    return newRequest;
}

std::vector<string> ParseLocalEnv(std::string_view str){
    std::vector<string> processes;
    size_t pos=0;
    do {
        pos = str.find(',');
        processes.emplace_back(str.substr(0,pos-1));
        str=str.substr(pos+1);
    }
    while(pos !=std::string::npos);
    return processes;
}

int main (int argc,char* argv[])
{
    if(argc==1) return 1;
    Monitor newMonitor;
    auto request= ParseCommand(argv[1]);
    switch (request.first) {
        case CMD_TYPE::ID: {
            newMonitor.KillProcess(std::get<int>(request.second));
            break;
        }
        case CMD_TYPE::NAME: {
            newMonitor.KillProcess(std::get<string>(request.second));
            break;
        }
        case CMD_TYPE::SHOW: {
            auto temp=std::get<string>(request.second);
            if(temp.empty()) newMonitor.ShowAllProcesses();
            else newMonitor.GetProcessInfo(temp);
            break;
        }
    }

    if(getenv("PROC_TO_KILL") != nullptr) {
        string localVar = getenv("PROC_TO_KILL");
        if(!localVar.empty()) {
            auto processes = ParseLocalEnv(localVar);
            for (const auto &proc: processes)
                newMonitor.KillProcess(proc);
        }
    }

    exit(0);
}