#include "ProcessHandler.hpp"
#include <filesystem>
#include <fstream>
#include <vector>
#include <algorithm>

namespace RR
{
    std::vector<ProcessHandler::ProcessInfo> ProcessHandler::CollectProcesses()
    {
        namespace fs = std::filesystem;

        std::vector<ProcessInfo> processes;

        for (const auto& entry : fs::directory_iterator("/proc")) {
            if (entry.is_directory()) {

                std::string dirName = entry.path().filename().string();
                if (std::all_of(dirName.begin(), dirName.end(), ::isdigit)) {
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

        auto it = std::find_if(processes.begin(), processes.end(), [processName](const ProcessInfo& process) {
            return process.name.find(processName) != std::string::npos;
        });

        return it != processes.end() ? it->pid : -1;
    }
}