# RAMRider library
set(RAMRIDER_SOURCES
	"DebugUtils/Assert.cpp"
	"DebugUtils/Assert.hpp"
	"DebugUtils/Compiler.hpp"
	"MemoryScanner.hpp"
	"ProcessHandler.hpp"
	"ProcessHandler.cpp"
)

add_library(ramrider STATIC ${RAMRIDER_SOURCES})

# Include directories for "RAMRider"
target_include_directories(ramrider PUBLIC
    "${CMAKE_SOURCE_DIR}/Sources/RAMRider"
)

# Set build-specific flags for Release and Debug
#target_compile_options(ramrider PRIVATE
#    $<$<CONFIG:Release>:-Ofast -flto>
#)