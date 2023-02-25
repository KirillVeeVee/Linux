//
// Created by kayvee on 24.02.23.
//
#ifndef LAB1_MONITOR_H
#define LAB1_MONITOR_H

#include <algorithm>
#include <map>
#include <iostream>
#include <dirent.h>
#include <filesystem>
#include <csignal>
#include <deque>

#include "Process.h"

class Monitor {
public:

    using Pointer=std::deque<Process>::iterator;

    Monitor();

    Monitor(const Monitor&) = delete;

    void Rescan();

    void ShowAllProcesses(std::ostream& output=std::cout) const;

    void KillProcess(int PID);

    void KillProcess(const std::string& processName);

    void GetProcessInfo(int PID,std::ostream& output=std::cout) const;

    void GetProcessInfo(const std::string& processName,std::ostream& output=std::cout) const;

private:

    std::deque<Process> processPool;
    std::map<std::string,Pointer> processByName;
    std::map<int,Pointer> processByPID;

    const std::filesystem::path PATH="/proc";
};


#endif //LAB1_MONITOR_H
