//
// Created by kayvee on 24.02.23.
//

#include "Process.h"


using namespace std;

Process::Process(filesystem::path  _procLink) : procLink(std::move(_procLink)) {
    ifstream statusFile(procLink.string()+'/'+STATUS_FILE.string());
    if(!statusFile.good()) throw runtime_error("Process is ZOMBIE");
    string temp;
    getline(statusFile,temp,'\n');
    procName=temp.substr(6);
    statusFile.ignore(256,'\n');
    statusFile.ignore(256,'\n');
    statusFile.ignore(256,'\n');
    statusFile.ignore(256,'\n');
    getline(statusFile,temp,'\n');
    PID=stoi(temp.substr(5));
}

void Process::ShowInfo(ostream &output) const {
    ifstream statusFile(procLink.string()+'/'+STATUS_FILE.string());
    if(!statusFile.good()) throw runtime_error("Can't open STATUS file");
    output<<statusFile.rdbuf()<<::endl;
}

::string Process::GetName() const {
    return procName;
}

int Process::GetPID() const {
    return PID;
}
