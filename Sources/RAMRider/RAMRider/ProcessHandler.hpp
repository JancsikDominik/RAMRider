#ifndef __RAMRIDER_PROCESS_HANDLER_HPP__
#define __RAMRIDER_PROCESS_HANDLER_HPP__

#include <string>
#include <vector>

namespace RR
{
    class ProcessHandler
    {
    public:
        struct ProcessInfo
        {
            std::string name;
            pid_t pid;
        };

        static std::vector<ProcessInfo> CollectProcesses();
        static pid_t FindProcessByName(std::string_view processName);
    };
}

#endif