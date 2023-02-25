//
// Created by kayvee on 24.02.23.
//

#ifndef LAB1_PROCESS_H
#define LAB1_PROCESS_H

#include <filesystem>
#include <iostream>
#include <fstream>
#include <exception>
#include <iterator>

class Process {
public:
    explicit Process(std::filesystem::path _procLink);

    void ShowInfo(std::ostream& output=std::cout) const;

    std::string GetName() const;

    int GetPID() const;

private:

    std::string procName;
    int PID;

    std::filesystem::path procLink;
    const std::filesystem::path STATUS_FILE="status";
};


#endif //LAB1_PROCESS_H
