# RAMRider library
set(RAMRIDER_SOURCES
	"RAMRider/DebugUtils/Assert.cpp"
	"RAMRider/DebugUtils/Assert.hpp"
	"RAMRider/DebugUtils/Compiler.hpp"
	"RAMRider/MemoryScanner.hpp"
	"RAMRider/MemoryScanner.cpp"
	"RAMRider/ProcessHandler.hpp"
	"RAMRider/ProcessHandler.cpp"
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