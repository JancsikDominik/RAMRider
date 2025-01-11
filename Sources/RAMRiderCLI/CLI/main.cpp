// from RAMRider
#include "RAMRider/ProcessHandler.hpp"
// from std
#include <iostream>

int main()
{
    auto processes = RR::ProcessHandler::CollectProcesses();

    for(const auto& [name, pid] : processes) {
        std::cout << "Process name: " << name << " PID: " << pid << std::endl;
    }

    std::cout << "pid of firefox: " << RR::ProcessHandler::FindProcessByName("firefox") << std::endl;

    return EXIT_SUCCESS;
}