#ifndef RAMRIDER_MEMORY_SCANNER_HPP_
#define RAMRIDER_MEMORY_SCANNER_HPP_

#include "DebugUtils/Assert.hpp"

#include <concepts>
#include <cstdint>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <sys/types.h>
#include <sys/uio.h>

namespace RR
{
    template<typename T>
    concept SearchType =
        std::same_as<T, int8_t>   || std::same_as<T, int16_t>  || std::same_as<T, int32_t>  || std::same_as<T, int64_t> ||
        std::same_as<T, uint8_t>  || std::same_as<T, uint16_t> || std::same_as<T, uint32_t> || std::same_as<T, uint64_t> ||
        std::same_as<T, float>    || std::same_as<T, double>   || std::same_as<T, std::string> || std::same_as<T, char*>;

    class MemoryScanner
    {
    public:
        explicit MemoryScanner(pid_t process);
        
        template<SearchType T>
        T* ScanForValue(const T& valueToFind) const;

    private:
        template<SearchType T>
        std::vector<T> ReinterpretData(const std::vector<char>& rawBytes) const;

        const pid_t m_processId;
    };

    template<SearchType T>
    T* MemoryScanner::ScanForValue(const T& valueToFind) const
    {
        std::ifstream mapsFile { "/proc/" + std::to_string(m_processId) + "/maps" };
        ASSERT(mapsFile.is_open(), "Failed to open memory maps file. Maybe wrong PID?");

        // Read memory mappings line by line
        std::string line;
        while (std::getline(mapsFile, line)) {
            std::istringstream iss(line);
            std::string addressRange;
            std::string permissions;
            uintptr_t startAddr = 0;
            uintptr_t endAddr = 0;

            // /proc/pid/maps format: ADDRESS   PERMS     OFFSET    DEVICE    INODE   PATH NAME
            // we only need the address range and permissions for now
            iss >> addressRange >> permissions;

            // Only scan readable regions (contain 'r' in permissions) to avoid crashes
            if (permissions.find('r') == std::string::npos) {
                continue;
            }

            // Split the address range (e.g. '00400000-0040b000')
            size_t dashPos = addressRange.find('-');
            ASSERT(dashPos != std::string::npos, "Failed to parse memory maps file. Wrong file?");

            startAddr = std::stoul(addressRange.substr(0, dashPos), nullptr, 16);
            endAddr = std::stoul(addressRange.substr(dashPos + 1), nullptr, 16);

            // Calculate the size of the region
            size_t regionSize = endAddr - startAddr;

            // Open /proc/pid/mem to read out actual memory values
            std::ifstream memFile { "/proc/" + std::to_string(m_processId) + "/mem", std::ios::binary };
            ASSERT(memFile.is_open(), "Failed to open memory file. Maybe wrong PID?");
            memFile.seekg(startAddr);

            std::vector<char> bytes(regionSize);
            ASSERT(memFile.read(bytes.data(), regionSize));
            memFile.close();

            // Search for the value we need
            auto typedData = ReinterpretData<T>(bytes);
            for (size_t i = 0; i < typedData.size(); i++) {
                if (typedData[i] == valueToFind)
                    return reinterpret_cast<T*>(startAddr + sizeof(T) * i);
            }
        }

        // Value not found
        return nullptr;
    }

    template <SearchType T>
    std::vector<T> MemoryScanner::ReinterpretData(const std::vector<char>& rawBytes) const
    {
        if (sizeof(T) == sizeof(char))
            return std::vector<T>(rawBytes.begin(), rawBytes.end());

        std::vector<T> result;
        result.reserve(rawBytes.size() / sizeof(T));
        for (size_t i = 0; i < rawBytes.size(); i += sizeof(T)) {
            result.push_back(*reinterpret_cast<const T*>(&rawBytes[i]));
        }

        return result;
    }
}

#endif
