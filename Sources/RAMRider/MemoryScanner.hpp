#ifndef __RAMRIDER_MEMORY_SCANNER_HPP__
#define __RAMRIDER_MEMORY_SCANNER_HPP__

#include <sys/types.h>

namespace RR
{
    class MemoryScanner
    {
    public:
        enum class DataType
        {
            Int8,
            Int16,
            Int32,
            Int64,
            UInt8,
            UInt16,
            UInt32,
            UInt64,
            Float,
            Double,
            String
        };

        MemoryScanner(pid_t process);
        
        template<typename T>
        void* ScanForValue(const T& valueToFind, DataType type);

    private:
        pid_t m_processId;
    };

    template<typename T>
    void* MemoryScanner::ScanForValue(const T& valueToFind, DataType type)
    {
        return nullptr;
    }
}

#endif
