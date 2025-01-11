// from RAMRider
#include "RAMRider/MemoryScanner.hpp"
#include "RAMRider/ProcessHandler.hpp"
// from std
#include <iostream>


int main()
{
    const pid_t processToScan = RR::ProcessHandler::FindProcessByName("test-app");
    std::cout << "pid of test-app: " << processToScan << std::endl;

    const RR::MemoryScanner scanner(processToScan);
    const auto* addr = scanner.ScanForValue<uint8_t>(8);
    std::cout << "Address of value 8: " << addr << " val: " << *addr << std::endl;

    return EXIT_SUCCESS;
}
