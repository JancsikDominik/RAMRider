cmake_minimum_required(VERSION 3.20)
project(RAMRider LANGUAGES CXX)

# Set C++ standard and warnings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -Werror")

# Output directories
set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/build")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}/bin)

# Define configurations
set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Production" CACHE STRING "Active build configurations" FORCE)

# Add subdirectories for projects
add_subdirectory(Sources/RAMRider)
add_subdirectory(Sources/RAMRiderCLI)
add_subdirectory(Dependencies/googletest/googletest)