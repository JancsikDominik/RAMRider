#include <iostream>
#include "ProcessHandler.hpp"

int main()
{
    auto processes = RR::ProcessHandler::CollectProcesses();

    for(const auto& process : processes) {
        std::cout << "Process name: " << process.name << " PID: " << process.pid << std::endl;
    }

    std::cout << "pid of firefox: " << RR::ProcessHandler::FindProcessByName("firefox") << std::endl;

    return EXIT_SUCCESS;
}