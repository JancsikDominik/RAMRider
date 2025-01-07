#ifndef __RAMRIDER_MEMORY_SCANNER_HPP__
#define __RAMRIDER_MEMORY_SCANNER_HPP__

#include <string>
#include <sys/types.h>

namespace RR
{
    class MemoryScanner
    {
    public:
        MemoryScanner(pid_t process);

        void ReadMemory();

    private:
        pid_t m_processId;
    };
}

#endif