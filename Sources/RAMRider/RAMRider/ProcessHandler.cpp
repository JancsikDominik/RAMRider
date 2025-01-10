#include "ProcessHandler.hpp"

// from std
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <vector>

namespace RR
{
    std::vector<ProcessHandler::ProcessInfo> ProcessHandler::CollectProcesses()
    {
        namespace fs = std::filesystem;

        std::vector<ProcessInfo> processes;

        for (const auto& entry : fs::directory_iterator("/proc")) {
            if (entry.is_directory()) {
                std::string dirName = entry.path().filename().string();
                if (std::ranges::all_of(dirName, ::isdigit)) {
                    pid_t pid = std::stoi(dirName);
                    std::ifstream cmdlineFile { entry.path() / "cmdline" };

                    if (cmdlineFile.is_open()) {
                        std::string cmdline;
                        std::getline(cmdlineFile, cmdline, '\0');
                        if (!cmdline.empty()) {
                            processes.push_back(ProcessInfo { cmdline, pid });
                        }
                    }
                }
            }
        }

        return processes;
    }

    pid_t ProcessHandler::FindProcessByName(std::string_view processName)
    {
        std::vector<ProcessInfo> processes = CollectProcesses();

        const auto it = std::ranges::find_if(processes, [processName](const ProcessInfo& process) {
            return process.name.find(processName) != std::string::npos;
        });

        return it != processes.end() ? it->pid : -1;
    }
}